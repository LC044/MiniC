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
#line 1 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"

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


#line 89 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"

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
  YYSYMBOL_T_AND = 15,                     /* T_AND  */
  YYSYMBOL_T_OR = 16,                      /* T_OR  */
  YYSYMBOL_T_INC = 17,                     /* T_INC  */
  YYSYMBOL_T_DEC = 18,                     /* T_DEC  */
  YYSYMBOL_T_CMP = 19,                     /* T_CMP  */
  YYSYMBOL_20_ = 20,                       /* '='  */
  YYSYMBOL_CMP_PREC = 21,                  /* CMP_PREC  */
  YYSYMBOL_22_ = 22,                       /* '+'  */
  YYSYMBOL_23_ = 23,                       /* '-'  */
  YYSYMBOL_24_ = 24,                       /* '*'  */
  YYSYMBOL_25_ = 25,                       /* '/'  */
  YYSYMBOL_26_ = 26,                       /* '%'  */
  YYSYMBOL_UMINUS = 27,                    /* UMINUS  */
  YYSYMBOL_28_ = 28,                       /* '!'  */
  YYSYMBOL_29_ = 29,                       /* "++"  */
  YYSYMBOL_30_ = 30,                       /* "--"  */
  YYSYMBOL_LOWER_THEN_ELSE = 31,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* ','  */
  YYSYMBOL_36_ = 36,                       /* '['  */
  YYSYMBOL_37_ = 37,                       /* ']'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Input = 41,                     /* Input  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_segment = 43,                   /* segment  */
  YYSYMBOL_type = 44,                      /* type  */
  YYSYMBOL_def = 45,                       /* def  */
  YYSYMBOL_idtail = 46,                    /* idtail  */
  YYSYMBOL_deflist = 47,                   /* deflist  */
  YYSYMBOL_defdata = 48,                   /* defdata  */
  YYSYMBOL_varrdef = 49,                   /* varrdef  */
  YYSYMBOL_functail = 50,                  /* functail  */
  YYSYMBOL_para = 51,                      /* para  */
  YYSYMBOL_paras = 52,                     /* paras  */
  YYSYMBOL_onepara = 53,                   /* onepara  */
  YYSYMBOL_paradata = 54,                  /* paradata  */
  YYSYMBOL_paradatatail = 55,              /* paradatatail  */
  YYSYMBOL_blockstat = 56,                 /* blockstat  */
  YYSYMBOL_subprogram = 57,                /* subprogram  */
  YYSYMBOL_onestatement = 58,              /* onestatement  */
  YYSYMBOL_localdef = 59,                  /* localdef  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_expr = 61,                      /* expr  */
  YYSYMBOL_cmp = 62,                       /* cmp  */
  YYSYMBOL_factor = 63,                    /* factor  */
  YYSYMBOL_rval = 64,                      /* rval  */
  YYSYMBOL_lval = 65,                      /* lval  */
  YYSYMBOL_lvaltail = 66,                  /* lvaltail  */
  YYSYMBOL_realarg = 67,                   /* realarg  */
  YYSYMBOL_realargs = 68,                  /* realargs  */
  YYSYMBOL_ident = 69,                     /* ident  */
  YYSYMBOL_num = 70                        /* num  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   397

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


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
       2,     2,     2,    28,     2,     2,     2,    26,     2,     2,
      32,    33,    24,    22,    35,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    21,    27,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    75,    80,    89,   133,   143,   154,   206,
     207,   208,   209,   214,   226,   227,   236,   237,   238,   241,
     242,   248,   249,   251,   253,   257,   266,   267,   268,   269,
     270,   271,   276,   277,   279,   280,   288,   289,   292,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     333,   341,   342,   343,   344,   345,   346,   347,   349,   350,
     351,   352,   353,   355,   356,   368,   369,   378,   381,   382,
     389,   397
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
  "T_CONTINUE", "T_WHILE", "T_RETURN", "T_AND", "T_OR", "T_INC", "T_DEC",
  "T_CMP", "'='", "CMP_PREC", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS",
  "'!'", "\"++\"", "\"--\"", "LOWER_THEN_ELSE", "'('", "')'", "';'", "','",
  "'['", "']'", "'{'", "'}'", "$accept", "Input", "program", "segment",
  "type", "def", "idtail", "deflist", "defdata", "varrdef", "functail",
  "para", "paras", "onepara", "paradata", "paradatatail", "blockstat",
  "subprogram", "onestatement", "localdef", "statement", "expr", "cmp",
  "factor", "rval", "lval", "lvaltail", "realarg", "realargs", "ident",
  "num", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,  -127,  -127,     5,    22,  -127,     7,  -127,  -127,  -127,
    -127,    76,   191,     1,  -127,     7,    21,  -127,  -127,    20,
    -127,     7,     7,   191,   191,   191,   237,  -127,  -127,    15,
     -10,  -127,   -11,     7,    13,  -127,     3,    20,    -5,    41,
    -127,  -127,    37,  -127,  -127,    51,  -127,   303,   191,   191,
    -127,   191,   191,   191,   191,   191,  -127,   191,  -127,  -127,
     191,    71,   191,    40,  -127,   110,  -127,  -127,  -127,    44,
     -11,    22,  -127,   191,  -127,    46,  -127,   371,   363,    39,
      39,  -127,  -127,  -127,   371,   351,  -127,   351,    53,    52,
     205,   191,    58,    59,    50,    61,    66,    49,  -127,  -127,
       7,  -127,   147,  -127,  -127,  -127,   251,    14,    64,  -127,
    -127,   351,  -127,  -127,   191,  -127,   221,   191,   191,  -127,
    -127,   191,  -127,   264,    20,  -127,  -127,  -127,  -127,    82,
      21,   351,  -127,   315,   277,   327,  -127,  -127,  -127,    88,
     179,   191,   179,  -127,    92,   290,  -127,   179,   191,  -127,
     339,   179,  -127
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     7,     0,     2,     3,     0,     1,     4,    80,
       5,     0,     0,     0,    14,     0,     0,     8,     9,     0,
      81,     0,     0,     0,     0,     0,     0,    59,    67,    68,
      73,    72,     0,     0,     0,    23,    24,     0,    18,     0,
      10,    66,    73,    65,    61,    68,    62,     0,     0,     0,
      60,     0,     0,     0,     0,     0,    11,     0,    64,    63,
       0,     0,     0,    74,    22,     0,    13,    21,    26,    27,
       0,     0,    15,     0,    16,    19,    69,    51,    52,    53,
      54,    55,    56,    57,    58,    50,    71,    78,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    33,
       0,    39,     0,    34,    37,    36,     0,     0,    28,    12,
      25,    17,    20,    70,     0,    75,     0,     0,     0,    45,
      46,     0,    49,     0,     0,    32,    35,    40,    29,     0,
       0,    79,    76,     0,     0,     0,    48,    38,    30,     0,
       0,     0,     0,    31,    41,     0,    43,     0,     0,    42,
       0,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -127,  -127,  -127,   122,    -9,  -127,  -127,   -17,    30,   -28,
      62,  -127,    60,  -127,  -127,  -127,   -26,  -127,    32,  -127,
    -126,   -12,  -127,    47,  -127,    36,  -127,  -127,  -127,    -3,
     -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    10,    17,    18,    37,    19,
      66,    34,    35,    36,    68,   108,   101,   102,   103,   104,
     105,   106,    57,    27,    28,    29,    63,    88,    89,    30,
      31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    39,    40,    11,    33,     7,    67,     1,     2,    56,
      74,     9,    38,    47,   144,    73,   146,    20,    42,    42,
      72,   149,    61,    64,    20,   152,    62,    65,     1,     2,
      69,    16,    58,    59,    32,    60,    77,    78,    71,    79,
      80,    81,    82,    83,    67,    84,    70,   112,    85,    87,
      90,   128,    20,     9,    14,    15,   100,    41,    43,    45,
      45,   111,    33,    53,    54,    55,    21,    22,    58,    59,
      44,    46,    23,    62,    20,     9,    91,    24,    75,   116,
     107,    25,    16,   122,   119,   123,   113,   114,    21,    22,
     117,   118,   129,   100,    23,   120,    12,    38,   121,    24,
     130,   147,   131,    25,    86,   133,   134,   137,    13,   135,
      14,    15,    16,    20,     9,   139,     1,     2,    92,   138,
      93,    94,    95,    96,    97,   143,     8,    21,    22,   145,
     124,   110,   109,    23,   126,     0,   150,     0,    24,     0,
       0,     0,    25,     0,    98,     0,     0,     0,    65,    99,
      20,     9,     0,     1,     2,    92,     0,    93,    94,    95,
      96,    97,     0,     0,    21,    22,     0,     0,     0,     0,
      23,     0,     0,     0,     0,    24,     0,     0,     0,    25,
       0,    98,    20,     9,     0,    65,   125,    92,     0,    93,
      94,    95,    96,    97,    20,     9,    21,    22,     0,     0,
       0,     0,    23,     0,     0,     0,     0,    24,    21,    22,
       0,    25,     0,    98,    23,     0,     0,    65,     0,    24,
      48,    49,     0,    25,    50,     0,     0,    51,    52,    53,
      54,    55,     0,     0,     0,     0,    48,    49,     0,     0,
      50,     0,   115,    51,    52,    53,    54,    55,     0,     0,
       0,     0,    48,    49,     0,     0,    50,     0,   132,    51,
      52,    53,    54,    55,     0,     0,    48,    49,     0,     0,
      50,    14,    15,    51,    52,    53,    54,    55,     0,    48,
      49,     0,     0,    50,     0,   127,    51,    52,    53,    54,
      55,     0,    48,    49,     0,     0,    50,     0,   136,    51,
      52,    53,    54,    55,     0,    48,    49,     0,     0,    50,
       0,   141,    51,    52,    53,    54,    55,     0,    48,    49,
       0,     0,    50,     0,   148,    51,    52,    53,    54,    55,
      48,    49,     0,     0,    50,     0,    76,    51,    52,    53,
      54,    55,    48,    49,     0,     0,    50,     0,   140,    51,
      52,    53,    54,    55,    48,    49,     0,     0,    50,     0,
     142,    51,    52,    53,    54,    55,    48,    49,     0,     0,
      50,     0,   151,    51,    52,    53,    54,    55,    48,     0,
       0,     0,    50,     0,     0,    51,    52,    53,    54,    55,
      50,     0,     0,    51,    52,    53,    54,    55
};

static const yytype_int16 yycheck[] =
{
      12,    16,    19,     6,    13,     0,    32,     6,     7,    26,
      38,     4,    15,    25,   140,    20,   142,     3,    21,    22,
      37,   147,    32,    34,     3,   151,    36,    38,     6,     7,
      33,    36,    17,    18,    33,    20,    48,    49,    35,    51,
      52,    53,    54,    55,    70,    57,    33,    75,    60,    61,
      62,    37,     3,     4,    34,    35,    65,    21,    22,    23,
      24,    73,    71,    24,    25,    26,    17,    18,    17,    18,
      23,    24,    23,    36,     3,     4,    36,    28,    37,    91,
      36,    32,    36,    34,    34,    97,    33,    35,    17,    18,
      32,    32,   107,   102,    23,    34,    20,   100,    32,    28,
      36,     9,   114,    32,    33,   117,   118,   124,    32,   121,
      34,    35,    36,     3,     4,   130,     6,     7,     8,    37,
      10,    11,    12,    13,    14,    37,     4,    17,    18,   141,
     100,    71,    70,    23,   102,    -1,   148,    -1,    28,    -1,
      -1,    -1,    32,    -1,    34,    -1,    -1,    -1,    38,    39,
       3,     4,    -1,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    32,
      -1,    34,     3,     4,    -1,    38,    39,     8,    -1,    10,
      11,    12,    13,    14,     3,     4,    17,    18,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    17,    18,
      -1,    32,    -1,    34,    23,    -1,    -1,    38,    -1,    28,
      15,    16,    -1,    32,    19,    -1,    -1,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,
      19,    -1,    37,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    15,    16,    -1,    -1,    19,    -1,    37,    22,
      23,    24,    25,    26,    -1,    -1,    15,    16,    -1,    -1,
      19,    34,    35,    22,    23,    24,    25,    26,    -1,    15,
      16,    -1,    -1,    19,    -1,    34,    22,    23,    24,    25,
      26,    -1,    15,    16,    -1,    -1,    19,    -1,    34,    22,
      23,    24,    25,    26,    -1,    15,    16,    -1,    -1,    19,
      -1,    34,    22,    23,    24,    25,    26,    -1,    15,    16,
      -1,    -1,    19,    -1,    34,    22,    23,    24,    25,    26,
      15,    16,    -1,    -1,    19,    -1,    33,    22,    23,    24,
      25,    26,    15,    16,    -1,    -1,    19,    -1,    33,    22,
      23,    24,    25,    26,    15,    16,    -1,    -1,    19,    -1,
      33,    22,    23,    24,    25,    26,    15,    16,    -1,    -1,
      19,    -1,    33,    22,    23,    24,    25,    26,    15,    -1,
      -1,    -1,    19,    -1,    -1,    22,    23,    24,    25,    26,
      19,    -1,    -1,    22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,    41,    42,    43,    44,     0,    43,     4,
      45,    69,    20,    32,    34,    35,    36,    46,    47,    49,
       3,    17,    18,    23,    28,    32,    61,    63,    64,    65,
      69,    70,    33,    44,    51,    52,    53,    48,    69,    70,
      47,    65,    69,    65,    63,    65,    63,    61,    15,    16,
      19,    22,    23,    24,    25,    26,    47,    62,    17,    18,
      20,    32,    36,    66,    34,    38,    50,    56,    54,    69,
      33,    35,    47,    20,    49,    37,    33,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    33,    61,    67,    68,
      61,    36,     8,    10,    11,    12,    13,    14,    34,    39,
      44,    56,    57,    58,    59,    60,    61,    36,    55,    50,
      52,    61,    49,    33,    35,    37,    61,    32,    32,    34,
      34,    32,    34,    61,    48,    39,    58,    34,    37,    70,
      36,    61,    37,    61,    61,    61,    34,    47,    37,    70,
      33,    34,    33,    37,    60,    61,    60,     9,    34,    60,
      61,    33,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    44,    44,    45,    46,
      46,    46,    46,    46,    47,    47,    48,    48,    48,    49,
      49,    50,    50,    51,    52,    52,    53,    54,    54,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      64,    64,    64,    65,    65,    66,    66,    67,    68,    68,
      69,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     1,
       2,     3,     4,     3,     1,     3,     2,     3,     1,     3,
       4,     1,     1,     1,     1,     3,     2,     1,     2,     2,
       3,     4,     3,     2,     1,     2,     1,     1,     3,     1,
       2,     5,     7,     5,     9,     2,     2,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     1,     3,
       4,     3,     1,     1,     2,     3,     4,     1,     1,     3,
       1,     1
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
#line 71 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                // Statements归约到Input时要执行的语义动作程序，C语言编写
                ast_root = (yyvsp[0].node);
            }
#line 1299 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 3: /* program: segment  */
#line 76 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                // 创建一个AST_CU类型的中间节点，孩子为Statement($1)
                (yyval.node) = new_ast_node(AST_CU, (yyvsp[0].node));
            }
