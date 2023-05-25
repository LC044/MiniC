//
// Created by zenglj on 2021/12/21.
//
#include <gvc.h>

#include <iostream>
#include <string>
#include <vector>

#include "ast.h"
#include "common.h"

using namespace std;

// 获取创建图形节点的编号Label
string getNodeLabelName()
{
    static int g_node_num = 0;
    return int2str(g_node_num++);
}

// 获取创建图形边的编号Label
string getEdgeLabelName()
{
    static int g_edge_num = 0;
    return int2str(g_edge_num++);
}

Agnode_t *graph_visit_ast_node(Agraph_t *g, struct ast_node *astnode);

// 表达式节点产生图片
Agnode_t *genExpressStatementGraphNode(Agraph_t *g, struct ast_node *astnode, bool show)
{
    // 遍历左侧抽象语法树
    Agnode_t *left = graph_visit_ast_node(g, astnode);

    // 创建一个图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        // 设置图形节点的属性，显示的Label名字
        if (show) {
            agsafeset(node, (char *)"label", (char *)"expr_show", (char *)"");
        } else {
            agsafeset(node, (char *)"label", (char *)"expr", (char *)"");
        }
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");

        // 创建边，每条边不设置名字
        agedge(g, node, left, "", 1);
    }

    return node;
}

// 两节点产生图片
Agnode_t *genTwoGraphNode(Agraph_t *g, struct ast_node *astnodeleft, struct ast_node *astnoderight, const std::string op_str)
{
    // 先遍历左侧再遍历右侧抽象语法树
    Agnode_t *left = graph_visit_ast_node(g, astnodeleft);
    Agnode_t *right = graph_visit_ast_node(g, astnoderight);

    // 创建一个图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        // 设置图形节点的属性，显示的Label名字
        agsafeset(node, (char *)"label", (char *)op_str.c_str(), (char *)"");
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");

        // 创建边，每条边不设置名字
        agedge(g, node, left, "", 1);
        agedge(g, node, right, "", 1);
    }

    return node;
}

// 叶子节点产生图片
Agnode_t *genLeafGraphNode(Agraph_t *g, struct ast_node *astnode)
{
    // 创建一个图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        std::string id = "-";

        // 设置图形节点的属性
        if (astnode->attr.kind == DIGIT_KIND_INT) {
            id = int2str(astnode->attr.integer_val);
        } else if (astnode->attr.kind == DIGIT_KIND_REAL) {
            id = double2str(astnode->attr.real_val);
        } else if (astnode->attr.kind == DIGIT_KIND_ID) {
            id = astnode->attr.id;
        } else if (astnode->attr.kind == KEYWORD_ID) {
            id = astnode->attr.id;
        }

        // 填充红色,必须加这一句，否则下面的fillcolor属性设置无效
        agsafeset(node, (char *)"style", (char *)"filled", (char *)"");
        agsafeset(node, (char *)"fillcolor", (char *)"yellow", (char *)"");
        agsafeset(node, (char *)"fontcolor", (char *)"black", (char *)"");
        agsafeset(node, (char *)"fontname", (char *)"SimSun", (char *)"");
        agsafeset(node, (char *)"label", (char *)id.c_str(), "");
        agsafeset(node, (char *)"shape", (char *)"record", (char *)"");
    }

    return node;
}

// 根节点产生图片
Agnode_t *genBlockGraphNode(Agraph_t *g, struct ast_node *astnode, const std::string op_str)
{
    std::vector<Agnode_t *> graph_nodes;

    std::vector<struct ast_node *>::iterator pIter;
    for (pIter = astnode->sons.begin(); pIter != astnode->sons.end(); ++pIter) {

        Agnode_t *temp_agnode = graph_visit_ast_node(g, *pIter);
        graph_nodes.push_back(temp_agnode);
    }

    // 创建一个root图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        // 设置图形节点的属性
        // agsafeset(node, (char *)"label", (char *)"block", (char *)"");
        agsafeset(node, (char *)"label", (char *)op_str.c_str(), (char *)"");
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");

        std::vector<Agnode_t *>::iterator pIterNode;
        for (pIterNode = graph_nodes.begin(); pIterNode != graph_nodes.end(); ++pIterNode) {

            // 添加root到该节点的边
            agedge(g, node, *pIterNode, "", 1);
        }
    }

    return node;
}

