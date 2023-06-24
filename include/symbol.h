/**
* @brief 各种符号(全局变量、函数、局部变量、临时变量、常量)的声明
* Created by zenglj on 2023/1/29.
* @LastEditors shuaikangzhou
*/
#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include "common.h"
// namespace std;
enum class ValueType {
    ValueType_Int,      // 整型
    ValueType_Real,     // 实数
    ValueType_ARRAY,    // 数组
    ValueType_Int_ptr,  // int指针
    ValueType_Void,     // void返回类型
    ValueType_Bool,     // boolean
    ValueType_MAX,      // 最大值，无效值
};


class Value {

protected:
    static std::unordered_map<std::string, uint64_t > funcTempVarCount;
    /// @brief 新建一个临时常量名
    /// \return
    static std::string createConstVarName()
    {
        static uint64_t tempConstCount = 0; // 临时变量计数，默认从0开始

        return "%c" + int2str(tempConstCount++);
    }

    /// @brief 新建一个临时变量名
    /// \return

    static std::string createTempVarName(std::string func_name, bool isLocal = false)
    {

        // static uint64_t tempVarCount = 0; // 临时变量计数，默认从0开始
        // 对每个函数单独编号
        if (isLocal)return "%l" + int2str(funcTempVarCount[func_name]++);
        return "%t" + int2str(funcTempVarCount[func_name]++);
    }

public:
    /// @brief 是否是常量
    bool isConst = false;

    /// @brief 是否编译器内部产生的临时变量
    bool isTemp = false;

    /// @brief 是否是用户定义的变量或标识符
    bool isId = false;

    /// @brief 变量名或内部标识的名字
    std::string name;
    /// @brief 变量名
    std::string id_name;
    /// @brief 类型
    ValueType type;

    /// @brief 整型常量的值
    int intVal = 0;
    // 不初始化会有问题
    int dims[10] = { 0,0,0,0,0,0,0,0,0,0 };
    int dim = 0;
    /// @brief 实数常量的值
    double realVal = 0;
    int scope;

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
    /// @brief 获取类型
    /// @return 
    virtual std::string getType() const
    {
        std::string typeName;
        switch (type) {
        case ValueType::ValueType_Int:
            typeName = "i32";
            break;
        case ValueType::ValueType_Int_ptr:
            typeName = "i32*";
            break;
        case ValueType::ValueType_Bool:
            typeName = "i1";
            break;
        case ValueType::ValueType_Void:
            typeName = "void";
            break;
        default:
            typeName = "i32";
            break;
        }
        return typeName;
    }
};

class TempValue : public Value {

public:
    /// @brief 创建临时Value，用于保存中间IR指令的值
    /// \param val
    TempValue(ValueType _type, std::string _func_name) : Value(_type)
    {
        isTemp = true;
        name = createTempVarName(_func_name);

    }

    /// @brief 创建临时Value，用于保存中间IR指令的值
    /// \param val
    TempValue(std::string _func_name) : Value(ValueType::ValueType_Real)
    {
        isTemp = true;
        name = createTempVarName(_func_name);
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
    VarValue(std::string _name, ValueType _type) : Value("@" + _name, _type)
    {
        isId = true;
    }

    /// @brief 创建变量Value，用于保存中间IR指令的值
    /// \param val
    VarValue(std::string _name) : Value("@" + _name, ValueType::ValueType_Real)
    {
        isId = true;
    }

    /// @brief 析构函数
    virtual ~VarValue() override
    {
        // 如有资源清理，请这里追加代码
    }
};
class LocalVarValue : public Value {
public:

    /// @brief 创建变量Value，用于保存中间IR指令的值
    /// \param val
    LocalVarValue(std::string _name, ValueType _type, std::string _func_name) : Value(_type)
    {
        id_name = _name;
        isId = true;
        name = createTempVarName(_func_name, true);
    }

    /// @brief 创建变量Value，用于保存中间IR指令的值
    /// \param val
    LocalVarValue(std::string _name, std::string _func_name) : Value(ValueType::ValueType_Real)
    {
        id_name = _name;
        isId = true;
        name = createTempVarName(_func_name, true);
    }

    /// @brief 析构函数
    virtual ~LocalVarValue() override
    {
        // 如有资源清理，请这里追加代码
    }
};

class LocalVarTable {
public:
    std::unordered_map<std::string, Value *> localVarsMap;
    int scope;
    Value *find(std::string var_name)
    {
        auto pItr = localVarsMap.find(var_name);
        if (pItr != localVarsMap.end()) {
            return pItr->second;
        }
        return nullptr;
    }
    void clear()
    {
        localVarsMap.clear();
    }
};
class VarStack {
public:
    int scope = -1;
    std::vector<LocalVarTable *> Stack;

    /// @brief 新增一个作用域
    /// @param varTable 符号表
    void push(LocalVarTable *varTable);
    // 离开作用域之后,将符号表出栈
    void pop(int scope);

    /// @brief 在整个栈里查找某个变量
    /// @param var_nam 变量名
    /// @return 变量Value
    Value *search(std::string var_nam, int currentScope);

    /// @brief 在当前作用域查找变量
    /// @param var_name 变量名
    /// @return 变量Value
    Value *find(std::string var_name, int currentScope);

