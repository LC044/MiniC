/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "D:/Project/Compile/lab3/MiniC/calculator.y"

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


#line 89 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "calculator_yacc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_DIGIT = 3,                    /* T_DIGIT  */
  YYSYMBOL_T_ID = 4,                       /* T_ID  */
  YYSYMBOL_T_FLOAT = 5,                    /* T_FLOAT  */
  YYSYMBOL_T_INT = 6,                      /* T_INT  */
  YYSYMBOL_T_VOID = 7,                     /* T_VOID  */
  YYSYMBOL_T_IF = 8,                       /* T_IF  */
  YYSYMBOL_T_ELSE = 9,                     /* T_ELSE  */
  YYSYMBOL_T_FOR = 10,                     /* T_FOR  */
  YYSYMBOL_T_BREAK = 11,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 12,                /* T_CONTINUE  */
  YYSYMBOL_T_WHILE = 13,                   /* T_WHILE  */
  YYSYMBOL_T_RETURN = 14,                  /* T_RETURN  */
  YYSYMBOL_T_MUL = 15,                     /* T_MUL  */
  YYSYMBOL_T_ADD = 16,                     /* T_ADD  */
  YYSYMBOL_T_DIV = 17,                     /* T_DIV  */
  YYSYMBOL_T_SUB = 18,                     /* T_SUB  */
  YYSYMBOL_T_MOD = 19,                     /* T_MOD  */
  YYSYMBOL_T_LPAREN = 20,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 21,                  /* T_RPAREN  */
  YYSYMBOL_T_ASSIGN = 22,                  /* T_ASSIGN  */
  YYSYMBOL_T_SEMICOLON = 23,               /* T_SEMICOLON  */
  YYSYMBOL_T_LC = 24,                      /* T_LC  */
  YYSYMBOL_T_RC = 25,                      /* T_RC  */
  YYSYMBOL_T_LB = 26,                      /* T_LB  */
  YYSYMBOL_T_RB = 27,                      /* T_RB  */
  YYSYMBOL_T_AND = 28,                     /* T_AND  */
  YYSYMBOL_T_OR = 29,                      /* T_OR  */
  YYSYMBOL_T_CMP = 30,                     /* T_CMP  */
  YYSYMBOL_31_ = 31,                       /* '='  */
  YYSYMBOL_CMP_PREC = 32,                  /* CMP_PREC  */
  YYSYMBOL_33_ = 33,                       /* "++"  */
  YYSYMBOL_34_ = 34,                       /* "--"  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_UMINUS = 39,                    /* UMINUS  */
  YYSYMBOL_40_ = 40,                       /* '!'  */
  YYSYMBOL_LOWER_THEN_ELSE = 41,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* ';'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* '['  */
  YYSYMBOL_47_ = 47,                       /* ']'  */
  YYSYMBOL_48_ = 48,                       /* '{'  */
  YYSYMBOL_49_ = 49,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_Input = 51,                     /* Input  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_segment = 53,                   /* segment  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_def = 55,                       /* def  */
  YYSYMBOL_idtail = 56,                    /* idtail  */
  YYSYMBOL_deflist = 57,                   /* deflist  */
  YYSYMBOL_defdata = 58,                   /* defdata  */
  YYSYMBOL_varrdef = 59,                   /* varrdef  */
  YYSYMBOL_functail = 60,                  /* functail  */
  YYSYMBOL_para = 61,                      /* para  */
  YYSYMBOL_paras = 62,                     /* paras  */
  YYSYMBOL_onepara = 63,                   /* onepara  */
  YYSYMBOL_blockstat = 64,                 /* blockstat  */
  YYSYMBOL_subprogram = 65,                /* subprogram  */
  YYSYMBOL_onestatement = 66,              /* onestatement  */
  YYSYMBOL_localdef = 67,                  /* localdef  */
  YYSYMBOL_statement = 68,                 /* statement  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_cmp = 70,                       /* cmp  */
  YYSYMBOL_factor = 71,                    /* factor  */
  YYSYMBOL_ident = 72,                     /* ident  */
  YYSYMBOL_num = 73                        /* num  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   108

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  85

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,     2,     2,     2,     2,     2,
      42,    43,    37,    35,    45,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    32,    33,    34,    39,
      41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    91,    96,   105,   148,   159,   198,   211,
     220,   224,   233,   239,   240,   249,   250,   252,   258,   263,
     267,   275,   287,   288,   289,   290,   298,   299,   302,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   330,   332,
     334,   335,   336,   338,   348,   352,   356,   360,   368
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_DIGIT", "T_ID",
  "T_FLOAT", "T_INT", "T_VOID", "T_IF", "T_ELSE", "T_FOR", "T_BREAK",
  "T_CONTINUE", "T_WHILE", "T_RETURN", "T_MUL", "T_ADD", "T_DIV", "T_SUB",
  "T_MOD", "T_LPAREN", "T_RPAREN", "T_ASSIGN", "T_SEMICOLON", "T_LC",
  "T_RC", "T_LB", "T_RB", "T_AND", "T_OR", "T_CMP", "'='", "CMP_PREC",
  "\"++\"", "\"--\"", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'!'",
  "LOWER_THEN_ELSE", "'('", "')'", "';'", "','", "'['", "']'", "'{'",
  "'}'", "$accept", "Input", "program", "segment", "type", "def", "idtail",
  "deflist", "defdata", "varrdef", "functail", "para", "paras", "onepara",
  "blockstat", "subprogram", "onestatement", "localdef", "statement",
  "expr", "cmp", "factor", "ident", "num", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -27,    28,    -2,   -27,     3,   -27,   -27,   -27,   -27,
     -26,    -2,    15,   -27,    62,    36,    -1,   -27,    -7,   -27,
      13,   -27,     3,   -27,   -27,   -21,    -2,     6,    62,     6,
     -27,    11,   -27,   -27,   -27,   -27,   -27,   -27,    16,    19,
      27,    31,    32,    32,    32,    32,   -27,     3,   -27,    -3,
     -27,   -27,   -27,    18,   -27,   -27,   -27,    32,   -27,   -27,
      32,    39,    45,    45,     0,    62,   -27,   -27,   -27,    32,
     -27,    32,    55,    57,   -27,   -27,   -27,    45,    45,    53,
      53,    73,   -27,    53,   -27
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     0,     2,     3,     0,     1,     4,    47,     5,
      13,    17,     0,     7,     0,     0,     0,    18,    19,    48,
       0,    10,     0,     8,    21,     0,     0,    13,     0,    13,
      16,    23,     9,    15,    20,    14,    11,    12,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,    29,     0,
      24,    27,    26,     0,    42,    46,    45,     0,    34,    35,
       0,     0,    40,    41,     0,     0,    22,    25,    43,     0,
      30,     0,     0,     0,    37,    44,    28,    38,    39,     0,
       0,    31,    33,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,   -27,    87,    -5,   -27,   -27,   -15,    49,     5,
     -27,   -27,    66,   -27,    74,   -27,    59,   -27,     1,    34,
     -27,   -27,     7,    90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     5,     9,    13,    23,    28,    14,
      32,    16,    17,    18,    48,    49,    50,    51,    52,    53,
      71,    54,    55,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,     8,    30,     1,     1,    38,    15,     8,    39,    40,
      41,    42,    10,    36,    19,     8,    11,     1,    19,    38,
      12,    15,    39,    40,    41,    42,    47,    31,     6,    29,
      68,    69,    35,    43,    37,    19,     8,    44,    26,    45,
      24,    46,    25,    75,    47,    31,    66,    43,    68,    69,
      76,    44,    12,    45,    29,    46,    19,     8,    57,    31,
      27,    38,    70,    58,    39,    40,    41,    42,    43,    68,
      69,    59,    44,    60,    45,    68,    61,    62,    63,    64,
      81,    82,    83,    74,    84,    68,    69,    68,    69,    43,
       7,    72,    34,    44,    73,    45,    65,    46,    79,    33,
      80,    31,    20,    77,     0,    78,    21,    22,    67
};

static const yytype_int8 yycheck[] =
{
       3,     4,    23,     6,     6,     8,    11,     4,    11,    12,
      13,    14,     5,    28,     3,     4,    42,     6,     3,     8,
      46,    26,    11,    12,    13,    14,    31,    48,     0,    22,
      30,    31,    27,    36,    29,     3,     4,    40,    45,    42,
       4,    44,    43,    43,    49,    48,    49,    36,    30,    31,
      65,    40,    46,    42,    47,    44,     3,     4,    42,    48,
      47,     8,    44,    44,    11,    12,    13,    14,    36,    30,
      31,    44,    40,    42,    42,    30,    42,    43,    44,    45,
      79,    80,     9,    44,    83,    30,    31,    30,    31,    36,
       3,    57,    26,    40,    60,    42,    47,    44,    43,    25,
      43,    48,    12,    69,    -1,    71,    44,    45,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    51,    52,    53,    54,     0,    53,     4,    55,
      72,    42,    46,    56,    59,    54,    61,    62,    63,     3,
      73,    44,    45,    57,     4,    43,    45,    47,    58,    72,
      23,    48,    60,    64,    62,    59,    57,    59,     8,    11,
      12,    13,    14,    36,    40,    42,    44,    54,    64,    65,
      66,    67,    68,    69,    71,    72,    73,    42,    44,    44,
      42,    69,    69,    69,    69,    58,    49,    66,    30,    31,
      44,    70,    69,    69,    44,    43,    57,    69,    69,    43,
      43,    68,    68,     9,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    54,    55,    56,    56,
      57,    57,    58,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    64,    65,    65,    65,    66,    66,    67,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      69,    69,    69,    70,    71,    71,    71,    72,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     2,     2,     4,
       1,     3,     2,     0,     4,     1,     1,     0,     1,     1,
       3,     2,     3,     0,     1,     2,     1,     1,     3,     1,
       2,     5,     7,     5,     2,     2,     1,     3,     3,     3,
       2,     2,     1,     1,     3,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Input: program  */
