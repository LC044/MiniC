#include <string>
#include <vector>
#include "ast.h"
#include "IRCode.h"
#include <string.h>
#include "symbol.h"
#include <stack>
struct DAGNode {
    InterCode blockInsts;  // 代码块
    int id;                // 唯一标识符
    std::string label;     // 标签
};
struct DAGEdge {
    int fromNodeID; // 起始节点标识符
    int toNodeID;   // 结束节点标识符
    std::string fromNodeLabel; //
    std::string toNodeLabel; //
};

// 获取节点的下一个节点
std::vector<DAGNode *> getNextNodes(DAGNode *node, std::vector<DAGNode *> &nodeTable, std::vector<DAGEdge *> &edgeTable)
{
    std::vector<DAGNode *> nodes;
    for (DAGEdge *edge : edgeTable) {
        if (edge->fromNodeID == node->id) {
            for (DAGNode *node0 : nodeTable) {
                if (node0->id == edge->toNodeID) {
                    nodes.push_back(node0);
                }
            }

        }
    }
    return nodes;
}

// 深搜遍历节点表，删除不需要的节点，然后修改边的指向

void DFS(std::vector<DAGNode *> &nodeTable, std::vector<DAGEdge *> &edgeTable, int curNodeID, bool *visited)
{
    // 标记当前节点已经访问
    visited[curNodeID] = true;
    // printf("访问的节点id:%d\n", curNodeID);
    // 获取当前节点信息
    DAGNode *currentNode = nodeTable[curNodeID];
    // and (code[0]->getOp() == IRINST_JUMP_BR or code[0]->getOp() == IRINST_JUMP_BC)
    // 判断当前节点是否需要删除
    std::vector<IRInst *> code = currentNode->blockInsts.getInsts();
    if (code.size() == 1) {
        // 删除当前节点
        nodeTable.erase(nodeTable.begin() + curNodeID);
        printf("删除的节点为: %s\n", currentNode->label.c_str());
        // 更新所有出边的终点（即当前节点）为当前节点的后继节点
        std::vector<DAGNode *> nextNodes = getNextNodes(currentNode, nodeTable, edgeTable);
        printf("删除节点的下一个节点的个数%d\n", nextNodes.size());
        for (DAGNode *nextNode : nextNodes) {
            for (DAGEdge *edge : edgeTable) {
                if (edge->toNodeID == currentNode->id) {
                    edge->toNodeID = nextNode->id;
                    edge->toNodeLabel = nextNode->label;
                    printf("删除节点的下一个节点：%s\n", nextNode->label.c_str());
                }
            }
        }

        // 从所有出边所指向的节点递归调用DFS
        for (DAGEdge *edge : edgeTable) {
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
        // 从所有出边所指向的节点递归调用DFS
        for (DAGEdge *edge : edgeTable) {
            if (edge->fromNodeID == currentNode->id && !visited[edge->toNodeID]) {
                DFS(nodeTable, edgeTable, edge->toNodeID, visited);
            }
        }
    }
}
// 根据节点id获取节点的label
int getNodeId(std::string label, std::vector<DAGNode *> &nodeTable)
{
    // printf("节点表的大小%d\n", nodeTable.size());
    for (DAGNode *Node : nodeTable) {
        if (Node->label == label) {
            return Node->id;
        }
    }
    return -1;
}
InterCode *Basic_block_division(InterCode *blockInsts)
{
    InterCode *BlockInsts = new InterCode();
    // return BlockInsts;
    printf("指令长度：%d\n", blockInsts->getCodeSize());
    std::vector<DAGNode *> nodeTable;
    std::vector<DAGEdge *> edgeTable;
    std::vector<IRInst *> code = blockInsts->getInsts();
    DAGNode *node = new DAGNode();
    node->label = ".L1";
    int id = 0;
    node->id = id++;
    // 划分基本块
    // 建立节点表和边表
    for (auto &inst : code) {
        if (inst->getOp() == IRINST_JUMP_BC) {
            DAGEdge *edge = new DAGEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label1;
            edgeTable.push_back(edge);
            edge = new DAGEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label2;
            edgeTable.push_back(edge);
            node->blockInsts.addInst(inst);
        } else if (inst->getOp() == IRINST_JUMP_BR) {
            DAGEdge *edge = new DAGEdge();
            edge->fromNodeLabel = node->label;
            edge->toNodeLabel = inst->label1;
            edgeTable.push_back(edge);
            node->blockInsts.addInst(inst);
        } else if (inst->getOp() == IRINST_OP_USELESS) {
            nodeTable.push_back(node);
            node = new DAGNode();
            node->id = id++;
            node->label = inst->getLabel();
            printf("%s %d\n", inst->getLabel().c_str(), node->id);
        } else {
            node->blockInsts.addInst(inst);
        }
    }
    nodeTable.push_back(node);
    // 更新边表里的节点id
    for (int i = 0; i < edgeTable.size(); i++) {
        DAGEdge *e = edgeTable[i];
        e->fromNodeID = getNodeId(e->fromNodeLabel, nodeTable);
        e->toNodeID = getNodeId(e->toNodeLabel, nodeTable);
        printf("%s -> %s, %d -> %d\n", e->fromNodeLabel.c_str(), e->toNodeLabel.c_str(), e->fromNodeID, e->toNodeID);
    }
    printf("\n代码块个数:%d\n", nodeTable.size());
    if (nodeTable.size() == 1) {
        return blockInsts;
    }
    bool visited[id];
    for (int i = 0; i < id; i++) { visited[i] = false; }

    DFS(nodeTable, edgeTable, 0, visited);
    printf("\n代码块个数:%d\n", nodeTable.size());

    for (int i = 0; i < edgeTable.size(); i++) {
        DAGEdge *e = edgeTable[i];
        printf("%s -> %s, %d -> %d\n", e->fromNodeLabel.c_str(), e->toNodeLabel.c_str(), e->fromNodeID, e->toNodeID);
    }
    // 
    for (int i = 0; i < nodeTable.size(); i++) {
        node = nodeTable[i];
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
                printf("%s->%s\n", node->label.c_str(), edgeTable[j]->toNodeLabel.c_str());
            }
        }
        std::vector<IRInst *> code;
        code = node->blockInsts.getInsts();
        printf("出度大小 %d \n", tolabels.size());
        if (tolabels.size() == 2) {
            for (int k = 0; k < code.size(); k++) {
                if (code[k]->getOp() == IRINST_JUMP_BC) {
                    code[k]->label1 = tolabels[0];
                    code[k]->label2 = tolabels[1];
                    printf("label2:%s\n", tolabels[1].c_str());
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

    return BlockInsts;
}