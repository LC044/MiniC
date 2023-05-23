%{

/* 这里声明语义动作符程序所需要的函数原型或者变量原型或定义等 */
/* 主要包含头文件，extern的全局变量，定义的全局变量等 */

#include <cstdio>
#include <cstring>

// 此文件定义了文法中终结符的类别
#include "parser.h"

%}

/* 使它不要添加默认的规则,这样输入无法被给定的规则完全匹配时，词法分析器可以报告一个错误 */
%option nodefault

/* 产生yywrap函数 */
%option noyywrap

/* flex 生成的扫描器用全局变量yylineno 维护着输入文件的当前行编号 */
%option yylineno

/* 区分大小写 */
%option case-sensitive

/* yytext的类型为指针类型，即char * */
%option pointer

/* 生成可重用的扫描器API，这些API用于多线程环境 */
/* %option reentrant */

%x COMMENT
/* 辅助定义式或者宏，后面使用时带上大括号 */

d			[0-9]
l           [a-zA-Z]
h           [0-9a-fA-F]
white		[\t\040]
white_line  [\r\n]

/* 正规式定义 */
%%
"/*"        {
                // 进入注释子有限自动机
                BEGIN(COMMENT); 
            }

<COMMENT>"*/" { 
                // 结束注释子有限自动机
                BEGIN(INITIAL); 
            }

<COMMENT>([^*]|\n)+|.  {
                ; // 注释子有限自动机中，忽略所有字符，含换行符等
            }

<COMMENT><<EOF>> {
                // 注释子有限自动机，没有遇到*/但是文件结束
                printf("Line %d: Unterminated comment\n", yylineno); 
                return YYerror; 
            }

"//".*    {
                ; // 忽略行注释
            }


[1-9]{d}*|0		{
                yylval.integer_num.val = (int)strtol(yytext, (char **)NULL, 10);
                yylval.integer_num.lineno = yylineno;
                // printf("%s  %d\n",yytext, yylval.integer_num.val);
                return T_DIGIT;
           }
"0"(x|X){h}+	{
                yylval.integer_num.val = (int)strtol(yytext, (char **)NULL, 16);
                yylval.integer_num.lineno = yylineno;
                // printf("%s  %d\n",yytext, yylval.integer_num.val);
                return T_DIGIT;
            }
"int"    {return INT}
"void"   {return VOID}
{l}+({d}|{l})* {
                char keywords[20][20] = {
                    "int","void","if","continue","break","for","else",
                };
                char str_1[] = "int"; 
                char str_2[] = "void";
                strncpy(yylval.var_id.id, yytext, sizeof(yylval.var_id.id));
                yylval.var_id.lineno = yylineno;
                for(int i = 0; i <20;i++){
                    if(strcmp(keywords[i], yytext) == 0) return yyetext;
                }
                return T_ID;
            }

((({d}+\.{d}+)|({d}+(\.)?)|(\.{d}+))(e|E)(-|\+)?{d}+)|(({d}+\.{d}+)|({d}+\.)|(\.{d}+))		{
                yylval.float_num.val = (double)strtod(yytext, (char **)NULL);
                yylval.float_num.lineno = yylineno;
                // printf("识别的数:%lf\n",yylval.float_num.val);
                return T_FLOAT;
            }
 
"("			{return T_LPAREN;}
")"			{return T_RPAREN;}

"*"			{return T_MUL;}
"+"			{return T_ADD;}
"/"         {return T_DIV;}
"-"         {return T_SUB;}
"="         {return T_ASSIGN;}
";"         {return T_SEMICOLON;}
\%          {return T_MOD;}
"int"       {
                strncpy(yylval.var_id.id, yytext, sizeof(yylval.var_id.id));
                yylval.var_id.lineno = yylineno;
                // yylval.var_id.type_ = 0;
                printf("%s\n", yylval.var_id.id);
                return T_INT;
            }
"void"      {return T_VOID;}

{white}+	 ;

{white_line}+ ;

.			{
                printf("Line %d: Invalid char %s\n", yylineno, yytext);
                return YYUNDEF;
            }
%%
