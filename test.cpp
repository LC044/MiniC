#include<stdio.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;
// 整数变字符串
string int2str(int num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}
class Value {
public:
    static int LocalCount;
    static int TempCount;
    static std::string createTempVarName(bool isLocal = false)
    {
        // static uint64_t tempVarCount = 0; // 临时变量计数，默认从0开始
        // 对每个函数单独编号
        if (isLocal)return "%l" + int2str(LocalCount++);
        return "%t" + int2str(LocalCount + TempCount++);
    }

};
int Value::LocalCount = 0;
int Value::TempCount = 0;
int main(int argc, char **argv)
{

    Value *val = new Value();
    std::string n1 = val->createTempVarName(true);
    std::string n2 = val->createTempVarName();
    std::string n3 = val->createTempVarName();
    std::string n4 = val->createTempVarName(true);
    std::string n5 = val->createTempVarName();
    std::string n6 = val->createTempVarName(true);
    cout << n1 << endl;
    cout << n2 << endl;
    cout << n3 << endl;
    cout << n4 << endl;
    cout << n5 << endl;
    cout << n6 << endl;
    return 0;
}