#include "IRInst.h"

/// @brief 构造函数
IRInst::IRInst()
{
    // 未知指令
    op = IRINST_OP_MAX;
}

/// @brief 构造函数
/// @param op 
/// @param result 
/// @param srcVal1 
/// @param srcVal2 
IRInst::IRInst(IRInstOperator _op, Value *_result) :
    op(_op), dstValue(_result)
{}

/// @brief 析构函数
IRInst::~IRInst()
{

}

/// @brief 获取指令操作码
/// @return 指令操作码
IRInstOperator IRInst::getOp()
{
    return op;
}

/// @brief 获取源操作数列表
/// @return 源操作数列表
std::vector<Value *> &IRInst::getSrc()
{
    return srcValues;
}

/// @brief 获取目的操作数，或者结果操作数
/// @return 目的操作数，或者结果操作数
Value *IRInst::getDst()
{
    return dstValue;
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void IRInst::toString(std::string &str)
{
    // 未知指令
    str = "Unkown IR Instruction";
}

/// @brief 构造函数
/// @param op 操作符
/// @param result 结果操作数
/// @param srcVal1 源操作数1
/// @param srcVal2 源操作数2
BinaryIRInst::BinaryIRInst(IRInstOperator _op, Value *_result, Value *_srcVal1, Value *_srcVal2) :
    IRInst(_op, _result)
{
    srcValues.push_back(_srcVal1);
    srcValues.push_back(_srcVal2);
}

/// @brief 析构函数
BinaryIRInst::~BinaryIRInst()
{

}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void BinaryIRInst::toString(std::string &str)
{

    Value *src1 = srcValues[0], *src2 = srcValues[1], *result = dstValue;
    /*   新增   */
    // 只需要判断结果类型即可判断是浮点运算还是整数运算
    str = "    ";
    switch (op) {
    case IRINST_OP_ADD:
        // 加法指令，二元运算
        if (result->type == ValueType::ValueType_Real) {
            // 浮点运算
            str += result->getName() + " = fadd " + src1->getName() + ", " + src2->getName();
        } else {
            str += result->getName() + " = add " + src1->getName() + ", " + src2->getName();
        }
        break;
    case IRINST_OP_MOD:
        // 取余指令，二元运算
        str += result->getName() + " = mod " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_MUL:

        // 乘法指令，二元运算
        if (result->type == ValueType::ValueType_Real) {
            // 浮点运算
            str += result->getName() + " = fmul " + src1->getName() + ", " + src2->getName();
        } else {
            str += result->getName() + " = mul " + src1->getName() + ", " + src2->getName();
        }
        break;
    case IRINST_OP_SUB:

        // 减法指令，二元运算
        if (result->type == ValueType::ValueType_Real) {
            // 浮点运算
            str += result->getName() + " = fsub " + src1->getName() + ", " + src2->getName();
        } else {
            str += result->getName() + " = sub " + src1->getName() + ", " + src2->getName();
        }
        break;
    case IRINST_OP_DIV:

        // 除法指令，二元运算
        if (result->type == ValueType::ValueType_Real) {
            // 浮点运算
            str += result->getName() + " = fdiv " + src1->getName() + ", " + src2->getName();
        } else {
            str += result->getName() + " = div " + src1->getName() + ", " + src2->getName();
        }
        break;
    default:
        // 未知指令
        IRInst::toString(str);
        break;
    }
}

/* 修改 */
TypeCovIRInst::TypeCovIRInst(Value *_result, Value *_srcVal1, bool _int2double) :
    IRInst(IRINST_OP_TYPECOV, _result)
{
    srcValues.push_back(_srcVal1);
    // srcValues.push_back(_srcVal2);
}

/// @brief 析构函数
TypeCovIRInst::~TypeCovIRInst()
{

}
void TypeCovIRInst::toString(std::string &str)
{
    Value *result = dstValue, *src1 = srcValues[0];
    str = result->getName() + " = int2double  " + src1->getName();
}

/* 修改 */
// 变量声明指令
DeclearIRInst::DeclearIRInst(Value *_result, bool _IsGlobal, bool _IsArray, bool _IsTemp) :
    IRInst(IRINST_OP_VAR_DEF, _result)
{
    IsGlobal = _IsGlobal;
    IsArray = _IsArray;
    IsTemp = _IsTemp;
    srcValues.push_back(_result);
    // srcValues.push_back(_srcVal2);
}

/// @brief 析构函数
DeclearIRInst::~DeclearIRInst()
{

}
void DeclearIRInst::toString(std::string &str)
{
    // todo 暂时只考虑int型，以后可以继续添加
    Value *result = dstValue;
    std::string type;
    if (result->type == ValueType::ValueType_Int) {
        type = "i32";
    }
    // type = "i32";
    if (IsGlobal) {
        // 全局变量用@符号
        str = "declare " + type + result->getName();
    } else {
        // 局部变量用%l符号
        str = "    declare " + type + " " + result->getName();

    }
    if (IsArray) {
        // 数组
        for (int i = 0; result->dims[i] != 0; i++) {
            str += "[" + int2str(result->dims[i]) + "]";
        }
    }
    if (!IsGlobal and !IsTemp) {
        str += " ; variable: " + result->id_name;
        if (IsArray) {
            // 数组
            for (int i = 0; result->dims[i] != 0; i++) {
                str += "[" + int2str(result->dims[i]) + "]";
            }
        }
    }
}

/* 修改 */
// 函数定义指令
FuncDefIRInst::FuncDefIRInst(FuncSymbol *_func_name, ValueType _ret_type) :
    IRInst(IRINST_OP_VAR_DEF, _func_name), ret_type(_ret_type)
{
    // srcValues.push_back(_paras);
    srcValues = _func_name->fargs;
    printf("srcValues size %d\n", srcValues.size());
}
FuncDefIRInst::FuncDefIRInst(Value *_func_name, ValueType _ret_type) :
    IRInst(IRINST_OP_VAR_DEF, _func_name), ret_type(_ret_type)
{
    // 形参拷贝
    // srcValues = _paras;
    srcValues = _func_name->fargs;
    printf("srcValues size %d\n", srcValues.size());
}
/// @brief 析构函数
FuncDefIRInst::~FuncDefIRInst()
{

}
void FuncDefIRInst::toString(std::string &str)
{
    // todo 暂时只考虑int型，以后可以继续添加
    Value *func_name = dstValue;
    std::string type;
    if (ret_type == ValueType::ValueType_Int) {
        type = "i32";
    }
    str = "define " + type + " @" + func_name->getName() + "(";
    for (size_t k = 0; k < srcValues.size(); ++k) {

        str += "i32 " + srcValues[k]->getName();

        if (k != (srcValues.size() - 1)) {

            str += ", ";
        }
    }
    str += ") {";
}

/// @brief 无参数的函数调用
/// @param name 函数名
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name) :
    IRInst(IRINST_OP_FUNC_CALL, nullptr), name(_name)
{}

