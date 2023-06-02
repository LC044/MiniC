#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
// std::string FuncName;
extern std::string FuncName;
// #include <iostream>
extern std::unordered_map<std::string, Value *> varsMap;
// 用来保存所有的函数信息
extern std::unordered_map<std::string, FuncSymbol *> funcsMap;
// 保存全局变量名，以便顺序遍历
extern std::vector<std::string > varsName;
// 保存函数名，以便顺序遍历
extern std::vector<std::string > funcsName;

static struct ast_node *ir_visit_ast_node(struct ast_node *node, bool isLast = false);
static bool ir_leaf_node(struct ast_node *node, bool isLeft = false);
static bool ir_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);

// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool ir_cu(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步遍历全局变量符号表
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算

        if ((*pIter)->type == AST_DEF_LIST) {
            struct ast_node *temp = ir_visit_ast_node(*pIter);
            node->blockInsts.addInst(
                temp->blockInsts
            );
        }
    }
    // 第二步遍历函数表
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        if ((*pIter)->type == AST_FUNC_DEF) {
            struct ast_node *temp = ir_visit_ast_node(*pIter);
            node->blockInsts.addInst(
                temp->blockInsts
            );
        }

        // node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}
// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool ir_block(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步首先是深度优先遍历，定义所有局部变量和临时变量
    // 第二步是遍历其他表达式语句
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        if ((*pIter)->type == AST_DEF_LIST) {
            continue;
        }

        struct ast_node *temp;
        if (pIter == node->sons.end() - 1) {
            temp = ir_visit_ast_node(*pIter, true);
        } else {
            // 遍历Block的每个语句，进行显示或者运算
            temp = ir_visit_ast_node(*pIter);
        }
        if (!temp) {
            return false;
        }
        // if语句的后一句一定是一个新的label
        // 下一条语句
        if (pIter != node->sons.begin() and (*(pIter - 1))->type == AST_OP_IF) {
            node->blockInsts.addInst(
                    new UselessIRInst(temp->label + ":")
            );
        }
        node->blockInsts.addInst(temp->blockInsts);
    }
    return true;
}

static bool ir_def_array(struct ast_node *node, ValueType type, bool isLocal)
{

    Value *val = nullptr;
    // 第一个孩子是标识符
    struct ast_node *temp_id = node->sons[0];
    if (isLocal) {
        val = funcsMap[FuncName]->localVarsMap[temp_id->attr.id];
    } else {
        val = varsMap[temp_id->attr.id];
    }
    node->val = val;
    return true;
}

static bool ir_def_list(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一个孩子节点是变量类型
    // struct ast_node *temp_type = node->sons[0];
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        Value *val = nullptr;
        struct ast_node *temp = *pIter;
        if (temp->type == AST_ARRAY) {
            // bool result = ir_def_array(temp, type);
            // if (!result)return false;
        } else {
            val = varsMap[temp->attr.id];
            temp->val = val;
        }
        // printf("global variable %s\n", temp->val->getName().c_str());
        node->blockInsts.addInst(
            new DeclearIRInst(temp->val, true, true)
        );
    }
    return true;
}

