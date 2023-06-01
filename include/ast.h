#pragma once

#include <cstdio>
#include <vector>
#include <string>

#include "IRCode.h"
#include "symbol.h"

enum ast_operator_type {
    AST_OP_NULL,  // 终结符节点
    AST_OP_ADD,   // 二元运算符+
    AST_OP_MUL,   // 二元运算符*
    // 增强
    AST_OP_DIV,   // 二元运算符/
    AST_OP_SUB,   // 二元运算符-
    AST_OP_MOD,   // 取模运算
    AST_OP_BLOCK, // 多个语句组成的块

    AST_OP_ASSIGN, // 赋值语句
    AST_OP_EXPR,   // 表达式语句，不显示表达式的值
    AST_OP_EXPR_SHOW, // 表达式语句，需要显示表达式的值

    // TODO 抽象语法树其它内部节点运算符追加
    AST_FUNC_CALL,    // 函数调用
    AST_REAL_ARGS,    // 实参
    AST_OP_LDEC,      // 左自减 --a
    AST_OP_LINC,      // 左自增 ++a
    AST_OP_RDEC,      // 右自减
    AST_OP_RINC,      // 右自增
    AST_OP_AND,       // 逻辑与
    AST_OP_INDEX,     // 数组索引
    AST_OP_OR,        // 逻辑或
    AST_OP_NEG,       // 取负
    AST_OP_NOT,       // 逻辑非
    AST_OP_CMP,       // 比较运算
    AST_OP_IF,        // IF语句
    AST_OP_WHILE,     // While 语句
    AST_OP_BREAK,     // break 语句
    AST_OP_CONTINUE,  // continue 语句
    AST_ARRAY,        // 数组定义
    AST_ARRAY_LIST,
    AST_DEF_LIST,
    AST_DIMS,         // 数组维度
    AST_EMPTY,        // 空语句
    AST_RETURN,       // 返回语句
    AST_CU,           // 文件，全局声明、定义
    AST_VAR_DECL,     // 变量声明
    AST_VAR_DEF,      // 变量定义
    AST_FUNC_DEF,     // 函数定义  
    AST_FUNC_DECL,    // 函数声明
    AST_FARGS,        // 参数列表
    AST_OP_MAX,       // 非法运算符
};

enum digitnum_kind {
    DIGIT_KIND_INT,  // 整型字面量
    DIGIT_KIND_REAL, // 实数字面量
    DIGIT_KIND_ID,   // 变量名称
    CMP_KIND,
    KEYWORD_ID,     // 关键词
    DEFAULT,
};
enum CMP_KIND_ {
    LT,
    GT,
    LE,
    GE,
    EQ,
    NE,
};

// 叶子节点的属性值
typedef struct ast_node_attr {

    enum digitnum_kind kind;
    enum CMP_KIND_ cmp_kind; // 比较运算符 只有CMP_KIND有效
    int lineno;  // 行号信息，只有DIGIT_KIND_ID有效

    union {
        int integer_val;
        double real_val;
        char id[256];
    };

} ast_node_attr;

struct ast_node {
    struct ast_node *parent;    // 父节点
    std::vector<struct ast_node *> sons; // 孩子节点

    enum ast_operator_type type; // 节点类型
    struct ast_node_attr attr;   // node的其它属性

    // 线性IR指令块，可包含多条IR指令
    InterCode blockInsts;

    // 线性IR指令或者运行产生的Value
    Value *val;
};

/// @brief 创建最多三个孩子的节点
struct ast_node *new_ast_node(
    enum ast_operator_type type,
    struct ast_node *first_son = nullptr,
    struct ast_node *second_son = nullptr,
    struct ast_node *third_son = nullptr,
    struct ast_node *forth_son = nullptr
);

/// @brief 创建抽象语法树的叶子节点
struct ast_node *new_ast_leaf_node(struct ast_node_attr &val);

/// @brief AST资源清理
void free_ast();
void free_ast_node(struct ast_node *node);
/// @brief抽象语法树的根节点指针
extern struct ast_node *ast_root;