/// @brief 含有参数的函数调用
/// @param _srcVal1 函数的实参Value
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name, Value *_srcVal1, Value *_result) :
    IRInst(IRINST_OP_FUNC_CALL, _result), name(_name)
{
    srcValues.push_back(_srcVal1);
}

/// @brief 含有参数的函数调用
/// @param srcVal 函数的实参Value
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name, std::vector<Value *> &_srcVal, Value *_result) :
    IRInst(IRINST_OP_FUNC_CALL, _result), name(_name)
{
    // 实参拷贝
    srcValues = _srcVal;
}

/// @brief 析构函数
FuncCallIRInst::~FuncCallIRInst()
{

}


/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void FuncCallIRInst::toString(std::string &str)
{
    Value *result = dstValue;

    // TODO 这里应该根据函数名查找函数定义或者声明获取函数的类型
    // 这里假定所有函数返回类型要么是i32，要么是void
    // 函数参数的类型是i32
    str = "    ";
    if (!dstValue) {

        // 函数没有返回值设置
        str += "call void @" + name + "(";
    } else {

        // 函数有返回值要设置到结果变量中
        str += result->getName() + " = call int @" + name + "(";
    }

    for (size_t k = 0; k < srcValues.size(); ++k) {

        str += "i32 " + srcValues[k]->getName();

        if (k != (srcValues.size() - 1)) {

            str += ", ";
        }
    }

    str += ")";
}

/// @brief 赋值IR指令
/// @param _result 
/// @param _srcVal1 
AssignIRInst::AssignIRInst(Value *_result, Value *_srcVal1) :
    IRInst(IRINST_OP_ASSIGN, _result)
{
    srcValues.push_back(_srcVal1);
}

/// @brief 析构函数
AssignIRInst::~AssignIRInst()
{

}


/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void AssignIRInst::toString(std::string &str)
{
    Value *src1 = srcValues[0], *result = dstValue;
    str = "    ";
    str += result->getName() + " = " + src1->getName();
}

/// @brief 赋值IR指令
/// @param _result 
/// @param _srcVal1 
ReturnIRInst::ReturnIRInst(Value *_result) :
    IRInst(IRINST_OP_RETURN, _result)
{
    // srcValues.push_back(_srcVal1);
}

/// @brief 析构函数
ReturnIRInst::~ReturnIRInst()
{

}


/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void ReturnIRInst::toString(std::string &str)
{
    Value *result = dstValue;
    str = "    ";
    str += "exit " + result->getName();
}

/// @brief 没啥用指令
/// @param  
UselessIRInst::UselessIRInst(std::string str) :
    useless_str(str)
{
    // srcValues.push_back(_srcVal1);
}

/// @brief 析构函数
UselessIRInst::~UselessIRInst()
{

}


/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void UselessIRInst::toString(std::string &str)
{
    str = useless_str;
}