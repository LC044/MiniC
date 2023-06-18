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
        // 填充红色,必须加这一句，否则下面的fillcolor属性设置无效
        // agsafeset(node, (char *)"style", (char *)"filled", (char *)"");
        // agsafeset(node, (char *)"fillcolor", (char *)"yellow", (char *)"");
        // agsafeset(node, (char *)"fontcolor", (char *)"black", (char *)"");
        // agsafeset(node, (char *)"fontname", (char *)"SimSun", (char *)"");
        string IRs;
        std::vector<IRInst *> code;
        code = node->blockInsts.getInsts();
        for (auto &inst : code) {
            std::string instStr;
            inst->toString(instStr);
            IRs += instStr + " \\l ";
            if (inst->getOp() == IRINST_JUMP_BR) {
                // break;
            }
            // if()
        }
        std::string label = node->label + "|" + IRs;
        //  "<TABLE><TR><TD>1</TD><TD>Node 1 Info</TD></TR></TABLE>"
        agsafeset(cfgnode, (char *)"label", (char *)label.c_str(), "");
        agsafeset(cfgnode, (char *)"shape", (char *)"record", (char *)"");
    }
    for (int i = 0;i < edgeTable.size();i++) {

        CfgEdge *edge = edgeTable[i];
        if (edge->Del) {
            continue;
        }
        // std::string label1 = edge->fromNodeLabel.substr(1, edge->fromNodeLabel.length() - 1);
        // std::string label2 = edge->toNodeLabel.substr(1, edge->toNodeLabel.length() - 1);
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