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
%token <var_id> T_RETURN    // return

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
%type <node> program segment type def idtail deflist defdata varrdef functail para onepara paras blockstat
%type <node> paradata paradatatail subprogram onestatement localdef statement 
%type <node> breakstat continuestat returnstat assignstat emptystat whilestat ifstat asstail ortail
%type <node> expr assexpr lval 
%type <node> orexpr andexpr cmpexpr cmps aloexpr addsub item muldiv factor lop selfexpr selfop
%type <node> funccall realarg elem literal 
%type <node> itemtail cmptail andtail alotail
%type <node> ident num
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD


%%
Input   : program
            {
                // Statements归约到Input时要执行的语义动作程序，C语言编写
                ast_root = $1;
            };
program   :  segment
            {
                // 创建一个AST_CU类型的中间节点，孩子为Statement($1)
                $$ = new_ast_node(AST_CU, $1);
            }
            |  program segment
            {
                // Statement($2)作为Block($1)的孩子 
                $2->parent = $1;
                $1->sons.push_back($2);
                $$ = $1;
            };

/*全局变量，函数声明，函数定义*/
segment   : type def
            {   
                //  判断是变量定义还是函数定义
                if ($2->type == AST_DEF_LIST) {
                    // int a,b,c[5]; int a[3];
                    // $$ = new_ast_node(AST_VAR_DECL, $1,$2);
                    struct ast_node * temp_node;
                    // $2 的第一个孩子节点为第一个变量，第二个孩子节点为
                    temp_node = new_ast_node(AST_VAR_DECL,$1,$2->sons[0]);
                    std::vector<struct ast_node *>::iterator pIterNode;
                    for (pIterNode = $2->sons[1]->sons.begin()+1; pIterNode != $2->sons[1]->sons.end(); ++pIterNode) {
                        temp_node->sons.push_back(*pIterNode);
                        pIterNode->parent = temp_node;
                    }
                    // 删除该节点
                    $2->sons[1]->sons.clear();
                    free_ast_node($2->sons[1]);
                    $2->sons.clear();
                    free_ast_node($2);

                    $$ = temp_node;
                }
                else if ($2->type == AST_OP_NULL){
                    // int a;
                    $$ = new_ast_node(AST_VAR_DECL, $1,$2);
                }
                else{
                    $$ = new_ast_node($2->type, $1,$2->sons[0],$2->sons[1],$2->sons[2]);
                    // 删除该节点
                    $2->sons.clear();
                    free_ast_node($2);
                }
                // $$ = $2;
            };
/* 类型 */
type   :  T_INT {
                // 终结符作为抽象语法树的叶子节点进行创建
                struct ast_node_attr temp_val;
                temp_val.kind = KEYWORD_ID;
                temp_val.lineno = $1.lineno;
                strncpy(temp_val.id, $1.id, sizeof(temp_val.id));
                printf("%s\n", temp_val.id);
                $$ = new_ast_leaf_node(temp_val);
            };

def    :  ident idtail
            {
                // 判断是函数还是变量
                if ($2==NULL)$$ = $1;   // 如果后面为';'，则只有ident一个变量 int a;
                else if ($2->type == AST_DEF_LIST ){
                    /* todo 增加多变量定义 */
                    if($2->sons.size()==0){
                        // 单个变量定义 int a;
                        $$ = $1;  
                    }
                    else{
                        $$ = new_ast_node(AST_DEF_LIST, $1,$2);
                    }
                    // 多个变量
                }
                else if ($2->type == AST_DIMS){
                    struct ast_node * temp_node;
                    temp_node = new_ast_node(AST_ARRAY,$1, $2);
                    $$ = temp_node;
                }
                else if ($2->type == AST_FUNC_DEF){
                    // 函数定义
                    struct ast_node * temp_node;
                    // 函数定义，孩子节点有三个，函数名、参数列表、函数语句块
                    temp_node = new_ast_node(AST_FUNC_DEF,$1, $2->sons[0],$2->sons[1]);
                    // 删除该节点
                    $2->sons.clear();
                    free_ast_node($2);
                    $$ = temp_node;
                }
            };

