#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
std::string FuncName;
static bool sym_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);
static bool sym_cu(struct ast_node *node);
static bool sym_block(struct ast_node *node);
static bool sym_def_list(struct ast_node *node, bool isLocal = false);
static bool sym_def_func(struct ast_node *node);
static struct ast_node *sym_visit_ast_node(struct ast_node *node);

static bool sym_block(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步首先是深度优先遍历，定义所有局部变量和临时变量
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        if ((*pIter)->type == AST_DEF_LIST) {
            // 第一个孩子为变量类型
            bool result = sym_def_list(*pIter, true);
            if (!result) {
                return false;
            }
        }
    }

    // 第二步是遍历其他表达式语句
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        if ((*pIter)->type == AST_DEF_LIST) {
            continue;
        }
        // 遍历Block的每个语句，进行显示或者运算
        struct ast_node *temp = sym_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }
    }
    return true;
}
static bool sym_def_func(struct ast_node *node)
{
    // struct ast_node *func_type = node->sons[0];
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
    Value *localVarValue = nullptr;
    // todo 暂时只考虑int类型
    localVarValue = newLocalVarValue("", ValueType::ValueType_Int, func_name->attr.id);
    node->sons[3]->val = localVarValue;
    // 实参赋值给临时变量
    for (pIter = func_paras->sons.end() - 1; pIter != func_paras->sons.begin() - 1; --pIter) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        struct ast_node *arg_name = (*pIter)->sons[1];
        Value *localVarValue = nullptr;
        // todo 暂时只考虑int类型
        localVarValue = newTempValue(ValueType::ValueType_Int, func_name->attr.id);
        arg_name->val = localVarValue;
    }
    // 第四个孩子是语句块
    struct ast_node *func_block = sym_visit_ast_node(node->sons[3]);
    if (func_block == NULL) return true;
    return true;
}
static bool sym_def_array(struct ast_node *node, ValueType type, bool isLocal)
{
    Value *val = nullptr;
    // 第一个孩子是标识符
    struct ast_node *temp_id = node->sons[0];
    if (!IsExist(temp_id->attr.id)) {
        // 变量名没有找到
        // 创建一个新的符号
        if (isLocal) {
            val = newLocalVarValue(temp_id->attr.id, type, FuncName);
            // printf("loacl Array\n");
        } else {
            val = newVarValue(temp_id->attr.id);
            val->type = type;
        }

    } else {
        // 若变量名已存在，则报错重定义
        std::string error = std::string("error: redefinition of ") + std::string(temp_id->attr.id);
        printError(temp_id->attr.lineno, error);
        return false;
    }
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
        kind0 = DIGIT_KIND_INT;
        type = ValueType::ValueType_Int;
    }

    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        Value *val = nullptr;
        struct ast_node *temp = *pIter;
        if (temp->type == AST_ARRAY) {
            bool result = sym_def_array(temp, type, isLocal);
            if (!result)return false;
        } else {
            if (!IsExist(temp->attr.id)) {
                // 变量名没有找到
                if (isLocal) {
                    val = newLocalVarValue(temp->attr.id, type, FuncName);
                } else {
                    val = newVarValue(temp->attr.id);
                }

                // printf("other value %s\n", temp->attr.id);
            } else {
                // 若变量名已存在，则报错重定义
                std::string error = std::string("error: redefinition of") + std::string(temp->attr.id);
                printError(temp->attr.lineno, error);
                return false;
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

    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            // Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            // node->blockInsts.addInst(
            // new TypeCovIRInst(resultValue0, left->val, true)
            // );
            // left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            // Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            // node->blockInsts.addInst(
            // new TypeCovIRInst(resultValue0, right->val, true)
            // );
            // right->val = resultValue0;
        }
        // Value *resultValue = newTempValue(ValueType::ValueType_Real);
        // node->blockInsts.addInst(
        //     new BinaryIRInst(IRINST_OP_ADD, resultValue, left->val, right->val)
        // );
        // node->val = resultValue;
    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令


    }
    // todo 暂时只考虑int类型
    Value *resultValue = newTempValue(ValueType::ValueType_Int, FuncName);
    // printf("新建临时变量%s\n", resultValue->getName().c_str());
    // node->blockInsts.addInst(
    //     new BinaryIRInst(IRINST_OP_ADD, resultValue, left->val, right->val));
    node->val = resultValue;
    return true;
}
static bool sym_leaf_node(struct ast_node *node)
{

    Value *val = nullptr;

    if (node->attr.kind == DIGIT_KIND_ID) {
        // 新建一个ID型Value
        // TODO 类型没有指定，有问题，需要修改

        // 变量，则需要在符号表中查找对应的值
        // 若变量之前没有有定值，则采用默认的值为0

        val = findValue(node->attr.id, FuncName, true);
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
static struct ast_node *sym_visit_ast_node(struct ast_node *node)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result = true;

    switch (node->type) {
    case AST_OP_NULL:
        result = sym_leaf_node(node);
        break;
    case AST_CU:
        result = sym_cu(node);
        break;
    case AST_DEF_LIST:
        result = sym_def_list(node);
        break;
    case AST_FUNC_DEF:
        result = sym_def_func(node);
    case AST_OP_BLOCK:
        result = sym_block(node);
        // TODO 其它运算符支持追加，同时增加表达式运算函数调用
    case AST_OP_ADD:
        ;
    case AST_OP_SUB:
        ;
    case AST_OP_MUL:
        ;
    case AST_OP_DIV:
        ;
    case AST_OP_MOD:
        printf("binary operator\n");
        result = sym_binary_op(node, node->type);
        break;
    case AST_OP_ASSIGN:
        ;
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