#include <string>
#include <iostream>

#include <unistd.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "lexer.h"
#include "parser.h"
#include "expr.h"
#include "graph.h"
#include "IRCode.h"
#include <time.h>
bool gShowHelp = false;

// 显示抽象语法树
int gShowAST = 0;

// 产生线性IR
int gGenIr = 0;

// 直接运行，默认运行
int gDirectRun = 0;

std::string gInputFile;
std::string gOutputFile;

void showHelp(const std::string &exeName)
{
    std::cout << exeName + " [-o output] -a source" << std::endl;
    std::cout << exeName + " [-o output] -r source" << std::endl;
    std::cout << exeName + " -R source" << std::endl;
}

// 删除字符串的前后空格
std::string trim(const std::string &str)
{
    std::string::size_type pos = str.find_first_not_of(' ');
    if (pos == std::string::npos) {
        return str;
    }

    std::string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != std::string::npos) {
        return str.substr(pos, pos2 - pos + 1);
    }

    return str.substr(pos);
}

int ArgsAnalysis(int argc, char *argv[])
{
    int ch;
    const char options[] = "ho:arR";

    opterr = 1;

lb_check:
    while ((ch = getopt(argc, argv, options)) != -1) {
        switch (ch) {
        case 'o':
            gOutputFile = optarg;
            break;
        case 'a':
            gShowAST = 1;
            break;
        case 'h':
            gShowHelp = true;
            break;
        case 'r':
            // 产生中间IR
            gGenIr = 1;
            break;
        case 'R':
            // 直接运行，默认运行
            gDirectRun = 1;
            break;
        default:
            return -1;
            break; /* no break */
        }
    }

    argc -= optind;
    argv += optind;

    if ((argc >= 1)) {
        gInputFile = argv[0];
        // 不需要这两步操作，否则会出现错误
        // argc--;
        // argv++;
    }

    if (argc != 0) {
        optind = 0;
        goto lb_check;
    }

    // 必须指定输入文件和输出文件
    if (gInputFile.length() == 0) {
        return -1;
    }

    // 这三者只能指定一个
    // !
    int flag = gShowAST + gGenIr + gDirectRun;
    if (flag != 1) {
        return -1;
    }

    if (gOutputFile.empty()) {

        // 默认文件名
        if (gShowAST) {
            gOutputFile = "ast.png";
        } else if (gGenIr) {
            gOutputFile = "ir.txt";
        }
    } else {

        // 输出文件指定，但没有指定-r或者-a或者指定了-R，则出差错
        if (gDirectRun) {
            return -1;
        }
    }

    return 0;
}

extern bool genIR(struct ast_node *, InterCode &);

// 计算器主程序
int main(int argc, char *argv[])
{
    int result;

#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    clock_t start, finish;
    start = clock();
    // 参数解析——有空看，没空不看
    result = ArgsAnalysis(argc, argv);
    if (result < 0) {
        showHelp(argv[0]);
        return -1;
    }

    // 显示帮助
    if (gShowHelp) {
        showHelp(argv[0]);
        return 0;
    }

    // 若指定有参数，则作为词法分析的输入文件
    if ((yyin = fopen(gInputFile.c_str(), "r")) == nullptr) {
        printf("Can't open file %s\n", gInputFile.c_str());
        return -1;
    }

    // 词法、语法分析生成抽象语法树AST
    result = yyparse();
    if (0 != result) {
        printf("yyparse failed\n");
        return -1;
    }

    if (gShowAST) {

        // 遍历抽象语法树，生成抽象语法树图片
        OutputAST(ast_root, gOutputFile);
    }

    if (gGenIr) {

        InterCode IRCode;

        // 产生IR
        result = genIR(ast_root, IRCode);
        if (!result) {
            return -1;
        }

        // 输出IR
        IRCode.outputIR(gOutputFile);
    }

    if (gDirectRun) {

        // 遍历抽象语法树，进行表达式运算
        expr_calculate_show(ast_root);
    }

    // 清理抽象语法树
    free_ast();

    // 清理符号表
    freeValues();
    finish = clock();
    printf("the time cost is: %lfs", double(finish - start) / CLOCKS_PER_SEC);
    // cout << endl << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << endl;
    return 0;
}
