#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
#include <stack>
#include <queue>
std::string FuncName;
static int ReturnFlag = 0;
bool ExitLabel = false;
bool WhileBlock = false;
int BreakFlag = 0;
int ContinueFlag = 0;
int IFflag = 0;
static bool sym_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);
static bool sym_cu(struct ast_node *node);
static bool sym_block(struct ast_node *node);
static bool sym_def_list(struct ast_node *node, bool isLocal = false);
static bool sym_def_func(struct ast_node *node);
static struct ast_node *sym_visit_ast_node(struct ast_node *node, bool isLeft = false, bool isLast = false);
void BFS(struct ast_node *node)
{
    // 广搜所有局部变量定义
    std::queue <struct ast_node *> q;
    q.push(node);//节点入栈
    while (!q.empty()) {
        struct ast_node *temp = q.front();//栈顶元素出栈并且访问该节点
        if (temp->type == AST_DEF_LIST) {
            sym_def_list(temp, true);
        }
        q.pop();
        std::vector<struct ast_node *>::iterator pIter;
        for (pIter = temp->sons.begin(); pIter != temp->sons.end(); ++pIter) {
            q.push(*pIter);
        }
    }
}
static bool sym_block(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第二步是遍历其他表达式语句
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        if ((*pIter)->type == AST_DEF_LIST) {
            continue;
        }
        if (pIter != node->sons.end() - 1) {
            (*pIter)->next = *(pIter + 1);
        } else {
            (*pIter)->next = node->parent->next;
        }
        // 遍历Block的每个语句，进行显示或者运算
        struct ast_node *temp;
        if (pIter == node->sons.end() - 1) {
            temp = sym_visit_ast_node(*pIter, true, true);
        } else {
            // 遍历Block的每个语句，进行显示或者运算
            temp = sym_visit_ast_node(*pIter, true, false);
        }
        if (!temp) {
            return false;
        }
        if (temp->type == AST_OP_IF) {
            node->labels = temp->labels;
        }
        // 如果if节点里含有两个return，就把后面的节点删除
        if (ReturnFlag == 2) {
            node->sons.erase(pIter + 1, node->sons.end());
            // ReturnFlag = 0;
            break;
        }
        temp->parent = node;
    }
    return true;
}
static bool sym_def_func(struct ast_node *node)
{
    struct ast_node *func_type = node->sons[0];
    // 第一个孩子是函数返回类型

    struct ast_node *func_name = node->sons[1];
    FuncName = func_name->attr.id;
    Value *val = nullptr;
    // 第二个孩子是函数名
    if (!GlobalIsExist(func_name->attr.id)) {
        // 变量名没有找到
        val = newFuncValue(func_name->attr.id);
    } else {
        // 若变量名已存在，则报错重定义
        std::string error = std::string("error: redefinition of ") + std::string(func_name->attr.id);
        printError(func_name->attr.lineno, error);
        return false;
    }
    func_name->val = val;
    if (strcmp(func_type->attr.id, "void") == 0) {
        // printf("int value\n");
        return true;
    }
    // 第三个孩子是参数列表
    struct ast_node *func_paras = node->sons[2];
    std::vector<struct ast_node *>::iterator pIter;
    for (pIter = func_paras->sons.begin(); pIter != func_paras->sons.end(); ++pIter) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        // struct ast_node *arg_name = (*pIter)->sons[1];
        // todo 暂时只考虑int类型
        newTempValue(ValueType::ValueType_Int, func_name->attr.id, true);
    }

    // 形参定义
    for (pIter = func_paras->sons.end() - 1; pIter != func_paras->sons.begin() - 1; --pIter) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        struct ast_node *arg_name = (*pIter)->sons[1];
        Value *localVarValue = nullptr;
        // todo 暂时只考虑int类型
        localVarValue = newLocalVarValue(arg_name->attr.id, ValueType::ValueType_Int, func_name->attr.id);
        arg_name->val = localVarValue;
    }
    // 返回值定义
        // todo 暂时只考虑int类型
    newLocalVarValue("return", ValueType::ValueType_Int, FuncName);
    // 第四个孩子是语句块
    // todo 这里有个bug，AST的parent节点有问题
    node->sons[3]->parent = node;
    printf("返回值复制给临时变量0\n");
    BFS(node->sons[3]);
    struct ast_node *func_block = sym_visit_ast_node(node->sons[3]);
    // 返回值复制给临时变量
    newTempValue(ValueType::ValueType_Int, FuncName);
    printf("返回值复制给临时变量\n");
    ReturnFlag = 0;
    if (func_block == NULL) return true;
    return true;
}
static bool sym_def_array(struct ast_node *node, ValueType type, bool isLocal)
{
    Value *val = nullptr;
    // 第一个孩子是标识符
    struct ast_node *temp_id = node->sons[0];
    if (isLocal) {
        // 局部变量
        if (!LocalIsExist(FuncName, temp_id->attr.id)) {
            val = newLocalVarValue(temp_id->attr.id, type, FuncName);

        } else {
            // 若变量名已存在，则报错重定义
            std::string error = std::string("error: redefinition of ") + std::string(temp_id->attr.id);
            printError(temp_id->attr.lineno, error);
            return false;
        }
    } else {
        // 全局变量
        if (!GlobalIsExist(temp_id->attr.id)) {
            val = newVarValue(temp_id->attr.id);
        } else {
            // 若变量名已存在，则报错重定义
            std::string error = std::string("error: redefinition of ") + std::string(temp_id->attr.id);
            printError(temp_id->attr.lineno, error);
            return false;
        }
    }
    val->type = type;

    struct ast_node *temp_dims = node->sons[1];
    // 第二个孩子是数组维度节点
    int i = 0;
    while (temp_dims) {
        val->dims[i] = temp_dims->sons[0]->attr.integer_val;
        if (temp_dims->sons.size() > 1) {
            temp_dims = temp_dims->sons[1];
        } else {
            temp_dims = nullptr;
        }
        i++;
    }
    node->val = val;
    return true;
}
static bool sym_def_list(struct ast_node *node, bool isLocal)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一个孩子节点是变量类型
    struct ast_node *temp_type = node->sons[0];
    enum digitnum_kind kind0;
    ValueType type;
    // todo 暂时只考虑int型变量
    if (strcmp(temp_type->attr.id, "int") == 0) {
        // printf("int value\n");
        kind0 = DIGIT_KIND_ID;
        type = ValueType::ValueType_Int;
    }

    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        Value *val = nullptr;
        struct ast_node *temp = *pIter;
        if (temp->type == AST_ARRAY) {
            bool result = sym_def_array(temp, type, isLocal);
            if (!result)return false;
        } else {
            if (isLocal) {
                // 局部变量
                if (!LocalIsExist(FuncName, temp->attr.id)) {
                    val = newLocalVarValue(temp->attr.id, type, FuncName);
                } else {
                    // 若变量名已存在，则报错重定义
                    std::string error = std::string("error: redefinition of ") + std::string(temp->attr.id);
                    printError(temp->attr.lineno, error);
                    return false;
                }
            } else {
                // 全局变量
                if (!GlobalIsExist(temp->attr.id)) {
                    val = newVarValue(temp->attr.id);
                } else {
                    // 若变量名已存在，则报错重定义
                    std::string error = std::string("error: redefinition of ") + std::string(temp->attr.id);
                    printError(temp->attr.lineno, error);
                    return false;
                }
            }

            temp->attr.kind = kind0;
            temp->val = val;
        }
        // 确定符号类型
        temp->val->type = type;
    }
    return true;
}
static bool sym_cu(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步首先确定所有全局变量
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        if ((*pIter)->type == AST_DEF_LIST) {
            struct ast_node *temp = sym_visit_ast_node(*pIter);
            if (temp == NULL) return true;
        }
    }
    // 第二步确定函数表
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        if ((*pIter)->type == AST_FUNC_DEF) {
            // struct ast_node *temp = sym_visit_ast_node(*pIter);
            // if (temp == NULL) return true;
            sym_visit_ast_node(*pIter);
        }
    }
    return true;
}
static bool sym_binary_op(struct ast_node *node, enum ast_operator_type type)
{
    // TODO real number add

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    struct ast_node *left = sym_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }
    // 加法的右边操作数
    struct ast_node *right = sym_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    Value *leftValue = left->val;
    Value *rightValue = right->val;
    Value *val = nullptr;
    // 变量当右值要先复制给临时变量再进行计算
    if (left->val->isId) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        val->isId = true;
        left->val = val;
    }
    if (right->val->isId) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        val->isId = true;
        right->val = val;
    }
    if (left->type == AST_OP_INDEX) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        left->val = val;
    }
    if (right->type == AST_OP_INDEX) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        right->val = val;
    }
    // 左右值都是常量就直接计算出来，代码优化 
    Value *resultValue = nullptr;
    if ((leftValue->isConst) and (rightValue->isConst)) {
        int result = 0;
        switch (type) {
        case AST_OP_ADD:
            result = rightValue->intVal + leftValue->intVal;
            break;
        case AST_OP_SUB:
            result = rightValue->intVal - leftValue->intVal;
            break;
        case AST_OP_MUL:
            result = rightValue->intVal * leftValue->intVal;
            break;
        case AST_OP_DIV:
            result = rightValue->intVal / leftValue->intVal;
            break;
        case AST_OP_MOD:
            result = rightValue->intVal % leftValue->intVal;
            break;
        default:
            break;
        }
        resultValue = newConstValue(result);
    } else {
        // todo 暂时只考虑int类型
        resultValue = newTempValue(ValueType::ValueType_Int, FuncName);
    }

    node->val = resultValue;
    printf("新建op临时变量: %s\n", node->val->getName().c_str());
    return true;
}
static bool sym_index(struct ast_node *node)
{
    // 数组索引第一个孩子节点是变量名
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *array_name = sym_visit_ast_node(src1_node);
    if (!array_name) {
        return false;
    }
    std::vector<struct ast_node *>::iterator pIter;
    Value *val = nullptr;
    // 第一步首先确定所有全局变量
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        struct ast_node *temp = sym_visit_ast_node(*pIter);
        if (temp == NULL) return false;
    }
    printf("数组引用\n");
    // 求偏移量
    // 假设最大支持10维数组
    int *dims = array_name->val->dims;
    int offsets[10] = { 1,1,1,1,1,1,1,1,1,1 };
    for (int i = 0; i < 10 && dims[i] != 0; i++) {
        // printf("%d ", dims[i]);
        for (int j = i + 1; j < 10 && dims[j] != 0; j++) {
            offsets[i] *= dims[j];
        }
    }
    // printf("\n");
    // for (int i = 0; i < 10 && dims[i] != 0; i++) {
    //     printf("%d ", offsets[i]);
    // }
    int offset = 0;
    for (int i = 1; i < node->sons.size(); ++i) {
        offset += node->sons[i]->val->intVal * offsets[i - 1];
    }
    val = newTempValue(ValueType::ValueType_Int_ptr, FuncName);
    val->intVal = offset * 4;
    printf("%s 数组引用结束 %d\n", array_name->attr.id, val->intVal);
    array_name->val = val;
    val = newTempValue(ValueType::ValueType_Int, FuncName);
    node->val = val;
    return true;
}
static bool sym_assign(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 赋值节点，自右往左运算

    // 赋值运算符的左侧操作数
    struct ast_node *left = sym_visit_ast_node(son1_node, true);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }

    // 赋值运算符的右侧操作数
    struct ast_node *right = sym_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    if (left->type == AST_OP_INDEX or right->type == AST_OP_INDEX) {
        // if (left->type == AST_OP_INDEX) {
        //     // leftValue = left->sons[0]->val;
        //     Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
        //     node->val = val;
        // }
        if (right->type == AST_OP_INDEX) {
            // leftValue = left->sons[0]->val;
            Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
            node->val = val;
        }
    } else {
        node->val = left->val;
    }
    // printf("赋值指令symbol\n");

    return true;
}
static bool sym_return(struct ast_node *node)
{
    ReturnFlag += 1;
    struct ast_node *son1_node = node->sons[0];
    struct ast_node *left = sym_visit_ast_node(son1_node, false);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }
    Value *val = nullptr;
    if (left->type == AST_OP_INDEX) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        left->val = val;
    }
    node->val = left->val;
    return true;
}
static bool sym_func_call(struct ast_node *node, bool isLeft)
{
    // 第一个节点是函数名
    struct ast_node *son1_node = node->sons[0];
    struct ast_node *left = sym_visit_ast_node(son1_node, true);
    if (!left) {
        return false;
    }
    // 这里应该先判断一下参数个数是否匹配
    if (node->sons.size() == 2) {
        std::vector<struct ast_node *>::iterator pIter;
        // 第一步首先确定所有全局变量
        for (pIter = node->sons[1]->sons.begin(); pIter != node->sons[1]->sons.end(); ++pIter) {
            struct ast_node *temp = sym_visit_ast_node(*pIter);
            // 变量当右值要先复制给临时变量再进行计算
            if (temp->val->isId) {
                Value *val;
                val = newTempValue(ValueType::ValueType_Int, FuncName);
                val->isId = true;
                temp->val = val;
            }
        }
    }

    if (!isLeft) {
        // 函数调用当左值，不需要赋值给临时变量
        Value *val;
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        node->val = val;
    }

    return true;
}
static bool sym_if(struct ast_node *node, bool isLast)
{
    IFflag++;
    if (!node->next) {
        node->next = node->parent->next;
    }
    node->label = node->parent->label;        // 供while语句使用
    std::string label1 = newLabel(FuncName);  // true语句
    std::string label2 = newLabel(FuncName);  // false语句
    std::string label3 = newLabel(FuncName);  // 下一条语句
    node->labels.push_back(label1);
    node->labels.push_back(label2);
    node->labels.push_back(label3);
    if (!node->next) {
        struct ast_node *temp = new_ast_node(AST_EMPTY);
        temp->label = label3;
        node->next = temp;
    } else {
        if (node->next->label.size() == 0) {
            node->next->label = label3;
        }
    }
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    src2_node->label = node->label;    // 供while语句使用
    // 条件表达式
    struct ast_node *cond = sym_visit_ast_node(src1_node);
    if (!cond) {
        return false;
    }
    bool true_break = false, false_break = false;
    bool true_return = false, false_return = false;
    bool true_continue = false, false_continue = false;
    // true表达式
    int returnflag = ReturnFlag;
    int break_flag = BreakFlag;
    int continue_flag = ContinueFlag;
    int trueIfFlag = IFflag;
    struct ast_node *true_node = sym_visit_ast_node(src2_node);
    if (!true_node) {
        // if后面没有语句
        src2_node->label = label3;
        node->labels[0] = label3;
    } else {
        src2_node->label = label1;
    }
    if (ReturnFlag > returnflag) {
        ExitLabel = true;
        true_return = true;
    }
    if (BreakFlag > break_flag) {
        true_break = true;
    }
    if (ContinueFlag > continue_flag) {
        true_continue = true;
    }
    if (node->sons.size() == 3) {
        if (true_break) {
            BreakFlag = false;
            node->labels[0] = node->next->label;
            true_node->next = node->next;
            true_node->labels = node->labels;
        }
        if (true_continue) {
            node->labels[0] = node->label;
            true_node->next = node;
            true_node->labels = node->labels;
        }
        struct ast_node *src3_node = node->sons[2];
        returnflag = ReturnFlag;
        break_flag = BreakFlag;
        continue_flag = ContinueFlag;
        int falseIfFlag = IFflag;
        struct ast_node *false_node = sym_visit_ast_node(src3_node);
        if (BreakFlag > break_flag) {
            false_break = true;
        }
        if (ContinueFlag > continue_flag) {
            false_continue = true;
        }
        if (false_break) {
            BreakFlag = false;
            node->labels[1] = node->next->label;
            false_node->next = node->next;
            false_node->labels = node->labels;
        }
        if (false_continue) {
            node->labels[1] = node->label;
            false_node->next = node;
            false_node->labels = node->labels;
        }
        if (!false_node) {
            // else 里没有语句
            src3_node->label = label3;
            node->labels[1] = label3;
        } else {
            src3_node->label = label2;
        }
        if (ReturnFlag > returnflag) {
            ExitLabel = true;
            false_return = true;
        }
        if (IFflag != trueIfFlag or (isLast and WhileBlock)) {
            true_node->jump = false;
        }
        if (IFflag != falseIfFlag or (isLast and WhileBlock)) {
            false_node->jump = false;
        }
        if (true_return and false_return) {
            // return语句直接跳转到L2
            if (node->next) {
                node->next->label = ".L2";
            }
            struct ast_node *temp = new_ast_node(AST_EMPTY);
            temp->label = ".L2";
            true_node->next = temp;
            false_node->next = temp;
        } else if (true_return and !false_return) {
            if (node->next) {
                node->next->label = false_node->labels[2];
            }
            struct ast_node *temp = new_ast_node(AST_EMPTY);
            temp->label = ".L2";
            true_node->next = temp;
        } else if (!true_return and false_return) {
            if (node->next) {
                node->next->label = true_node->labels[2];
            }
            struct ast_node *temp = new_ast_node(AST_EMPTY);
            temp->label = ".L2";
            false_node->next = temp;
        } else {
            if (node->next) {
                true_node->next = node->next;
                false_node->next = node->next;
            } else {

            }
        }
    } else {
        if (true_return) {
            struct ast_node *temp = new_ast_node(AST_EMPTY);
            temp->label = ".L2";
            true_node->next = temp;
            node->labels[1] = node->next->label;
        } else {
            // printf("Break next label :%s\n", node->next->label.c_str());
            if (true_break) {
                node->labels[1] = node->next->label;
                node->next = node->parent->next;
                node->labels[0] = node->next->label;

                printf("Break next label :%s\n", node->next->label.c_str());
                true_node->next = node->next;
            } else if (true_continue) {
                node->labels[0] = label1;
                node->labels[1] = node->next->label;
                printf("Continue next label :%s\n", node->next->label.c_str());
                true_node->next = node;
                true_node->labels = node->labels;
            } else {
                node->labels[1] = node->next->label;
                if (node->next) {
                    true_node->next = node->next;
                } else {}
            }
        }
        if (WhileBlock and !true_break and !true_continue) {
            node->labels[1] = node->label;
        }
    }
    node->val = node->sons[0]->val;
    sym_visit_ast_node(src1_node, true);
    return true;
}
static bool sym_cmp(struct ast_node *node, bool isSecond)
{
    if (isSecond) {
        node->labels = node->parent->labels;
        return true;
    }
    // 仅第一次访问有效
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[2];
    struct ast_node *left = sym_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    struct ast_node *right = sym_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }
    Value *val = nullptr;
    // 变量当右值要先复制给临时变量再进行计算
    if (left->val->isId) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        val->isId = true;
        left->val = val;
    }
    if (right->val->isId) {
        val = newTempValue(ValueType::ValueType_Int, FuncName);
        val->isId = true;
        right->val = val;
    }
    val = newTempValue(ValueType::ValueType_Bool, FuncName);
    node->val = val;
    return true;
}
static bool sym_neg(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *left = sym_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    if (left->val->isId) {
        Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
        node->val = val;
    } else {
        left->val->intVal = -left->val->intVal;
        node->val = left->val;
    }

    return true;
}
static bool sym_while(struct ast_node *node)
{
    WhileBlock = true;
    std::string label1 = newLabel(FuncName);
    std::string label2 = newLabel(FuncName);
    std::string label3 = newLabel(FuncName);
    node->labels.push_back(label2);
    node->labels.push_back(label3);
    node->labels.push_back(label1);
    // label1会一直往子语句块传下去，if语句没有else跳转到该label
    node->label = label1;// 供while语句使用
    if (!node->next) {
        struct ast_node *temp = new_ast_node(AST_EMPTY);
        temp->label = label3;
        node->next = temp;
        printf("label:%s  while没有下一个节点\n", label3.c_str());
    } else {
        if (node->next->label.size() == 0) {
            node->next->label = label3;
            printf("label:%s  while有下一个节点\n", label3.c_str());
        }
    }
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    src2_node->label = node->label;
    src2_node->next = node->next;
    struct ast_node *left = sym_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    struct ast_node *right = sym_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }
    sym_visit_ast_node(src1_node, true);
    WhileBlock = false;
    return true;
}
static bool sym_logical_operation(struct ast_node *node, enum ast_operator_type type, bool isSecond)
{

    if (type == AST_OP_NOT) {
        struct ast_node *src1_node = node->sons[0];
        struct ast_node *left = sym_visit_ast_node(src1_node);
        if (!left) {
            return false;
        }
    } else {
        if (!isSecond) {
            std::string label = newLabel(FuncName);
            node->label = label;
            struct ast_node *src1_node = node->sons[0];
            struct ast_node *src2_node = node->sons[1];
            struct ast_node *left = sym_visit_ast_node(src1_node);
            if (!left) {
                return false;
            }
            struct ast_node *right = sym_visit_ast_node(src2_node);
            if (!right) {
                return false;
            }
            right->label = label;
            // printf("逻辑运算\n");
        } else {
            node->labels = node->parent->labels;
            struct ast_node *src1_node = node->sons[0];
            struct ast_node *src2_node = node->sons[1];
            struct ast_node *left = sym_visit_ast_node(src1_node, true);
            if (!left) {
                return false;
            }

            struct ast_node *right = sym_visit_ast_node(src2_node, true);
            if (!right) {
                return false;
            }
            if (type == AST_OP_OR) {
                left->labels[1] = node->label;
                left->next = right;
            } else {
                left->labels[0] = node->label;
                left->next = right;
            }

            // printf("逻辑运算\n");
        }

    }
    return true;
}
static bool sym_leaf_node(struct ast_node *node, bool isLeft)
{

    Value *val = nullptr;

    if (node->attr.kind == DIGIT_KIND_ID) {
        // 新建一个ID型Value
        // TODO 类型没有指定，有问题，需要修改

        // 变量，则需要在符号表中查找对应的值
        // 若变量之前没有有定值，则采用默认的值为0

        val = findValue(node->attr.id, FuncName, true);
        if (!isLeft) {
            // val = newTempValue(ValueType::ValueType_MAX, FuncName);
        }
        if (!val) {
            printf("Line(%d) Variable(%s) not defined\n",
                   node->attr.lineno,
                   node->attr.id);
            return false;
        }
    } else if (node->attr.kind == DIGIT_KIND_INT) {
        // 新建一个整数常量Value
        val = newConstValue(node->attr.integer_val);
    } else {
        // 新建一个实数型常量Value
        val = newConstValue(node->attr.real_val);
    }
    node->val = val;
    return true;
}
static struct ast_node *sym_visit_ast_node(struct ast_node *node, bool isLeft, bool isLast)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result = true;

    switch (node->type) {
    case AST_OP_NULL:
        result = sym_leaf_node(node, isLeft);
        break;
    case AST_EMPTY:
        result = false;
        break;
    case AST_OP_BREAK:
        result = true;
        BreakFlag++;
        break;
    case AST_OP_CONTINUE:
        result = true;
        ContinueFlag++;
        break;
    case AST_OP_INDEX:
        result = sym_index(node);
        break;
    case AST_FUNC_CALL:
        result = sym_func_call(node, isLeft);
        break;
    case AST_RETURN:
        // printf("return\n");
        result = sym_return(node);
        break;
    case AST_CU:
        result = sym_cu(node);
        break;
    case AST_OP_IF:
        result = sym_if(node, isLast);
        break;
    case AST_OP_CMP:
        result = sym_cmp(node, isLeft);
        break;
    case AST_OP_WHILE:
        result = sym_while(node);
        break;
    case AST_OP_OR:
        result = sym_logical_operation(node, AST_OP_OR, isLeft);
        break;
    case AST_OP_AND:
        result = sym_logical_operation(node, AST_OP_AND, isLeft);
        break;
    case AST_DEF_LIST:
        result = sym_def_list(node);
        break;
    case AST_FUNC_DEF:
        result = sym_def_func(node);
        break;
    case AST_OP_BLOCK:
        result = sym_block(node);
        break;
    case AST_OP_NEG:
        result = sym_neg(node);
        break;
        // TODO 其它运算符支持追加，同时增加表达式运算函数调用
    case AST_OP_ADD:
    case AST_OP_SUB:
    case AST_OP_MUL:
    case AST_OP_DIV:
    case AST_OP_MOD:
        result = sym_binary_op(node, node->type);
        break;
    case AST_OP_ASSIGN:
        result = sym_assign(node);
        break;
    default:
        // 错误，不支持
        result = false;
        break;
    }

    // 语义解析错误，则出错返回
    if (!result) {
        node = nullptr;
    }

    return node;
}
/// @brief 遍历抽象语法树产生线性IR，保存到IRCode中
/// @param root 抽象语法树
/// @param IRCode 线性IR
/// @return true: 成功 false: 失败
bool genSymbol(struct ast_node *root)
{
    bool result = true;
    printf("*** start genSymbol *** \n");
    result = sym_cu(root);
    if (!result) {
        return false;
    }
    printf("*** end genSymbol *** \n");

    return true;
}