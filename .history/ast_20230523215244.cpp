#include <iostream>
#include "ast.h"

/* 整个AST的根节点 */
struct ast_node *ast_root = nullptr;

/// @brief 创建最多四个孩子的节点
struct ast_node *new_ast_node(enum ast_operator_type type,
    struct ast_node *first_son,
    struct ast_node *second_son,
    struct ast_node *third_son,
    struct ast_node *forth_son = nullptr
)
{
    struct ast_node *nd = new struct ast_node();
    nd->type = type;
    nd->parent = nullptr;
    nd->val = nullptr;

    if (first_son != nullptr) {
        nd->sons.push_back(first_son);
        first_son->parent = nd;
    }

    if (second_son != nullptr) {
        nd->sons.push_back(second_son);
        second_son->parent = nd;
    }

    if (third_son != nullptr) {
        nd->sons.push_back(third_son);
        third_son->parent = nd;
    }
    if (forth_son != nullptr) {
        nd->sons.push_back(third_son);
        third_son->parent = nd;
    }
    return nd;
}

/// @brief 创建AST的叶子节点，或者终结符节点
/// @param val
struct ast_node *new_ast_leaf_node(struct ast_node_attr &val)
{
    struct ast_node *nd = new struct ast_node();
    nd->type = AST_OP_NULL;
    nd->parent = nullptr;
    nd->val = nullptr;
    nd->attr = val;

    return nd;
}

/// @brief 递归清理抽象语法树
/// @param node AST的节点
void free_ast_node(struct ast_node *node)
{
    if (node) {

        for (auto child : node->sons) {

            free_ast_node(child);
        }

        // 清理孩子元素
        node->sons.clear();

        // 清理node资源
        delete node;
    }
}

/// @brief AST资源清理
void free_ast()
{
    free_ast_node(ast_root);
    ast_root = nullptr;
}