#line 1308 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 4: /* program: program segment  */
#line 81 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                // Statement($2)作为Block($1)的孩子 
                (yyvsp[0].node)->parent = (yyvsp[-1].node);
                (yyvsp[-1].node)->sons.push_back((yyvsp[0].node));
                (yyval.node) = (yyvsp[-1].node);
            }
#line 1319 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 5: /* segment: type def  */
#line 90 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
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
                    (yyval.node) = new_ast_node(AST_DEF_LIST, (yyvsp[-1].node),(yyvsp[0].node));
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
                    // $2->sons.clear();
                    // free_ast($2);
                    // delete $2;
                }
            }
#line 1366 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 6: /* type: T_INT  */
#line 133 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                {
                // 终结符作为抽象语法树的叶子节点进行创建
                struct ast_node_attr temp_val;
                temp_val.kind = KEYWORD_ID;
                temp_val.lineno = (yyvsp[0].var_id).lineno;
                strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
                // strncpy(temp_val.id, "int", sizeof("int"));
                // printf("%s\n", temp_val.id);
                (yyval.node) = new_ast_leaf_node(temp_val);
            }
#line 1381 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 7: /* type: T_VOID  */
#line 143 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                {
            // 终结符作为抽象语法树的叶子节点进行创建
                struct ast_node_attr temp_val;
                temp_val.kind = KEYWORD_ID;
                temp_val.lineno = (yyvsp[0].var_id).lineno;
                strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
                // printf("%s\n", temp_val.id);
                (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1395 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 8: /* def: ident idtail  */
#line 155 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
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
                else if ((yyvsp[0].node)->type == AST_VAR_INIT){
                    // 第一个变量是数组,int a[5],b,c;
                    // 第$2第一个孩子节点是[5],第二个孩子节点为AST_DEF_LIST
                    struct ast_node * temp_node;
                    temp_node = new_ast_node(AST_OP_ASSIGN,(yyvsp[-1].node), (yyvsp[0].node)->sons[0]);
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
                    // $2->sons[1]->parent = temp_node;
                    // $2->sons.clear();
                    // delete $2;

                    (yyval.node) = temp_node;
                }
            }
