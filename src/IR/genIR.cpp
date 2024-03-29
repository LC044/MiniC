/**
* @file
* @brief		生成中间IR
* @author		shuaikangzhou
* @date		    2023/06/18
* @details
*/


#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
#include <stack>
static bool WhileBlock = false;
extern bool ExitLabel;
static int IFflag = 0;
int dimFlag = 0;
std::string ArrName;
std::stack<std::string> Bc1Labels;
std::stack<std::string> Bc2Labels;
std::stack<std::string> Breaklabels;
std::stack<std::string> ContinueLabels;
extern std::string FuncName;
extern SymbolTable *symbolTable;
extern InterCode *Basic_block_division(InterCode *blockInsts);
static struct ast_node *ir_visit_ast_node(struct ast_node *node, bool isLeft = false);
static bool ir_leaf_node(struct ast_node *node, bool isLeft = false);
static bool ir_def_array(struct ast_node *node, ValueType type = ValueType::ValueType_Int, bool isLocal = false);
// 这个也废弃了
static bool isJump(struct ast_node *node)
{
    switch (node->type) {
    case AST_OP_IF:
        return true;
    case AST_OP_WHILE:
        return true;
    default:
        return false;
    }
}
// 从抽象语法树的根开始遍历，然后输出计算出表达式的值
static bool ir_cu(struct ast_node *node)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一步遍历全局变量符号表
    for (int i = 0; i < symbolTable->varsName.size(); ++i) {
        Value *val;
        val = symbolTable->varsMap[symbolTable->varsName[i]];
        node->blockInsts.addInst(
            new DeclearIRInst(val, true, true)
        );
    }
    // 第二步遍历函数表
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
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
    LocalVarTable *localVarTable = new LocalVarTable();

    FuncSymbol *funcSymbol = symbolTable->findFuncValue(FuncName);
    if (funcSymbol->currentScope == -1) {

    } else {
        funcSymbol->tempStack.push(localVarTable);
    }
    funcSymbol->currentScope++;
    // printf("函数%s 作用域 %d\n", FuncName.c_str(), funcSymbol->currentScope)
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {
        // 判断是否有局部变量定义
        struct ast_node *temp;
        temp = ir_visit_ast_node(*pIter, true);
        if (!temp) {
            continue;
        }
        node->blockInsts.addInst(temp->blockInsts);
        if (temp->type == AST_RETURN) {
            break;
        }
    }
    funcSymbol->tempStack.pop(funcSymbol->currentScope);
    funcSymbol->currentScope--;
    return true;
}
// 数组定义
static bool ir_def_array(struct ast_node *node, ValueType type, bool isLocal)
{
    Value *val = nullptr;
    // 第一个孩子是标识符
    struct ast_node *temp_id = node->sons[0];
    if (isLocal) {
        // 局部变量
        // val = symbolTable->findValue(temp_id->attr.id, FuncName, false);
        FuncSymbol *sym = symbolTable->findFuncValue(FuncName);
        val = sym->localVarsMap[sym->localVarsName[sym->currentLocal++]];
        symbolTable->addValue(temp_id->attr.id, val, FuncName, true);
    }
    return true;
}
// 变量定义
static bool ir_def_list(struct ast_node *node, bool isLocal)
{
    std::vector<struct ast_node *>::iterator pIter;
    // 第一个孩子节点是变量类型
    struct ast_node *temp_type = node->sons[0];
    ValueType type;
    // todo 暂时只考虑int型变量
    if (strcmp(temp_type->attr.id, "int") == 0) {
        type = ValueType::ValueType_Int;
    }

    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        Value *val = nullptr;
        struct ast_node *temp = *pIter;
        if (temp->type == AST_ARRAY) {
            bool result = ir_def_array(temp, type, isLocal);
            if (!result)return false;
        } else {
            // val = symbolTable->findValue(temp->attr.id, FuncName, false);
            FuncSymbol *sym = symbolTable->findFuncValue(FuncName);
            val = sym->localVarsMap[sym->localVarsName[sym->currentLocal++]];
            // val = 
            symbolTable->addValue(temp->attr.id, val, FuncName, true);
        }
    }
    return true;
}
// 函数定义IR
static bool ir_def_func(struct ast_node *node)
{
    struct ast_node *func_type = node->sons[0];

    // 第二个孩子是函数名
    struct ast_node *func_name = node->sons[1];
    struct ast_node *func_paras = node->sons[2];
    FuncName = func_name->attr.id;
    FuncSymbol *FuncVal = symbolTable->funcsMap[FuncName];
    func_name->val = FuncVal;
    if (is_buildIn_func(FuncName)) {
        return true;
    }
    LocalVarTable *localVarTable = new LocalVarTable();
    FuncVal->tempStack.push(localVarTable);
    FuncVal->currentScope = 0;
    FuncVal->currentLocal = 0;
    // 第一个孩子是函数返回类型
    ValueType type;
    Value *returnValue;
    if (strcmp(func_type->attr.id, "int") == 0) {
        type = ValueType::ValueType_Int;
        returnValue = FuncVal->stack.search("return", 0);
        int return_index = func_paras->sons.size();
        returnValue = FuncVal->localVarsMap[FuncVal->localVarsName[return_index]];
        FuncVal->addValue(returnValue, "return", true);
        FuncVal->currentLocal++;
    } else if (strcmp(func_type->attr.id, "void") == 0) {
        type = ValueType::ValueType_Void;
    }
    if (node->sons[3]->type == AST_EMPTY) {
        return true;
    }

    printf("Function: %s\n", FuncVal->getName().c_str());
    node->blockInsts.addInst(
        new FuncDefIRInst(FuncVal, type)
    );
    // 形参定义
    // 第三个孩子是参数列表

    std::vector<struct ast_node *>::iterator pIter;
    int i = 0;

    for (pIter = func_paras->sons.end() - 1; pIter != func_paras->sons.begin() - 1; --pIter, i++) {
        struct ast_node *arg_name = (*pIter)->sons[1];
        // Value *resultValue = nullptr;
        if (arg_name->type == AST_ARRAY) {
            // resultValue = symbolTable->findValue(arg_name->sons[0]->attr.id, FuncName, false);
            symbolTable->addValue(arg_name->sons[0]->attr.id, arg_name->val, FuncName, true);
        } else {
            // resultValue = symbolTable->findValue(arg_name->attr.id, FuncName, false);
            // printf("参数名%s:%s\n", arg_name->attr.id, arg_name->val->getName().c_str());
            symbolTable->addValue(arg_name->attr.id, arg_name->val, FuncName, true);
        }
        FuncVal->currentLocal++;
    }
    // printf("进入语句块\n");
    // 第四个孩子是语句块
    FuncVal->currentScope = -1;
    struct ast_node *func_block = ir_visit_ast_node(node->sons[3]);
    InterCode *blockInsts = new InterCode();
    // 形参赋值给局部变量
    for (int i = 0; i < FuncVal->fargs.size(); ++i) {
        Value *srcValue = nullptr;
        srcValue = FuncVal->tempVarsMap[FuncVal->tempVarsName[i]];
        Value *resultValue = nullptr;
        resultValue = FuncVal->localVarsMap[FuncVal->localVarsName[i]];
        blockInsts->addInst(
            new AssignIRInst(resultValue, srcValue)
        );
    }
    // printf("形参复制给临时变量结束\n");
    blockInsts->addInst(func_block->blockInsts);
    // printf("指令长度：%d\n", blockInsts->getCodeSize());
    // 如果if里有return语句则在exit这里加个label
    if (ExitLabel) {
        blockInsts->addInst(
            new JumpIRInst(IRINST_JUMP_BR, ".L2")
        );
        blockInsts->addInst(
            new UselessIRInst(".L2:")
        );
    }
    ExitLabel = false;
    // 退出语句 exit 
    FuncVal->currentScope = 0;
    if (strcmp(func_type->attr.id, "int") == 0) {
        Value *srcValue = nullptr;
        srcValue = newTempValue(ValueType::ValueType_Int, FuncName);
        blockInsts->addInst(
            new AssignIRInst(srcValue, returnValue)
        );
        blockInsts->addInst(
            new UnaryIRInst(IRINST_OP_RETURN, srcValue, srcValue)
        );
    } else {
        // printf("%s 无返回值\n", func_name->attr.id);
        blockInsts->addInst(
            new UnaryIRInst(IRINST_OP_RETURN)
        );
    }
    // 添加局部变量定义IR指令
    // printf("函数局部变量个数:%d\n", FuncVal->localVarsName.size());
    for (int i = 0; i < FuncVal->localVarsName.size(); ++i) {
        Value *localVarValue = nullptr;
        localVarValue = FuncVal->localVarsMap[FuncVal->localVarsName[i]];
        node->blockInsts.addInst(
            new DeclearIRInst(localVarValue, false, true)
        );
    }
    // 添加临时变量定义IR指令
    // printf("函数临时变量个数:%d\n", FuncVal->tempVarsName.size());
    for (int i = FuncVal->fargs.size(); i < FuncVal->tempVarsName.size(); ++i) {
        Value *localVarValue = nullptr;
        localVarValue = FuncVal->tempVarsMap[FuncVal->tempVarsName[i]];
        node->blockInsts.addInst(
            new DeclearIRInst(localVarValue, false, true, true)
        );
    }
    // 函数进入IR指令
    node->blockInsts.addInst(
        new UselessIRInst("    entry")
    );
    // printf("指令长度：%d\n", blockInsts->getCodeSize());
    // node->blockInsts.addInst(*blockInsts);
    InterCode *BlockInsts = Basic_block_division(blockInsts);
    node->blockInsts.addInst(*BlockInsts);
    node->blockInsts.addInst(
        new UselessIRInst("}")
    );
    // printf("函数%s结束\n", FuncName.c_str());
    return true;
}
// return IR
static bool ir_return(struct ast_node *node)
{
    // 没有返回值

    if (node->sons.size() == 0) {
        if (IFflag) {
            node->blockInsts.addInst(
                new JumpIRInst(IRINST_JUMP_BR, ".L2")
            );
            ExitLabel = true;
        }
        return true;
    }
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *result = ir_visit_ast_node(src1_node);
    if (!result) {
        // 解析错误
        return false;
    }
    node->blockInsts.addInst(result->blockInsts);
    Value *returnValue = symbolTable->findValue("return", FuncName, true);
    // printf("return 语句 %s \n", returnValue->getName().c_str());
    node->blockInsts.addInst(
            new AssignIRInst(returnValue, result->val)
    );
    if (IFflag) {
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BR, ".L2")
        );
        ExitLabel = true;
    }
    // return语句不应该放在return里面，应该放在函数定义的结尾
    return true;
}
// 函数调用
static bool ir_func_call(struct ast_node *node, bool isLeft)
{
    // 第一个节点是函数名
    struct ast_node *son1_node = node->sons[0];
    struct ast_node *left = ir_visit_ast_node(son1_node, true);
    if (!left) {
        return false;
    }
    // printf("函数调用指令\n");
    // 这里应该先判断一下参数个数是否匹配
    if (node->sons.size() == 2) {
        std::vector<struct ast_node *>::iterator pIter;
        // 第一步首先将变量实参复制给临时变量
        for (pIter = node->sons[1]->sons.begin(); pIter != node->sons[1]->sons.end(); ++pIter) {
            struct ast_node *temp = ir_visit_ast_node(*pIter);
            node->blockInsts.addInst(temp->blockInsts);
        }
        std::vector<Value *> _srcVal;
        // 第二步将实参加入参数列表
        for (pIter = node->sons[1]->sons.begin(); pIter != node->sons[1]->sons.end(); ++pIter) {
            // struct ast_node *temp = ir_visit_ast_node(*pIter);
            _srcVal.push_back((*pIter)->val);
        }
        if (isLeft) {
            // 无返回值函数调用
            node->blockInsts.addInst(
            new FuncCallIRInst(left->attr.id, _srcVal, true)
            );
        } else {
            // 有返回值函数调用
            Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
            node->blockInsts.addInst(
            new FuncCallIRInst(left->attr.id, _srcVal, true, val)
            );
            node->val = val;
        }
    } else {
        // 无参函数调用
        if (isLeft) {
            node->blockInsts.addInst(
            new FuncCallIRInst(left->attr.id)
            );
        } else {
            Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
            node->blockInsts.addInst(
            new FuncCallIRInst(left->attr.id, val)
            );
            node->val = val;
        }
    }
    return true;
}
// 二元运算 + - * / %
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
        node->val = resultValue;
    } else {
        resultValue = newTempValue(ValueType::ValueType_Int, FuncName);
        node->val = resultValue;
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
// 自增自减
static bool ir_inc_dec(struct ast_node *node, enum ast_operator_type type, bool isLeft)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *left = ir_visit_ast_node(src1_node, true);
    if (!left) {
        return false;
    }
    node->blockInsts.addInst(left->blockInsts);
    Value *ConstVal = newConstValue(1);
    Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
    switch (type) {
    case AST_OP_LINC: {
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_ADD, val, left->val, ConstVal)
        );
        node->blockInsts.addInst(
            new AssignIRInst(left->val, val)
        );
        node->val = left->val;
        break;}
    case AST_OP_RINC: {
        node->blockInsts.addInst(
            new AssignIRInst(val, left->val)
        );
        Value *tempval = newTempValue(ValueType::ValueType_Int, FuncName);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_ADD, tempval, left->val, ConstVal)
        );
        node->blockInsts.addInst(
            new AssignIRInst(left->val, tempval)
        );
        node->val = val;
        break;}
    case AST_OP_LDEC: {
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_SUB, val, left->val, ConstVal)
        );
        node->blockInsts.addInst(
            new AssignIRInst(left->val, val)
        );
        node->val = left->val;
        break;}
    case AST_OP_RDEC: {
        node->blockInsts.addInst(
            new AssignIRInst(val, left->val)
        );
        Value *tempval = newTempValue(ValueType::ValueType_Int, FuncName);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_SUB, tempval, left->val, ConstVal)
        );
        node->blockInsts.addInst(
            new AssignIRInst(left->val, tempval)
        );
        node->val = val;
        break;}
    default:
        break;
    }
    return true;
}
// 取负运算
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
    if (!(left->val->isConst or left->val->type == ValueType::ValueType_Bool)) {
        Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
        node->blockInsts.addInst(
        new UnaryIRInst(IRINST_OP_NEG, val, left->val));
        node->val = val;
    } else {
        node->val = left->val;
        node->val->intVal = -node->val->intVal;
    }
    return true;
}
// 数组索引的维度处理
// 应该是废弃了
static bool ir_dimensions(struct ast_node *node, bool isSecond)
{

    if (isSecond) {
        dimFlag++;
        if (node->sons.size() > 1) {
            struct ast_node *src1_node = node->sons[0];
            struct ast_node *left = ir_visit_ast_node(src1_node, isSecond);
            node->blockInsts.addInst(left->blockInsts);
            Value *val = findValue(ArrName, FuncName, true);
            int dim = val->dims[val->dim - dimFlag + 1];
            if (dimFlag == 1) {
                dim = 4;
            }
            if (node->sons[0]->val->isConst and node->sons[1]->val->isConst) {
                node->val->intVal = (node->sons[0]->val->intVal + node->sons[1]->val->intVal) * dim;

            } else {
                Value *offsetVal = newConstValue(dim);
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_ADD, node->sons[2]->val, node->sons[0]->val, node->sons[1]->val)
                );
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_MUL, node->val, node->sons[2]->val, offsetVal)
                );
            }

        } else {
            Value *val = findValue(ArrName, FuncName, true);
            int dim = val->dims[val->dim - dimFlag + 1];
            if (dimFlag == 1) {
                dim = 4;
            }
            if (node->sons[0]->val->isConst) {
                node->val->intVal *= dim;
            } else {

                Value *offsetVal = newConstValue(dim);
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_MUL, node->val, node->sons[0]->val, offsetVal)
                );
            }
        }
        dimFlag--;
    } else {
        if (node->sons.size() > 1) {
            struct ast_node *src1_node = node->sons[0];
            struct ast_node *left = ir_visit_ast_node(src1_node, isSecond);
            struct ast_node *src2_node = node->sons[1];
            struct ast_node *right = ir_visit_ast_node(src2_node);
            node->blockInsts.addInst(left->blockInsts);
            node->blockInsts.addInst(right->blockInsts);
        } else {
            struct ast_node *src1_node = node->sons[0];
            struct ast_node *left = ir_visit_ast_node(src1_node);
            node->blockInsts.addInst(left->blockInsts);
        }
    }
    return true;
}
// 数组引用
static bool ir_index(struct ast_node *node, bool isLeft)
{
    // 数组索引第一个孩子节点是变量名
    // printf("数组索引\n");
    struct ast_node *src1_node = node->sons[0];
    // struct ast_node *src2_node = node->sons[1];
    struct ast_node *array_name = src1_node;
    ArrName = array_name->attr.id;
    Value *ArrVal = findValue(ArrName, FuncName, true);
    std::vector<struct ast_node *>::iterator pIter;
    for (pIter = node->sons.begin() + 1; pIter != node->sons.end(); ++pIter) {
        struct ast_node *temp;
        temp = ir_visit_ast_node(*pIter, false);
        if (!temp) {
            continue;
        }
        node->blockInsts.addInst(temp->blockInsts);
    }
    Value *Resultval1 = node->sons[1]->val;
    // 变量名起的有点乱
    // int a[3][5][7];
    // a[i][j][k] = 3;
    // 拿演草纸自己推导一下就知道了
    if (node->sons.size() > 2) {
        int i = 0;
        for (pIter = node->sons.begin() + 1; pIter != node->sons.end() - 1; ++pIter, ++i) {
            struct ast_node *temp1 = *(pIter);
            struct ast_node *temp2 = *(pIter + 1);
            int dim = ArrVal->dims[i + 1];
            // printf("数组维度: %d\n", dim);
            if (temp1->val->isConst and temp2->val->isConst) {
                temp2->val->intVal = (temp1->val->intVal * dim + temp2->val->intVal);
                Resultval1 = temp2->val;
            } else {
                Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
                Value *offsetVal = newConstValue(dim);
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_MUL, val, temp1->val, offsetVal)
                );
                Resultval1 = newTempValue(ValueType::ValueType_Int, FuncName);
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_ADD, Resultval1, val, temp2->val)
                );
                temp2->val = Resultval1;
            }
        }
    } else {
    }

    Value *Resultval3;
    int dim = 4;
    if (Resultval1->isConst) {
        Resultval3 = newConstValue(Resultval1->intVal * dim);
    } else {
        Resultval3 = newTempValue(ValueType::ValueType_Int, FuncName);
        Value *offsetVal = newConstValue(dim);
        node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_MUL, Resultval3, Resultval1, offsetVal)
        );
    }

    Value *Resultval2 = newTempValue(ValueType::ValueType_Int_ptr, FuncName);
    node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_ADD, Resultval2, ArrVal, Resultval3)
    );
    node->val = Resultval2;
    // newTempValue(ValueType::ValueType_Int, FuncName);
    if (!isLeft) {
        if (node->sons.size() - 1 < ArrVal->dim) {
            // b[2][100];
            // a = b[2];
        } else {
            // 数组索引做右值，要先赋值给临时变量
            // a = b[0] + 1;
            Value *val = newTempValue(ValueType::ValueType_Int, FuncName);
            node->blockInsts.addInst(
            new AssignIRInst(val, Resultval2)
            );
            node->val = val;
        }

    } else {
        // newTempValue(ValueType::ValueType_Int, FuncName);
    }
    return true;
}
// 赋值操作
static bool ir_assign(struct ast_node *node)
{
    // TODO real number add

    struct ast_node *son1_node = node->sons[0];
    struct ast_node *son2_node = node->sons[1];

    // 赋值运算符的右侧操作数

    // 赋值运算符的左侧操作数
    struct ast_node *left = ir_visit_ast_node(son1_node, true);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }
    struct ast_node *right = ir_visit_ast_node(son2_node, false);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    // 创建临时变量保存IR的值，以及线性IR指令
    // 赋值节点，自右往左运算
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);

    Value *leftValue = left->val, *rightValue = right->val;
    node->blockInsts.addInst(
        new AssignIRInst(leftValue, rightValue)
    );
    return true;
}
// 关系运算
static bool ir_cmp(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[2];
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);

    Value *val = newTempValue(ValueType::ValueType_Bool, FuncName);
    node->val = val;
    // 比较运算符
    struct ast_node *cmp_node = node->sons[1];
    node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, cmp_node->attr.id, node->val, left->val, right->val)
    );
    // printf("cmp指令0\n");
    node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, node->val, Bc1Labels.top(), Bc2Labels.top())
    );
    // printf("cmp指1\n");
    return true;
}
// if语句
static bool ir_if(struct ast_node *node)
{
    // if 有三个孩子节点，比较运算、true代码块、false代码块(false可能不存在)
    IFflag++;
    std::string label1 = newLabel(FuncName);  // true语句
    std::string label2 = newLabel(FuncName);  // false语句
    std::string label3 = newLabel(FuncName);  // 下一条语句
    if (node->sons.size() == 3) {
        Bc1Labels.push(label1);
        Bc2Labels.push(label2);
    } else {
        Bc1Labels.push(label1);
        Bc2Labels.push(label3);
    }
    // printf("%s,%s,%s\n", label1.c_str(), label2.c_str(), label3.c_str());
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    struct ast_node *cond = ir_visit_ast_node(src1_node);
    if (!cond) {
        return false;
    }
    node->blockInsts.addInst(cond->blockInsts);
    if (src1_node->type == AST_OP_AND || src1_node->type == AST_OP_OR || src1_node->type == AST_OP_CMP || src1_node->type == AST_OP_NOT) {
    } else {
        if (src1_node->val->isId) {
            Value *val = findValue(src1_node->attr.id, FuncName, true);
            Value *dstVal = src1_node->val;
            node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
            );
        }
        if (src1_node->val->type == ValueType::ValueType_Bool) {

        } else {
            Value *val = newTempValue(ValueType::ValueType_Bool, FuncName);

            Value *constVal = newConstValue(0);
            node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_CMP, "ne", val, cond->val, constVal)
            );
            // printf("cmp指令0\n");
            node->blockInsts.addInst(
                    new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
            );
            node->val = val;
        }

    }

    if (node->sons.size() == 3) {
        struct ast_node *src3_node = node->sons[2];
        struct ast_node *true_node = ir_visit_ast_node(src2_node, true);
        struct ast_node *false_node = ir_visit_ast_node(src3_node, true);
        // printf("if 语句结束\n");
        if (true_node->type != AST_EMPTY and false_node->type != AST_EMPTY) {
            if (true_node->newLabel) {
                node->blockInsts.addInst(
                        new UselessIRInst(label1 + ":")
                );
            }

            node->blockInsts.addInst(true_node->blockInsts);
            if (true_node->jump) {
                node->blockInsts.addInst(
                        new JumpIRInst(IRINST_JUMP_BR, label3)
                );
            }
            // printf("if 语句结束1\n");
            if (false_node->newLabel) {
                node->blockInsts.addInst(
                new UselessIRInst(label2 + ":")
                );
            }
            node->blockInsts.addInst(false_node->blockInsts);
            if (false_node->jump) {
                node->blockInsts.addInst(
                        new JumpIRInst(IRINST_JUMP_BR, label3)
                );
            }
            // printf("if 语句结束2\n");
        } else if (true_node->type != AST_EMPTY and false_node->type == AST_EMPTY) {

        }
    } else {
        struct ast_node *true_node = ir_visit_ast_node(src2_node, true);
        node->blockInsts.addInst(
                new UselessIRInst(label1 + ":")
        );
        node->blockInsts.addInst(true_node->blockInsts);
        if (true_node->jump) {
            node->blockInsts.addInst(
                    new JumpIRInst(IRINST_JUMP_BR, label3)
            );
        }
    }
    node->blockInsts.addInst(
        new UselessIRInst(label3 + ":")
    );
    Bc1Labels.pop();
    Bc2Labels.pop();
    IFflag--;
    return true;
}
// while语句
static bool ir_while(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    WhileBlock = true;
    IFflag++;
    std::string label1 = newLabel(FuncName);  // 条件语句
    std::string label2 = newLabel(FuncName);  // true语句
    std::string label3 = newLabel(FuncName);  // 下一条语句
    Bc1Labels.push(label2);
    Bc2Labels.push(label3);
    Breaklabels.push(label3);
    ContinueLabels.push(label1);
    // printf("while ir 0");
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    // printf("while ir 0.5\n");
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }
    // printf("while ir 1\n");
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, label1)
    );
    node->blockInsts.addInst(
        new UselessIRInst(label1 + ":")
    );
    node->blockInsts.addInst(left->blockInsts);
    if (src1_node->type == AST_OP_AND || src1_node->type == AST_OP_OR || src1_node->type == AST_OP_CMP || src1_node->type == AST_OP_NOT) {
    } else {
        if (src1_node->val->isId) {
            Value *val = findValue(src1_node->attr.id, FuncName, true);
            Value *dstVal = src1_node->val;
            node->blockInsts.addInst(
                new AssignIRInst(dstVal, val)
            );
        }
        if (src1_node->val->type == ValueType::ValueType_Bool) {

        } else {
            Value *val = newTempValue(ValueType::ValueType_Bool, FuncName);

            Value *constVal = newConstValue(0);
            node->blockInsts.addInst(
            new BinaryIRInst(IRINST_OP_CMP, "ne", val, left->val, constVal)
            );
            // printf("cmp指令0\n");
            node->blockInsts.addInst(
                    new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
            );
            node->val = val;
        }

    }
    node->blockInsts.addInst(
        new UselessIRInst(label2 + ":")
    );
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, label1)
    );
    node->blockInsts.addInst(
        new UselessIRInst(label3 + ":")
    );
    Bc1Labels.pop();
    Bc2Labels.pop();
    Breaklabels.pop();
    ContinueLabels.pop();
    WhileBlock = false;
    IFflag--;
    return true;
}
// for语句
static bool ir_for(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    struct ast_node *src3_node = node->sons[2];
    struct ast_node *src4_node = node->sons[3];
    WhileBlock = true;
    std::string label1 = newLabel(FuncName);  // 条件语句
    std::string label2 = newLabel(FuncName);  // true语句
    std::string label3 = newLabel(FuncName);  // 下一条语句
    Bc1Labels.push(label2);
    Bc2Labels.push(label3);
    Breaklabels.push(label3);
    ContinueLabels.push(label1);
    struct ast_node *init_node = ir_visit_ast_node(src1_node);
    if (!init_node) {
        return false;
    }
    node->blockInsts.addInst(init_node->blockInsts);

    struct ast_node *cond = ir_visit_ast_node(src2_node);
    if (!cond) {
        return false;
    }
    struct ast_node *expr3 = ir_visit_ast_node(src3_node);
    struct ast_node *block_node = ir_visit_ast_node(src4_node);
    if (!block_node) {
        return false;
    }
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, label1)
    );
    node->blockInsts.addInst(
        new UselessIRInst(label1 + ":")
    );
    node->blockInsts.addInst(cond->blockInsts);
    if (!(cond->val->type == ValueType::ValueType_Bool)) {
        Value *val = nullptr;
        val = newTempValue(ValueType::ValueType_Bool, FuncName);
        Value *constVal = newConstValue(0);
        node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, "ne", val, cond->val, constVal)
        );
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
        );
        node->val = val;
    }
    node->blockInsts.addInst(
        new UselessIRInst(label2 + ":")
    );
    node->blockInsts.addInst(block_node->blockInsts);
    node->blockInsts.addInst(expr3->blockInsts);
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, label1)
    );
    node->blockInsts.addInst(
        new UselessIRInst(label3 + ":")
    );
    Bc1Labels.pop();
    Bc2Labels.pop();
    Breaklabels.pop();
    ContinueLabels.pop();
    WhileBlock = false;
    return true;
}
// break语句
static bool ir_break(struct ast_node *node)
{
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, Breaklabels.top())
    );
    return true;
}
// continue语句
static bool ir_continue(struct ast_node *node)
{
    node->blockInsts.addInst(
        new JumpIRInst(IRINST_JUMP_BR, ContinueLabels.top())
    );
    return true;
}
// 逻辑运算 ||
static bool ir_or(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    std::string label1 = newLabel(FuncName);  // true语句
    Bc2Labels.push(label1);
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    node->val = left->val;
    Bc2Labels.pop();
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }
    node->blockInsts.addInst(left->blockInsts);
    if (!(left->val->type == ValueType::ValueType_Bool)) {
        Value *val = nullptr;
        val = newTempValue(ValueType::ValueType_Bool, FuncName);
        Value *constVal = newConstValue(0);
        node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, "ne", val, left->val, constVal)
        );
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
        );
        node->val = val;
    }
    node->blockInsts.addInst(
            new UselessIRInst(label1 + ":")
    );
    node->blockInsts.addInst(right->blockInsts);
    if (!(right->val->type == ValueType::ValueType_Bool)) {
        Value *val = nullptr;
        val = newTempValue(ValueType::ValueType_Bool, FuncName);
        Value *constVal = newConstValue(0);
        node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, "ne", val, right->val, constVal)
        );
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
        );
        node->val = val;
    }
    return true;
}
// 逻辑运算 &&
static bool ir_and(struct ast_node *node)
{
    struct ast_node *src1_node = node->sons[0];
    struct ast_node *src2_node = node->sons[1];
    std::string label1 = newLabel(FuncName);  // true语句
    Bc1Labels.push(label1);

    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    node->val = left->val;
    Bc1Labels.pop();
    struct ast_node *right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    node->blockInsts.addInst(left->blockInsts);
    if (!(left->val->type == ValueType::ValueType_Bool)) {
        Value *val = nullptr;
        val = newTempValue(ValueType::ValueType_Bool, FuncName);
        Value *constVal = newConstValue(0);
        node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, "ne", val, left->val, constVal)
        );
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
        );
        node->val = val;
    }
    node->blockInsts.addInst(
            new UselessIRInst(label1 + ":")
    );
    node->blockInsts.addInst(right->blockInsts);
    if (!(right->val->type == ValueType::ValueType_Bool)) {
        Value *val = nullptr;
        val = newTempValue(ValueType::ValueType_Bool, FuncName);
        Value *constVal = newConstValue(0);
        node->blockInsts.addInst(
        new BinaryIRInst(IRINST_OP_CMP, "ne", val, right->val, constVal)
        );
        node->blockInsts.addInst(
            new JumpIRInst(IRINST_JUMP_BC, val, Bc1Labels.top(), Bc2Labels.top())
        );
        node->val = val;
    }
    return true;
}
// 逻辑非运算
static bool ir_not(struct ast_node *node, bool isLeft)
{
    struct ast_node *src1_node = node->sons[0];
    // std::
    std::string label1 = Bc1Labels.top();
    Bc1Labels.pop();
    std::string label2 = Bc2Labels.top();
    Bc2Labels.pop();
    Bc1Labels.push(label2);
    Bc2Labels.push(label1);
    struct ast_node *left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }
    node->blockInsts.addInst(left->blockInsts);

    if (isLeft) {

    } else {
        if (left->val->isConst) {
        } else {
            if (left->val->type == ValueType::ValueType_Bool) {
                node->val = left->val;
            } else {
                Value *val = newTempValue(ValueType::ValueType_Bool, FuncName);
                node->val = val;
                Value *constVal = newConstValue(0);
                node->blockInsts.addInst(
                    new BinaryIRInst(IRINST_OP_CMP, "ne", node->val, left->val, constVal)
                );
                printf("cmp指令0\n");
                node->blockInsts.addInst(
                        new JumpIRInst(IRINST_JUMP_BC, node->val, Bc1Labels.top(), Bc2Labels.top())
                );

            }

        }
    }
    label1 = Bc1Labels.top();
    Bc1Labels.pop();
    label2 = Bc2Labels.top();
    Bc2Labels.pop();
    Bc1Labels.push(label2);
    Bc2Labels.push(label1);
    return true;
}
// 叶子节点
static bool ir_leaf_node(struct ast_node *node, bool isLeft)
{
    Value *val = nullptr;
    if (node->attr.kind == DIGIT_KIND_ID) {
        // 变量，则需要在符号表中查找对应的值
        val = findValue(node->attr.id, FuncName, true);
        if (!val) {
            printf("Line(%d) Variable(%s) not defined\n",
                   node->attr.lineno,
                   node->attr.id);
            return false;
        }
        node->val = val;
        // printf("找到变量:%s %s\n", val->getName().c_str(), val->id_name.c_str());
        if (!isLeft) {
            if (val->dim > 0 or val->dims[0] != 0) {
                // 数组符号做右值
                // a[5];
                // b = sort(a);
                // 变量做右值需要先复制给临时变量
                Value *dstVal = newTempValue(ValueType::ValueType_Int_ptr, FuncName);
                node->blockInsts.addInst(
                        new AssignIRInst(dstVal, val, true)
                );
                node->val = dstVal;
            } else {
                // 变量做右值需要先复制给临时变量
                Value *dstVal = newTempValue(ValueType::ValueType_Int, FuncName);
                node->blockInsts.addInst(
                        new AssignIRInst(dstVal, val)
                );
                node->val = dstVal;
            }

        }
    } else if (node->attr.kind == DIGIT_KIND_INT) {
        // 新建一个整数常量Value
        val = newConstValue(node->attr.integer_val);
        node->val = val;
    } else {
        // 新建一个实数型常量Value
        val = newConstValue(node->attr.real_val);
        node->val = val;
    }

    return true;
}
static struct ast_node *ir_visit_ast_node(struct ast_node *node, bool isLeft)
{
    // 非法节点
    if (nullptr == node) {
        return nullptr;
    }
    // if (node->type != AST_DIMS) {
    //     if (!node->visited) {
    //         node->visited = true;
    //     } else {
    //         return nullptr;
    //     }
    // }

