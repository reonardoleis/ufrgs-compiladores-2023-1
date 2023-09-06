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
#line 3 "parser.y"

#include "hash.h"
#include "ast_types.h"
#include "ast.h"    
#include "semantic.h"
#include "tac.h"
#include "asmgen.h"
int SyntaxErrors = 0;
int optimize = 0;

#line 82 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    KW_CHAR = 258,                 /* KW_CHAR  */
    KW_INT = 259,                  /* KW_INT  */
    KW_REAL = 260,                 /* KW_REAL  */
    KW_BOOL = 261,                 /* KW_BOOL  */
    KW_IF = 262,                   /* KW_IF  */
    KW_ELSE = 263,                 /* KW_ELSE  */
    KW_LOOP = 264,                 /* KW_LOOP  */
    KW_INPUT = 265,                /* KW_INPUT  */
    KW_OUTPUT = 266,               /* KW_OUTPUT  */
    KW_RETURN = 267,               /* KW_RETURN  */
    OPERATOR_LE = 268,             /* OPERATOR_LE  */
    OPERATOR_GE = 269,             /* OPERATOR_GE  */
    OPERATOR_EQ = 270,             /* OPERATOR_EQ  */
    OPERATOR_DIF = 271,            /* OPERATOR_DIF  */
    TK_IDENTIFIER = 272,           /* TK_IDENTIFIER  */
    LIT_INT = 273,                 /* LIT_INT  */
    LIT_REAL = 274,                /* LIT_REAL  */
    LIT_CHAR = 275,                /* LIT_CHAR  */
    LIT_STRING = 276,              /* LIT_STRING  */
    TOKEN_ERROR = 277              /* TOKEN_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define KW_CHAR 258
#define KW_INT 259
#define KW_REAL 260
#define KW_BOOL 261
#define KW_IF 262
#define KW_ELSE 263
#define KW_LOOP 264
#define KW_INPUT 265
#define KW_OUTPUT 266
#define KW_RETURN 267
#define OPERATOR_LE 268
#define OPERATOR_GE 269
#define OPERATOR_EQ 270
#define OPERATOR_DIF 271
#define TK_IDENTIFIER 272
#define LIT_INT 273
#define LIT_REAL 274
#define LIT_CHAR 275
#define LIT_STRING 276
#define TOKEN_ERROR 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "parser.y"

    HASH* symbol; 
    AST *ast;

#line 184 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KW_CHAR = 3,                    /* KW_CHAR  */
  YYSYMBOL_KW_INT = 4,                     /* KW_INT  */
  YYSYMBOL_KW_REAL = 5,                    /* KW_REAL  */
  YYSYMBOL_KW_BOOL = 6,                    /* KW_BOOL  */
  YYSYMBOL_KW_IF = 7,                      /* KW_IF  */
  YYSYMBOL_KW_ELSE = 8,                    /* KW_ELSE  */
  YYSYMBOL_KW_LOOP = 9,                    /* KW_LOOP  */
  YYSYMBOL_KW_INPUT = 10,                  /* KW_INPUT  */
  YYSYMBOL_KW_OUTPUT = 11,                 /* KW_OUTPUT  */
  YYSYMBOL_KW_RETURN = 12,                 /* KW_RETURN  */
  YYSYMBOL_OPERATOR_LE = 13,               /* OPERATOR_LE  */
  YYSYMBOL_OPERATOR_GE = 14,               /* OPERATOR_GE  */
  YYSYMBOL_OPERATOR_EQ = 15,               /* OPERATOR_EQ  */
  YYSYMBOL_OPERATOR_DIF = 16,              /* OPERATOR_DIF  */
  YYSYMBOL_TK_IDENTIFIER = 17,             /* TK_IDENTIFIER  */
  YYSYMBOL_LIT_INT = 18,                   /* LIT_INT  */
  YYSYMBOL_LIT_REAL = 19,                  /* LIT_REAL  */
  YYSYMBOL_LIT_CHAR = 20,                  /* LIT_CHAR  */
  YYSYMBOL_LIT_STRING = 21,                /* LIT_STRING  */
  YYSYMBOL_TOKEN_ERROR = 22,               /* TOKEN_ERROR  */
  YYSYMBOL_23_ = 23,                       /* '&'  */
  YYSYMBOL_24_ = 24,                       /* '|'  */
  YYSYMBOL_25_ = 25,                       /* '~'  */
  YYSYMBOL_26_ = 26,                       /* '>'  */
  YYSYMBOL_27_ = 27,                       /* '<'  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_declaration_list = 43,          /* declaration_list  */
  YYSYMBOL_var_declaration = 44,           /* var_declaration  */
  YYSYMBOL_vec_init_opt = 45,              /* vec_init_opt  */
  YYSYMBOL_vec_declaration = 46,           /* vec_declaration  */
  YYSYMBOL_parameter = 47,                 /* parameter  */
  YYSYMBOL_parameter_list = 48,            /* parameter_list  */
  YYSYMBOL_parameter_list_aux = 49,        /* parameter_list_aux  */
  YYSYMBOL_func_declaration = 50,          /* func_declaration  */
  YYSYMBOL_body = 51,                      /* body  */
  YYSYMBOL_cmd_list = 52,                  /* cmd_list  */
  YYSYMBOL_if_body = 53,                   /* if_body  */
  YYSYMBOL_if_statement = 54,              /* if_statement  */
  YYSYMBOL_cmd = 55,                       /* cmd  */
  YYSYMBOL_var_attrib = 56,                /* var_attrib  */
  YYSYMBOL_vec_attrib = 57,                /* vec_attrib  */
  YYSYMBOL_output_cmd = 58,                /* output_cmd  */
  YYSYMBOL_output_param_list = 59,         /* output_param_list  */
  YYSYMBOL_return_cmd = 60,                /* return_cmd  */
  YYSYMBOL_input_expr = 61,                /* input_expr  */
  YYSYMBOL_expr = 62,                      /* expr  */
  YYSYMBOL_func_call = 63,                 /* func_call  */
  YYSYMBOL_expr_list = 64,                 /* expr_list  */
  YYSYMBOL_expr_list_aux = 65              /* expr_list_aux  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   476

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
       2,     2,     2,     2,     2,     2,     2,     2,    23,     2,
      37,    38,    30,    28,    36,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      27,    33,    26,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    24,    40,    25,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,   149,   150,   151,   154,   155,   156,   160,
     161,   162,   163,   165,   166,   167,   168,   170,   171,   172,
     173,   175,   176,   177,   178,   180,   181,   182,   183,   185,
     186,   187,   188,   191,   192,   193,   194,   196,   197,   198,
     199,   201,   202,   203,   204,   207,   208,   209,   210,   214,
     215,   216,   217,   220,   221,   222,   223,   226,   227,   228,
     229,   231,   232,   233,   234,   237,   238,   239,   240,   243,
     244,   247,   248,   251,   252,   253,   254,   257,   263,   264,
     265,   267,   269,   272,   273,   276,   277,   278,   282,   284,
     285,   286,   287,   288,   289,   291,   292,   293,   296,   297,
     298,   299,   300,   303,   304,   307,   308,   311,   314,   315,
     316,   317,   320,   321,   322,   325,   330,   331,   332,   333,
     336,   337,   339,   340,   341,   343,   344,   345,   347,   348,
     349,   351,   352,   353,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   383,   385,   386,   387,
     390,   391,   394,   396,   397
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
  "\"end of file\"", "error", "\"invalid token\"", "KW_CHAR", "KW_INT",
  "KW_REAL", "KW_BOOL", "KW_IF", "KW_ELSE", "KW_LOOP", "KW_INPUT",
  "KW_OUTPUT", "KW_RETURN", "OPERATOR_LE", "OPERATOR_GE", "OPERATOR_EQ",
  "OPERATOR_DIF", "TK_IDENTIFIER", "LIT_INT", "LIT_REAL", "LIT_CHAR",
  "LIT_STRING", "TOKEN_ERROR", "'&'", "'|'", "'~'", "'>'", "'<'", "'+'",
  "'-'", "'*'", "'/'", "';'", "'='", "'['", "']'", "','", "'('", "')'",
  "'{'", "'}'", "$accept", "program", "declaration_list",
  "var_declaration", "vec_init_opt", "vec_declaration", "parameter",
  "parameter_list", "parameter_list_aux", "func_declaration", "body",
  "cmd_list", "if_body", "if_statement", "cmd", "var_attrib", "vec_attrib",
  "output_cmd", "output_param_list", "return_cmd", "input_expr", "expr",
  "func_call", "expr_list", "expr_list_aux", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-282)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-165)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     259,   170,   174,   189,   260,     8,  -282,     0,    14,   259,
     -12,    63,    58,    83,    61,    88,    71,   125,  -282,   259,
     259,   259,   259,  -282,    -6,   289,     5,    92,   434,   318,
     326,   348,    94,   434,   360,   403,   370,    97,   434,   425,
     452,   400,   209,   434,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,    79,   102,
      89,   101,   140,   155,   131,   156,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,   178,   190,   167,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,   193,
     197,   186,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,   220,   221,   240,   456,   228,  -282,  -282,  -282,
    -282,   434,  -282,   219,   456,   248,   219,   456,   251,   219,
     456,   256,   219,   456,   456,   456,  -282,  -282,  -282,   131,
     233,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,    28,   296,
     310,   208,   233,   239,   233,    91,  -282,  -282,  -282,  -282,
     310,   310,    87,   118,  -282,  -282,  -282,   107,   310,   310,
     310,  -282,  -282,   207,  -282,   401,   310,   310,   310,  -282,
    -282,  -282,   233,   233,   169,   188,   459,   455,   310,   310,
     310,   296,   296,   438,   130,   327,   296,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   296,
     401,   401,   346,  -282,  -282,   242,   273,   280,   284,     6,
      21,    29,    34,   249,    35,    41,    67,    69,   150,    73,
     369,    75,  -282,  -282,  -282,  -282,   438,   438,   438,   438,
     420,   420,   438,   438,   130,   130,  -282,  -282,  -282,     1,
     287,  -282,   278,   262,   287,   294,   287,   295,    70,   303,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,  -282,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,   310,   310,  -282,
    -282,  -282,  -282,  -282,  -282,   310,   310,  -282,   287,  -282,
    -282,   287,  -282,   287,  -282,  -282,   287,   150,   150,   401,
     401,  -282,  -282,  -282,  -282,  -282,  -282
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     0,     0,     0,     2,     0,     0,     8,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     8,
       8,     8,     8,     5,     0,     0,     0,     0,    70,     0,
       0,     0,     0,    70,     0,     0,     0,     0,    70,     0,
       0,     0,     0,    70,     6,     3,     7,     4,    22,    30,
      26,    34,    42,    38,    46,    10,    18,    14,     0,     0,
       0,     0,     0,     0,    72,     0,    21,    29,    25,    33,
      41,    37,    45,     9,    17,    13,     0,     0,     0,    23,
      31,    27,    35,    43,    39,    47,    11,    19,    15,     0,
       0,     0,    24,    32,    28,    36,    44,    40,    48,    12,
      20,    16,     0,     0,     0,    52,     0,    66,    65,    67,
      68,     0,    69,     0,    52,     0,     0,    52,     0,     0,
      52,     0,     0,    52,    52,    52,    58,    62,    54,    72,
     102,    74,    57,    61,    53,    73,    59,    63,    55,    75,
      60,    64,    56,    76,    49,    50,    51,    71,     0,   114,
       0,     0,   102,     0,   102,     0,    98,    99,   100,   101,
       0,     0,     0,     0,   134,   137,   136,     0,     0,     0,
       0,   107,   139,     0,   140,   115,     0,     0,     0,    79,
      77,    80,   102,   102,     0,     0,   121,     0,   161,     0,
     161,   114,   114,   146,   145,     0,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
     104,   103,     0,    81,    78,   102,   102,   102,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   108,   155,   113,   149,   150,   151,   152,
     147,   148,   153,   154,   143,   144,   141,   142,   109,     0,
     102,    83,    95,     0,   102,    89,   102,    90,     0,    85,
     127,   125,   124,   122,   130,   128,   133,   131,   120,   126,
     117,   123,   116,   129,   118,   132,   119,     0,     0,   160,
     159,   158,   138,   157,   156,     0,     0,    97,   102,    84,
      93,   102,    94,   102,    88,    87,   102,     0,     0,   106,
     105,    96,    91,    92,    86,   163,   162
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -282,  -282,   433,  -282,   288,  -282,   211,   267,   195,  -282,
     -53,   -14,  -213,  -282,  -121,  -282,  -282,  -282,  -106,  -282,
    -282,  -150,  -282,   128,  -281
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     5,     6,     7,   126,     8,    64,    65,   112,     9,
     251,   153,   252,   154,   253,   156,   157,   158,   171,   159,
     172,   173,   174,   229,   279
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     175,    19,   285,   255,   257,   259,    54,   260,    18,   155,
     184,   185,    48,    49,    50,    21,   305,   306,   193,   194,
     195,    24,   262,    55,    56,    57,   210,   211,   212,   160,
     264,   155,    20,   155,   286,   266,   269,   287,   228,   230,
     228,   290,   271,   292,   261,   295,    22,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   263,
     131,   155,   155,   135,    25,   161,   139,   265,   273,   143,
     275,   294,   267,   270,   280,   301,   283,   152,   302,   272,
     303,   149,   150,   304,    30,   232,   233,   151,   186,    35,
     235,    29,   182,    58,    34,    76,    26,    27,    89,   152,
      28,   152,  -102,   248,    39,   274,   107,   276,   191,   130,
      59,   281,    77,   284,   105,    90,    31,    32,   108,   188,
      33,    36,    37,   183,   187,    38,    40,   297,   298,   152,
     152,  -135,  -135,  -135,  -135,   299,   300,   106,   179,  -110,
     181,  -135,  -135,   192,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,   277,   189,  -135,  -135,   190,  -135,   109,    41,    42,
     207,   208,    43,   197,   198,   199,   200,   111,   213,   214,
     215,    10,   110,   201,   202,    12,   203,   204,   205,   206,
     207,   208,   197,   198,   199,   200,   278,    11,  -164,   217,
      14,    13,   201,   202,   113,   203,   204,   205,   206,   207,
     208,   197,   198,   199,   200,   116,    15,   216,   196,   176,
     102,   201,   202,   114,   203,   204,   205,   206,   207,   208,
     197,   198,   199,   200,   119,   115,   218,   103,   117,   127,
     201,   202,   118,   203,   204,   205,   206,   207,   208,  -111,
     148,   177,   178,   209,   149,   150,   123,   124,   125,   133,
     151,   250,   137,   149,   150,   120,   121,   141,   130,   151,
     -52,    16,     1,     2,     3,     4,   123,   124,   125,   123,
     124,   125,   130,   -82,   123,   124,   125,    17,   122,   180,
     -52,   130,   254,   -52,   149,   150,   288,   268,   -52,   256,
     151,   149,   150,   258,   289,   149,   150,   151,   149,   150,
      78,   151,   291,   293,   151,    91,   162,    51,    52,    53,
     104,   296,   130,   163,   164,   165,   166,   167,   231,   130,
     162,   168,   129,   130,   147,   169,   130,   163,   164,   165,
     166,     0,     0,   170,     0,   168,    66,    67,    68,   169,
     197,   198,   199,   200,    69,    70,    71,   170,     0,    72,
     201,   202,     0,   203,   204,   205,   206,   207,   208,   197,
     198,   199,   200,     0,     0,   234,    73,    74,    75,   201,
     202,    85,   203,   204,   205,   206,   207,   208,    79,    80,
      81,   249,   197,   198,   199,   200,     0,     0,    86,    87,
      88,     0,   201,   202,   128,   203,   204,   205,   206,   207,
     208,    98,   132,   134,   282,   136,   138,     0,   140,   142,
       0,   144,   145,   146,   197,   198,   199,   200,    99,   100,
     101,    82,    83,    84,   201,   202,     0,   203,   204,   205,
     206,   207,   208,   197,   198,   199,   200,    60,    61,    62,
      63,     0,    23,    92,    93,    94,   203,   204,   205,   206,
     207,   208,    44,    45,    46,    47,   223,     0,   224,   225,
     226,   227,   219,   220,   221,   222,   205,   206,   207,   208,
      95,    96,    97,     0,   123,   124,   125
};

static const yytype_int16 yycheck[] =
{
     150,     1,     1,   216,   217,   218,     1,     1,     0,   130,
     160,   161,    18,    19,    20,     1,   297,   298,   168,   169,
     170,    33,     1,    18,    19,    20,   176,   177,   178,     1,
       1,   152,    32,   154,    33,     1,     1,   250,   188,   189,
     190,   254,     1,   256,    38,   258,    32,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,    38,
     113,   182,   183,   116,     1,    37,   119,    38,     1,   122,
       1,     1,    38,    38,     1,   288,     1,   130,   291,    38,
     293,    11,    12,   296,     1,   191,   192,    17,     1,     1,
     196,    33,     1,     1,    33,     1,    33,    34,     1,   152,
      37,   154,    32,   209,    33,    38,    17,    38,     1,    39,
      18,    38,    18,    38,    35,    18,    33,    34,    17,     1,
      37,    33,    34,    32,    37,    37,     1,   277,   278,   182,
     183,    13,    14,    15,    16,   285,   286,    35,   152,    32,
     154,    23,    24,    36,    26,    27,    28,    29,    30,    31,
      32,     1,    34,    35,    36,    37,    38,    17,    33,    34,
      30,    31,    37,    13,    14,    15,    16,    36,   182,   183,
       1,     1,    17,    23,    24,     1,    26,    27,    28,    29,
      30,    31,    13,    14,    15,    16,    36,    17,    38,     1,
       1,    17,    23,    24,    38,    26,    27,    28,    29,    30,
      31,    13,    14,    15,    16,    38,    17,    38,     1,     1,
       1,    23,    24,    35,    26,    27,    28,    29,    30,    31,
      13,    14,    15,    16,    38,    35,    38,    18,    35,     1,
      23,    24,    35,    26,    27,    28,    29,    30,    31,    32,
       7,    33,    34,    36,    11,    12,    18,    19,    20,     1,
      17,     9,     1,    11,    12,    35,    35,     1,    39,    17,
      32,     1,     3,     4,     5,     6,    18,    19,    20,    18,
      19,    20,    39,    40,    18,    19,    20,    17,    38,    40,
      32,    39,     9,    32,    11,    12,     8,    38,    32,     9,
      17,    11,    12,     9,    32,    11,    12,    17,    11,    12,
      33,    17,     8,     8,    17,    38,    10,    18,    19,    20,
      43,     8,    39,    17,    18,    19,    20,    21,   190,    39,
      10,    25,   111,    39,   129,    29,    39,    17,    18,    19,
      20,    -1,    -1,    37,    -1,    25,    18,    19,    20,    29,
      13,    14,    15,    16,    18,    19,    20,    37,    -1,     1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    13,
      14,    15,    16,    -1,    -1,    38,    18,    19,    20,    23,
      24,     1,    26,    27,    28,    29,    30,    31,    18,    19,
      20,    35,    13,    14,    15,    16,    -1,    -1,    18,    19,
      20,    -1,    23,    24,   106,    26,    27,    28,    29,    30,
      31,     1,   114,   115,    35,   117,   118,    -1,   120,   121,
      -1,   123,   124,   125,    13,    14,    15,    16,    18,    19,
      20,    18,    19,    20,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    13,    14,    15,    16,     3,     4,     5,
       6,    -1,     9,    18,    19,    20,    26,    27,    28,    29,
      30,    31,    19,    20,    21,    22,     1,    -1,     3,     4,
       5,     6,     3,     4,     5,     6,    28,    29,    30,    31,
      18,    19,    20,    -1,    18,    19,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    42,    43,    44,    46,    50,
       1,    17,     1,    17,     1,    17,     1,    17,     0,     1,
      32,     1,    32,    43,    33,     1,    33,    34,    37,    33,
       1,    33,    34,    37,    33,     1,    33,    34,    37,    33,
       1,    33,    34,    37,    43,    43,    43,    43,    18,    19,
      20,    18,    19,    20,     1,    18,    19,    20,     1,    18,
       3,     4,     5,     6,    47,    48,    18,    19,    20,    18,
      19,    20,     1,    18,    19,    20,     1,    18,    48,    18,
      19,    20,    18,    19,    20,     1,    18,    19,    20,     1,
      18,    48,    18,    19,    20,    18,    19,    20,     1,    18,
      19,    20,     1,    18,    48,    35,    35,    17,    17,    17,
      17,    36,    49,    38,    35,    35,    38,    35,    35,    38,
      35,    35,    38,    18,    19,    20,    45,     1,    45,    47,
      39,    51,    45,     1,    45,    51,    45,     1,    45,    51,
      45,     1,    45,    51,    45,    45,    45,    49,     7,    11,
      12,    17,    51,    52,    54,    55,    56,    57,    58,    60,
       1,    37,    10,    17,    18,    19,    20,    21,    25,    29,
      37,    59,    61,    62,    63,    62,     1,    33,    34,    52,
      40,    52,     1,    32,    62,    62,     1,    37,     1,    34,
      37,     1,    36,    62,    62,    62,     1,    13,    14,    15,
      16,    23,    24,    26,    27,    28,    29,    30,    31,    36,
      62,    62,    62,    52,    52,     1,    38,     1,    38,     3,
       4,     5,     6,     1,     3,     4,     5,     6,    62,    64,
      62,    64,    59,    59,    38,    59,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    59,    35,
       9,    51,    53,    55,     9,    53,     9,    53,     9,    53,
       1,    38,     1,    38,     1,    38,     1,    38,    38,     1,
      38,     1,    38,     1,    38,     1,    38,     1,    36,    65,
       1,    38,    35,     1,    38,     1,    33,    53,     8,    32,
      53,     8,    53,     8,     1,    53,     8,    62,    62,    62,
      62,    53,    53,    53,    53,    65,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    43,    43,    43,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    45,
      45,    45,    45,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    47,    47,    48,
      48,    49,    49,    50,    50,    50,    50,    51,    52,    52,
      52,    52,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      59,    59,    59,    59,    59,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    63,    63,
      64,    64,    65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     3,     2,     3,     3,     0,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     2,
       2,     2,     0,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     2,     2,     2,     2,     2,
       0,     3,     0,     6,     6,     6,     6,     3,     3,     2,
       2,     3,     0,     1,     2,     5,     7,     6,     6,     5,
       5,     7,     7,     6,     6,     5,     7,     6,     1,     1,
       1,     1,     0,     3,     3,     6,     6,     2,     3,     3,
       1,     1,     3,     3,     0,     2,     4,     4,     4,     4,
       4,     2,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     4,     1,
       1,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     4,     4,     4,
       2,     0,     3,     3,     0
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
  case 2: /* program: declaration_list  */