#line 1450 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 9: /* idtail: deflist  */
#line 206 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = (yyvsp[0].node);}
#line 1456 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 10: /* idtail: varrdef deflist  */
#line 207 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node)=new_ast_node(AST_ARRAY_LIST,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1462 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 11: /* idtail: '=' expr deflist  */
#line 208 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node)=new_ast_node(AST_VAR_INIT,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1468 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 12: /* idtail: '(' para ')' functail  */
#line 210 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {  
                // 函数定义
                (yyval.node) = new_ast_node(AST_FUNC_DEF,(yyvsp[-2].node),(yyvsp[0].node));
            }
#line 1477 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 13: /* idtail: '(' ')' functail  */
#line 215 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                // 参数为空
                struct ast_node * nd = new struct ast_node();
                nd->type = AST_FARGS;
                // 函数定义
                (yyval.node) = new_ast_node(AST_FUNC_DEF,nd,(yyvsp[0].node));
            }
#line 1489 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 14: /* deflist: ';'  */
#line 226 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
              { (yyval.node) = new_ast_node(AST_DEF_LIST);}
#line 1495 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 15: /* deflist: ',' defdata deflist  */
#line 228 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
        {
            // 递归的添加参数，后面的参数为第一个参数的孩子节点
            (yyvsp[-1].node)->parent = (yyvsp[0].node);
            (yyvsp[0].node)->sons.push_back((yyvsp[-1].node));
            (yyval.node) = (yyvsp[0].node);
        }
