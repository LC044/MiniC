//
// Created by zenglj on 2023/1/29.
//
#include <unordered_map>
#include <vector>
#include "symbol.h"

using namespace std;
// class的静态成员要在class外初始化
std::unordered_map<std::string, uint64_t > Value::funcTempVarCount = { {"main",0} };
// 保存全局变量名，以便顺序遍历
std::vector<std::string > varsName;
// 保存函数名，以便顺序遍历
std::vector<std::string > funcsName;
// 用来保存所有的全局变量
std::unordered_map<std::string, Value *> varsMap;

// 用来保存所有的函数信息
std::unordered_map<std::string, FuncSymbol *> funcsMap;

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
    varsName.push_back(name);
    return temp;
}
Value *newFuncValue(std::string name)
{
    // 类型待定
    FuncSymbol *tempSymbol = new FuncSymbol(name, ValueType::ValueType_Int);
    funcsMap.emplace(name, tempSymbol);
    funcsName.push_back(name);
    return tempSymbol;
}
/// 新建一个局部变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newLocalVarValue(std::string name, ValueType type, std::string func_name)
{
    // 类型待定
    auto pIter1 = funcsMap.find(func_name);
    Value *temp = new LocalVarValue(name, type, func_name);
    pIter1->second->localVarsMap.emplace(temp->name, temp);
    pIter1->second->localVarsName.push_back(temp->name);
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
Value *newTempValue(ValueType type, std::string func_name, bool isFfargs)
{
    auto pIter1 = funcsMap.find(func_name);
    Value *temp = new TempValue(type, func_name);
    pIter1->second->tempVarsName.push_back(temp->name);
    pIter1->second->tempVarsMap.emplace(temp->name, temp);
    if (isFfargs) {
        // 
        printf("形参 %s\n", temp->name.c_str());
        pIter1->second->fargs.push_back(temp);
    } else {

    }
    return temp;
}

/// 根据变量名取得当前符号的值。若变量不存在，则说明变量之前没有定值，则创建一个未知类型的值，初值为0
/// \param name 变量名
/// \return 变量对应的值
Value *findValue(std::string name, std::string func_name, bool checkExist)
{
    Value *temp = nullptr;
    temp = findFuncValue(func_name);
    // 先在函数表的局部变量里找
    if (temp != nullptr) {
        auto pIter = temp->localVarsMap.find(name);
        if (pIter == temp->localVarsMap.end()) {
            // 变量名没有找到
        } else {
            temp = pIter->second;
            return temp;
        }
    }
    // 局部变量找不到在全局变量里找
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
Value *findFuncValue(std::string name)
{
    Value *temp = nullptr;

    auto pIter = funcsMap.find(name);
    if (pIter == funcsMap.end()) {
        return nullptr;
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
// 判断全局符号是否存在(全局变量,函数名)
bool GlobalIsExist(std::string name)
{
    auto pIter = varsMap.find(name);
    if (pIter == varsMap.end()) {
        auto pIter1 = funcsMap.find(name);
        if (pIter1 == funcsMap.end()) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }

}
bool LocalIsExist(std::string func_name, std::string var_name)
{
    auto pIter = funcsMap.find(func_name);
    if (pIter == funcsMap.end()) {
        printf("function %s not found\n", func_name.c_str());
        return false;
    }
    auto pIter1 = pIter->second->localVarsMap.find(var_name);
    if (pIter1 == pIter->second->localVarsMap.end()) {
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
