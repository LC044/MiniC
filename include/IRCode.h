#pragma once

#include <vector>

#include "IRInst.h"

/*
    中间代码
*/
class InterCode {

protected:

    std::vector<IRInst *> code;

public:
    // 构造函数
    InterCode();

    /// 析构函数
    ~InterCode();

    // 添加一个指令块
    void addInst(InterCode &block);

    // 添加一条中间指令
    void addInst(IRInst *inst);
    int getCodeSize();
    //获取中间代码序列
    std::vector<IRInst *> &getInsts();

    /// @brief 文本输出线性IR指令
    void outputIR(const std::string &filePath);
};
