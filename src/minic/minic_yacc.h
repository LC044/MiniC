/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_D_PROJECT_CPPPROJECT_COMPILE_LAB3_MINIC_SRC_MINIC_MINIC_YACC_H_INCLUDED
# define YY_YY_D_PROJECT_CPPPROJECT_COMPILE_LAB3_MINIC_SRC_MINIC_MINIC_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_DIGIT = 258,                 /* T_DIGIT  */
    T_ID = 259,                    /* T_ID  */
    T_FLOAT = 260,                 /* T_FLOAT  */
    T_INT = 261,                   /* T_INT  */
    T_VOID = 262,                  /* T_VOID  */
    T_IF = 263,                    /* T_IF  */
    T_ELSE = 264,                  /* T_ELSE  */
    T_FOR = 265,                   /* T_FOR  */
    T_BREAK = 266,                 /* T_BREAK  */
    T_CONTINUE = 267,              /* T_CONTINUE  */
    T_WHILE = 268,                 /* T_WHILE  */
    T_RETURN = 269,                /* T_RETURN  */
    T_AND = 270,                   /* T_AND  */
    T_OR = 271,                    /* T_OR  */
    T_INC = 272,                   /* T_INC  */
    T_DEC = 273,                   /* T_DEC  */
    T_CMP = 274,                   /* T_CMP  */
    T_COM_ASSIGN = 275,            /* T_COM_ASSIGN  */
    CMP_PREC = 276,                /* CMP_PREC  */
    UMINUS = 277,                  /* UMINUS  */
    LOWER_THEN_ELSE = 280          /* LOWER_THEN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/minic.y"

    struct ast_node * node;
    digit_int_attr integer_num; // 整型字面量
    digit_real_attr float_num;  // 实数字面量
    var_id_attr var_id;         // 标识符（变量名）
    cmp_attr   cmp_attr;

#line 95 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/minic_yacc.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_D_PROJECT_CPPPROJECT_COMPILE_LAB3_MINIC_SRC_MINIC_MINIC_YACC_H_INCLUDED  */