#line 1506 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 16: /* defdata: ident varrdef  */
#line 236 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_ARRAY,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1512 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 17: /* defdata: ident '=' expr  */
#line 237 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_ASSIGN,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1518 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 18: /* defdata: ident  */
#line 238 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = (yyvsp[0].node);}
#line 1524 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 19: /* varrdef: '[' num ']'  */
#line 241 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-1].node));}
#line 1530 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 20: /* varrdef: '[' num ']' varrdef  */
#line 242 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1536 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 21: /* functail: blockstat  */
#line 248 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                     {(yyval.node) = (yyvsp[0].node);}
#line 1542 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 22: /* functail: ';'  */
#line 249 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
              {(yyval.node) = new_ast_node(AST_EMPTY);}
#line 1548 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 23: /* para: paras  */
#line 251 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                {(yyval.node) = (yyvsp[0].node);}
#line 1554 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 24: /* paras: onepara  */
#line 254 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
        {
            (yyval.node) = new_ast_node(AST_FARGS,(yyvsp[0].node));
        }
#line 1562 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 25: /* paras: onepara ',' paras  */
#line 258 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                // 递归的添加参数，后面的参数为第一个参数的孩子节点
                (yyvsp[-2].node)->parent = (yyvsp[0].node);
                (yyvsp[0].node)->sons.push_back((yyvsp[-2].node));
                (yyval.node) = (yyvsp[0].node);
            }