// 函数定义IR
static bool ir_def_func(struct ast_node *node)
{
    // struct ast_node *func_type = node->sons[0];
    // 第一个孩子是函数返回类型
    // 第二个孩子是函数名
    struct ast_node *func_name = node->sons[1];
    Value *val = nullptr;
    FuncName = func_name->attr.id;
    val = funcsMap[FuncName];
    func_name->val = val;
    // printf("Function: %s\n", func_name->attr.id);
    printf("Function: %s\n", val->getName().c_str());
    // 添加函数定义IR指令
    node->blockInsts.addInst(
            new FuncDefIRInst(func_name->val)
    );
    // 添加局部变量定义IR指令
    printf("函数局部变量个数:%d\n", func_name->val->localVarsName.size());
    for (int i = 0; i < func_name->val->localVarsName.size(); ++i) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        // struct ast_node *arg_name = (*pIter)->sons[1];
        Value *localVarValue = nullptr;
        localVarValue = func_name->val->localVarsMap[func_name->val->localVarsName[i]];
        // printf("形参定义 %s\n", localVarValue->getName().c_str());
        // arg_name->val = localVarValue;
        node->blockInsts.addInst(
            new DeclearIRInst(localVarValue, false, true)
        );
    }
    // 添加临时变量定义IR指令
    printf("函数临时变量个数:%d\n", func_name->val->tempVarsName.size());
    for (int i = func_name->val->fargs.size(); i < func_name->val->tempVarsName.size(); ++i) {
        Value *localVarValue = nullptr;
        localVarValue = func_name->val->tempVarsMap[func_name->val->tempVarsName[i]];
        node->blockInsts.addInst(
            new DeclearIRInst(localVarValue, false, true, true)
        );
    }
    // 函数进入IR指令
    node->blockInsts.addInst(
        new UselessIRInst("    entry")
    );
    for (int i = 0; i < func_name->val->fargs.size(); ++i) {
        Value *srcValue = nullptr;
        srcValue = func_name->val->tempVarsMap[func_name->val->tempVarsName[i]];
        Value *resultValue = nullptr;
        resultValue = func_name->val->localVarsMap[func_name->val->localVarsName[i]];
        node->blockInsts.addInst(
            new AssignIRInst(resultValue, srcValue)
        );
    }
    // return true;
    // 第四个孩子是语句块
    struct ast_node *func_block = ir_visit_ast_node(node->sons[3]);
    // return true;
    node->blockInsts.addInst(func_block->blockInsts);
    // 语句块结束之后应该加一个 '}'
    node->blockInsts.addInst(
        new UselessIRInst("}")
    );
    return true;
}
// return IR
static bool ir_return(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *result = ir_visit_ast_node(src1_node);
    if (!result) {
        // 解析错误
        return false;
    }
    node->blockInsts.addInst(result->blockInsts);
    Value *returnValue = findValue("return", FuncName, true);
    node->blockInsts.addInst(
            new AssignIRInst(returnValue, result->val)
    );
    node->blockInsts.addInst(
            new AssignIRInst(node->val, returnValue)
    );
    // node->blockInsts.addInst(
    //     new ReturnIRInst(node->val)
    // );
    node->blockInsts.addInst(
        new UnaryIRInst(IRINST_OP_RETURN, node->val, node->val)
    );
    return true;
}


static bool ir_binary_op(struct ast_node *node, enum ast_operator_type type)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 减法节点，左结合，先计算左节点，后计算右节点

    // 减法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 减法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    Value *leftValue = left->val;
    Value *rightValue = right->val;
    if (left->val->isId) {
        Value *val = findValue(left->attr.id, FuncName, true);
        Value *dstVal = left->val;
        node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
        );
    }
    if (right->val->isId) {
        Value *val = findValue(right->attr.id, FuncName, true);
        Value *dstVal = right->val;
        node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
        );
    }
    if ((leftValue->isConst) and (rightValue->isConst)) {
        ;
    } else {

        switch (type) {
        case AST_OP_ADD:
            node->blockInsts.addInst(
                new BinaryIRInst(IRINST_OP_ADD, node->val, left->val, right->val)
            );
            break;
        case AST_OP_SUB:
            node->blockInsts.addInst(
                new BinaryIRInst(IRINST_OP_SUB, node->val, left->val, right->val)
            );
            break;
        case AST_OP_MUL:
            node->blockInsts.addInst(
                new BinaryIRInst(IRINST_OP_MUL, node->val, left->val, right->val)
            );
            break;
        case AST_OP_DIV:
            node->blockInsts.addInst(
                new BinaryIRInst(IRINST_OP_DIV, node->val, left->val, right->val)
            );
            break;
        case AST_OP_MOD:
            node->blockInsts.addInst(
                new BinaryIRInst(IRINST_OP_MOD, node->val, left->val, right->val)
            );
            break;
        default:
            break;
        }

    }
    return true;
}

