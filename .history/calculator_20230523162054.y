%{
#include <cstdio>
#include <cstring>

// 词法分析头文件
#include "lexer.h"

// bison生成的头文件
#include "parser.h"

// 抽象语法树函数定义原型头文件
#include "ast.h"

// LR分析失败时所调用函数的原型声明
void yyerror(char * msg);

%}

// 联合体声明，用于后续终结符和非终结符号属性指定使用
%union {
    struct ast_node * node;
    digit_int_attr integer_num; // 整型字面量
    digit_real_attr float_num;  // 实数字面量
    var_id_attr var_id;         // 标识符（变量名）
    keyword_attr keyword;
};

// 文法的开始符号
%start  Input

// 指定文法的终结符号，<>可指定文法属性
%token <integer_num> T_DIGIT
%token <var_id> T_ID

%token <float_num> T_FLOAT
%token <var_id> T_INT       // INT 类型关键字
%token <var_id> T_VOID     // void 类型关键字
%token <var_id> T_IF       // INT 类型关键字
%token <var_id> T_ELSE     // void 类型关键字
%token <var_id> T_FOR       // INT 类型关键字
%token <var_id> T_BREAK     // void 类型关键字
%token <var_id> T_CONTINUE     // INT 类型关键字
%token <var_id> T_WHILE     // INT 类型关键字
%token <var_id> T_RETURN

%token T_MUL        // 乘法运算符'*'
%token T_ADD        // 加法运算符'+'
%token T_DIV        // 除法运算符'/''
%token T_SUB        // 减法运算符'-'
%token T_MOD        // 取模运算符'%'
%token T_LPAREN     // 左小括号'('
%token T_RPAREN     // 右小括号')'
%token T_ASSIGN     // 赋值运算符=
%token T_SEMICOLON  // 分号;
%token T_LC         // {
%token T_RC         // }
%token T_LB         // [
%token T_RB         // ]
/* 新增MiniC的终结符 */


/* %token  */
// 指定文法的非终结符号，<>可指定文法属性
%type <node> Block
%type <node> Statement
%type <node> program segment type def idtail deflist defdata varrdef functail para onepara blockstat
%type <node> paradata paradatatail subprogram onestatement localdef statement 
%type <node> breakstat continuestat returnstat assignstat emptystat whilestat ifstat
%type <node> expr assexpr lval 
%type <node> orexpr andexpr cmpexpr cmps aloexpr addsub item muldiv factor lop selfexpr selfop
%type <node> funccall realarg elem literal 

%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
/* %left P */
%nonassoc '|' UMINUS

%%
Input        : program
            {
                // Statements归约到Input时要执行的语义动作程序，C语言编写
                ast_root = $1;
            }
program   : segment
            {
                // 创建一个AST_OP_BLOCK类型的中间节点，孩子为Statement($1)
                $$ = new_ast_node(AST_OP_BLOCK, $1);
            }
        | program segment
                {
                    // Statement($2)作为Block($1)的孩子 
                    $2->parent = $1;
                    $1->sons.push_back($2);
                    $$ = $1;
                };

segment   :type def
            {
                $$ = new_ast_node(AST_DEF, $1,$2);
            }
type   :  T_INT {
                // 终结符作为抽象语法树的叶子节点进行创建
                struct ast_node_attr temp_val;
                temp_val.kind = KEYWORD_ID;
                temp_val.lineno = $1.lineno;
                strncpy(temp_val.id, $1.id, sizeof(temp_val.id));
                printf("%s\n", temp_val.id);
                $$ = new_ast_leaf_node(temp_val);
                // $$ = $1;
            }
def    :  T_ID T_SEMICOLON
        {
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_ID;
                temp_val.lineno = $1.lineno;
                strncpy(temp_val.id, $1.id, sizeof(temp_val.id));
                $$ = new_ast_leaf_node(temp_val);
        };


%%

// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