#line 1573 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 26: /* onepara: type paradata  */
#line 266 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = new_ast_node(AST_VAR_DECL, (yyvsp[-1].node),(yyvsp[0].node));}
#line 1579 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 27: /* paradata: ident  */
#line 267 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = (yyvsp[0].node);}
#line 1585 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 28: /* paradata: ident paradatatail  */
#line 268 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = new_ast_node(AST_ARRAY, (yyvsp[-1].node),(yyvsp[0].node));}
#line 1591 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 29: /* paradatatail: '[' ']'  */
#line 269 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = new_ast_node(AST_DIMS);}
#line 1597 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 30: /* paradatatail: '[' num ']'  */
#line 270 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-1].node));}
#line 1603 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 31: /* paradatatail: paradatatail '[' num ']'  */
#line 271 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                        {(yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-1].node),(yyvsp[-3].node));}
#line 1609 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 32: /* blockstat: '{' subprogram '}'  */
#line 276 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                              {(yyval.node) = (yyvsp[-1].node);}
#line 1615 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 33: /* blockstat: '{' '}'  */
#line 277 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                              {(yyval.node) = new_ast_node(AST_EMPTY);}
#line 1621 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 34: /* subprogram: onestatement  */
#line 279 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                         {(yyval.node) = new_ast_node(AST_OP_BLOCK, (yyvsp[0].node));}
#line 1627 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 35: /* subprogram: subprogram onestatement  */
#line 281 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                (yyvsp[0].node)->parent = (yyvsp[-1].node);
                (yyvsp[-1].node)->sons.push_back((yyvsp[0].node));
                (yyval.node) = (yyvsp[-1].node);
            }