// 赋值操作
static bool ir_assign(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 赋值节点，自右往左运算

    // 赋值运算符的左侧操作数
    struct ast_node *left = ir_visit_ast_node(son1_node, true);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }

    // 赋值运算符的右侧操作数
    struct ast_node *right = ir_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);
    // return true;
    // 左值类型与右值类型相同
    // 加上这行代码才能判断是否要进行类型转换
    left->val->type = right->val->type;

    node->blockInsts.addInst(
        new AssignIRInst(left->val, right->val));
    node->val = left->val;

    return true;
}
static bool ir_neg(struct ast_node *node)
{
    struct ast_node *son1_node = node->sons[0];
    struct ast_node *left = ir_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(
        new UnaryIRInst(IRINST_OP_NEG, node->val, left->val));

    return true;
}
static bool ir_cmp(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[2];

    // 减法节点，左结合，先计算左节点，后计算右节点

    // 减法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 减法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);
    if (left->val->isId) {
        Value *val = findValue(left->attr.id, FuncName, true);
        Value *dstVal = left->val;
        node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
        );
    }
    if (right->val->isId) {
        Value *val = findValue(right->attr.id, FuncName, true);
        Value *dstVal = right->val;
        node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
        );
    }
    // 比较运算符
    struct ast_node *cmp_node = node->sons[1];
    node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, cmp_node->attr.id, node->val, left->val, right->val)
    );
    // printf("cmp指令\n");
    return true;
}
static bool ir_if(struct ast_node *node, bool isLast)
{

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 减法节点，左结合，先计算左节点，后计算右节点

    // 减法的左边操作数
    struct ast_node *cond = ir_visit_ast_node(src1_node);
    if (!cond) {
        // 某个变量没有定值
        return false;
    }
    node->blockInsts.addInst(cond->blockInsts);
    std::string label1;  // true语句
    std::string label2;  // false语句
    std::string label3 = node->next->label;  // 下一条语句
    // 指令跳转语句
    if (node->sons.size() == 3) {
        struct ast_node *src3_node;
        src3_node = node->sons[2];
        if (src2_node->type == AST_EMPTY) {
            label1 = label3;
        } else {
            label1 = src2_node->label;
        }
        if (src3_node->type == AST_EMPTY) {
            label2 = label3;
        } else {
            label2 = src3_node->label;
        }
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, node->val, label1, label2)
        );
    } else {
        if (src2_node->type == AST_EMPTY) {
            label1 = label3;
            label2 = label3;
        } else {
            label1 = src2_node->label;
        }
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, node->val, label1, label3)
        );
    }
    // 条件表达式为真
    struct ast_node *true_node = ir_visit_ast_node(src2_node);
    if (true_node->type == AST_EMPTY) {
        if (node->sons.size() == 2) {
            // // 下一条语句
            // if (!isLast) {
            //     node->blockInsts.addInst(
            //             new UselessIRInst(label3 + ":")
            //     );
            // }
            return true;
        }
    } else {
        // 条件表达式为真的语句
        // printf("label1 %s\n", label1.c_str());
        node->blockInsts.addInst(
                new UselessIRInst(label1 + ":")
        );
        node->blockInsts.addInst(true_node->blockInsts);
        // 下一条语句
        if (!isLast and true_node->type != AST_OP_IF) {
            node->blockInsts.addInst(
                    new JumpIRInst(IRINST_JUMP_BR, label3)
            );
        }
    }
    // 条件表达式为假，else存在
    if (node->sons.size() == 3) {
        struct ast_node *src3_node = node->sons[2];
        struct ast_node *false_node = ir_visit_ast_node(src3_node);
        if (false_node->type == AST_EMPTY) {
            // 某个变量没有定值
            // return true;
        } else {
            // printf("label2 %s\n", label2.c_str());
            node->blockInsts.addInst(
            new UselessIRInst(label2 + ":")
            );
            node->blockInsts.addInst(false_node->blockInsts);
            // 下一条语句
            if (!isLast and true_node->type != AST_OP_IF) {
                node->blockInsts.addInst(
                        new JumpIRInst(IRINST_JUMP_BR, label3)
                );
            }
        }
    }
    // // 下一条语句
    // if (!isLast) {
    //     printf("label3 %s\n", label3.c_str());
    //     node->blockInsts.addInst(
    //             new UselessIRInst(label3 + ":")
    //     );
    // }
    return true;
}
static bool ir_leaf_node(struct ast_node *node, bool isLeft)
{

    // Value *val = nullptr;

    if (node->attr.kind == DIGIT_KIND_ID) {
        // 新建一个ID型Value
        // TODO 类型没有指定，有问题，需要修改

        // 变量，则需要在符号表中查找对应的值
        // 若变量之前没有有定值，则采用默认的值为0
        if (isLeft) {
            // val = findValue(node->attr.id, FuncName, true);
            // node->val = val;
        } else {
            // val = findValue(node->attr.id, FuncName, true);
            // Value *dstVal = node->val;
            // node->blockInsts.addInst(
            //     new AssignIRInst(dstVal, val)
            // );
        }

        // node->val = val;
    }
    return true;
}

