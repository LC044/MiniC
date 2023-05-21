#include "expr.h"
#include "symbol.h"

static struct ast_node *expr_visit_ast_node(struct ast_node *node);

/// @brief 无须指定动作函数，正常返回
/// @param node 
/// @return 
static bool expr_noaction(struct ast_node *node)
{
    (void)node;
    return true;
}

/// @brief 缺省动作，不认识的节点操作符，失败返回
/// @param node 
/// @return 
static bool expr_default(struct ast_node *node)
{
    // 未知的节点
    printf("Unkown node(%d)\n", node->type);
    return false;
}

// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool expr_block(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        struct ast_node *temp = expr_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }
    }

    return true;
}

// expression print
static bool expr_show(struct ast_node *node)
{
    // TODO real number print

    struct ast_node *son1_node = node->sons[0];

    struct ast_node *result_node = expr_visit_ast_node(son1_node);
    if (!result_node) {
        // 解析错误
        return false;
    }

    Value *result_value = result_node->val;

    if (result_value->type == ValueType::ValueType_Int) {
        printf("%d\n", result_value->intVal);
    } else {
        printf("%lf\n", result_value->realVal);
    }

    return true;
}

// expresion add
static bool expr_add(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // printf("%d %lf %d\n", static_cast<int>(leftValue->type), leftValue->realVal, leftValue->intVal);
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        double e1 = leftValue->realVal, e2 = rightValue->realVal;
        if (leftValue->type == ValueType::ValueType_Int) {
            e1 = (double)(leftValue->intVal);
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            e2 = (double)(rightValue->intVal);
        }
        node->val = newConstValue(e1 + e2);
    } else {
        node->val = newConstValue(leftValue->intVal + rightValue->intVal);
    }

    return true;
}
// expresion sub
static bool expr_sub(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // printf("%d %lf %d\n", static_cast<int>(leftValue->type), leftValue->realVal, leftValue->intVal);
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        double e1 = leftValue->realVal, e2 = rightValue->realVal;
        if (leftValue->type == ValueType::ValueType_Int) {
            e1 = (double)(leftValue->intVal);
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            e2 = (double)(rightValue->intVal);
        }
        node->val = newConstValue(e1 - e2);
    } else {
        node->val = newConstValue(leftValue->intVal - rightValue->intVal);
    }

    return true;
}

// expresion multiply
static bool expr_mul(struct ast_node *node)
{
    // TODO real number mul

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        double e1 = leftValue->realVal, e2 = rightValue->realVal;
        if (leftValue->type == ValueType::ValueType_Int) {
            e1 = (double)(leftValue->intVal);
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            e2 = (double)(rightValue->intVal);
        }
        node->val = newConstValue(e1 * e2);
    } else {
        node->val = newConstValue(leftValue->intVal * rightValue->intVal);
    }

    return true;
}
// expression divide
static bool expr_div(struct ast_node *node)
{
    // TODO real number mul

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        double e1 = leftValue->realVal, e2 = rightValue->realVal;
        if (leftValue->type == ValueType::ValueType_Int) {
            e1 = (double)(leftValue->intVal);
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            e2 = (double)(rightValue->intVal);
        }
        node->val = newConstValue(e1 / e2);
    } else {
        node->val = newConstValue(leftValue->intVal / rightValue->intVal);
    }
    // node->val = newConstValue(leftValue->intVal * rightValue->intVal);

    return true;
}
// expression mod
static bool expr_mod(struct ast_node *node)
{
    // TODO real number mul

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    node->val = newConstValue(leftValue->intVal % rightValue->intVal);
    // printf("mod\n");
    return true;
}
// expresion assign
static bool expr_assign(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 赋值运算符节点，自右往左运算
    struct ast_node *right = expr_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    struct ast_node *left = expr_visit_ast_node(son1_node);
    if (!left) {
        // 应该不可能发生
        return false;
    }

    // TODO 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    if (rightValue->type == ValueType::ValueType_Real) {
        // 赋值操作，类型为浮点数
        leftValue->type = ValueType::ValueType_Real;
        leftValue->realVal = rightValue->realVal;
    } else {
        // 赋值操作，类型为整数
        leftValue->type = ValueType::ValueType_Int;
        leftValue->intVal = rightValue->intVal;
    }

    // 结果结点的value为leftValue
    node->val = leftValue;

    return true;
}

static bool expr_leaf_node(struct ast_node *node)
{
    Value *val = nullptr;

    if (node->attr.kind == DIGIT_KIND_ID) {
        // 新建一个ID型Value
        // TODO 类型没有指定，有问题，需要修改

        // 变量，则需要在符号表中查找对应的值
        // 若变量之前没有有定值，则采用默认的值为0

        val = findValue(node->attr.id);
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

typedef bool (*expr_handler_t)(struct ast_node *);

static struct {
    enum ast_operator_type type;
    expr_handler_t action;
} expr_handlers[] = {
    {AST_OP_NULL,      expr_leaf_node},
    {AST_OP_MUL,       expr_mul},
    {AST_OP_ADD,       expr_add},
    {AST_OP_EXPR,      expr_noaction},
    {AST_OP_EXPR_SHOW, expr_show},
    {AST_OP_ASSIGN,    expr_assign},
    {AST_OP_BLOCK,     expr_block},
    {AST_OP_DIV,       expr_div},
    {AST_OP_SUB,       expr_sub},
    {AST_OP_MOD,       expr_mod},
};

// 递归遍历抽象语法树进行计算
static struct ast_node *expr_visit_ast_node(struct ast_node *node)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    // 根据动作节点运算符查找对应的动作函数
    expr_handler_t handler = expr_default;
    for (size_t n = 0; n < sizeof(expr_handlers) / sizeof(expr_handlers[0]); n++) {
        if (expr_handlers[n].type == node->type) {
            handler = expr_handlers[n].action;
        }
    }

    // 执行动作
    bool result = handler(node);
    if (!result) {
        // 语义解析错误，则出错返回
        node = nullptr;
    }

    return node;
}

/// @brief 表达式计算
void expr_calculate_show(struct ast_node *root)
{
    expr_visit_ast_node(root);
}