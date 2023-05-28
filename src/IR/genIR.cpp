#include "ast.h"
#include "IRCode.h"
#include<string.h>
#include "symbol.h"
// #include <iostream>
static struct ast_node *ir_visit_ast_node(struct ast_node *node);
static bool ir_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);
// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool ir_cu(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步首先是深度优先遍历，定义所有局部变量和临时变量
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        struct ast_node *temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }

    return true;
}
// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool ir_block(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步首先是深度优先遍历，定义所有局部变量和临时变量
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
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
                Value *localVarValue = nullptr;
                struct ast_node *temp = *pIter1;
                if (temp->type == AST_ARRAY) {
                    // 数组变量
                    bool result = ir_def_array(temp, type_, true);
                    if (!result)return false;
                } else {
                    if (!IsExist(temp->attr.id)) {
                        // 变量名没有找到
                        localVarValue = newLocalVarValue(temp->attr.id, type_);
                    } else {
                        // 若变量名已存在，则报错重定义
                        std::string error = std::string("error: redefinition of") + std::string(temp->attr.id);
                        printError(temp->attr.lineno, error);
                        return false;
                    }
                    temp->val = localVarValue;
                }

                printf("localVarValue:%s;%s\n", temp->val->getName().c_str(), temp->val->getName().c_str());
                // (*pIter1)->val = localVarValue;
                node->blockInsts.addInst(
                    new DeclearIRInst(temp->val, false, true)
                );
            }
        }
    }
    // 函数进入语句
    node->blockInsts.addInst(
        new UselessIRInst("    entry")
    );
    // 第二步是遍历其他表达式语句
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        if ((*pIter)->type == AST_DEF_LIST) {
            continue;
        }
        // 遍历Block的每个语句，进行显示或者运算
        struct ast_node *temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
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

static bool ir_def_list(struct ast_node *node)
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
        printf("ok\n");
        if (temp->type == AST_ARRAY) {
            bool result = ir_def_array(temp, type);
            if (!result)return false;
        } else {
            printf("%s\n", temp->attr.id);
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
    struct ast_node *func_name = node->sons[1];
    Value *val = nullptr;
    // 第二个孩子是函数名
    if (!IsExist(func_name->attr.id)) {
        // 变量名没有找到
        val = newVarValue(func_name->attr.id);
    } else {
        // 若变量名已存在，则报错重定义
        std::string error = std::string("error: redefinition of") + std::string(func_name->attr.id);
        printError(func_name->attr.lineno, error);
        return false;
    }
    func_name->val = val;
    // 第三个孩子是参数列表
    struct ast_node *func_paras = node->sons[2];
    std::vector<struct ast_node *>::iterator pIter;
    std::vector<Value *> fargs;
    for (pIter = func_paras->sons.begin(); pIter != func_paras->sons.end(); ++pIter) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        // struct ast_node *arg_name = (*pIter)->sons[1];
        // todo 暂时只考虑int类型
        Value *fargsValue = newTempValue(ValueType::ValueType_Int);
        fargs.push_back(fargsValue);
    }

    node->blockInsts.addInst(
            new FuncDefIRInst(func_name->val, fargs)
    );
    // 形参定义
    for (pIter = func_paras->sons.end() - 1; pIter != func_paras->sons.begin() - 1; --pIter) {
        // 获取参数类型
        // struct ast_node *arg_type = (*pIter)->sons[0];
        // 获取参数名
        struct ast_node *arg_name = (*pIter)->sons[1];
        Value *localVarValue = nullptr;
        // todo 暂时只考虑int类型
        localVarValue = newLocalVarValue(arg_name->attr.id, ValueType::ValueType_Int);
        arg_name->val = localVarValue;
        node->blockInsts.addInst(
            new DeclearIRInst(arg_name->val, false, true)
        );
    }
    // 返回值定义
    Value *localVarValue = nullptr;
    // todo 暂时只考虑int类型
    localVarValue = newLocalVarValue("", ValueType::ValueType_Int);
    node->blockInsts.addInst(
        new DeclearIRInst(localVarValue, false, true)
    );
    // 第四个孩子是语句块
    struct ast_node *func_block = ir_visit_ast_node(node->sons[3]);
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

    node->blockInsts.addInst(
        new ReturnIRInst(result->val)
    );

    node->val = result->val;
    return true;
}
// 产生IR显示的IR指令
static bool ir_show(struct ast_node *node, bool show)
{
    // TODO real number print

    struct ast_node *src1_node = node->sons[0];

    struct ast_node *result = ir_visit_ast_node(src1_node);
    if (!result) {
        // 解析错误
        return false;
    }

    node->blockInsts.addInst(result->blockInsts);

    if (show) {

        node->blockInsts.addInst(
            new FuncCallIRInst("printI", result->val));
    }

    node->val = nullptr;

    return true;
}