#line 79 "parser.y"
                            { 
                              
                                    root = astCreate(AST_PROGRAM, NULL, (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber()); (yyvsp[0].ast) = root; (yyval.ast) = (yyvsp[0].ast);
                                   
                                    set_param_list_item_function(root);
                                    set_expr_list_item_function(root);
                                    check_and_set_declarations((yyvsp[0].ast));
                                    check_undeclared();
                                    
                                    check_operands((yyvsp[0].ast));
                                    
                                    check_assignments((yyvsp[0].ast));	
                                        
                                    check_return((yyvsp[0].ast));
                                        
                                    check_function_call((yyvsp[0].ast));
                                    
                                    check_conditional_stmts((yyvsp[0].ast));


                                    if (SyntaxErrors == 0 && SemanticErrors == 0) {
                                       
                                        if (optimize) {
                                            fprintf(stderr, "Generating optimized code...\n");
                                            ast_collect_loop_elements((yyvsp[0].ast));
                                            ast_collect_loop_conditions((yyvsp[0].ast));
                                            ast_collect_loop_variables((yyvsp[0].ast));
                                            // ast_collect_has_dependencies($1);
                                           
                                            ast_collect_varies((yyvsp[0].ast));
                                            
                                            ast_set_dependencies((yyvsp[0].ast));

                                            ast_set_varies((yyvsp[0].ast));
                                            ast_set_order_dependencies((yyvsp[0].ast));
                                     
                                           // ast_print_cond_list();
                                        
                                            ast_optimize((yyvsp[0].ast));
                                            if (optimized > 0) {
                                                ast_handle_marked_assignments((yyvsp[0].ast));
                                                ast_add_assignment_conds((yyvsp[0].ast));
                                                fprintf(stderr, "Optimization done!\n");
                                            } else {
                                                fprintf(stderr, "No optimization done!\n");
                                            }
                                            
                                        } else {
                                            fprintf(stderr, "Generating unoptimized code...\n");
                                        }
                                      
                                        TAC * code = generate_code((yyvsp[0].ast));
                                        code = generate_code((yyvsp[0].ast));
                                        //tac_print_backwards(code);
                                        generate_asm(code);
                                        
                                    }
                                

                                
                                //astPrint($1, 0);
                                /*AST * test = $1;
                                test = test->son[0]->son[1]->son[0]->son[1]->son[0]->son[0]->son[0];
                                int typecheck_result = expression_typecheck(test);
                                fprintf(stderr, "typecheck result: %d\n", typecheck_result);*/

                               
                            }
#line 1529 "y.tab.c"
    break;

  case 3: /* declaration_list: var_declaration ';' declaration_list  */
#line 149 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_DECL_LIST, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1535 "y.tab.c"
    break;

  case 4: /* declaration_list: vec_declaration ';' declaration_list  */
#line 150 "parser.y"
                                            { (yyval.ast) = astCreate(AST_DECL_LIST, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1541 "y.tab.c"
    break;

  case 5: /* declaration_list: func_declaration declaration_list  */
#line 151 "parser.y"
                                         { (yyval.ast) = astCreate(AST_DECL_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1547 "y.tab.c"
    break;

  case 6: /* declaration_list: var_declaration error declaration_list  */
#line 154 "parser.y"
                                                          { (yyval.ast) = astCreate(AST_DECL_LIST, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of variable declaration\n"); SyntaxErrors++; }
#line 1553 "y.tab.c"
    break;

  case 7: /* declaration_list: vec_declaration error declaration_list  */
#line 155 "parser.y"
                                                          { (yyval.ast) = astCreate(AST_DECL_LIST, NULL, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of vector declaration\n"); SyntaxErrors++; }
#line 1559 "y.tab.c"
    break;

  case 8: /* declaration_list: %empty  */
#line 156 "parser.y"
                 { (yyval.ast) = 0; }
#line 1565 "y.tab.c"
    break;

  case 9: /* var_declaration: KW_INT TK_IDENTIFIER '=' LIT_INT  */
#line 160 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1571 "y.tab.c"
    break;

  case 10: /* var_declaration: KW_CHAR TK_IDENTIFIER '=' LIT_INT  */
#line 161 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1577 "y.tab.c"
    break;

  case 11: /* var_declaration: KW_REAL TK_IDENTIFIER '=' LIT_INT  */
#line 162 "parser.y"
                                                      { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1583 "y.tab.c"
    break;

  case 12: /* var_declaration: KW_BOOL TK_IDENTIFIER '=' LIT_INT  */
#line 163 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1589 "y.tab.c"
    break;

  case 13: /* var_declaration: KW_INT TK_IDENTIFIER '=' LIT_CHAR  */
#line 165 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1595 "y.tab.c"
    break;

  case 14: /* var_declaration: KW_CHAR TK_IDENTIFIER '=' LIT_CHAR  */
#line 166 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol),astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1601 "y.tab.c"
    break;

  case 15: /* var_declaration: KW_REAL TK_IDENTIFIER '=' LIT_CHAR  */
#line 167 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1607 "y.tab.c"
    break;

  case 16: /* var_declaration: KW_BOOL TK_IDENTIFIER '=' LIT_CHAR  */
#line 168 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1613 "y.tab.c"
    break;

  case 17: /* var_declaration: KW_INT TK_IDENTIFIER '=' LIT_REAL  */
#line 170 "parser.y"
                                                   { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1619 "y.tab.c"
    break;

  case 18: /* var_declaration: KW_CHAR TK_IDENTIFIER '=' LIT_REAL  */
#line 171 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1625 "y.tab.c"
    break;

  case 19: /* var_declaration: KW_REAL TK_IDENTIFIER '=' LIT_REAL  */
#line 172 "parser.y"
                                                         { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1631 "y.tab.c"
    break;

  case 20: /* var_declaration: KW_BOOL TK_IDENTIFIER '=' LIT_REAL  */
#line 173 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 1637 "y.tab.c"
    break;

  case 21: /* var_declaration: KW_INT error '=' LIT_INT  */
#line 175 "parser.y"
                                           { (yyval.ast) = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1643 "y.tab.c"
    break;

  case 22: /* var_declaration: KW_CHAR error '=' LIT_INT  */
#line 176 "parser.y"
                                           { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1649 "y.tab.c"
    break;

  case 23: /* var_declaration: KW_REAL error '=' LIT_INT  */
#line 177 "parser.y"
                                           { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1655 "y.tab.c"
    break;

  case 24: /* var_declaration: KW_BOOL error '=' LIT_INT  */
#line 178 "parser.y"
                                           { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1661 "y.tab.c"
    break;

  case 25: /* var_declaration: KW_INT error '=' LIT_CHAR  */
#line 180 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1667 "y.tab.c"
    break;

  case 26: /* var_declaration: KW_CHAR error '=' LIT_CHAR  */
#line 181 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1673 "y.tab.c"
    break;

  case 27: /* var_declaration: KW_REAL error '=' LIT_CHAR  */
#line 182 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1679 "y.tab.c"
    break;

  case 28: /* var_declaration: KW_BOOL error '=' LIT_CHAR  */
#line 183 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1685 "y.tab.c"
    break;

  case 29: /* var_declaration: KW_INT error '=' LIT_REAL  */
#line 185 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1691 "y.tab.c"
    break;

  case 30: /* var_declaration: KW_CHAR error '=' LIT_REAL  */
#line 186 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1697 "y.tab.c"
    break;

  case 31: /* var_declaration: KW_REAL error '=' LIT_REAL  */
#line 187 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1703 "y.tab.c"
    break;

  case 32: /* var_declaration: KW_BOOL error '=' LIT_REAL  */
#line 188 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
#line 1709 "y.tab.c"
    break;

  case 33: /* var_declaration: KW_INT TK_IDENTIFIER error LIT_INT  */
#line 191 "parser.y"
                                                    { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1715 "y.tab.c"
    break;

  case 34: /* var_declaration: KW_CHAR TK_IDENTIFIER error LIT_INT  */
#line 192 "parser.y"
                                         { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1721 "y.tab.c"
    break;

  case 35: /* var_declaration: KW_REAL TK_IDENTIFIER error LIT_INT  */
#line 193 "parser.y"
                                         { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1727 "y.tab.c"
    break;

  case 36: /* var_declaration: KW_BOOL TK_IDENTIFIER error LIT_INT  */
#line 194 "parser.y"
                                         { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1733 "y.tab.c"
    break;

  case 37: /* var_declaration: KW_INT TK_IDENTIFIER error LIT_CHAR  */
#line 196 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1739 "y.tab.c"
    break;

  case 38: /* var_declaration: KW_CHAR TK_IDENTIFIER error LIT_CHAR  */
#line 197 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1745 "y.tab.c"
    break;

  case 39: /* var_declaration: KW_REAL TK_IDENTIFIER error LIT_CHAR  */
#line 198 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1751 "y.tab.c"
    break;

  case 40: /* var_declaration: KW_BOOL TK_IDENTIFIER error LIT_CHAR  */
#line 199 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1757 "y.tab.c"
    break;

  case 41: /* var_declaration: KW_INT TK_IDENTIFIER error LIT_REAL  */
#line 201 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1763 "y.tab.c"
    break;

  case 42: /* var_declaration: KW_CHAR TK_IDENTIFIER error LIT_REAL  */
#line 202 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1769 "y.tab.c"
    break;

  case 43: /* var_declaration: KW_REAL TK_IDENTIFIER error LIT_REAL  */
#line 203 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1775 "y.tab.c"
    break;

  case 44: /* var_declaration: KW_BOOL TK_IDENTIFIER error LIT_REAL  */
#line 204 "parser.y"
                                          { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
#line 1781 "y.tab.c"
    break;

  case 45: /* var_declaration: KW_INT TK_IDENTIFIER '=' error  */
#line 207 "parser.y"
                                     { (yyval.ast) = astCreate(AST_VAR_DECL_INT, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_INTEGER), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
#line 1787 "y.tab.c"
    break;

  case 46: /* var_declaration: KW_CHAR TK_IDENTIFIER '=' error  */
#line 208 "parser.y"
                                     { (yyval.ast) = astCreate(AST_VAR_DECL_CHAR, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_CHAR), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
#line 1793 "y.tab.c"
    break;

  case 47: /* var_declaration: KW_REAL TK_IDENTIFIER '=' error  */
#line 209 "parser.y"
                                     { (yyval.ast) = astCreate(AST_VAR_DECL_REAL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_REAL), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
#line 1799 "y.tab.c"
    break;

  case 48: /* var_declaration: KW_BOOL TK_IDENTIFIER '=' error  */
#line 210 "parser.y"
                                     { (yyval.ast) = astCreate(AST_VAR_DECL_BOOL, (yyvsp[-2].symbol), astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_INTEGER), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
#line 1805 "y.tab.c"
    break;

  case 49: /* vec_init_opt: LIT_INT vec_init_opt  */
#line 214 "parser.y"
                                   { (yyval.ast) = astCreate(AST_VEC_INIT_OPT_INT, NULL, astCreate(AST_LIT_INT, (yyvsp[-1].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber());}
#line 1811 "y.tab.c"
    break;

  case 50: /* vec_init_opt: LIT_REAL vec_init_opt  */
#line 215 "parser.y"
                                   { (yyval.ast) = astCreate(AST_VEC_INIT_OPT_REAL, NULL, astCreate(AST_LIT_REAL, (yyvsp[-1].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1817 "y.tab.c"
    break;

  case 51: /* vec_init_opt: LIT_CHAR vec_init_opt  */
#line 216 "parser.y"
                                    { (yyval.ast) = astCreate(AST_VEC_INIT_OPT_CHAR, NULL, astCreate(AST_LIT_CHAR, (yyvsp[-1].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1823 "y.tab.c"
    break;

  case 52: /* vec_init_opt: %empty  */
#line 217 "parser.y"
          { (yyval.ast) = 0; }
#line 1829 "y.tab.c"
    break;

  case 53: /* vec_declaration: KW_INT TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt  */
#line 220 "parser.y"
                                                                     { (yyval.ast) = astCreate(AST_VEC_DECL_INT, (yyvsp[-4].symbol),  astCreate(AST_LIT_INT, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1835 "y.tab.c"
    break;

  case 54: /* vec_declaration: KW_CHAR TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt  */
#line 221 "parser.y"
                                                                    { (yyval.ast) = astCreate(AST_VEC_DECL_CHAR, (yyvsp[-4].symbol), astCreate(AST_LIT_INT, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1841 "y.tab.c"
    break;

  case 55: /* vec_declaration: KW_REAL TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt  */
#line 222 "parser.y"
                                                                    { (yyval.ast) = astCreate(AST_VEC_DECL_REAL, (yyvsp[-4].symbol), astCreate(AST_LIT_INT, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1847 "y.tab.c"
    break;

  case 56: /* vec_declaration: KW_BOOL TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt  */
#line 223 "parser.y"
                                                                    { (yyval.ast) = astCreate(AST_VEC_DECL_BOOL, (yyvsp[-4].symbol), astCreate(AST_LIT_INT, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1853 "y.tab.c"
    break;

  case 57: /* vec_declaration: KW_INT TK_IDENTIFIER '[' error ']' vec_init_opt  */
#line 226 "parser.y"
                                                                  { (yyval.ast) = 0; fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
#line 1859 "y.tab.c"
    break;

  case 58: /* vec_declaration: KW_CHAR TK_IDENTIFIER '[' error ']' vec_init_opt  */
#line 227 "parser.y"
                                                                  { (yyval.ast) = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
#line 1865 "y.tab.c"
    break;

  case 59: /* vec_declaration: KW_REAL TK_IDENTIFIER '[' error ']' vec_init_opt  */
#line 228 "parser.y"
                                                                   { (yyval.ast) = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
#line 1871 "y.tab.c"
    break;

  case 60: /* vec_declaration: KW_BOOL TK_IDENTIFIER '[' error ']' vec_init_opt  */
#line 229 "parser.y"
                                                                   { (yyval.ast) = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
#line 1877 "y.tab.c"
    break;

  case 61: /* vec_declaration: KW_INT TK_IDENTIFIER '[' LIT_INT ']' error  */
#line 231 "parser.y"
                                                             { (yyval.ast) = 0; fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
#line 1883 "y.tab.c"
    break;

  case 62: /* vec_declaration: KW_CHAR TK_IDENTIFIER '[' LIT_INT ']' error  */
#line 232 "parser.y"
                                                             { (yyval.ast) = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
#line 1889 "y.tab.c"
    break;

  case 63: /* vec_declaration: KW_REAL TK_IDENTIFIER '[' LIT_INT ']' error  */
#line 233 "parser.y"
                                                              { (yyval.ast) = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
#line 1895 "y.tab.c"
    break;

  case 64: /* vec_declaration: KW_BOOL TK_IDENTIFIER '[' LIT_INT ']' error  */
#line 234 "parser.y"
                                                              { (yyval.ast) = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
#line 1901 "y.tab.c"
    break;

  case 65: /* parameter: KW_INT TK_IDENTIFIER  */
#line 237 "parser.y"
                                    { (yyval.ast) = astCreate(AST_PARAM_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 1907 "y.tab.c"
    break;

  case 66: /* parameter: KW_CHAR TK_IDENTIFIER  */
#line 238 "parser.y"
                                    { (yyval.ast) = astCreate(AST_PARAM_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 1913 "y.tab.c"
    break;

  case 67: /* parameter: KW_REAL TK_IDENTIFIER  */
#line 239 "parser.y"
                                    { (yyval.ast) = astCreate(AST_PARAM_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 1919 "y.tab.c"
    break;

  case 68: /* parameter: KW_BOOL TK_IDENTIFIER  */
#line 240 "parser.y"
                                    { (yyval.ast) = astCreate(AST_PARAM_BOOL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 1925 "y.tab.c"
    break;

  case 69: /* parameter_list: parameter parameter_list_aux  */
#line 243 "parser.y"
                                             { (yyval.ast) = astCreate(AST_PARAM_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1931 "y.tab.c"
    break;

  case 70: /* parameter_list: %empty  */
#line 244 "parser.y"
      { (yyval.ast) = astCreate(AST_EMPTY_PARAM_LIST, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
#line 1937 "y.tab.c"
    break;

  case 71: /* parameter_list_aux: ',' parameter parameter_list_aux  */
#line 247 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_PARAM_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1943 "y.tab.c"
    break;

  case 72: /* parameter_list_aux: %empty  */
#line 248 "parser.y"
      { (yyval.ast) = 0; }
#line 1949 "y.tab.c"
    break;

  case 73: /* func_declaration: KW_INT TK_IDENTIFIER '(' parameter_list ')' body  */
#line 251 "parser.y"
                                                                        { (yyval.ast) = astCreate(AST_FUNC_DECL_INT, (yyvsp[-4].symbol), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1955 "y.tab.c"
    break;

  case 74: /* func_declaration: KW_CHAR TK_IDENTIFIER '(' parameter_list ')' body  */
#line 252 "parser.y"
                                                                        { (yyval.ast) = astCreate(AST_FUNC_DECL_CHAR, (yyvsp[-4].symbol), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1961 "y.tab.c"
    break;

  case 75: /* func_declaration: KW_REAL TK_IDENTIFIER '(' parameter_list ')' body  */
#line 253 "parser.y"
                                                                        { (yyval.ast) = astCreate(AST_FUNC_DECL_REAL, (yyvsp[-4].symbol), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1967 "y.tab.c"
    break;

  case 76: /* func_declaration: KW_BOOL TK_IDENTIFIER '(' parameter_list ')' body  */
#line 254 "parser.y"
                                                                        { (yyval.ast) = astCreate(AST_FUNC_DECL_BOOL, (yyvsp[-4].symbol), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1973 "y.tab.c"
    break;

  case 77: /* body: '{' cmd_list '}'  */
#line 257 "parser.y"
                       { (yyval.ast) = astCreate(AST_BODY, NULL, (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber()); }
#line 1979 "y.tab.c"
    break;

  case 78: /* cmd_list: cmd ';' cmd_list  */
#line 263 "parser.y"
                           { (yyval.ast) = astCreate(AST_CMD_LIST, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1985 "y.tab.c"
    break;

  case 79: /* cmd_list: body cmd_list  */
#line 264 "parser.y"
                           { (yyval.ast) = astCreate(AST_CMD_LIST, 0, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1991 "y.tab.c"
    break;

  case 80: /* cmd_list: if_statement cmd_list  */
#line 265 "parser.y"
                                    { (yyval.ast) = astCreate(AST_CMD_LIST, 0, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 1997 "y.tab.c"
    break;

  case 81: /* cmd_list: cmd error cmd_list  */
#line 267 "parser.y"
                           { (yyval.ast) = astCreate(AST_CMD_LIST, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of command\n"); SyntaxErrors++; }
#line 2003 "y.tab.c"
    break;

  case 82: /* cmd_list: %empty  */
#line 269 "parser.y"
          { (yyval.ast) = 0; }
#line 2009 "y.tab.c"
    break;

  case 83: /* if_body: body  */
#line 272 "parser.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 2015 "y.tab.c"
    break;

  case 84: /* if_body: cmd ';'  */
#line 273 "parser.y"
                 { (yyval.ast) = (yyvsp[-1].ast); }
#line 2021 "y.tab.c"
    break;

  case 85: /* if_statement: KW_IF '(' expr ')' if_body  */
#line 276 "parser.y"
                                                   { (yyval.ast) = astCreate(AST_IF, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 2027 "y.tab.c"
    break;

  case 86: /* if_statement: KW_IF '(' expr ')' if_body KW_ELSE if_body  */
#line 277 "parser.y"
                                                   { (yyval.ast) = astCreate(AST_IF_ELSE, 0, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, getLineNumber()); }
#line 2033 "y.tab.c"
    break;

  case 87: /* if_statement: KW_IF '(' expr ')' KW_LOOP if_body  */
#line 278 "parser.y"
                                                   { (yyval.ast) = astCreate(AST_LOOP, 0, (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 2039 "y.tab.c"
    break;

  case 88: /* if_statement: KW_IF '(' expr ')' KW_LOOP error  */
#line 282 "parser.y"
                                                 { (yyval.ast) = astCreate(AST_LOOP, 0, (yyvsp[-3].ast), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting loop body\n"); SyntaxErrors++; }
#line 2045 "y.tab.c"
    break;

  case 89: /* if_statement: KW_IF error expr ')' if_body  */
#line 284 "parser.y"
                                             { (yyval.ast) = astCreate(AST_IF, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of if condition\n"); SyntaxErrors++; }
#line 2051 "y.tab.c"
    break;

  case 90: /* if_statement: KW_IF '(' expr error if_body  */
#line 285 "parser.y"
                                             { (yyval.ast) = astCreate(AST_IF, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of if condition\n"); SyntaxErrors++; }
#line 2057 "y.tab.c"
    break;

  case 91: /* if_statement: KW_IF error expr ')' if_body KW_ELSE if_body  */
#line 286 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_IF_ELSE, 0, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of if condition\n"); SyntaxErrors++; }
#line 2063 "y.tab.c"
    break;

  case 92: /* if_statement: KW_IF '(' expr error if_body KW_ELSE if_body  */
#line 287 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_IF_ELSE, 0, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of if condition\n"); SyntaxErrors++; }
#line 2069 "y.tab.c"
    break;

  case 93: /* if_statement: KW_IF error expr ')' KW_LOOP if_body  */
#line 288 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_LOOP, 0, (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of loop condition\n"); SyntaxErrors++;}
#line 2075 "y.tab.c"
    break;

  case 94: /* if_statement: KW_IF '(' expr error KW_LOOP if_body  */
#line 289 "parser.y"
                                                     { (yyval.ast) = astCreate(AST_LOOP, 0, (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of loop condition\n"); SyntaxErrors++;}
#line 2081 "y.tab.c"
    break;

  case 95: /* if_statement: KW_IF error expr error if_body  */
#line 291 "parser.y"
                                               { (yyval.ast) = astCreate(AST_IF, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting if condition to be inside (...)\n"); SyntaxErrors++; }
#line 2087 "y.tab.c"
    break;

  case 96: /* if_statement: KW_IF error expr error if_body KW_ELSE if_body  */
#line 292 "parser.y"
                                                       { (yyval.ast) = astCreate(AST_IF_ELSE, 0, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), NULL, getLineNumber()); fprintf(stderr, "Expecting if condition to be inside (...)\n"); SyntaxErrors++; }
#line 2093 "y.tab.c"
    break;

  case 97: /* if_statement: KW_IF error expr error KW_LOOP if_body  */
#line 293 "parser.y"
                                                       { (yyval.ast) = astCreate(AST_LOOP, 0, (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting loop condition to be inside (...)\n"); SyntaxErrors++;}
#line 2099 "y.tab.c"
    break;

  case 98: /* cmd: var_attrib  */
#line 296 "parser.y"
                 {  (yyval.ast) = (yyvsp[0].ast); }
#line 2105 "y.tab.c"
    break;

  case 99: /* cmd: vec_attrib  */
#line 297 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 2111 "y.tab.c"
    break;

  case 100: /* cmd: output_cmd  */
#line 298 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 2117 "y.tab.c"
    break;

  case 101: /* cmd: return_cmd  */
#line 299 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 2123 "y.tab.c"
    break;

  case 102: /* cmd: %empty  */
#line 300 "parser.y"
      { (yyval.ast) = 0; }
#line 2129 "y.tab.c"
    break;

  case 103: /* var_attrib: TK_IDENTIFIER '=' expr  */
#line 303 "parser.y"
                                   { (yyval.ast) = astCreate(AST_VAR_ATTRIB, (yyvsp[-2].symbol), (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber());  }
#line 2135 "y.tab.c"
    break;

  case 104: /* var_attrib: TK_IDENTIFIER error expr  */
#line 304 "parser.y"
                               { (yyval.ast) = astCreate(AST_VAR_ATTRIB, (yyvsp[-2].symbol), (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting = on variable assignment\n"); SyntaxErrors++;  }
#line 2141 "y.tab.c"
    break;

  case 105: /* vec_attrib: TK_IDENTIFIER '[' expr ']' '=' expr  */
#line 307 "parser.y"
                                                { (yyval.ast) = astCreate(AST_VEC_ATTRIB, (yyvsp[-5].symbol), (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 2147 "y.tab.c"
    break;

  case 106: /* vec_attrib: TK_IDENTIFIER '[' expr ']' error expr  */
#line 308 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VEC_ATTRIB, (yyvsp[-5].symbol), (yyvsp[-3].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());  fprintf(stderr, "Expecting = on vector assignment\n"); SyntaxErrors++; }
#line 2153 "y.tab.c"
    break;

  case 107: /* output_cmd: KW_OUTPUT output_param_list  */
#line 311 "parser.y"
                                        { (yyval.ast) = astCreate(AST_OUTPUT_CMD, 0, (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber()); }
#line 2159 "y.tab.c"
    break;

  case 108: /* output_param_list: LIT_STRING ',' output_param_list  */
#line 314 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 2165 "y.tab.c"
    break;

  case 109: /* output_param_list: expr ',' output_param_list  */
#line 315 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); }
#line 2171 "y.tab.c"
    break;

  case 110: /* output_param_list: LIT_STRING  */
#line 316 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
#line 2177 "y.tab.c"
    break;

  case 111: /* output_param_list: expr  */
#line 317 "parser.y"
                                                        { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, NULL, (yyvsp[0].ast),  NULL, NULL, NULL, getLineNumber()); }
#line 2183 "y.tab.c"
    break;

  case 112: /* output_param_list: LIT_STRING error output_param_list  */
#line 320 "parser.y"
                                            { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, (yyvsp[-2].symbol), NULL, NULL, NULL, NULL, getLineNumber()), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting , on output command\n"); SyntaxErrors++; }
#line 2189 "y.tab.c"
    break;

  case 113: /* output_param_list: expr error output_param_list  */
#line 321 "parser.y"
                                            { (yyval.ast) = astCreate(AST_OUTPUT_PARAM_LIST, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting , on output command\n"); SyntaxErrors++; }
#line 2195 "y.tab.c"
    break;

  case 114: /* output_param_list: %empty  */
#line 322 "parser.y"
                   { (yyval.ast) = 0; }
#line 2201 "y.tab.c"
    break;

  case 115: /* return_cmd: KW_RETURN expr  */
#line 325 "parser.y"
                           { (yyval.ast) = astCreate(AST_RETURN_CMD, 0, (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber()); }
#line 2207 "y.tab.c"
    break;

  case 116: /* input_expr: KW_INPUT '(' KW_INT ')'  */
#line 330 "parser.y"
                                     { (yyval.ast) = astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2213 "y.tab.c"
    break;

  case 117: /* input_expr: KW_INPUT '(' KW_CHAR ')'  */
#line 331 "parser.y"
                                     { (yyval.ast) = astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2219 "y.tab.c"
    break;

  case 118: /* input_expr: KW_INPUT '(' KW_REAL ')'  */
#line 332 "parser.y"
                                     { (yyval.ast) = astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2225 "y.tab.c"
    break;

  case 119: /* input_expr: KW_INPUT '(' KW_BOOL ')'  */
#line 333 "parser.y"
                                     { (yyval.ast) = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2231 "y.tab.c"
    break;

  case 120: /* input_expr: KW_INPUT '(' error ')'  */
#line 336 "parser.y"
                                   { (yyval.ast) = astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting type on input command\n"); SyntaxErrors++; }
#line 2237 "y.tab.c"
    break;

  case 121: /* input_expr: KW_INPUT error  */
#line 337 "parser.y"
                           {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting (type) on input command\n"); SyntaxErrors++; }
#line 2243 "y.tab.c"
    break;

  case 122: /* input_expr: KW_INPUT error KW_INT ')'  */
#line 339 "parser.y"
                                      { (yyval.ast) =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(int) instead\n"); SyntaxErrors++; }
#line 2249 "y.tab.c"
    break;

  case 123: /* input_expr: KW_INPUT '(' KW_INT error  */
#line 340 "parser.y"
                                      {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(int) instead\n"); SyntaxErrors++; }
#line 2255 "y.tab.c"
    break;

  case 124: /* input_expr: KW_INPUT error KW_INT error  */
#line 341 "parser.y"
                                        {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(int)\n"); SyntaxErrors++; }
#line 2261 "y.tab.c"
    break;

  case 125: /* input_expr: KW_INPUT error KW_CHAR ')'  */
#line 343 "parser.y"
                                       {  (yyval.ast) = astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(char) instead\n"); SyntaxErrors++; }
#line 2267 "y.tab.c"
    break;

  case 126: /* input_expr: KW_INPUT '(' KW_CHAR error  */
#line 344 "parser.y"
                                       {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(char) instead\n"); SyntaxErrors++; }
#line 2273 "y.tab.c"
    break;

  case 127: /* input_expr: KW_INPUT error KW_CHAR error  */
#line 345 "parser.y"
                                         {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(char)\n"); SyntaxErrors++; }
#line 2279 "y.tab.c"
    break;

  case 128: /* input_expr: KW_INPUT error KW_REAL ')'  */
#line 347 "parser.y"
                                       {  (yyval.ast) = astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(real) instead\n"); SyntaxErrors++; }
#line 2285 "y.tab.c"
    break;

  case 129: /* input_expr: KW_INPUT '(' KW_REAL error  */
#line 348 "parser.y"
                                       {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(real) instead\n"); SyntaxErrors++; }
#line 2291 "y.tab.c"
    break;

  case 130: /* input_expr: KW_INPUT error KW_REAL error  */
#line 349 "parser.y"
                                         {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(real)\n"); SyntaxErrors++; }
#line 2297 "y.tab.c"
    break;

  case 131: /* input_expr: KW_INPUT error KW_BOOL ')'  */
#line 351 "parser.y"
                                       {  (yyval.ast) = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( before input command type, it should be input(bool) instead\n"); SyntaxErrors++; }
#line 2303 "y.tab.c"
    break;

  case 132: /* input_expr: KW_INPUT '(' KW_BOOL error  */
#line 352 "parser.y"
                                       {  (yyval.ast) =  astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(bool) instead\n"); SyntaxErrors++; }
#line 2309 "y.tab.c"
    break;

  case 133: /* input_expr: KW_INPUT error KW_BOOL error  */
#line 353 "parser.y"
                                         {   (yyval.ast) = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(bool)\n"); SyntaxErrors++; }
#line 2315 "y.tab.c"
    break;

  case 134: /* expr: LIT_INT  */
#line 357 "parser.y"
                                            { (yyval.ast) = astCreate(AST_LIT_INT, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2321 "y.tab.c"
    break;

  case 135: /* expr: TK_IDENTIFIER  */
#line 358 "parser.y"
                                            { (yyval.ast) = astCreate(AST_IDENTIFIER, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber());    }
#line 2327 "y.tab.c"
    break;

  case 136: /* expr: LIT_CHAR  */
#line 359 "parser.y"
                                            { (yyval.ast) = astCreate(AST_LIT_CHAR, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2333 "y.tab.c"
    break;

  case 137: /* expr: LIT_REAL  */
#line 360 "parser.y"
                                            { (yyval.ast) = astCreate(AST_LIT_REAL, (yyvsp[0].symbol), NULL, NULL, NULL, NULL, getLineNumber()); }
#line 2339 "y.tab.c"
    break;

  case 138: /* expr: TK_IDENTIFIER '[' expr ']'  */
#line 361 "parser.y"
                                            { (yyval.ast) = astCreate(AST_VEC_ACCESS, (yyvsp[-3].symbol), (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber());   }
#line 2345 "y.tab.c"
    break;

  case 139: /* expr: input_expr  */
#line 362 "parser.y"
                                            { (yyval.ast) = (yyvsp[0].ast);                                                 }
#line 2351 "y.tab.c"
    break;

  case 140: /* expr: func_call  */
#line 363 "parser.y"
                                            { (yyval.ast) = (yyvsp[0].ast);                                                }
#line 2357 "y.tab.c"
    break;

  case 141: /* expr: expr '*' expr  */
#line 364 "parser.y"
                                            { (yyval.ast) = astCreate(AST_MUL, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2363 "y.tab.c"
    break;

  case 142: /* expr: expr '/' expr  */
#line 365 "parser.y"
                                            { (yyval.ast) = astCreate(AST_DIV, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2369 "y.tab.c"
    break;

  case 143: /* expr: expr '+' expr  */
#line 366 "parser.y"
                                            { (yyval.ast) = astCreate(AST_ADD, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2375 "y.tab.c"
    break;

  case 144: /* expr: expr '-' expr  */
#line 367 "parser.y"
                                            { (yyval.ast) = astCreate(AST_SUB, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2381 "y.tab.c"
    break;

  case 145: /* expr: '-' expr  */
#line 368 "parser.y"
                                            { (yyval.ast) = astCreate(AST_NEG, 0, (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber());       }
#line 2387 "y.tab.c"
    break;

  case 146: /* expr: '~' expr  */
#line 369 "parser.y"
                                            { (yyval.ast) = astCreate(AST_NOT, 0, (yyvsp[0].ast), NULL, NULL, NULL, getLineNumber());       }
#line 2393 "y.tab.c"
    break;

  case 147: /* expr: expr '&' expr  */
#line 370 "parser.y"
                                            { (yyval.ast) = astCreate(AST_AND, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2399 "y.tab.c"
    break;

  case 148: /* expr: expr '|' expr  */
#line 371 "parser.y"
                                            { (yyval.ast) = astCreate(AST_OR, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2405 "y.tab.c"
    break;

  case 149: /* expr: expr OPERATOR_LE expr  */
#line 372 "parser.y"
                                            { (yyval.ast) = astCreate(AST_LE, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2411 "y.tab.c"
    break;

  case 150: /* expr: expr OPERATOR_GE expr  */
#line 373 "parser.y"
                                            { (yyval.ast) = astCreate(AST_GE, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2417 "y.tab.c"
    break;

  case 151: /* expr: expr OPERATOR_EQ expr  */
#line 374 "parser.y"
                                            { (yyval.ast) = astCreate(AST_EQ, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2423 "y.tab.c"
    break;

  case 152: /* expr: expr OPERATOR_DIF expr  */
#line 375 "parser.y"
                                            { (yyval.ast) = astCreate(AST_DIF, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());         }
#line 2429 "y.tab.c"
    break;

  case 153: /* expr: expr '>' expr  */
#line 376 "parser.y"
                                            { (yyval.ast) = astCreate(AST_GT, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2435 "y.tab.c"
    break;

  case 154: /* expr: expr '<' expr  */
#line 377 "parser.y"
                                            { (yyval.ast) = astCreate(AST_LT, 0, (yyvsp[-2].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());          }
#line 2441 "y.tab.c"
    break;

  case 155: /* expr: '(' expr ')'  */
#line 378 "parser.y"
                                            { (yyval.ast) = astCreate(AST_NESTED_EXPR, 0, (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber()); }
#line 2447 "y.tab.c"
    break;

  case 156: /* func_call: TK_IDENTIFIER '(' expr_list ')'  */
#line 383 "parser.y"
                                           { (yyval.ast) = astCreate(AST_FUNC_CALL, (yyvsp[-3].symbol), (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber());  }
#line 2453 "y.tab.c"
    break;

  case 157: /* func_call: TK_IDENTIFIER '(' expr_list error  */
#line 385 "parser.y"
                                        { (yyval.ast) = astCreate(AST_FUNC_CALL, (yyvsp[-3].symbol), (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) on end of function call\n"); SyntaxErrors++; }
#line 2459 "y.tab.c"
    break;

  case 158: /* func_call: TK_IDENTIFIER error expr_list ')'  */
#line 386 "parser.y"
                                        { (yyval.ast) = astCreate(AST_FUNC_CALL, (yyvsp[-3].symbol), (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( on start of function call\n"); SyntaxErrors++; }
#line 2465 "y.tab.c"
    break;

  case 159: /* func_call: TK_IDENTIFIER error expr_list error  */
#line 387 "parser.y"
                                          { (yyval.ast) = astCreate(AST_FUNC_CALL, (yyvsp[-3].symbol), (yyvsp[-1].ast), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting function parameters to be inside (...)\n"); SyntaxErrors++; }
#line 2471 "y.tab.c"
    break;

  case 160: /* expr_list: expr expr_list_aux  */
#line 390 "parser.y"
                                      { (yyval.ast) = astCreate(AST_EXPR_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());}
#line 2477 "y.tab.c"
    break;

  case 161: /* expr_list: %empty  */
#line 391 "parser.y"
                                      { (yyval.ast) = 0; }
#line 2483 "y.tab.c"
    break;

  case 162: /* expr_list_aux: ',' expr expr_list_aux  */
#line 394 "parser.y"
                                      { (yyval.ast) = astCreate(AST_EXPR_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber());}
#line 2489 "y.tab.c"
    break;

  case 163: /* expr_list_aux: error expr expr_list_aux  */
#line 396 "parser.y"
                               { (yyval.ast) = astCreate(AST_EXPR_LIST, NULL, (yyvsp[-1].ast), (yyvsp[0].ast), NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting function parameters to be separated by a ,\n"); SyntaxErrors++; }
#line 2495 "y.tab.c"
    break;

  case 164: /* expr_list_aux: %empty  */
#line 397 "parser.y"
                                      { (yyval.ast) = 0; }
#line 2501 "y.tab.c"
    break;


#line 2505 "y.tab.c"

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

#line 401 "parser.y"


#include "definitions.h" // yyparse() is defined here
