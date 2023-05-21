#include "IRCode.h"

InterCode::InterCode()
{

}

InterCode::~InterCode()
{
    // 资源清理
    for (auto inst : code) {

        delete inst;
    }

    code.clear();
}

// 添加一个指令块,添加到尾部，并清除原来指令块的内容
void InterCode::addInst(InterCode &block)
{
    std::vector<IRInst *> &insert = block.getInsts();

    code.insert(code.end(), insert.begin(), insert.end());

    // InterCode析构会清理资源，因此移动指令到code中后必须清理，否则会释放多次导致程序例外
    // 当然，这里也可不清理，但InterCode的析构函数不能清理，需专门的函数清理即可。
    insert.clear();
}

// 添加一条中间指令
void InterCode::addInst(IRInst *inst)
{
    code.push_back(inst);
}

//获取中间代码序列
std::vector<IRInst *> &InterCode::getInsts()
{
    return code;
}

/// @brief 文本输出线性IR指令
void InterCode::outputIR(const std::string &filePath)
{
    // 这里使用C的文件操作，也可以使用C++的文件操作

    FILE *fp = fopen(filePath.c_str(), "w");
    if (nullptr == fp) {
        printf("fopen() failed\n");
        return;
    }

    // 遍历所有的线性IR指令，文本输出
    for (auto &inst : code) {

        std::string instStr;
        inst->toString(instStr);

        if (!instStr.empty()) {
            fprintf(fp, "%s\n", instStr.c_str());
        }
    }

    fclose(fp);
}