// expresion add
static bool ir_add(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, left->val, true)
            );
            left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, right->val, true)
            );
            right->val = resultValue0;
        }
        Value *resultValue = newTempValue(ValueType::ValueType_Real);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_ADD, resultValue, left->val, right->val)
        );
        node->val = resultValue;

    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令
        Value *resultValue = newTempValue(ValueType::ValueType_Int);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_ADD, resultValue, left->val, right->val));
        node->val = resultValue;
    }
    return true;
}
// expresion usb
static bool ir_sub(struct ast_node *node)
{
    // TODO real number add

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


    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, left->val, true)
            );
            left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, right->val, true)
            );
            right->val = resultValue0;
        }
        Value *resultValue = newTempValue(ValueType::ValueType_Real);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_SUB, resultValue, left->val, right->val)
        );
        node->val = resultValue;

    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令
        Value *resultValue = newTempValue(ValueType::ValueType_Int);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_SUB, resultValue, left->val, right->val));
        node->val = resultValue;
    }
    return true;
}
// expresion mod
static bool ir_mod(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, left->val, true)
            );
            left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, right->val, true)
            );
            right->val = resultValue0;
        }
        char *error = "错了错了,'%' 运算必须是int";
        error = "error: invalid operands to binary % (must 'int' and 'int')";
        printf("%s\n", error);
        return false;
    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令
        Value *resultValue = newTempValue(ValueType::ValueType_Int);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_MOD, resultValue, left->val, right->val));
        node->val = resultValue;
    }
    return true;
}

// expresion multiply
static bool ir_mul(struct ast_node *node)
{
    // TODO real number mul

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, left->val, true)
            );
            left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, right->val, true)
            );
            right->val = resultValue0;
        }
        Value *resultValue = newTempValue(ValueType::ValueType_Real);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_MUL, resultValue, left->val, right->val)
        );
        node->val = resultValue;

    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令
        Value *resultValue = newTempValue(ValueType::ValueType_Int);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_MUL, resultValue, left->val, right->val));
        node->val = resultValue;
    }

    return true;
}
// expresion divide
static bool ir_div(struct ast_node *node)
{
    // TODO real number mul

    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    Value *leftValue = left->val;
    Value *rightValue = right->val;
    // 先把左右孩子操作数添加进去，在添加当前节点的操作数
    // 后序遍历
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    if ((leftValue->type == ValueType::ValueType_Real) or (rightValue->type == ValueType::ValueType_Real)) {
        // 处理实数类型的指令
        // 创建临时变量保存IR的值，以及线性IR指令

        // 判断是否需要类型转换
        if (leftValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, left->val, true)
            );
            left->val = resultValue0;
        }
        if (rightValue->type == ValueType::ValueType_Int) {
            Value *resultValue0 = newTempValue(ValueType::ValueType_Real);
            node->blockInsts.addInst(
            new TypeCovIRInst(resultValue0, right->val, true)
            );
            right->val = resultValue0;
        }
        Value *resultValue = newTempValue(ValueType::ValueType_Real);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_DIV, resultValue, left->val, right->val)
        );
        node->val = resultValue;

    } else {
        // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
        // 创建临时变量保存IR的值，以及线性IR指令
        Value *resultValue = newTempValue(ValueType::ValueType_Int);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_DIV, resultValue, left->val, right->val));
        node->val = resultValue;
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
    struct ast_node *left = ir_visit_ast_node(son1_node);
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
    /*   新增  */
    // 左值类型与右值类型相同
    // 加上这行代码才能判断是否要进行类型转换
    left->val->type = right->val->type;

    node->blockInsts.addInst(
        new AssignIRInst(left->val, right->val));
    node->val = left->val;

    return true;
}

static bool ir_leaf_node(struct ast_node *node)
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

// 递归遍历抽象语法树进行计算
static struct ast_node *ir_visit_ast_node(struct ast_node *node)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result = true;

    switch (node->type) {
    case AST_OP_NULL:
        // 叶子节点
        result = ir_leaf_node(node);
        break;

    case AST_OP_MUL:
        // 乘法节点
        result = ir_mul(node);
        break;

    case AST_OP_ADD:
        // 加法节点
        result = ir_add(node);
        break;
    case AST_OP_SUB:
        // 乘法节点
        result = ir_sub(node);
        break;

    case AST_OP_DIV:
        // 加法节点
        result = ir_div(node);
        break;
    case AST_OP_MOD:
        // 加法节点
        result = ir_mod(node);
        break;
    case AST_OP_EXPR:

        // 表达式结点，不显示表达式的值
        // 由于不显示值，并且不支持赋值操作，都是右值操作，这里什么都不做
        result = ir_show(node, false);
        break;

    case AST_OP_EXPR_SHOW:

        // 表达式结点，显示表达式的值
        result = ir_show(node, true);
        break;

    case AST_OP_ASSIGN:

        // 赋值语句
        result = ir_assign(node);
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
        printf("AST_DEF_LIST\n");
        // 变量定义
        result = ir_def_list(node);
        break;
    case AST_FUNC_DEF:
        // printf("AST_DEF_array\n");
        // 数组定义
        result = ir_def_func(node);
        break;
    case AST_RETURN:
        // printf("AST_DEF_array\n");
        // 数组定义
        result = ir_return(node);
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
        return false;
    }

    IRCode.addInst(root->blockInsts);

    return true;
}