idtail : varrdef deflist 
        { 
            // if($1==NULL and $2!=NULL) {$$ = $2;}
            // else if($2==NULL and $1!=NULL){ $$= $1;printf("array\n");}
            // else if($1 and $2){$$ = new_ast_node(AST_VAR_DECL,$1,$2);}
            // else {$$=NULL;}
            if($1==NULL and $2!=NULL) {$$ = $2;}
            else if($2==NULL and $1!=NULL){ $$= $1;printf("array\n");}
            else if($1 and $2){$$ = new_ast_node(AST_VAR_DECL,$1,$2);}
            else {$$=NULL;}
        }
        | '(' para ')' functail 
        {  
            // $$ = new_ast_node(AST_OP_SUB, $4);
            $$ = new_ast_node(AST_FUNC_DEF,$2,$4);
            // $$ = $4;
             };

/* todo 增加多变量声明和定义：如 int a,b=1,c[4]; */
deflist : ';' { 
        // $$ = NULL; 
            $$ = new_ast_node(AST_DEF_LIST);
        };
        | ',' defdata deflist
        {
            // $$ = new_ast_node(AST_DEF_LIST,$2,$3);
            // 递归的添加参数，后面的参数为第一个参数的孩子节点
            $2->parent = $3;
            $3->sons.push_back($2);
            $$ = $3;
        }
/* 单个变量或数组:a,b[3] */
defdata : ident varrdef{
    if($2!=NULL) $$ = new_ast_node(AST_ARRAY,$1,$2);
    else $$ = $1;
    }

/* 多维数组a[5][9][2] */
varrdef : {$$ = NULL; }
        | '[' num ']' varrdef
        {
            $$ = new_ast_node(AST_DIMS,$2,$4);
        }

functail : blockstat {$$ = $1;}
        | T_SEMICOLON {};

para    : {
            // 参数为空
            struct ast_node * nd = new struct ast_node();
            nd->type = AST_FARGS;
            $$ = nd;
            }
        | paras
        {   
            $$ = $1;
        }

paras   : onepara
        {
            $$ = new_ast_node(AST_FARGS,$1);
        }
        | onepara ',' paras
            {
                // 递归的添加参数，后面的参数为第一个参数的孩子节点
                $1->parent = $3;
                $3->sons.push_back($1);
                $$ = $3;
            };
onepara : type T_ID
            {
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_ID;
                temp_val.lineno = $2.lineno;
                strncpy(temp_val.id, $2.id, sizeof(temp_val.id));
                $$ = new_ast_node(AST_VAR_DECL, $1,new_ast_leaf_node(temp_val));
            };
blockstat : '{' subprogram '}'
            {
                $$ = $2;
                };
subprogram : 
            | onestatement
                {
                    // 创建一个AST_OP_BLOCK类型的中间节点，孩子为Statement($1)
                $$ = new_ast_node(AST_OP_BLOCK, $1);
                }
            | subprogram onestatement
                {
                    // Statement($2)作为Block($1)的孩子 
                    $2->parent = $1;
                    $1->sons.push_back($2);
                    $$ = $1;
                };
onestatement : statement
            {
                $$ = $1;
            }

statement   : blockstat{$$ = $1;}  //另一个语句块
            | assignstat{$$ = $1;} //赋值语句
            | T_RETURN expr ';' {$$ = new_ast_node(AST_RETURN,$2);} // return 语句
assignstat  : expr ';'
            {
                 $$ = $1;
            };
            
expr        : expr '=' expr
            {
                // 创建一个AST_OP_ASSIGN类型的中间节点，孩子为Id和Expr($3)
                $$ = new_ast_node(AST_OP_ASSIGN, $1, $3);
            }
            | expr '+' expr
            {
                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_ADD, $1, $3);
            }
            | expr '-' expr
            {
                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_SUB, $1, $3);
            }
            | expr '*' expr
            {
                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_MUL, $1, $3);
            }
            | expr '/' expr
            {
                // 创建一个AST_OP_ADD类型的中间节点，孩子为Expr($1)和Term($3)
                $$ = new_ast_node(AST_OP_DIV, $1, $3);
            }
            | factor
                {
                    $$ = $1;
                };

factor          : '(' expr ')'
                    {
                        $$ = $2;
                    }
                | num
                    {
                        $$ = $1;
                    }
                | ident 
                    {
                        $$ = $1;
                    };
ident   : T_ID
        {
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_ID;
            temp_val.lineno = $1.lineno;
            strncpy(temp_val.id, $1.id, sizeof(temp_val.id));
            $$ = new_ast_leaf_node(temp_val);
        }
num     : T_DIGIT
        {
          // 终结符作为抽象语法树的叶子节点进行创建
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_INT;
            temp_val.integer_val = $1.val;
            temp_val.lineno = $1.lineno;
            printf("%d\n", temp_val.integer_val);
            $$ = new_ast_leaf_node(temp_val);
        }
%%

// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