#line 87 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                // Statements归约到Input时要执行的语义动作程序，C语言编写
                ast_root = (yyvsp[0].node);
            }
#line 1211 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 3: /* program: segment  */
#line 92 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                // 创建一个AST_CU类型的中间节点，孩子为Statement($1)
                (yyval.node) = new_ast_node(AST_CU, (yyvsp[0].node));
            }
#line 1220 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 4: /* program: program segment  */
#line 97 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                // Statement($2)作为Block($1)的孩子 
                (yyvsp[0].node)->parent = (yyvsp[-1].node);
                (yyvsp[-1].node)->sons.push_back((yyvsp[0].node));
                (yyval.node) = (yyvsp[-1].node);
            }
#line 1231 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 5: /* segment: type def  */
#line 106 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {   
                //  判断是变量定义还是函数定义
                if ((yyvsp[0].node)->type == AST_DEF_LIST) {
                    // int a,b,c[5]; int a[3];              
                    // $2 的第一个孩子节点为第一个变量，第二个孩子节点为变量列表，是一个二层树
                    // 需要把变量列表展开，并删除$2这个临时节点
                    // 返回结果为AST_VAR_DECL节点，第一个孩子为变量类型，后面的孩子为变量名
                    struct ast_node * temp_node;
                    temp_node = new_ast_node(AST_DEF_LIST,(yyvsp[-1].node),(yyvsp[0].node)->sons[0]);
                    std::vector<struct ast_node *>::iterator pIterNode;
                    // 变量列表是从右向左递归生成的，所以要倒序遍历
                    for (pIterNode = (yyvsp[0].node)->sons[1]->sons.end()-1; pIterNode != (yyvsp[0].node)->sons[1]->sons.begin()-1; --pIterNode) {
                        temp_node->sons.push_back(*pIterNode);
                        (*pIterNode)->parent = temp_node;
                    }
                    // 删除该节点
                    (yyvsp[0].node)->sons[1]->sons.clear();
                    free_ast_node((yyvsp[0].node)->sons[1]);
                    (yyvsp[0].node)->sons.clear();
                    free_ast_node((yyvsp[0].node));

                    (yyval.node) = temp_node;
                }
                else if ((yyvsp[0].node)->type == AST_OP_NULL){
                    // 单变量定义，$2为一个叶子节点
                    // int a;
                    (yyval.node) = new_ast_node(AST_VAR_DECL, (yyvsp[-1].node),(yyvsp[0].node));
                }
                else{
                    // 函数定义
                    // 有四个孩子节点
                    // 1、函数返回类型 int or void
                    // 2、函数名 main
                    // 3、参数列表，有没有参数该节点都存在，该节点的孩子节点（AST_VAR_DECL）为参数，可能有多个
                    // 4、语句块
                    (yyval.node) = new_ast_node((yyvsp[0].node)->type, (yyvsp[-1].node),(yyvsp[0].node)->sons[0],(yyvsp[0].node)->sons[1],(yyvsp[0].node)->sons[2]);
                    // 删除该节点
                    (yyvsp[0].node)->sons.clear();
                    free_ast_node((yyvsp[0].node));
                }
            }