    bool result = true;

    switch (node->type) {
    case AST_OP_NULL:
        // 叶子节点
        result = ir_leaf_node(node, isLeft);
        break;
    case AST_OP_BREAK:
        result = ir_break(node);
        break;
    case AST_OP_CONTINUE:
        result = ir_continue(node);
        break;
    case AST_EMPTY:
        result = true;
        break;
    case AST_DIMS:
        result = ir_dimensions(node, isLeft);
        break;
    case AST_OP_INDEX:
        result = ir_index(node, isLeft);
        break;
    case AST_FUNC_CALL:
        result = ir_func_call(node, isLeft);
        break;
    case AST_OP_MUL:
    case AST_OP_ADD:
    case AST_OP_SUB:
    case AST_OP_DIV:
    case AST_OP_MOD:
        result = ir_binary_op(node, node->type);
        break;
    case AST_OP_LINC:
    case AST_OP_LDEC:
    case AST_OP_RDEC:
    case AST_OP_RINC:
        result = ir_inc_dec(node, node->type, isLeft);
        break;
    case AST_OP_ASSIGN:
        result = ir_assign(node);
        break;
    case AST_OP_NEG:
        result = ir_neg(node);
        break;
    case AST_OP_IF:
        result = ir_if(node);
        break;
    case AST_OP_WHILE:
        result = ir_while(node);
        break;
    case AST_OP_FOR:
        result = ir_for(node);
        break;
    case AST_OP_CMP:
        result = ir_cmp(node);
        break;
    case AST_OP_OR:
        result = ir_or(node);
        break;
    case AST_OP_AND:
        result = ir_and(node);
        break;
    case AST_OP_NOT:
        result = ir_not(node, isLeft);
        break;
    case AST_RETURN:
        result = ir_return(node);
        break;
    case AST_OP_BLOCK:
        result = ir_block(node);
        if (!result) {
            printf("error:in block\n");
        }
        break;
    case AST_CU:
        result = ir_cu(node);
        break;
    case AST_DEF_LIST:
        result = ir_def_list(node, true);
        break;
    case AST_FUNC_DEF:
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
    IRCode.addInst(root->blockInsts);
    // 第二步遍历函数表，定义函数语句
    return true;
}
