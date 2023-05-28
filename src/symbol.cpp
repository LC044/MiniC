//
// Created by zenglj on 2023/1/29.
//
#include <unordered_map>

#include "symbol.h"

using namespace std;
struct FuncSymbol {
    Value FuncValue;
    // 用来保存所有的局部变量信息
    std::unordered_map<std::string, Value *> localVarsMap;
    /* data */
};

// 用来保存所有的变量信息
static std::unordered_map<std::string, Value *> varsMap;

// 用来保存所有的函数信息
static std::unordered_map<std::string, FuncSymbol *> funcsMap;

/// @brief 新建变量型Value
/// @param name 变量ID
/// @param type 变量类型
void newVarValue(std::string name, ValueType type)
{
    auto pIter = varsMap.find(name);
    if (pIter != varsMap.end()) {

        // 符号表中存在，则只是更新值
        pIter->second->type = type;

        if (type == ValueType::ValueType_Int) {
            pIter->second->intVal = 0;
        } else {
            pIter->second->realVal = 0;
        }
    } else {
        Value *temp = new VarValue(name, type);
        varsMap.emplace(name, temp);
    }
}

/// 新建一个变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newVarValue(std::string name)
{
    // 类型待定
    Value *temp = new VarValue(name, ValueType::ValueType_MAX);
    varsMap.emplace(temp->name, temp);

    return temp;
}

/// 新建一个局部变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newLocalVarValue(std::string name, ValueType type)
{
    // 类型待定
    Value *temp = new LocalVarValue(name, type);
    varsMap.emplace(temp->name, temp);

    return temp;
}
/// 新建一个整型数值的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newConstValue(int intVal)
{
    Value *temp = new ConstValue(intVal);
    varsMap.emplace(temp->name, temp);

    return temp;
}

/// 新建一个实数数值的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newConstValue(double realVal)
{
    Value *temp = new ConstValue(realVal);
    varsMap.emplace(temp->name, temp);

    return temp;
}

/// 新建一个临时型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newTempValue(ValueType type)
{
    Value *temp = new TempValue(type);
    varsMap.emplace(temp->name, temp);

    return temp;
}

/// 根据变量名取得当前符号的值。若变量不存在，则说明变量之前没有定值，则创建一个未知类型的值，初值为0
/// \param name 变量名
/// \return 变量对应的值
Value *findValue(std::string name, bool checkExist)
{
    Value *temp = nullptr;

    auto pIter = varsMap.find(name);
    if (pIter == varsMap.end()) {

        // 变量名没有找到
        if (!checkExist) {
            temp = newVarValue(name);
        }

    } else {
        temp = pIter->second;
    }

    return temp;
}
// 查看变量名是否存在
bool IsExist(std::string name)
{
    auto pIter = varsMap.find(name);
    if (pIter == varsMap.end()) {
        return false;
    } else {
        return true;
    }
}
/// @brief 清理注册的所有Value资源
void freeValues()
{
    // 清理Hash表中的所有创建的Value
    for (auto [k, v] : varsMap) {
        delete v;
    }

    // Hash表清空
    varsMap.clear();
}