#line 1277 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 6: /* type: T_INT  */
#line 148 "D:/Project/Compile/lab3/MiniC/calculator.y"
                {
                // 终结符作为抽象语法树的叶子节点进行创建
                struct ast_node_attr temp_val;
                temp_val.kind = KEYWORD_ID;
                temp_val.lineno = (yyvsp[0].var_id).lineno;
                strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
                printf("%s\n", temp_val.id);
                (yyval.node) = new_ast_leaf_node(temp_val);
            }
#line 1291 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 7: /* def: ident idtail  */
#line 160 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                // 判断是函数还是变量
                if ((yyvsp[0].node)==NULL)(yyval.node) = (yyvsp[-1].node);
                else if ((yyvsp[0].node)->type == AST_DEF_LIST ){
                    // 第一个变量不是数组
                    /* todo 增加多变量定义 */
                    if((yyvsp[0].node)->sons.size()==0){
                        // 单个变量定义 int a;
                        (yyval.node) = (yyvsp[-1].node);  
                    }
                    else{
                        // 多个变量
                        (yyval.node) = new_ast_node(AST_DEF_LIST, (yyvsp[-1].node),(yyvsp[0].node));
                    }
                }
                else if ((yyvsp[0].node)->type == AST_ARRAY_LIST){
                    // 第一个变量是数组,int a[5],b,c;
                    // 第$2第一个孩子节点是[5],第二个孩子节点为AST_DEF_LIST
                    struct ast_node * temp_node;
                    temp_node = new_ast_node(AST_ARRAY,(yyvsp[-1].node), (yyvsp[0].node)->sons[0]);
                    // $$ = temp_node;
                    (yyval.node) = new_ast_node(AST_DEF_LIST, temp_node,(yyvsp[0].node)->sons[1]);
                    // 删除该节点
                    (yyvsp[0].node)->sons.clear();
                    free_ast_node((yyvsp[0].node));
                }
                else if ((yyvsp[0].node)->type == AST_FUNC_DEF){
                    // 函数定义
                    struct ast_node * temp_node;
                    // 函数定义，孩子节点有三个，函数名、参数列表、函数语句块
                    temp_node = new_ast_node(AST_FUNC_DEF,(yyvsp[-1].node), (yyvsp[0].node)->sons[0],(yyvsp[0].node)->sons[1]);
                    // 删除该节点
                    (yyvsp[0].node)->sons.clear();
                    free_ast_node((yyvsp[0].node));
                    (yyval.node) = temp_node;
                }
            }
