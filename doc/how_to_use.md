[TOC]



## 前言

这是一个可写进简历的课程作业。

参考:

[南大的编译原理实验课](https://github.com/three-water666/MiniC/)

## 词法分析

### 💠识别Token

词法分析器需要遍历输入的源代码，识别出其中的Token，本项目中使用**Flex**工具进行词法分析。Token是源代码中的最小语法单元，可以是关键字、标识符、运算符、常量等。

🔸 关键字

&emsp;&emsp;MiniC文法里面的关键字有：int , void, if, else, return, break, continue, while, for(后加的)

🔸 标识符

&emsp;&emsp;标识符必须以字母a~z、 A~Z或下划线开头，后面可跟任意个(可为0)字符，这些字符可以是字母、下划线和数字

&emsp;&emsp;标识符最大长度为256

```bash
[a-zA-Z_]([a-zA-Z0-9_])*
```

<div align="center", >
<img src="./image/runoob-regex-id.png">
<p >图1 识别标识符</p>
</div>

🔸 运算符

&emsp;&emsp;支持的运算有

&emsp;&emsp;二元运算：+,-,*,/,%

&emsp;&emsp;一元运算: -(取负), ++, --

&emsp;&emsp;逻辑运算: &&, ||, !

&emsp;&emsp;关系运算: >, <, >=, <=, ==, !=

🔸 常量

  🔹 十进制整数

  ```
  [1-9][0-9]*|0
  ```

  🔹 十六进制整数

  ```
  0(x|X)[0-9a-fA-F]+
  ```

  🔹 八进制整数

  ```
  0[0-7]+
  ```

​		由于文法暂不支持浮点数，所以这里就不写浮点数的识别

### 💠屏蔽注释

词法分析器需要屏蔽注释，以便后续的处理程序忽略注释。

MiniC中支持两种注释

```c
// 单行注释

/*
多行注释
*/
```

### 💠跳过空格和换行符

词法分析器需要跳过输入中的空格和换行符，在Token之间建立正确的分隔符。

### 💠错误处理

词法分析器需要处理输入中的错误，并在出现错误时向后续的处理程序报告错误信息。

```c
int main()
{
	int a, b, c;
	a = -1.5;
	return t;
}
```

错误信息

```bash
Line 5: Invalid num 1.5, Only supports integers 
Line 5: syntax error
yyparse failed
```

## 语法分析

### 💡改造后的MiniC文法

高层定义，包括全局变量的定义int a,b;和函数的定义 int main();

```yacc
Input     : program
program   : segment |  program segment
segment   : type def
type      :  T_INT | T_VOID
def       :  ident idtail
idtail    : varrdef deflist
          | '(' para ')' functail
          | '('  ')' functail
deflist   : ';' | ',' defdata deflist
defdata   : ident varrdef
varrdef   : '[' num ']' varrdef | ε 
para      : paras
paras     : onepara | onepara ',' paras
onepara   : type paradata
paradata  : ident | ident paradatatail
paradatatail : '[' ']' | '[' num ']' | '[' num ']' paradatatail
```

函数内部语句块

```
functail : blockstat | ';'
blockstat : '{' subprogram '}'
subprogram : onestatement| subprogram onestatement | ε 
onestatement : statement | localdef
localdef    : type defdata deflist
```

一条语句，包括语句块、表达式语句，if、while、for、break、continue、return和空语句

```
statement   : blockstat      
             | expr ';' 
             | T_IF '(' expr ')' statement %prec LOWER_THEN_ELSE
             | T_IF '(' expr ')' statement T_ELSE statement
             | T_WHILE '(' expr ')' statement 
             | T_FOR '(' expr ';' expr ';'expr ')' statement
             | T_BREAK ';' 
             | T_CONTINUE ';' 
             | T_RETURN expr ';'
             | T_RETURN ';'  
             | ';' 
```

表达式语句，需要自己定义优先级

```
expr    : lval '=' expr
        | expr T_AND expr
        | expr T_OR expr
        | expr '+' expr
        | expr '-' expr
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr 
        | expr cmp expr
        | factor
cmp     : T_CMP
```

一元运算

```
factor  : '-' factor
        | '!' factor
        | lval T_DEC
        | lval T_INC
        | T_DEC lval
        | T_INC lval
        | rval
rval    : lval
        | '(' expr ')'
        | ident '(' realarg ')'
        | ident '(' ')'
        | num
lval    : ident
        | ident lvaltail
lvaltail    :'[' expr ']'
            |  lvaltail '[' expr ']'
ident   : T_ID
num     : T_DIGIT
realarg     :  realargs
realargs    : expr
            | realargs ',' expr 
```

### 💡构建抽象语法树（AST）

语法分析器需要将识别出的语法结构组织成一个抽象语法树（AST），该树表示程序的语法结构。通常，AST是一种高度抽象的表示程序结构的树形结构。这里使用**Bison**工具进行词法分析构建抽象语法树。

### 💡检查语法错误

语法分析器需要检查程序中是否存在语法错误。如果发现语法错误，语法分析器需要报告错误信息并停止编译过程。

### 💡处理优先级和结合性

语法分析器需要考虑不同运算符的优先级和结合性，从而正确地构建AST。

### 💡处理语法糖

语法分析器需要将语法糖转换为等价的代码。语法糖指的是一些语法上的简写形式，可以简化代码，但需要在语法分析阶段进行转换。

### 💡生成代码注释

语法分析器可以生成代码注释，以便程序员在查看生成代码时更容易理解代码的含义。

💡抽象语法树的实现

示例代码

```c
// test if-else
int ifElse() {
  int a;
  a = 5;
  if (a == 5) {
    a = 25;
  } else {
    a = a * 2;
  }
  return (a);
}


int main() {
  return (ifElse());
}
```

<div align="center", >
<img src="./image/028_if_test1_ast.jpg">
<p >抽象语法树</p>
</div>

本项目是用的是Flex+Bison套装实现的词法分析和语法分析

抽象语法树的每一个非叶子节点都是一个运算符，AST的结构会直接影响到后序IR的生成。因此，在生成AST的时候应尽可能使树结构简单化，避免产生一些不必要的节点，从而加大后续工作量。

## 语义分析

### 🎓类型检查

语义分析器需要对程序中的表达式和操作进行类型检查，确保相容的类型之间进行正确的操作，避免类型不匹配的错误。

### 🎓符号表管理

语义分析器需要构建符号表，用于记录程序中的变量、函数等符号的信息。符号表可以用于检查变量的重复声明、判断变量的作用域、检查函数的参数匹配等。

### 🎓函数调用检查

语义分析器需要检查函数调用的合法性，包括检查函数名、参数个数、参数类型等是否正确。

### 🎓作用域分析

语义分析器需要处理变量和标识符的作用域，确保变量在其作用域内被正确引用和使用。

### 🎓常量折叠

语义分析器可以进行常量折叠优化，将表达式中的常量计算出来，并用计算结果替换表达式。

### 🎓类型推导

语义分析器可以进行类型推导，根据上下文推断变量或表达式的类型，简化程序中类型注解的书写。

### 🎓错误处理

语义分析器需要检测并报告源代码中的语义错误，如未声明的变量、类型不匹配、函数调用错误等。

## 中间代码生成

### ⌛构建中间表示

中间代码生成器需要根据源代码和语法分析器生成的抽象语法树（AST），构建一种中间表示形式。这种中间表示通常是一种高级语言或类似汇编语言的形式，比源代码更接近目标代码，但相对简化和规范化。

### ⌛表达式转换

中间代码生成器需要将源代码中的各种表达式转换为中间表示形式。这包括算术表达式、逻辑表达式、赋值表达式等。

### ⌛控制流转换

中间代码生成器需要处理分支语句（如if语句、switch语句）和循环语句（如for循环、while循环），将它们转换为中间表示形式。

### ⌛符号表处理

中间代码生成器需要处理符号表，以解析变量和函数的引用、处理作用域等。

### ⌛常量和临时变量处理

中间代码生成器需要处理常量的表示和处理临时变量的生成，以便进行计算和存储。

### ⌛优化

中间代码生成器可以进行一些简单的局部优化，如常量折叠、常量传播等，以改进中间代码的质量和效率。

### ⌛错误处理

中间代码生成器需要检查源代码和语法分析器生成的抽象语法树是否存在不符合语义规则的情况，并报告错误信息。

## 代码优化

### 🔎去除冗余代码

通过识别和删除冗余代码来减少代码的大小和复杂度，提高代码可读性和维护性。

### 🔎减少函数调用

减少函数调用可以减少函数调用的开销和栈帧的创建和销毁等操作。

### 🔎循环优化

对循环结构进行优化，例如展开循环、循环变量初始值的调整等，以提高循环的效率。

### 🔎常数折叠

在编译期间对一些常量表达式进行计算，以减少程序运行时的计算量。

### 🔎变量复用

通过复用已有的变量来减少内存分配和释放的开销，提高程序的效率。

### 🔎数据流分析

对程序的数据流进行分析，以便更好地了解程序的执行过程并优化程序。

### 🔎硬件指令优化

针对特定的硬件指令，对程序进行优化以提高程序性能。

### 🔎并行优化

对多线程、多进程、分布式和GPU编程等内容进行优化，以利用多核处理器和其他并行资源提高程序性能。

## 基本块划分及控制流图