// 递归遍历抽象语法树进行计算
static struct ast_node *ir_visit_ast_node(struct ast_node *node, bool isLast)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result = true;

    switch (node->type) {
    case AST_OP_NULL:
        // 叶子节点
        result = ir_leaf_node(node, isLast);
        break;
    case AST_EMPTY:
        result = true;
        break;
    case AST_OP_MUL:
        // 乘法节点
        ;

    case AST_OP_ADD:
        // 加法节点
        ;
    case AST_OP_SUB:
        // 乘法节点
        ;

    case AST_OP_DIV:
        // 加法节点
        ;
    case AST_OP_MOD:
        // 加法节点
        result = ir_binary_op(node, node->type);
        break;
    case AST_OP_ASSIGN:

        // 赋值语句
        result = ir_assign(node);
        break;
    case AST_OP_NEG:
        result = ir_neg(node);
        break;
    case AST_OP_IF:
        printf("IF\n");
        result = ir_if(node, isLast);
        break;
    case AST_OP_CMP:
        printf("CMP\n");
        result = ir_cmp(node);
        break;
    case AST_RETURN:

        // 赋值语句
        result = ir_return(node);
        break;
    case AST_OP_BLOCK:

        // 多个语句组成的块
        result = ir_block(node);
        if (!result) {
            printf("error:in block\n");
        }
        break;
    case AST_CU:
        printf("CU\n");
        // 多个语句组成的块
        result = ir_cu(node);
        break;
    case AST_DEF_LIST:
        // printf("AST_DEF_LIST\n");
        // 变量定义
        result = ir_def_list(node);
        break;
    case AST_FUNC_DEF:
        // printf("AST_DEF_array\n");
        // 数组定义
        result = ir_def_func(node);
        break;
        // TODO 其它运算符支持追加，同时增加表达式运算函数调用
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
bool genIR(struct ast_node *root, InterCode &IRCode)
{
    bool result;
    printf("*** start genIR *** \n");
    result = ir_visit_ast_node(root);
    if (!result) {
        printf("***genIr failed***\n");
        return false;
    }
    printf("*** end genIR *** \n");
    // 第一步遍历符号表，声明所有全局变量
    // result = global_var_def(root);
    // if (!result) {
    //     return false;
    // }
    IRCode.addInst(root->blockInsts);
    // 第二步遍历函数表，定义函数语句
    return true;
}