#line 1333 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 8: /* idtail: varrdef deflist  */
#line 199 "D:/Project/Compile/lab3/MiniC/calculator.y"
        { 
            if((yyvsp[-1].node)==NULL) {
                // int a,b;
                // a不是数组
                (yyval.node) = (yyvsp[0].node);
            }
            else {
                // int a[5],b,c[4];
                // 第一个变量是数组
                (yyval.node)=new_ast_node(AST_ARRAY_LIST,(yyvsp[-1].node),(yyvsp[0].node));
            }
        }
#line 1350 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 9: /* idtail: '(' para ')' functail  */
#line 212 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {  
            // 函数定义
            (yyval.node) = new_ast_node(AST_FUNC_DEF,(yyvsp[-2].node),(yyvsp[0].node));
             }
#line 1359 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 10: /* deflist: ';'  */
#line 220 "D:/Project/Compile/lab3/MiniC/calculator.y"
              { 
        // $$ = NULL; 
            (yyval.node) = new_ast_node(AST_DEF_LIST);
        }
#line 1368 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 11: /* deflist: ',' defdata deflist  */
#line 225 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {
            // $$ = new_ast_node(AST_DEF_LIST,$2,$3);
            // 递归的添加参数，后面的参数为第一个参数的孩子节点
            (yyvsp[-1].node)->parent = (yyvsp[0].node);
            (yyvsp[0].node)->sons.push_back((yyvsp[-1].node));
            (yyval.node) = (yyvsp[0].node);
        }
