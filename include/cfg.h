#include <string>
#include <vector>
#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
#include <stack>
// #ifndef GDOT
// #define GDOT
// int gDot = 0;
// #endif


struct CfgNode {
    InterCode blockInsts;  // 代码块
    int id;                // 唯一标识符
    bool Del = false;      // 删除标记
    std::string label;     // 标签
};
static std::vector<CfgNode *> resultNodeTable;
struct CfgEdge {
    int fromNodeID; // 起始节点标识符
    int toNodeID;   // 结束节点标识符
    std::string fromNodeLabel; //
    std::string toNodeLabel; //
    bool Del = false; // 删除标记
};
/// @brief 生成控制流图
/// @param nodeTable 节点表
/// @param edgeTable 边表
/// @param filePath 输出文件名
void OutputCFG(std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable, const std::string filePath);