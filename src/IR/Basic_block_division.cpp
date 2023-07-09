/**
* @file
* @brief		进行基本块划分
* @author		shuaikangzhou
* @date		    2023/06/11
* @details      对函数内的线性IR划分基本块，生成控制流图的节点表和边表
*/

#include <string>
#include <vector>
#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
#include <stack>
#include "cfg.h"
int gDot = 0;
bool gshowCfg = false;
std::string gCfgFuncName;
std::string gDotFile = "ssa_cfg.dot";
extern std::string FuncName;
// 获取节点的下一个节点
std::vector<CfgNode *> getNextNodes(CfgNode *node, std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable)
{
    std::vector<CfgNode *> nodes;
    for (CfgEdge *edge : edgeTable) {
        if (edge->fromNodeID == node->id) {
            for (CfgNode *node0 : nodeTable) {
                if (node0->id == edge->toNodeID) {
                    nodes.push_back(node0);
                }
            }

        }
    }
    return nodes;
}

// 判断该节点是否需要删除
bool isDelete(CfgNode *node)
{
    std::vector<IRInst *> code = node->blockInsts.getInsts();
    bool flag = true;
    for (auto &inst : code) {
        if (inst->getOp() == IRINST_JUMP_BR) {
            if (flag) {
                break;
            }
        } else {
            flag = false;
        }
    }
    return flag;
}
// 根据节点id获取节点的label
int getNodeId(std::string label, std::vector<CfgNode *> &nodeTable)
{
    // printf("节点表的大小%d\n", nodeTable.size());
    for (CfgNode *Node : nodeTable) {
        if (Node->label == label) {
            return Node->id;
        }
    }
    return -1;
}
CfgNode *getNodeById(int id, std::vector<CfgNode *> &nodeTable)
{
    for (CfgNode *Node : nodeTable) {
        if (Node->id == id) {
            return Node;
        }
    }
    return nullptr;
}
// 深搜遍历节点表，删除不需要的节点，然后修改边的指向
void DFS(std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable, int curNodeID, bool *visited)
{
    // 标记当前节点已经访问
    visited[curNodeID] = true;

    // 获取当前节点信息
    CfgNode *currentNode = getNodeById(curNodeID, nodeTable);
    // printf("访问的节点\n", curNodeID);
    // printf("访问的节点为: %s,id:%d\n", currentNode->label.c_str(), curNodeID);
    // and (code[0]->getOp() == IRINST_JUMP_BR or code[0]->getOp() == IRINST_JUMP_BC)
    // 判断当前节点是否需要删除
    std::vector<IRInst *> code = currentNode->blockInsts.getInsts();
    if (isDelete(currentNode)) {
        // 删除当前节点
        // std::remove(nodeTable);
        // nodeTable.remove(currentNode);
        nodeTable[curNodeID]->Del = true;
        // printf("删除的节点为: %s\n", currentNode->label.c_str());
        // 更新所有出边的终点（即当前节点）为当前节点的后继节点
        std::vector<CfgNode *> nextNodes = getNextNodes(currentNode, nodeTable, edgeTable);
        // printf("删除节点的下一个节点的个数%d\n", nextNodes.size());
        for (CfgNode *nextNode : nextNodes) {
            for (CfgEdge *edge : edgeTable) {
                if (edge->toNodeID == currentNode->id) {
                    edge->toNodeID = nextNode->id;
                    edge->toNodeLabel = nextNode->label;
                    // printf("删除节点的下一个节点：%s\n", nextNode->label.c_str());
                }
            }
        }

        // 从所有出边所指向的节点递归调用DFS
        for (CfgEdge *edge : edgeTable) {
            if (edge->fromNodeID == currentNode->id && !visited[edge->toNodeID]) {
                DFS(nodeTable, edgeTable, edge->toNodeID, visited);
            }
        }

        // 删除当前节点的所有出边
        int i = 0;
        while (i < edgeTable.size()) {
            if (edgeTable[i]->fromNodeID == currentNode->id || edgeTable[i]->toNodeID == currentNode->id) {
                edgeTable.erase(edgeTable.begin() + i);
            } else {
                i++;
            }
        }
    } else {
        resultNodeTable.push_back(currentNode);
        // 从所有出边所指向的节点递归调用DFS
        for (CfgEdge *edge : edgeTable) {
            if (edge->fromNodeID == currentNode->id && !visited[edge->toNodeID]) {
                DFS(nodeTable, edgeTable, edge->toNodeID, visited);
            }
        }
    }
}