// 遍历抽象语法树节点产生图片
Agnode_t *graph_visit_ast_node(Agraph_t *g, struct ast_node *astnode)
{
    // 非法节点
    if (nullptr == astnode) {
        return nullptr;
    }

    Agnode_t *graph_node;

    switch (astnode->type) {
    case AST_OP_NULL:

        // 叶子节点
        graph_node = genLeafGraphNode(g, astnode);

        break;

    case AST_OP_MUL:

        // 乘法节点
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "*");

        break;
        /*有修改*/
    case AST_OP_DIV:

        // 除法节点
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "/");

        break;
    case AST_OP_MOD:

        // 除法节点
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "%");

        break;
    case AST_OP_ADD:

        // 加法节点
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "+");

        break;
    case AST_OP_SUB:

        // 减法节点
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "-");

        break;

    case AST_OP_EXPR:

        // 表达式结点，不显示表达式的值

        graph_node = genExpressStatementGraphNode(g, astnode->sons[0], false);

        break;

    case AST_OP_EXPR_SHOW:

        // 表达式结点，显示表达式的值

        graph_node = genExpressStatementGraphNode(g, astnode->sons[0], true);

        break;

    case AST_OP_ASSIGN:

        // 赋值语句
        graph_node = genTwoGraphNode(g, astnode->sons[0], astnode->sons[1], "=");

        break;

    case AST_OP_BLOCK:
        graph_node = genBlockGraphNode(g, astnode, "block");
        break;
    case AST_CU:
        graph_node = genBlockGraphNode(g, astnode, "CU");
        break;
    case AST_VAR_DECL:
        graph_node = genBlockGraphNode(g, astnode, "VARDECL");
        break;
    case AST_FUNC_DEF:
        graph_node = genBlockGraphNode(g, astnode, "FUNCDEF");
        break;
    case AST_ARRAY:
        graph_node = genBlockGraphNode(g, astnode, "ARRAY");
        break;
    case AST_DEF_LIST:
        graph_node = genBlockGraphNode(g, astnode, "DEF_LIST");
        break;
    case AST_DIMS:
        graph_node = genBlockGraphNode(g, astnode, "DIMS");
        break;
    case AST_FARGS:
        graph_node = genBlockGraphNode(g, astnode, "FARGS");
        break;
    case AST_RETURN:
        graph_node = genBlockGraphNode(g, astnode, "RET");
        break;
    case AST_OP_IF:
        graph_node = genBlockGraphNode(g, astnode, "IF");
        break;
    case AST_OP_WHILE:
        graph_node = genBlockGraphNode(g, astnode, "IF");
        break;
    case AST_OP_BREAK:
        graph_node = genBlockGraphNode(g, astnode, "BREAK");
        break;
    case AST_OP_CONTINUE:
        graph_node = genBlockGraphNode(g, astnode, "CONTINUE");
        break;
    default:
        // 错误，不支持
        graph_node = nullptr;
        break;
    }

    return graph_node;
}

// 遍历抽象语法树生成图片
void OutputAST(struct ast_node *root, const std::string filePath)
{
    // 创建GV的上下文
    GVC_t *gv = gvContext();

    // 创建一个图形
    Agraph_t *g = agopen((char *)"ast", Agdirected, nullptr);

    // 设置graph的属性
    // agsafeset(g, (char *)"rankdir", (char *)"LR", (char *)"LR");
    // 指定输出的图像质量
    agsafeset(g, (char *)"dpi", (char *)"600", (char *)"");

    (void)graph_visit_ast_node(g, root);

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
