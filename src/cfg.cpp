/**
* @file
* @brief		生成控制流图
* @author		shuaikangzhou
* @date		    2023/06/18
* @details      将节点表和边表转化成图形化的控制流图
*/
#include <gvc.h>
#include <iostream>
#include <string>
#include <vector>
#include "ast.h"
#include "common.h"
#include "cfg.h"
#include <unordered_map>
using namespace std;

// 遍历抽象语法树节点产生图片
void graph_visit_ast_node(Agraph_t *g, std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable)
{
    // Agnode_t *graph_node;
    std::unordered_map<std::string, Agnode_t *> GraphNodeMap;
    for (int i = 0; i < nodeTable.size();i++) {
        CfgNode *node = nodeTable[i];
        if (node->Del) { continue; }
        Agnode_t *cfgnode = agnode(g, (char *)node->label.c_str(), 1);
        GraphNodeMap.emplace(node->label, cfgnode);
        string IRs;
        std::vector<IRInst *> code;
        code = node->blockInsts.getInsts();
        // 换行要用\\l
        for (auto &inst : code) {
            std::string instStr;
            inst->toString(instStr);
            IRs += instStr + " \\l ";
        }
        // | 用于分栏
        std::string label = node->label + "|" + IRs;
        agsafeset(cfgnode, (char *)"label", (char *)label.c_str(), "");
        agsafeset(cfgnode, (char *)"shape", (char *)"record", (char *)"");
    }
    for (int i = 0;i < edgeTable.size();i++) {
        CfgEdge *edge = edgeTable[i];
        if (edge->Del) {
            continue;
        }
        std::string label1 = edge->fromNodeLabel;
        std::string label2 = edge->toNodeLabel;
        // 创建边，每条边不设置名字
        agedge(g, GraphNodeMap[label1], GraphNodeMap[label2], "", 1);
    }
    // return graph_node;
}
// 产生控制流图
void OutputCFG(std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable, const std::string filePath)
{
    // 创建GV的上下文
    GVC_t *gv = gvContext();

    // 创建一个图形
    Agraph_t *g = agopen((char *)"ast", Agdirected, nullptr);

    // 设置graph的属性
    // agsafeset(g, (char *)"rankdir", (char *)"LR", (char *)"LR");
    // 指定输出的图像质量
    agsafeset(g, (char *)"dpi", (char *)"600", (char *)"");

    (void)graph_visit_ast_node(g, nodeTable, edgeTable);

    // 设置图形的布局
    gvLayout(gv, g, "dot");

    string fileExtName;

    string::size_type pos = filePath.find_last_of('.');
    if (pos == string::npos) {
        fileExtName = "png";
    } else {
        fileExtName = filePath.substr(pos + 1);
    }

    // 输出到一个文件中，png格式
    gvRenderFilename(gv, g, fileExtName.c_str(), filePath.c_str());

    // 关闭图形上下文，并清理资源
    gvFreeLayout(gv, g);
    agclose(g);
    gvFreeContext(gv);

}