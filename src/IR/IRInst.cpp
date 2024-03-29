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
{

}

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
/// @brief 获取跳转指令的跳转标签
/// @return 跳转的标签
std::string IRInst::getLabel()
{
    return ".L1";
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
BinaryIRInst::BinaryIRInst(IRInstOperator _op, std::string _cmp, Value *_result, Value *_srcVal1, Value *_srcVal2) :
    IRInst(_op, _result)
{
    cmp = _cmp;
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
    case IRINST_OP_CMP:
        str += result->getName() + " = cmp " + cmp + " " + src1->getName() + ", " + src2->getName();
        break;
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
    std::string type = result->getType();
    // type = "i32";
    if (IsGlobal) {
        // 全局变量用@符号
        str = "declare " + type + " " + result->getName();
    } else {
        // 局部变量用%l符号
        str = "    declare " + type + " " + result->getName();

    }
    if (IsArray) {
        // 数组
        if (result->dims[0] == 999) {
            str += "[0]";
            for (int i = 1; result->dims[i] != 0; i++) {
                str += "[" + int2str(result->dims[i]) + "]";
            }
        } else {
            for (int i = 0; result->dims[i] != 0; i++) {
                str += "[" + int2str(result->dims[i]) + "]";
            }
        }
    }
    if (!IsGlobal and !IsTemp) {
        str += " ; variable: " + result->id_name;
        if (IsArray) {
            // 数组
            if (result->dims[0] == 999) {
                str += "[0]";
                for (int i = 1; result->dims[i] != 0; i++) {
                    str += "[" + int2str(result->dims[i]) + "]";
                }
            } else {
                for (int i = 0; result->dims[i] != 0; i++) {
                    str += "[" + int2str(result->dims[i]) + "]";
                }
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
    // printf("srcValues size %d\n", srcValues.size());
}
// FuncDefIRInst::FuncDefIRInst(FuncSymbol *_func_name, ValueType _ret_type) :
//     IRInst(IRINST_OP_VAR_DEF, _func_name), ret_type(_ret_type)
// {
//     // 形参拷贝
//     // srcValues = _paras;
//     srcValues = _func_name->fargs;
//     // printf("srcValues size %d\n", srcValues.size());
// }
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
    } else if (ret_type == ValueType::ValueType_Void) {
        type = "void";
        printf("void 返回类型\n\n");
    }
    str = "define " + type + " @" + func_name->getName() + "(";
    for (size_t k = 0; k < srcValues.size(); ++k) {
        str += "i32 " + srcValues[k]->getName();
        if (srcValues[k]->dims[0] == 999) {
            str += "[0]";
            for (int i = 1; srcValues[k]->dims[i] != 0; i++) {
                str += "[" + int2str(srcValues[k]->dims[i]) + "]";
            }
        } else {
            for (int i = 0; srcValues[k]->dims[i] != 0; i++) {
                str += "[" + int2str(srcValues[k]->dims[i]) + "]";
            }
        }
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
/// @brief 无参数的函数调用
/// @param name 函数名
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name, Value *_result) :
    IRInst(IRINST_OP_FUNC_CALL, _result), name(_name)
{}

/// @brief 含参函数调用
/// @param _name 函数名
/// @param _srcVal1 参数
/// @param _paras 含参
/// @param _result 返回值
FuncCallIRInst::FuncCallIRInst(std::string _name, Value *_srcVal1, bool _paras, Value *_result) :
    IRInst(IRINST_OP_FUNC_CALL, _result), name(_name)
{
    srcValues.push_back(_srcVal1);
}

/// @brief 含参函数调用
/// @param _name 函数名
/// @param _srcVal 参数列表
/// @param _paras 含参
/// @param _result 返回值
FuncCallIRInst::FuncCallIRInst(std::string _name, std::vector<Value *> &_srcVal, bool _paras, Value *_result) :
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
        str += result->getName() + " = call i32 @" + name + "(";
    }

    for (size_t k = 0; k < srcValues.size(); ++k) {
        std::string type = "i32 ";
        if (srcValues[k]->type == ValueType::ValueType_Int_ptr) {
            type = "i32* ";
        }
        str += type + srcValues[k]->getName();

        if (k != (srcValues.size() - 1)) {

            str += ", ";
        }
    }

    str += ")";
}

/// @brief 赋值IR指令
/// @param _result 
/// @param _srcVal1 
AssignIRInst::AssignIRInst(Value *_result, Value *_srcVal1, bool _check_ptr) :
    IRInst(IRINST_OP_ASSIGN, _result)
{
    check_ptr = _check_ptr;
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
    std::string resultName, srcName;
    // 指针引用需要加 * 号
    if (result->type == ValueType::ValueType_Int_ptr) {
        if (check_ptr) {
            resultName = result->getName();
        } else {
            resultName = "*" + result->getName();
        }

    } else {
        resultName = result->getName();
    }
    if (src1->type == ValueType::ValueType_Int_ptr) {
        srcName = "*" + src1->getName();
    } else {
        srcName = src1->getName();
    }
    str += resultName + " = " + srcName;
}

/// @brief 一元运算，包括函数退出指令 exit %t8 和取负运算 a = neg %t8
/// @param op 指令码
/// @param result 目的操作数
/// @param src 源操作数
UnaryIRInst::UnaryIRInst(IRInstOperator _op, Value *_result, Value *_srcVal1) :
    IRInst(_op, _result)
{
    srcValues.push_back(_srcVal1);
}
/// @brief void函数的退出语句 exit
/// @param op 
UnaryIRInst::UnaryIRInst(IRInstOperator _op) :
    IRInst(_op)
{}
/// @brief 析构函数
UnaryIRInst::~UnaryIRInst()
{

}


/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void UnaryIRInst::toString(std::string &str)
{
    Value *result = dstValue, *src;
    str = "    ";
    switch (op) {
    case IRINST_OP_NEG:
        src = srcValues[0];
        str += result->getName() + " = neg " + src->getName();
        break;
    case IRINST_OP_RETURN:
        if (srcValues.size() > 0) {
            src = srcValues[0];
            str += "exit " + src->getName();
        } else {
            str += "exit";
        }
        break;
    default:
        break;
    }

}

/// @brief 有条件跳转指令
/// @param op 操作码
/// @param src1 源操作数
/// @param label1 跳转label1
/// @param label2 跳转label2
JumpIRInst::JumpIRInst(IRInstOperator _op, Value *_src1, std::string _label1, std::string _label2) :
    IRInst(_op, _src1)
{

    label1 = _label1;
    label2 = _label2;
}
/// @brief 无条件跳转指令
/// @param op 操作码
/// @param label 跳转label
JumpIRInst::JumpIRInst(IRInstOperator _op, std::string _label) :
    IRInst(_op)
{
    dstValue = nullptr;
    label1 = _label;
}
/// @brief 析构函数
JumpIRInst::~JumpIRInst()
{

}
/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void JumpIRInst::toString(std::string &str)
{

    str = "    ";
    switch (op) {
    case IRINST_JUMP_BR:
        str += "br label " + label1;
        break;
    case IRINST_JUMP_BC: {
        Value *src1 = dstValue;
        str += "bc " + src1->getName() + ", label " + label1 + ", label " + label2;
        break;
    }
    default:
        break;
    }

}
/// @brief 没啥用指令
/// @param  
UselessIRInst::UselessIRInst(std::string str) :
    useless_str(str)
{
    op = IRINST_OP_USELESS;
    // srcValues.push_back(_srcVal1);
}

/// @brief 析构函数
UselessIRInst::~UselessIRInst()
{

}
std::string UselessIRInst::getLabel()
{
    return useless_str.substr(0, useless_str.size() - 1);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void UselessIRInst::toString(std::string &str)
{
    str = useless_str;
}