#line 1637 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 36: /* onestatement: statement  */
#line 288 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1643 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 37: /* onestatement: localdef  */
#line 289 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                       {(yyval.node) = (yyvsp[0].node);}
#line 1649 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 38: /* localdef: type defdata deflist  */
#line 293 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
                struct ast_node * temp_node;
                temp_node = new_ast_node(AST_DEF_LIST,(yyvsp[-2].node),(yyvsp[-1].node));
                std::vector<struct ast_node *>::iterator pIterNode;
                // 变量列表是从右向左递归生成的，所以要倒序遍历
                for (pIterNode = (yyvsp[0].node)->sons.end()-1; pIterNode != (yyvsp[0].node)->sons.begin()-1; --pIterNode) {
                    temp_node->sons.push_back(*pIterNode);
                    (*pIterNode)->parent = temp_node;
                }
                (yyval.node) = temp_node;
            }
#line 1665 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 39: /* statement: blockstat  */
#line 306 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = (yyvsp[0].node);}
#line 1671 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 40: /* statement: expr ';'  */
#line 307 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = (yyvsp[-1].node);}
#line 1677 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 41: /* statement: T_IF '(' expr ')' statement  */
#line 308 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_IF,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1683 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 42: /* statement: T_IF '(' expr ')' statement T_ELSE statement  */
#line 309 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_IF,(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));}
#line 1689 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 43: /* statement: T_WHILE '(' expr ')' statement  */
#line 310 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_WHILE,(yyvsp[-2].node),(yyvsp[0].node));}
#line 1695 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 44: /* statement: T_FOR '(' expr ';' expr ';' expr ')' statement  */
#line 311 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_FOR,(yyvsp[-6].node),(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));}
#line 1701 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 45: /* statement: T_BREAK ';'  */
#line 312 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_BREAK);(yyval.node)->attr.lineno=(yyvsp[-1].var_id).lineno;}
#line 1707 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 46: /* statement: T_CONTINUE ';'  */
#line 313 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_OP_CONTINUE);(yyval.node)->attr.lineno=(yyvsp[-1].var_id).lineno;}
#line 1713 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 47: /* statement: ';'  */
#line 314 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_EMPTY);}
#line 1719 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 48: /* statement: T_RETURN expr ';'  */
#line 315 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_RETURN,(yyvsp[-1].node));}
#line 1725 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 49: /* statement: T_RETURN ';'  */
#line 316 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                                                {(yyval.node) = new_ast_node(AST_RETURN);(yyval.node)->attr.lineno=(yyvsp[-1].var_id).lineno;}
#line 1731 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 50: /* expr: lval '=' expr  */
#line 320 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_ASSIGN, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1737 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 51: /* expr: expr T_AND expr  */
#line 321 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_AND, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1743 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 52: /* expr: expr T_OR expr  */
#line 322 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_OR, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1749 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 53: /* expr: expr '+' expr  */
#line 323 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_ADD, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1755 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 54: /* expr: expr '-' expr  */
#line 324 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_SUB, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1761 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 55: /* expr: expr '*' expr  */
#line 325 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_MUL, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1767 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 56: /* expr: expr '/' expr  */
#line 326 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_DIV, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1773 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 57: /* expr: expr '%' expr  */
#line 327 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_OP_MOD, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1779 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 58: /* expr: expr cmp expr  */
#line 328 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                           {(yyval.node) = new_ast_node(AST_OP_CMP, (yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1785 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 59: /* expr: factor  */
#line 329 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1791 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 60: /* cmp: T_CMP  */
#line 333 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
               {
            struct ast_node_attr temp_val;
            temp_val.kind = CMP_KIND;
            temp_val.lineno = (yyvsp[0].var_id).lineno;
            strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
            // printf("%s\n", temp_val.id);
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1804 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 61: /* factor: '-' factor  */
#line 341 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                      {(yyval.node) = new_ast_node(AST_OP_NEG, (yyvsp[0].node));}
#line 1810 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 62: /* factor: '!' factor  */
#line 342 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_NOT, (yyvsp[0].node));}
#line 1816 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 63: /* factor: lval T_DEC  */
#line 343 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_RDEC,(yyvsp[-1].node));}
#line 1822 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 64: /* factor: lval T_INC  */
#line 344 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_RINC,(yyvsp[-1].node));}
#line 1828 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 65: /* factor: T_DEC lval  */
#line 345 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_LDEC,(yyvsp[0].node));}
#line 1834 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 66: /* factor: T_INC lval  */
#line 346 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = new_ast_node(AST_OP_LINC,(yyvsp[0].node));}
#line 1840 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 67: /* factor: rval  */
#line 347 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                            {(yyval.node) = (yyvsp[0].node);}
#line 1846 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 68: /* rval: lval  */
#line 349 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node)=(yyvsp[0].node);}
#line 1852 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 69: /* rval: '(' expr ')'  */
#line 350 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node) = (yyvsp[-1].node);}
#line 1858 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 70: /* rval: ident '(' realarg ')'  */
#line 351 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                                {(yyval.node) = new_ast_node(AST_FUNC_CALL,(yyvsp[-3].node),(yyvsp[-1].node));}
#line 1864 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 71: /* rval: ident '(' ')'  */
#line 352 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node) = new_ast_node(AST_FUNC_CALL,(yyvsp[-2].node));}
#line 1870 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 72: /* rval: num  */
#line 353 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1876 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 73: /* lval: ident  */
#line 355 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                {(yyval.node) = (yyvsp[0].node);}
#line 1882 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 74: /* lval: ident lvaltail  */
#line 356 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                         {  // 数组引用
            // $$ = new_ast_node(AST_OP_INDEX,$1,$2);
            struct ast_node * temp_node;
            temp_node = new_ast_node(AST_OP_INDEX,(yyvsp[-1].node));
            std::vector<struct ast_node *>::iterator pIterNode;
            for (pIterNode = (yyvsp[0].node)->sons.begin(); pIterNode != (yyvsp[0].node)->sons.end(); ++pIterNode) {
                temp_node->sons.push_back(*pIterNode);
                (*pIterNode)->parent = temp_node;
            }
            (yyval.node) = temp_node;
            }