#line 1380 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 12: /* defdata: ident varrdef  */
#line 233 "D:/Project/Compile/lab3/MiniC/calculator.y"
                       {
    if((yyvsp[0].node)!=NULL) (yyval.node) = new_ast_node(AST_ARRAY,(yyvsp[-1].node),(yyvsp[0].node));
    else (yyval.node) = (yyvsp[-1].node);
    }
#line 1389 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 13: /* varrdef: %empty  */
#line 239 "D:/Project/Compile/lab3/MiniC/calculator.y"
          {(yyval.node) = NULL; }
#line 1395 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 14: /* varrdef: '[' num ']' varrdef  */
#line 241 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {
            (yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-2].node),(yyvsp[0].node));
        }
#line 1403 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 15: /* functail: blockstat  */
#line 249 "D:/Project/Compile/lab3/MiniC/calculator.y"
                     {(yyval.node) = (yyvsp[0].node);}
#line 1409 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 16: /* functail: T_SEMICOLON  */
#line 250 "D:/Project/Compile/lab3/MiniC/calculator.y"
                      {}
#line 1415 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 17: /* para: %empty  */
#line 252 "D:/Project/Compile/lab3/MiniC/calculator.y"
          {
            // 参数为空
            struct ast_node * nd = new struct ast_node();
            nd->type = AST_FARGS;
            (yyval.node) = nd;
            }
#line 1426 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 18: /* para: paras  */
#line 259 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {   
            (yyval.node) = (yyvsp[0].node);
        }
#line 1434 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 19: /* paras: onepara  */
#line 264 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {
            (yyval.node) = new_ast_node(AST_FARGS,(yyvsp[0].node));
        }
#line 1442 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 20: /* paras: onepara ',' paras  */
#line 268 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                // 递归的添加参数，后面的参数为第一个参数的孩子节点
                (yyvsp[-2].node)->parent = (yyvsp[0].node);
                (yyvsp[0].node)->sons.push_back((yyvsp[-2].node));
                (yyval.node) = (yyvsp[0].node);
            }
#line 1453 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 21: /* onepara: type T_ID  */
#line 276 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                struct ast_node_attr temp_val;
                temp_val.kind = DIGIT_KIND_ID;
                temp_val.lineno = (yyvsp[0].var_id).lineno;
                strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
                (yyval.node) = new_ast_node(AST_VAR_DECL, (yyvsp[-1].node),new_ast_leaf_node(temp_val));
            }
#line 1465 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 22: /* blockstat: '{' subprogram '}'  */
#line 287 "D:/Project/Compile/lab3/MiniC/calculator.y"
                              {(yyval.node) = (yyvsp[-1].node);}
#line 1471 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 23: /* subprogram: %empty  */
#line 288 "D:/Project/Compile/lab3/MiniC/calculator.y"
             {(yyval.node)=NULL;}
#line 1477 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 24: /* subprogram: onestatement  */
#line 289 "D:/Project/Compile/lab3/MiniC/calculator.y"
                          {(yyval.node) = new_ast_node(AST_OP_BLOCK, (yyvsp[0].node));}
#line 1483 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 25: /* subprogram: subprogram onestatement  */
#line 291 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                (yyvsp[0].node)->parent = (yyvsp[-1].node);
                (yyvsp[-1].node)->sons.push_back((yyvsp[0].node));
                (yyval.node) = (yyvsp[-1].node);
            }
#line 1493 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 26: /* onestatement: statement  */
#line 298 "D:/Project/Compile/lab3/MiniC/calculator.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1499 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 27: /* onestatement: localdef  */
#line 299 "D:/Project/Compile/lab3/MiniC/calculator.y"
                      {(yyval.node) = (yyvsp[0].node);}