    /// @brief 在当前作用域增加变量
    /// @param val 变量Value
    /// @param var_name 变量名
    void addValue(Value *val, std::string var_name, int currentScope);
};
class FuncSymbol : public Value {
public:
    /// @brief 函数名
    // 用来保存所有的局部变量信息
    // 参数列表
    std::vector<Value *> fargs;
    // 局部变量表
    std::unordered_map<std::string, Value *> localVarsMap;
    std::vector<std::string > localVarsName;
    // 临时变量表
    std::unordered_map<std::string, Value *> tempVarsMap;
    std::vector<std::string > tempVarsName;
    // 局部变量符号栈
    VarStack stack;
    // 产生IR时用的临时符号栈
    VarStack tempStack;
    int currentScope = 0;
    /// @brief 从符号栈中查找某个变量
    /// @param val_name 变量名
    /// @param Temp 临时栈还是符号栈
    /// @return 变量
    Value *findValue(std::string val_name, bool Temp);
    /// @brief 添加符号到符号栈里
    /// @param value 变量
    /// @param val_name 变量名
    /// @param Temp 添加到临时栈还是符号栈
    void addValue(Value *value, std::string val_name, bool Temp = false);
    FuncSymbol() : Value(ValueType::ValueType_Int) {}
    FuncSymbol(std::string _name, ValueType _type) : Value(_name, _type) {}
    /// @brief 析构函数
    virtual ~FuncSymbol()
    {
        // 如有资源清理，请这里追加代码

    }
};
class SymbolTable {
public:
    std::vector<std::string > varsName;
    // 保存函数名，以便顺序遍历
    std::vector<std::string > funcsName;
    // 用来保存所有的全局变量
    std::unordered_map<std::string, Value *> varsMap;
    // 用来保存所有的函数信息
    std::unordered_map<std::string, FuncSymbol *> funcsMap;
    /// @brief 查找全局变量
    /// @param varName 变量名
    /// @return 变量
    Value *findValue(std::string varName);
    /// @brief 查找局部变量
    /// @param var_name 变量名
    /// @param func_name 函数名
    /// @param tempStack 是否在临时栈里查找
    /// @return 变量
    Value *findValue(std::string var_name, std::string func_name, bool tempStack = false);
    /// @brief 查找函数
    /// @param func_name 函数名
    /// @return 函数符号
    FuncSymbol *findFuncValue(std::string func_name);
    /// @brief 添加全局变量
    /// @param var_name 变量名
    /// @param value 变量符号
    /// @return true:添加成功；false:变量已存在
    bool addValue(std::string var_name, Value *value);
    /// @brief 添加局部变量
    /// @param var_name 变量名
    /// @param value 变量value
    /// @param func_name 函数名
    /// @param Temp 是否添加到临时栈里
    void addValue(std::string var_name, Value *value, std::string func_name, bool Temp = false);
    /// @brief 添加函数
    /// @param func_name 函数名
    /// @param symbol 函数符号
    void addFunction(std::string func_name, FuncSymbol *symbol);
};

/// @brief 根据变量名取得当前符号的值。若变量不存在，则说明变量之前没有定值，则创建一个未知类型的值，初值为0
/// \param name 变量名
/// \param checkExist 检查变量存在不？若true则检查，不存在则返回nullptr，否则创建新变量
/// \return 变量对应的值
Value *findValue(std::string name, std::string func_name, bool checkExist = false);
FuncSymbol *findFuncValue(std::string name);
bool IsExist(std::string name);
bool LocalIsExist(std::string func_name, std::string var_name);
bool GlobalIsExist(std::string name);
/// @brief 新建变量型Value
/// @param name 变量ID
/// @param type 变量类型
void newVarValue(std::string name, ValueType type);

/// @brief 新建一个变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newVarValue(std::string name);

/// @brief 新建一个局部变量型的Value，并加入到符号表，用于后续释放空间
/// \param intVal 整数值
/// \return 常量Value
Value *newLocalVarValue(std::string name, ValueType type, std::string func_name);

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
Value *newTempValue(ValueType type, std::string func_name, bool isFfargs = false);

/// @brief 新建一个函数Value，并加入到函数表，用于后续释放空间
/// \param name 函数名
/// \return 函数Value
FuncSymbol *newFuncValue(std::string name, ValueType type = ValueType::ValueType_Int);
/// @brief 清理注册的所有Value资源
void freeValues();
// 用来保存所有的变量信息
// 存储函数里的label编号
static std::unordered_map<std::string, uint64_t > funcLabelCount;
/// @brief 新建一个label
/// @param func_name 函数名
/// @return label
static std::string newLabel(std::string func_name)
{
    std::string name;
    auto pIter = funcLabelCount.find(func_name);
    if (pIter == funcLabelCount.end()) {
        funcLabelCount[func_name] = 3;
        name = ".L" + int2str(funcLabelCount[func_name]);
    } else {
        name = ".L" + int2str(++funcLabelCount[func_name]);
    }
    // Value *temp = new FuncSymbol(name, ValueType::ValueType_Int);
    // return temp;
    return name;
}
/// @brief 判断是不是内置函数
/// @param funcname 函数名
/// @return 是内置函数为true
static bool is_buildIn_func(std::string funcname)
{
    if (funcname == "putint") {
        return true;
    } else if (funcname == "getint") {
        return true;
    } else if (funcname == "putch") {
        return true;
    } else if (funcname == "getch") {
        return true;
    } else if (funcname == "getarray") {
        return true;
    } else if (funcname == "putarray") {
        return true;
    }
    return false;
}