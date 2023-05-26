//
// Created by zenglj on 2023/1/29.
//
#pragma once

#include <cstdint>
#include <string>

#include "common.h"

enum class ValueType {
    ValueType_Int,   // 整型
    ValueType_Real,  // 实数
    ValueType_ARRAY, // 数组
    ValueType_MAX,   // 最大值，无效值
};

class Value {

protected:

    /// @brief 新建一个临时常量名
    /// \return
    static std::string createConstVarName()
    {
        static uint64_t tempConstCount = 0; // 临时变量计数，默认从0开始

        return "%c" + int2str(tempConstCount++);
    }

    /// @brief 新建一个临时变量名
    /// \return
    static std::string createTempVarName()
    {
        static uint64_t tempVarCount = 0; // 临时变量计数，默认从0开始

        return "%t" + int2str(tempVarCount++);
    }

protected:

    /// @brief 是否是常量
    bool isConst = false;

    /// @brief 是否编译器内部产生的临时变量
    bool isTemp = false;

    /// @brief 是否是用户定义的变量或标识符
    bool isId = false;

public:

    /// @brief 变量名或内部标识的名字
    std::string name;

    /// @brief 类型
    ValueType type;

    /// @brief 整型常量的值
    int intVal = 0;
    int dims[10];
    /// @brief 实数常量的值
    double realVal = 0;

protected:

    /// @brief 默认实数类型的构造函数，初始值为0
    Value() : type(ValueType::ValueType_Real)
    {
        // 不需要增加代码
    }

    /// @brief 构造函数
    /// @param _name 
    /// @param _type 
    Value(std::string _name, ValueType _type) : name(_name), type(_type)
    {
        // 不需要增加代码
    }

    /// @brief 构造函数
    /// @param _type 
    Value(ValueType _type) : type(_type)
    {
        // 不需要增加代码
    }

public:

    /// @brief 析构函数
    virtual ~Value()
    {
        // 如有资源清理，请这里追加代码
    }

    /// @brief 获取名字
    /// @return 
    virtual std::string getName() const
    {

        return name;
    }
};

class TempValue : public Value {

public:
    /// @brief 创建临时Value，用于保存中间IR指令的值
    /// \param val
    TempValue(ValueType _type) : Value(_type)
    {
        isTemp = true;
        name = createTempVarName();
    }

    /// @brief 创建临时Value，用于保存中间IR指令的值
    /// \param val
    TempValue() : Value(ValueType::ValueType_Real)
    {
        isTemp = true;
        name = createTempVarName();
    }

    /// @brief 析构函数
    virtual ~TempValue() override
    {
        // 如有资源清理，请这里追加代码
    }
};

class ConstValue : public Value {

public:
    /// @brief 整数的临时变量值
    /// \param val
    ConstValue(int val) : Value(ValueType::ValueType_Int)
    {
        isConst = true;
        name = createConstVarName();
        intVal = val;
    }

    /// @brief 实数的临时变量值
    /// \param val
    ConstValue(double val) : Value(ValueType::ValueType_Real)
    {
        isConst = true;
        name = createConstVarName();
        realVal = val;
    }

    /// @brief 析构函数
    virtual ~ConstValue() override
    {
        // 如有资源清理，请这里追加代码
    }

    /// @brief 获取名字
    /// @return 
    virtual std::string getName() const override
    {
        if (type == ValueType::ValueType_Int) {
            return int2str(this->intVal);
        } else {
            // 要修改的地方
            return double2str(this->realVal);
        }
    }
};

class VarValue : public Value {

public:
    /// @brief 创建变量Value，用于保存中间IR指令的值
    /// \param val
    VarValue(std::string _name, ValueType _type) : Value(_name, _type)
    {
        isId = true;
    }

    /// @brief 创建变量Value，用于保存中间IR指令的值
    /// \param val
    VarValue(std::string _name) : Value(_name, ValueType::ValueType_Real)
    {
        isId = true;
    }

    /// @brief 析构函数
    virtual ~VarValue() override
    {
        // 如有资源清理，请这里追加代码
    }
};

/// @brief 根据变量名取得当前符号的值。若变量不存在，则说明变量之前没有定值，则创建一个未知类型的值，初值为0
/// \param name 变量名
/// \param checkExist 检查变量存在不？若true则检查，不存在则返回nullptr，否则创建新变量
/// \return 变量对应的值
Value *findValue(std::string name, bool checkExist = false);

bool IsExist(std::string name);
/// @brief 新建变量型Value
/// @param name 变量ID
/// @param type 变量类型
void newVarValue(std::string name, ValueType type);

/// @brief 新建一个变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newVarValue(std::string name);

/// @brief 新建一个整型数值的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 临时Value
Value *newConstValue(int intVal);

/// @brief 新建一个实数数值的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 临时Value
Value *newConstValue(double realVal);

/// @brief 新建一个临时型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newTempValue(ValueType type);

/// @brief 清理注册的所有Value资源
void freeValues();