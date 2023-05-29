#pragma once

#include <vector>

#include "symbol.h"

/// @brief IR指令操作码
enum IRInstOperator {

    IRINST_OP_ADD,       // 加法指令，二元运算
    IRINST_OP_MUL,       // 乘法指令，二元运算
    IRINST_OP_SUB,       // 减法指令，二元运算
    IRINST_OP_DIV,       // 除法指令，二元运算
    IRINST_OP_MOD,       // 取余指令，二元运算
    IRINST_OP_ASSIGN,    // 赋值指令，一元运算
    IRINST_OP_TYPECOV,   // 类型转换指令
    IRINST_OP_FUNC_DEF,  // 函数定义指令
    IRINST_OP_VAR_DEF,   // 变量定义指令
    IRINST_OP_RETURN,    // 函数返回指令
    IRINST_OP_FUNC_CALL, // 函数调用，多目运算，个数不限

    IRINST_OP_MAX  // 最大指令码，也是无效指令
};

/// @brief IR指令的基类
class IRInst {

protected:
    /// @brief 构造函数
    IRInst();

    /// @brief 构造函数
    /// @param op 
    /// @param result 
    /// @param srcVal1 
    /// @param srcVal2 
    IRInst(IRInstOperator op, Value *result = nullptr);

public:
    /// @brief 析构函数
    virtual ~IRInst();

    /// @brief 获取指令操作码
    /// @return 指令操作码
    IRInstOperator getOp();

    /// @brief 获取源操作数列表
    /// @return 源操作数列表
    std::vector<Value *> &getSrc();

    /// @brief 获取目的操作数，或者结果操作数
    /// @return 目的操作数，或者结果操作数
    Value *getDst();

    /// @brief 转换成字符串
    virtual void toString(std::string &str);

protected:

    /// @brief IR指令操作码
    enum IRInstOperator op;

    /// @brief 源操作树
    std::vector<Value *> srcValues;

    /// @brief 目的操作数或结果或跳转指令的目标
    Value *dstValue;
};

/// @brief 二元运算指令
class BinaryIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param op 
    /// @param result 
    /// @param srcVal1 
    /// @param srcVal2 
    BinaryIRInst(IRInstOperator op, Value *result, Value *srcVal1, Value *srcVal2);

    /// @brief 析构函数
    virtual ~BinaryIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;

};
/*  修改  */
/// @brief 类型转换指令
class TypeCovIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param op 
    /// @param result 
    TypeCovIRInst(Value *result, Value *srcVal1, bool int2double = true);

    /// @brief 析构函数
    virtual ~TypeCovIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;
};

/*  修改  */
/// @brief 变量声明指令
class DeclearIRInst : public IRInst {

public:
    bool IsGlobal = true;
    bool IsArray = false;
    bool IsTemp = false;
    /// @brief 构造函数
    /// @param result
    /// @param 是否是全局变量
    /// @param 是否是数组
    DeclearIRInst(Value *result, bool IsGlobal = true, bool IsArray = false, bool IsTemp = false);

    /// @brief 析构函数
    virtual ~DeclearIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;
};
/*  修改  */
/// @brief 函数定义指令
class FuncDefIRInst : public IRInst {
protected:

    /// @brief 函数名
    std::string name;

public:
    bool IsGlobal = true;
    bool IsArray = false;
    ValueType ret_type;  // 返回值类型
    /// @brief 构造函数
    /// @param result
    /// @param 是否是全局变量
    /// @param 是否是数组
    FuncDefIRInst(FuncSymbol *func_name, ValueType ret_type = ValueType::ValueType_Int);
    FuncDefIRInst(Value *func_name, ValueType ret_type = ValueType::ValueType_Int);
    /// @brief 析构函数
    virtual ~FuncDefIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;
};

/// @brief 函数调用指令
class FuncCallIRInst : public IRInst {

protected:

    /// @brief 函数名
    std::string name;

public:

    /// @brief 无参数并且没有要设置的返回值的函数调用
    /// @param name 函数名
    FuncCallIRInst(std::string _name);

    /// @brief 含有参数的函数调用
    /// @param _srcVal1 函数的实参Value
    /// @param result 保存返回值的Value
    FuncCallIRInst(std::string _name, Value *_srcVal1, Value *_result = nullptr);

    /// @brief 含有参数的函数调用
    /// @param srcVal 函数的实参Value
    /// @param result 保存返回值的Value
    FuncCallIRInst(std::string _name, std::vector<Value *> &_srcVal, Value *_result = nullptr);

    /// @brief 析构函数
    virtual ~FuncCallIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;
};

/// @brief 赋值指令或者说复制指令
class AssignIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param result 
    /// @param srcVal1 
    AssignIRInst(Value *result, Value *srcVal1);

    /// @brief 析构函数
    virtual ~AssignIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;

};

/// @brief return指令
class ReturnIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param result 
    /// @param srcVal1 
    ReturnIRInst(Value *result);

    /// @brief 析构函数
    virtual ~ReturnIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;

};

/// @brief 没啥用指令
class UselessIRInst : public IRInst {
private:
    std::string useless_str;
public:
    /// @brief 构造函数
    /// @param str 没啥用字符串 
    UselessIRInst(std::string str);

    /// @brief 析构函数
    virtual ~UselessIRInst() override;

    /// @brief 转换成字符串
    void toString(std::string &str) override;

};