/// @brief 生成.dot文件，可以利用graphviz生成控制流图
/// @param filePath 文件名
/// @param nodeTable 节点表
/// @param edgeTable 边表
void outputDot(const std::string &filePath, std::vector<CfgNode *> &nodeTable, std::vector<CfgEdge *> &edgeTable)
{
    // 这里使用C的文件操作，也可以使用C++的文件操作
    // SetFileApisToOEM();
    FILE *fp = fopen(filePath.c_str(), "w");
    if (nullptr == fp) {
        printf("fopen() failed\n");
        return;
    }
    std::string start = "digraph{\n node[shape = record];\n entry [label=\"L0 | entry \\l\"];";
    fprintf(fp, "%s\n", start.c_str());

    for (int i = 0;i < nodeTable.size();i++) {
        CfgNode *node = nodeTable[i];
        if (node->Del) {
            continue;
        }
        std::vector<IRInst *> code;
        code = node->blockInsts.getInsts();
        std::string Block;
        std::string label = node->label.substr(1, node->label.length() - 1);
        Block += label + " [label=\"" + label + " |  ";
        for (auto &inst : code) {
            std::string instStr;
            inst->toString(instStr);
            Block += instStr + " \\l ";
            if (inst->getOp() == IRINST_JUMP_BR) {
                // break;
            }
            // if()
        }
        Block += " \"];";
        fprintf(fp, "%s\n", Block.c_str());
    }
    std::string edges = "entry -> " + nodeTable[0]->label.substr(1, nodeTable[0]->label.length() - 1) + ";";
    fprintf(fp, "%s\n", edges.c_str());
    for (int i = 0;i < edgeTable.size();i++) {

        CfgEdge *edge = edgeTable[i];
        if (edge->Del) {
            continue;
        }
        std::string label1 = edge->fromNodeLabel.substr(1, edge->fromNodeLabel.length() - 1);
        std::string label2 = edge->toNodeLabel.substr(1, edge->toNodeLabel.length() - 1);
        edges = label1 + " -> " + label2 + ";";
        fprintf(fp, "%s\n", edges.c_str());
    }
    // 遍历所有的线性IR指令，文本输出
    fprintf(fp, "}");

    fclose(fp);
}
InterCode *Basic_block_division(InterCode *blockInsts)
{
    InterCode *BlockInsts = new InterCode();
    // return BlockInsts;
    // printf("指令长度：%d\n", blockInsts->getCodeSize());
    std::vector<CfgNode *> nodeTable;

    std::vector<CfgEdge *> edgeTable;
    std::vector<IRInst *> code = blockInsts->getInsts();
    CfgNode *node = new CfgNode();
    node->label = ".L1";
    int id = 0;
    node->id = id++;
    // 划分基本块
    // 建立节点表和边表
    for (auto &inst : code) {
        if (inst->getOp() == IRINST_JUMP_BC) {
            CfgEdge *edge = new CfgEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label1;
            edgeTable.push_back(edge);
            edge = new CfgEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label2;
            edgeTable.push_back(edge);
            node->blockInsts.addInst(inst);
        } else if (inst->getOp() == IRINST_JUMP_BR) {
            std::vector<IRInst *> code = node->blockInsts.getInsts();
            if (code.size() > 0) {
                if (code[code.size() - 1]->getOp() == IRINST_JUMP_BR) {
                    continue;
                }
            }
            CfgEdge *edge = new CfgEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label1;
            edgeTable.push_back(edge);
            node->blockInsts.addInst(inst);
        } else if (inst->getOp() == IRINST_OP_USELESS) {
            nodeTable.push_back(node);
            node = new CfgNode();
            node->id = id++;
            node->label = inst->getLabel();
            // printf("%s %d\n", inst->getLabel().c_str(), node->id);
        } else {
            node->blockInsts.addInst(inst);
        }
    }
    nodeTable.push_back(node);
    // 更新边表里的节点id
    for (int i = 0; i < edgeTable.size(); i++) {
        CfgEdge *e = edgeTable[i];
        e->fromNodeID = getNodeId(e->fromNodeLabel, nodeTable);
        e->toNodeID = getNodeId(e->toNodeLabel, nodeTable);
        // printf("%s -> %s, %d -> %d\n", e->fromNodeLabel.c_str(), e->toNodeLabel.c_str(), e->fromNodeID, e->toNodeID);
    }
    // printf("\n代码块个数:%d\n", nodeTable.size());

    bool visited[id];
    for (int i = 0; i < id; i++) { visited[i] = false; }

    DFS(nodeTable, edgeTable, 0, visited);
    // printf("\n代码块个数:%d\n", nodeTable.size());
    // 将不可达节点删除
    for (int i = 0; i < nodeTable.size(); i++) {
        node = nodeTable[i];
        if (!visited[i]) {
            node->Del = true;
            for (CfgEdge *edge : edgeTable) {
                if (edge->fromNodeID == node->id) {
                    edge->Del = true;
                }
            }
        }
    }
    // 
    for (int i = 0; i < nodeTable.size(); i++) {
        node = nodeTable[i];
        if (node->Del) {
            continue;
        }
        // printf("剩余label：%s\n", node->label.c_str());
        if (i != 0) {
            BlockInsts->addInst(
                new UselessIRInst(node->label + ":")
            );
        }
        std::vector<std::string> tolabels;
        for (int j = 0; j < edgeTable.size(); j++) {
            if (edgeTable[j]->fromNodeID == node->id) {
                tolabels.push_back(edgeTable[j]->toNodeLabel);
                // printf("%s->%s\n", node->label.c_str(), edgeTable[j]->toNodeLabel.c_str());
            }
        }
        std::vector<IRInst *> code;
        code = node->blockInsts.getInsts();
        // printf("出度大小 %d \n", tolabels.size());
        if (tolabels.size() == 2) {
            for (int k = 0; k < code.size(); k++) {
                if (code[k]->getOp() == IRINST_JUMP_BC) {
                    code[k]->label1 = tolabels[0];
                    code[k]->label2 = tolabels[1];
                    // printf("label2:%s\n", tolabels[1].c_str());
                    break;
                }
            }
        } else if (tolabels.size() == 1) {
            for (int k = 0; k < code.size(); k++) {
                if (code[k]->getOp() == IRINST_JUMP_BR) {
                    code[k]->label1 = tolabels[0];
                    break;
                }
            }
        }
        tolabels.clear();
        for (int k = 0; k < code.size(); k++) {
            // 
            BlockInsts->addInst(code[k]);
            if (code[k]->getOp() == IRINST_JUMP_BR) {
                break;
            }
        }

    }
    if (gDot and gCfgFuncName == FuncName) {
        // outputDot(gDotFile, nodeTable, edgeTable);
        OutputCFG(nodeTable, edgeTable, gDotFile);
        gshowCfg = true;
        // printf("\n\n生成控制流图\n");
    }
    if (nodeTable.size() == 1) {
        return blockInsts;
    }
    return BlockInsts;
}