#line 1898 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 75: /* lvaltail: '[' expr ']'  */
#line 368 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                       {(yyval.node) = new_ast_node(AST_DIMS,(yyvsp[-1].node));}
#line 1904 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 76: /* lvaltail: lvaltail '[' expr ']'  */
#line 370 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
         {
            (yyvsp[-1].node)->parent = (yyvsp[-3].node);
            (yyvsp[-3].node)->sons.push_back((yyvsp[-1].node));
            (yyval.node) = (yyvsp[-3].node);
            // struct ast_node * temp_node = new_ast_node(AST_EMPTY);
            // $$ = new_ast_node(AST_DIMS,$1,$3,temp_node);
         }
#line 1916 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 77: /* realarg: realargs  */
#line 378 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1922 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 78: /* realargs: expr  */
#line 381 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
                   { (yyval.node) = new_ast_node(AST_REAL_ARGS,(yyvsp[0].node));}
#line 1928 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 79: /* realargs: realargs ',' expr  */
#line 383 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
            {
            (yyvsp[0].node)->parent = (yyvsp[-2].node);
            (yyvsp[-2].node)->sons.push_back((yyvsp[0].node));
            (yyval.node) = (yyvsp[-2].node);
            }
#line 1938 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 80: /* ident: T_ID  */
#line 390 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
        {
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_ID;
            temp_val.lineno = (yyvsp[0].var_id).lineno;
            strncpy(temp_val.id, (yyvsp[0].var_id).id, sizeof(temp_val.id));
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1950 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;

  case 81: /* num: T_DIGIT  */
#line 398 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"
        {
          // 终结符作为抽象语法树的叶子节点进行创建
            struct ast_node_attr temp_val;
            temp_val.kind = DIGIT_KIND_INT;
            temp_val.integer_val = (yyvsp[0].integer_num).val;
            temp_val.lineno = (yyvsp[0].integer_num).lineno;
            // printf("%d\n", temp_val.integer_val);
            (yyval.node) = new_ast_leaf_node(temp_val);
        }
#line 1964 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"
    break;


#line 1968 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator_yacc.cpp"

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

#line 407 "D:/Project/CppProject/Compile/lab3/MiniC/src/minic/calculator.y"


// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
