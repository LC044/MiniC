#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
static bool sym_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);
static bool sym_cu(struct ast_node *node);

static bool sym_def_list(struct ast_node *node);

static bool sym_def_array(struct ast_node *node, ValueType type, bool isLocal)
{
    Value *val = nullptr;
    // 第一个孩子是标识符
    struct ast_node *temp_id = node->sons[0];
    if (!IsExist(temp_id->attr.id)) {
        // 变量名没有找到
        // 创建一个新的符号
        if (isLocal) {
            val = newLocalVarValue(temp_id->attr.id, type);
            printf("loacl Arrar\n");
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
static bool sym_def_list(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一个孩子节点是变量类型
    struct ast_node *temp_type = node->sons[0];
    enum digitnum_kind kind0;
    ValueType type;
    // 暂时只考虑int型变量
    if (strcmp(temp_type->attr.id, "int") == 0) {
        printf("int value\n");
        kind0 = DIGIT_KIND_INT;
        type = ValueType::ValueType_Int;
    }
    // printf("other value %s\n", temp_type->attr.id);
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        Value *val = nullptr;
        struct ast_node *temp = *pIter;
        if (temp->type == AST_ARRAY) {
            bool result = sym_def_array(temp, type);
            if (!result)return false;
        } else {
            if (!IsExist(temp->attr.id)) {
                // 变量名没有找到
                val = newVarValue(temp->attr.id);
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
            // 第一个孩子为变量类型
            struct ast_node *temp_type = (*pIter)->sons[0];
            ValueType type_;
            // todo 暂时只考虑int类型
            if (strcmp(temp_type->attr.id, "int") == 0) {
                type_ = ValueType::ValueType_Int;
            }
            // 后面的孩子为变量名
            std::vector<struct ast_node *>::iterator pIter1;
            for (pIter1 = (*pIter)->sons.begin() + 1; pIter1 != (*pIter)->sons.end(); ++pIter1) {
                Value *val = nullptr;
                struct ast_node *temp = *pIter1;
                if (temp->type == AST_ARRAY) {
                    // 数组变量
                    bool result = sym_def_array(temp, type_, true);
                    if (!result)return false;
                } else {
                    if (!IsExist(temp->attr.id)) {
                        // 变量名没有找到
                        val = newVarValue(temp->attr.id);
                    } else {
                        // 若变量名已存在，则报错重定义
                        std::string error = std::string("error: redefinition of") + std::string(temp->attr.id);
                        printError(temp->attr.lineno, error);
                        return false;
                    }
                    temp->val = val;
                }
            }
        }
    }
    return true;
}
static struct ast_node *ir_visit_ast_node(struct ast_node *node)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result = true;

    switch (node->type) {
    case AST_CU:
        result = sym_cu(node);
        break;
    case AST_DEF_LIST:
        result = sym_def_list(node);
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
bool genSymbol(struct ast_node *root)
{
    bool result = true;
    printf("*** start genSymbol *** \n");
    // result = sym_cu(root);
    if (!result) {
        return false;
    }
    printf("*** end genSymbol *** \n");
    return true;
}