#line 1505 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 28: /* localdef: type defdata deflist  */
#line 303 "D:/Project/Compile/lab3/MiniC/calculator.y"
            {
                struct ast_node * temp_node;
                temp_node = new_ast_node(AST_DEF_LIST,(yyvsp[-2].node),(yyvsp[-1].node));
                std::vector<struct ast_node *>::iterator pIterNode;
                // 变量列表是从右向左递归生成的，所以要倒序遍历
                for (pIterNode = (yyvsp[0].node)->sons.end()-1; pIterNode != (yyvsp[0].node)->sons.begin()-1; --pIterNode) {
                    temp_node->sons.push_back(*pIterNode);
                    (*pIterNode)->parent = temp_node;
                }
                // 删除该节点
                (yyvsp[0].node)->sons.clear();
                free_ast_node((yyvsp[0].node));
                (yyval.node) = temp_node;
                // $$ = new_ast_node(AST_DEF_LIST, $1, $2, $3);
            }
#line 1525 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 29: /* statement: blockstat  */
#line 319 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = (yyvsp[0].node);}
#line 1531 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 30: /* statement: expr ';'  */
#line 320 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = (yyvsp[-1].node);}
#line 1537 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 31: /* statement: T_IF '(' expr ')' statement  */
#line 321 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_IF,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1543 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 32: /* statement: T_IF '(' expr ')' statement T_ELSE statement  */
#line 322 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_IF,(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));}
#line 1549 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 33: /* statement: T_WHILE '(' expr ')' statement  */
#line 323 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_WHILE,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1555 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 34: /* statement: T_BREAK ';'  */
#line 324 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_BREAK);}
#line 1561 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 35: /* statement: T_CONTINUE ';'  */
#line 325 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_CONTINUE);}
#line 1567 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 36: /* statement: ';'  */
#line 326 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = NULL;}
#line 1573 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 37: /* statement: T_RETURN expr ';'  */
#line 327 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_RETURN,(yyvsp[-1].node));}
#line 1579 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 38: /* expr: expr '=' expr  */
#line 330 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_ASSIGN, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1585 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 39: /* expr: expr cmp expr  */
#line 332 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                           {(yyval.node) = new_ast_node(AST_OP_CMP, (yyvsp[-2].node), (yyvsp[-1].node),(yyvsp[0].node));}
#line 1591 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 40: /* expr: '-' expr  */
#line 334 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                            {(yyval.node) = new_ast_node(AST_OP_NEG, (yyvsp[0].node));}
#line 1597 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 41: /* expr: '!' expr  */
#line 335 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_NOT, (yyvsp[0].node));}
#line 1603 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 42: /* expr: factor  */
#line 336 "D:/Project/Compile/lab3/MiniC/calculator.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1609 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 43: /* cmp: T_CMP  */
#line 338 "D:/Project/Compile/lab3/MiniC/calculator.y"
               {
            {
            struct ast_node_attr temp_val;
            temp_val.kind = CMP_KIND;
            temp_val.lineno = (yyvsp[0].var_id).lineno;
            strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
            printf("%s\n", temp_val.id);
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
        }
#line 1624 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 44: /* factor: '(' expr ')'  */
#line 349 "D:/Project/Compile/lab3/MiniC/calculator.y"
                    {
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 1632 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 45: /* factor: num  */
#line 353 "D:/Project/Compile/lab3/MiniC/calculator.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1640 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 46: /* factor: ident  */
#line 357 "D:/Project/Compile/lab3/MiniC/calculator.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1648 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 47: /* ident: T_ID  */
#line 361 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_ID;
            temp_val.lineno = (yyvsp[0].var_id).lineno;
            strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1660 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;

  case 48: /* num: T_DIGIT  */
#line 369 "D:/Project/Compile/lab3/MiniC/calculator.y"
        {
          // 终结符作为抽象语法树的叶子节点进行创建
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_INT;
            temp_val.integer_val = (yyvsp[0].integer_num).val;
            temp_val.lineno = (yyvsp[0].integer_num).lineno;
            printf("%d\n", temp_val.integer_val);
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1674 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"
    break;


#line 1678 "D:/Project/Compile/lab3/MiniC/calculator_yacc.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 378 "D:/Project/Compile/lab3/MiniC/calculator.y"


// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
