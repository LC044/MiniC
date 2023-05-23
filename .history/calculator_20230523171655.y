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
%type <node> program segment type def idtail deflist defdata varrdef functail para onepara paras blockstat
%type <node> paradata paradatatail subprogram onestatement localdef statement 
%type <node> breakstat continuestat returnstat assignstat emptystat whilestat ifstat asstail ortail
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
program   :  program segment
                {
                    // Statement($2)作为Block($1)的孩子 
                    $2->parent = $1;
                    $1->sons.push_back($2);
                    $$ = $1;
                };
            |    segment
            {
                // 创建一个AST_OP_BLOCK类型的中间节点，孩子为Statement($1)
                $$ = new_ast_node(AST_OP_BLOCK, $1);
            }

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
def    :  T_ID idtail
            {
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_ID;
                temp_val.lineno = $1.lineno;
                strncpy(temp_val.id, $1.id, sizeof(temp_val.id));
                $$ = new_ast_leaf_node(temp_val);
                    };

idtail : varrdef deflist
        {
            
        }
        | '(' para ')' functail
        {

        }
functail : blockstat
            {}
        | T_SEMICOLON
        {}
para    : 
        | onepara paras
onepara : type paradata
            {

            }
paras   : 
        {

        }
        | ',' onepara paras
            {

            }
blockstat : '{' subprogram '}'
            {}
subprogram : 
            | onestatement
            | subprogram onestatement
onestatement : localdef
             | statement
localdef    : type defdata
            | deflist
statement   : blockstat
            | assignstat
assignstat  : expr ';'

// --完成--
assexpr         : orexpr asstail
                    {
                    };

// --完成--
asstail         :   { $$ = NULL; }
                | '=' assexpr asstail
                    {
                    };

// --完成--
orexpr          : andexpr ortail
                    {
                    };

// --完成--
ortail          :   { $$ = NULL; }
                | OR andexpr ortail
                    {
                    };

// --完成--
Andexpr         : Cmpexpr Andtail
                    {
                        $$ = node_struct($1, $2, yylineno);
                        parser_tracker("Andexpr-> Cmpexpr Andtail");
                    };

// --完成--
Andtail         :   { $$ = NULL; }
                | AND Cmpexpr Andtail
                    {
                        $$ = operator_node_struct($1, $2, $3, yylineno);
                        parser_tracker("Andexpr-> AND Cmpexpr Andtail");
                    };

// --完成--
Cmpexpr         : Aloexpr Cmptail
                    {
                        $$ = node_struct($1, $2, yylineno);
                        parser_tracker("Cmpexpr-> Aloexpr Cmptail");
                    };

// --完成--
Cmptail         :   { $$ = NULL; }
                | Cmps Aloexpr Cmptail
                    {
                        $$ = operator_node_struct($1, $2, $3, yylineno);
                        parser_tracker("Cmptail-> Cmps Aloexpr Cmptail");
                    };

// --完成--
Cmps            : '>' { $$ = new Operator(Operator::BINARY_GREATER); } 
                | '<' { $$ = new Operator(Operator::BINARY_LESS); } 
                | GE { $$ = new Operator(Operator::BINARY_GREATER_EQUAL); }
                | LE { $$ = new Operator(Operator::BINARY_LESS_EQUAL); }
                | EQ { $$ = new Operator(Operator::BINARY_EQUAL); }
                | NE { $$ = new Operator(Operator::BINARY_NOT_EQUAL); }

// --完成--
Aloexpr         : Item Alotail
                    {
                        if ($2 != NULL)
                            $$ = new Op($1, $2->p_node, $2->p_operator, yylineno);
                        else
                            $$ = $1;
                        parser_tracker("Aloexpr-> Item Alotail");
                    };

// --完成--
Alotail         :   { $$ = NULL; }
                | Addsub Item Alotail
                    {
                        $$ = operator_node_struct($1, $2, $3, yylineno);
                        parser_tracker("Alotail-> Addsub Item Alotail");
                    };

// 之后这些应该就是用来算数的了
// --完成--
Addsub          : '+' { $$ = new Operator(Operator::BINARY_ADD); }
                | '-' { $$ = new Operator(Operator::BINARY_SUB); };

// --完成--
Item            : Factor Itemtail
                    {
                        if ($2 != NULL)
                            $$ = new Op($1, $2->p_node, $2->p_operator, yylineno);
                        else
                            $$ = $1;
                        parser_tracker("Item-> Factor Itemtail");
                    };

// --完成--
Itemtail        :   { $$ = NULL; }
                | Muldiv Factor Itemtail
                    {
                        $$ = operator_node_struct($1, $2, $3, yylineno);
                        parser_tracker("Itemtail-> Muldiv Factor Itemtail");
                    };

// --完成--
Muldiv          : '*' { $$ = new Operator(Operator::BINARY_MUL); }
                | '/' { $$ = new Operator(Operator::BINARY_DIV); };

// --完成--
Factor          : Lop Factor
                    {
                        $$ = new Unary($2, $1, yylineno);
                        parser_tracker("Factor-> Lop Factor");
                    }
                | Val
                    {
                        $$ = $1;
                        parser_tracker("Factor-> Val");
                    }

// --完成--
Lop             : '!' { $$ = new Operator(Operator::UNARY_NOT); }
                | '-' { $$ = new Operator(Operator::UNARY_MINUS); }
                | '&' { $$ = new Operator(Operator::UNARY_ADDRESS); }
                | '*' { $$ = new Operator(Operator::UNARY_INDIRECTION); }  // 这个应该是解引用符号吧，回头要注意
                | INCR { $$ = new Operator(Operator::UNARY_INCR); } 
                | DECR { $$ = new Operator(Operator::UNARY_DECR); };

%%

// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
