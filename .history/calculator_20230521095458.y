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
};

// 文法的开始符号
%start  Input

// 指定文法的终结符号，<>可指定文法属性
%token <integer_num> T_DIGIT
%token <var_id> T_ID

%token <float_num> T_FLOAT

%token T_MUL        // 乘法运算符'*'
%token T_ADD        // 加法运算符'+'
%token T_DIV        // 除法运算符'/''
%token T_SUB        // 减法运算符'-'
%token T_MOD        // 取模运算符'%'
%token T_LPAREN     // 左小括号'('
%token T_RPAREN     // 右小括号')'
%token T_ASSIGN     // 赋值运算符=
%token T_SEMICOLON  // 分号;
/* 新增MiniC的终结符 */
%token T_INT       // INT 类型关键字
%token T_VOID     // void 类型关键字

/* %token  */
// 指定文法的非终结符号，<>可指定文法属性
%type <node> Block
%type <node> Statement
%type <node> P
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> type
%type <node> def
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
/* %left P */
%nonassoc '|' UMINUS
%%
Input        : Block
            {
                // Statements归约到Input时要执行的语义动作程序，C语言编写
                ast_root = $1;
            }
Block   : Statement
            {
                // 创建一个AST_OP_BLOCK类型的中间节点，孩子为Statement($1)
                $$ = new_ast_node(AST_OP_BLOCK, $1);
            }
        | Block Statement
                {
                    // Statement($2)作为Block($1)的孩子 
                    $2->parent = $1;
                    $1->sons.push_back($2);
                    $$ = $1;
                };

Statement   :  T_ID T_ASSIGN Expr T_SEMICOLON
            {
                // 归约到Statement时要执行的语义动作程序
                // 赋值语句，不显示值

                struct ast_node * id_leaf_node;

                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_ID;
                temp_val.lineno = $1.lineno;
                strncpy(temp_val.id, $1.id, sizeof(temp_val.id));

                id_leaf_node = new_ast_leaf_node(temp_val);

                // 创建一个AST_OP_ASSIGN类型的中间节点，孩子为Id和Expr($3)
                $$ = new_ast_node(AST_OP_ASSIGN, id_leaf_node, $3);
            }
        | type def
            {
                // 创建一个AST_OP_EXPR类型的中间节点，孩子为Expr($1)
                $$ = new_ast_node(AST_DEF, $1,$2);
            }
        | Expr T_SEMICOLON
            {
                // Expr归约到Statement时要执行的语义动作程序
                // 表达式语句，不显示表达式的值

                // 创建一个AST_OP_EXPR类型的中间节点，孩子为Expr($1)
                $$ = new_ast_node(AST_OP_EXPR, $1);
            }
        | Expr
            {
                // Expr归约到Statement时要执行的语义动作程序
                // 表达式语句，需要显示表达式的值

                // 创建一个AST_OP_EXPR_SHOW类型的中间节点，孩子为Expr($1)
                $$ = new_ast_node(AST_OP_EXPR_SHOW, $1);
            };

Expr   :  Expr T_ADD Term
            {
                /* Expr = Expr + Term */

                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_ADD, $1, $3);
            }
        | Expr T_SUB Term
            {
                /* Expr = Expr - Term */

                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_SUB, $1, $3);
            }
       |  Term
            {
                /* Expr = Term */
                $$ = $1;
            };

Term   :  Term T_MUL P
            {
                /* Term = Term * Factor */

                // 创建一个AST_OP_MUL类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_MUL, $1, $3);
            }
        | Term T_DIV P
        {
                /* Term = Term / Factor */

                // 创建一个AST_OP_DIV类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_DIV, $1, $3);
        }
        | Term T_MOD P
        {
                /* Term = Term % Factor */

                // 创建一个AST_OP_MOD类型的中间节点，孩子为Expr($1)和Term($3)
                if($1->attr.kind == DIGIT_KIND_REAL or $3->attr.kind == DIGIT_KIND_REAL){
                    char *error = "错了错了,'%' 运算必须是int";
                    error = "error: invalid operands to binary % (must 'int' and 'int')";
                    yyerror(error);
                    return -1;
                }
                $$ = new_ast_node(AST_OP_MOD, $1, $3);
        }
       |  P
            {
                /* Term = Factor */
                $$ = $1;
            };
P       : T_ADD P  %prec UMINUS
            {
                
                // 创建抽象语法树的叶子节点，赋值为0
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_INT;
                temp_val.integer_val = 0;
                temp_val.lineno = $2->attr.lineno;
                // 创建一个AST_OP_MUL类型的中间节点，孩子为0和Term($2)
                struct ast_node *temp_node  = new struct ast_node();
                temp_node->attr = temp_val;
                $$ = new_ast_node(AST_OP_ADD, temp_node, $2);
            }
        | T_SUB P %prec UMINUS
            {
                // 创建抽象语法树的叶子节点，赋值为0
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_INT;
                temp_val.integer_val = 0;
                temp_val.lineno = $2->attr.lineno;
                // 创建一个AST_OP_SUB类型的中间节点，孩子为0和Term($3)
                struct ast_node *temp_node  = new struct ast_node();
                temp_node->attr = temp_val;
                $$ = new_ast_node(AST_OP_SUB, temp_node, $2);
            }
        | Factor
            {
                $$ = $1;
            }
type   :  T_INT
            {
                
            }
        | T_VOID
            {

            }
Factor :  T_LPAREN Expr T_RPAREN
            {
                /* Factor = Expr */
                $$ = $2;
            }
       |  T_DIGIT
            {
                // 终结符作为抽象语法树的叶子节点进行创建

                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_INT;
                temp_val.integer_val = $1.val;
                temp_val.lineno = $1.lineno;

                $$ = new_ast_leaf_node(temp_val);
            }
       |  T_FLOAT
            {
                // 终结符作为抽象语法树的叶子节点进行创建

                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_REAL;
                temp_val.real_val = $1.val;
                temp_val.lineno = $1.lineno;

                $$ = new_ast_leaf_node(temp_val);
            }
       | T_ID {
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
