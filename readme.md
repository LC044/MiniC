# minic

[![stars](https://img.shields.io/github/stars/LC044/MiniC.svg)](https://github.com/LC044/MiniC/stargazers)
[![文档](https://img.shields.io/badge/文档-最新-brightgreen.svg)](./doc/readme.md)
[![LICENSE](https://img.shields.io/badge/license-GPL3.0-blue.svg)](LICENSE)

- [minic](#minic)
  - [功能](#功能)
  - [功能示例](#功能示例)
  - [具体功能](#具体功能)
    - [词法分析](#词法分析)
    - [语法分析](#语法分析)
    - [语义分析](#语义分析)
    - [代码优化](#代码优化)
  - [源代码构成](#源代码构成)
  - [注意](#注意)

## 功能

1. ✅选项-a可产生抽象语法树AST

    cmake-build-debug\minic.exe -a -o test.jpg  test.c

2. ✅选项-r可产生线性IR

    cmake-build-debug\minic.exe -i -o test.ir  test.c

3. ✅选项-c可产生控制流图

    cmake-build-debug\minic.exe -c main -o test_main_cfg.png  test.c

## 功能示例

1. [028_if_test1.c](/doc/image/028_if_test1_ast.jpg) 抽象语法树

    <div align="center", >
    <img src="./doc/image/028_if_test1_ast.jpg">
    <p >抽象语法树</p>
    </div>

2. [028_if_test1.c](/doc/image/028_if_test1_ast.jpg) 线性ir

    ``` bash
    define i32 @ifElse() {
        declare i32 %l0 ; variable: return
        declare i32 %l1 ; variable: a
        declare i32 %t2
        declare i1 %t3
        declare i32 %t4
        declare i32 %t5
        declare i32 %t6
        declare i32 %t7
        entry
        %l1 = 5
        %t2 = %l1
        %t3 = cmp eq %t2, 5
        bc %t3, label .L3, label .L4
    .L3:
        %l1 = 25
        br label .L5
    .L4:
        %t4 = %l1
        %t5 = mul %t4, 2
        %l1 = %t5
        br label .L5
    .L5:
        %t6 = %l1
        %l0 = %t6
        %t7 = %l0
        exit %t7
    }
    define i32 @main() {
        declare i32 %l0 ; variable: return
        declare i32 %t1
        declare i32 %t2
        entry
        %t1 = call i32 @ifElse()
        %l0 = %t1
        %t2 = %l0
        exit %t2
    }
    ```

3. [028_if_test1.c](/doc/image/028_if_test1_ast.jpg) 控制流图

    <div align="center">
    <img src="./doc/image/028_if_test1_cfg.png">
    <p>控制流图</p>
    </div>

## 具体功能

### 词法分析

1. 词法分析使用flex实现
2. 识别MiniC文法的所有终结符(标识符、关键字、十进制、八进制、十六进制整数)
3. C语言的注释识别支持
4. 提供文法识别错误的行号定位信息

### 语法分析

1. 语法分析使用bison实现
2. 支持int和void类型，变量只允许int，函数返回值可以使用void和int
3. 变量定义(含全局变量、局部变量)与使用
4. 表达式语句、空语句支持
5. if语句、while语句和赋值语句支持
6. 语句块支持
7. 表达式支持算术运算、关系运算、逻辑运算；满足C语言的优先级、结合性等要求
8. 支持函数定义、声明与函数调用
9. 支持一维数组和多维数组定义与使用
10. 简单变量定义时初始化支持(语法支持，语义暂不支持)
11. 支持for循环
12. 支持自增与自减运算
13. 语法分析错误检查与定位(暂只支持错误定位，不支持错误类型判断)

### 语义分析

1. 采用语法制导翻译，生成抽象语法树
2. 遍历抽象语法树产生中间IR
3. 变量分层管理支持，支持变量的作用域，特别是变量的重名
4. 变量或函数要先声明后使用，否则语义错误
5. 逻辑运算支持短路求值
6. 具备简单的语义错误检查定位和输出
7. 中间IR表达采用实验定义IR

### 代码优化

1. 基本块划分与控制流图生成
2. 控制流图图形化显示(使用graphviz的API产生控制流图)
3. 控制流的优化
   1. 删除不可达基本块
   2. 删除多余Label指令
4. IR的优化
   1. 常量折叠(a = 2+3等价于a=5)
   2. 没有了

<!-- 
git config --global --unset http.proxy

git config --golbal http.proxy <http://127.0.0.1:7890>

git commit -m

git push -u origin main

git reset --hard

老师写好的程序运行方式

.\test\IRCompiler\MINGW-x86_64\IRCompiler.exe -S -I -o test.ir0 test.c -->

## 源代码构成

calculator.l 借助flex工具实现的词法分析器脚本源代码

calculator_lex.cpp 借助flex工具实现的词法分析器自动生成C语言源文件

calculator_lex.h 借助flex工具实现的词法分析器自动生成C语言头文件

calculator.y 借助bison工具实现的语法分析器脚本源代码

calculator_yacc.cpp 借助bison工具实现的语法分析器自动生成C语言源文件

calculator_yacc.h 借助bison工具实现的语法分析器自动生成C语言头文件

ast.cpp 抽象语法树创建所需要的函数

ast.h ast.cpp对应的头文件

graph.cpp 遍历抽象语法树利用graphviz生成图片

graph.h graph.cpp对应的头文件

symbol.cpp 符号表管理

symbol.h symbol.cpp对应的头文件

genIR.cpp 遍历抽象语法树产生线性IR

genSymbol.cpp 遍历抽象语法树产生符号表

Basic_block_diivision.cpp 基本块划分

cfg.cpp 生成控制流图

cfg.h cfg.cpp 对应的头文件

IRInst.cpp 线性IR指令类的实现

IRInst.h 线性IR指令类的头文件

IRCode.cpp 线性IR管理类的实现

IRCode.h 线性IR管理类的头文件

main.cpp MiniC程序的主函数

test.c 测试用例代码

## 注意

注意：该项目受到GPL-3.0许可证的保护。

Copyright © by ShuaikangZhou

警告：本项目的代码和文档受到版权保护，违反GPL-3.0协议的使用将导致法律后果。本项目仅供交流学习和课程作业使用，严禁任何形式的抄袭和未经授权的使用。

如果您是本课程的学生，请务必遵守学院、教师或课程要求，严禁抄袭代码和报告。任何抄袭行为都将视为学术不端，并且可能导致严重的学术和法律后果，本人对违反规定使用本项目的行为不负任何责任。

如果您有任何疑问或需要进一步了解许可证的使用限制，请与我联系。
