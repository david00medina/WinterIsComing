/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "flex-bison/wic.y" /* yacc.c:337  */


    /* Declaraciones */

    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "../utils/termcolor.hpp"
    #include "../symbol-table/SymbolTable.hpp"
    #include "../ast/AbstractSyntaxTree.hpp"

    int yylex(void);
    void yyerror(char const *);

    extern int level;
    extern int yylineno;

    wic::GSymbolTable* gst = new wic::GSymbolTable();
    wic::SSymbolTable* sst = new wic::SSymbolTable();
    wic::LSymbolTable* lst = new wic::LSymbolTable();
    wic::AbstractSyntaxTree* ast;

    wic::data_type promote_to_float(wic::ASTNode*, wic::ASTNode*);

#line 97 "wic.tab.c" /* yacc.c:337  */
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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "wic.tab.h".  */
#ifndef YY_YY_WIC_TAB_H_INCLUDED
# define YY_YY_WIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEW = 258,
    CONTINUE = 259,
    BREAK = 260,
    RETURN = 261,
    FUN = 262,
    GLOBAL = 263,
    STATIC = 264,
    INT_VAL = 265,
    REAL_VAL = 266,
    BOOL_VAL = 267,
    CHAR_VAL = 268,
    STRING_VAL = 269,
    INT_TYPE = 270,
    REAL_TYPE = 271,
    BOOL_TYPE = 272,
    CHAR_TYPE = 273,
    VOID = 274,
    ASSIGN = 275,
    SUM = 276,
    SUBSTRACT = 277,
    PRODUCT = 278,
    DIVIDE = 279,
    MODULUS = 280,
    POWER = 281,
    RADICAL = 282,
    INCREMENT = 283,
    DECREMENT = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    EQUALS = 288,
    NOT_EQUALS = 289,
    GREATER = 290,
    GREATER_EQUALS = 291,
    LESS = 292,
    LESS_EQUALS = 293,
    AND_BIT = 294,
    OR_BIT = 295,
    XOR_BIT = 296,
    LEFT_SHIFT = 297,
    RIGHT_SHIFT = 298,
    UNION = 299,
    DIFFERENCE = 300,
    INTERSECTION = 301,
    IF_CLAUSE = 302,
    FOR_WHILE_CLAUSE = 303,
    HEADER_END = 304,
    ELSE_IF_FOR_WHILE_CLAUSE = 305,
    SQUARE_BRACKET_OPEN = 306,
    SQUARE_BRACKET_CLOSE = 307,
    CURLY_BRACKET_OPEN = 308,
    CURLY_BRACKET_CLOSE = 309,
    ELEM_SEPARATOR = 310,
    PARETHESES_OPEN = 311,
    PARETHESES_CLOSE = 312,
    END_OF_INSTR = 313,
    OPEN_CONTEXT_TAG = 314,
    CLOSE_CONTEXT_TAG = 315,
    CHAR_QUOTE = 316,
    STRING_QUOTE = 317,
    ID = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  void *  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WIC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   600

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  244

#define YYUNDEFTOK  2
#define YYMAXUTOK   318

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    90,    91,    93,   100,   107,   114,
     115,   116,   118,   119,   121,   127,   133,   139,   146,   150,
     160,   161,   162,   163,   168,   169,   171,   172,   174,   175,
     177,   184,   191,   192,   194,   196,   201,   205,   208,   211,
     213,   218,   222,   225,   228,   230,   235,   239,   242,   245,
     247,   249,   262,   262,   283,   284,   294,   304,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     330,   340,   350,   360,   362,   372,   373,   375,   376,   378,
     383,   390,   395,   402,   407,   413,   419
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEW", "CONTINUE", "BREAK", "RETURN",
  "FUN", "GLOBAL", "STATIC", "INT_VAL", "REAL_VAL", "BOOL_VAL", "CHAR_VAL",
  "STRING_VAL", "INT_TYPE", "REAL_TYPE", "BOOL_TYPE", "CHAR_TYPE", "VOID",
  "ASSIGN", "SUM", "SUBSTRACT", "PRODUCT", "DIVIDE", "MODULUS", "POWER",
  "RADICAL", "INCREMENT", "DECREMENT", "AND", "OR", "NOT", "EQUALS",
  "NOT_EQUALS", "GREATER", "GREATER_EQUALS", "LESS", "LESS_EQUALS",
  "AND_BIT", "OR_BIT", "XOR_BIT", "LEFT_SHIFT", "RIGHT_SHIFT", "UNION",
  "DIFFERENCE", "INTERSECTION", "IF_CLAUSE", "FOR_WHILE_CLAUSE",
  "HEADER_END", "ELSE_IF_FOR_WHILE_CLAUSE", "SQUARE_BRACKET_OPEN",
  "SQUARE_BRACKET_CLOSE", "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE",
  "ELEM_SEPARATOR", "PARETHESES_OPEN", "PARETHESES_CLOSE", "END_OF_INSTR",
  "OPEN_CONTEXT_TAG", "CLOSE_CONTEXT_TAG", "CHAR_QUOTE", "STRING_QUOTE",
  "ID", "$accept", "input", "data_init", "array_init", "data_type",
  "instr", "comma_exp_init", "comma_exp", "fun_init", "fun_call",
  "while_instr", "while_middle_block", "for_instr", "for_middle_block",
  "if_instr", "if_middle_block", "array_access", "expr", "@1", "term",
  "power", "factor", "data_value", "data_vector", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

#define YYPACT_NINF -46

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,    96,    33,    33,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,    22,   -45,   -37,   133,   -46,   301,    -1,    -1,    16,
      29,     8,    46,   -10,   -46,     5,    11,   -46,   -46,   -46,
     -46,   -46,   443,    99,    45,   -46,   -46,   -46,     0,    20,
     -46,     5,   -46,     5,   -46,   -46,   -46,   -46,    99,    12,
      -9,   337,   -46,    27,    23,    54,   -46,   -46,   110,   -46,
     108,   -46,   111,    15,    -1,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,    81,   107,   133,   133,   133,   133,   133,
      78,    82,   -46,   365,   -46,    -1,   -46,   -46,    85,   164,
     301,    77,   301,    90,   -46,   -46,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    88,    93,   391,    45,    45,    45,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,    94,   554,   130,
     554,   -46,    95,    98,   103,    64,    92,   -46,   133,    -1,
      -1,   106,   -19,   104,    -4,    99,   102,   113,    -1,   119,
     -46,   116,   121,   -46,   131,   132,   120,   124,   -46,   125,
     138,   141,   105,   149,   151,    -1,    -1,   139,   218,   154,
     241,   156,   155,   146,   148,   153,   160,   527,   157,   165,
     471,   167,   288,   -46,   -46,   159,   161,   173,   172,   174,
     184,   176,   186,   499,    -1,   177,   179,    -1,   180,   183,
     185,   187,   301,   163,    -1,   189,   178,    -1,   190,    -1,
     195,   417,   -46,   182,    -1,   -46,   196,    -1,   197,    -1,
     200,   -46,   199,   -46,   201,   -46,   202,   205,   -46,   -46,
     -46,    -1,   206,   -46
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     0,    89,    91,    93,    14,    15,    16,
      17,     0,     0,     0,     0,    29,     0,     5,     5,     0,
       0,    51,     0,     0,    11,     8,     0,    24,    25,    22,
      21,    20,    23,    78,    83,    86,    88,    79,     0,     0,
       9,     6,    10,     7,    90,    92,    57,    59,    69,     0,
      51,     0,     3,     0,     0,     0,    58,    60,     0,    29,
      52,     1,    18,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,    87,     5,    94,    95,     0,     0,
       0,     0,     0,     0,    13,     2,    55,    56,    67,    68,
      65,    66,    63,    64,    61,    62,    70,    71,    72,    73,
      74,    75,    76,    77,     0,     0,     0,    80,    81,    82,
      85,    84,    27,    27,    28,     4,    50,     0,    54,     0,
      19,    12,     0,     0,     0,     0,     0,    34,     0,     5,
       5,     0,     0,     0,     0,    53,     0,     0,     5,     0,
      33,     0,     0,    32,    47,    37,     0,     0,    26,     0,
       0,     0,     0,     0,    42,     5,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     5,     0,     5,
       0,     0,    46,     0,     5,    36,     0,     5,     0,     5,
       0,    45,     0,    35,     0,    41,     0,     0,    48,    38,
      40,     5,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -17,   -46,    10,     2,   -46,    80,   208,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -14,   -46,    24,
      40,   -12,   -46,   -46
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    25,    26,   145,    49,    27,    28,
      29,   173,    30,   182,    31,   171,    60,    32,   101,    33,
      34,    35,    36,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    53,    51,    39,    41,    43,     1,     2,     3,     4,
       5,     6,    40,    42,     7,     8,     9,    10,    46,    56,
      57,    11,     4,     5,     6,   103,    47,    12,    13,    54,
     159,    14,    44,    45,    11,    93,    56,    57,    48,   160,
      12,    13,    58,    55,    14,   162,    61,   105,     7,     8,
       9,    10,    15,    62,   163,    16,    63,    17,    18,    58,
      19,    20,    21,    90,    59,    15,    92,   104,    16,    64,
     126,    88,    89,    19,    20,    50,   130,   131,   135,     7,
       8,     9,    10,    91,    96,    93,   138,    95,   140,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     7,     8,     9,
      10,     7,     8,     9,    10,    38,    97,     4,     5,     6,
      98,   152,    85,    86,    87,   127,   128,   129,   100,    11,
     124,   102,   156,   157,   132,    12,    13,   136,   133,    14,
     139,   166,   141,     4,     5,     6,   142,   153,   153,   154,
     148,   143,   147,   179,   149,    11,   125,   150,   183,   184,
      15,   151,   164,    16,   187,   158,   190,   161,    19,    20,
      50,   168,   155,   165,     4,     5,     6,   167,   203,   169,
     174,   170,   172,   175,   176,   177,    11,   213,   185,    16,
     216,   178,    12,    13,    19,    20,    14,   223,   221,   180,
     226,   181,   228,   188,   191,   192,   193,   232,   194,   196,
     234,   195,   236,   146,   199,   198,   201,    15,   204,   205,
      16,   137,   206,   222,   242,    19,    20,    50,     4,     5,
       6,   207,   208,   209,   210,   211,   214,   215,   225,   217,
      11,   218,   231,     0,   219,   220,    12,    13,   224,   227,
      14,     4,     5,     6,   229,     0,   233,   235,   237,   238,
       0,   239,   240,    11,   241,   186,   243,    99,     0,    12,
      13,    15,     0,    14,    16,     0,     0,     0,     0,    19,
      20,    50,     0,     0,     0,     0,     0,     0,     0,   189,
       0,     0,     0,     0,    15,     0,     0,    16,     4,     5,
       6,     0,    19,    20,    50,     0,     0,     0,     0,     0,
      11,     4,     5,     6,     0,     0,    12,    13,     0,     0,
      14,     0,     0,    11,     0,     0,     0,     0,     0,    12,
      13,     0,     0,    14,     0,     0,   202,     0,     0,     0,
       0,    15,     0,     0,    16,     0,     0,     0,     0,    19,
      20,    50,     0,     0,    15,     0,     0,    16,    65,    66,
       0,     0,    19,    20,    50,     0,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    65,    66,     0,     0,
       0,     0,     0,     0,    94,    67,    68,     0,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    65,    66,     0,     0,     0,     0,     0,     0,
     134,    67,    68,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    65,    66,
     144,     0,     0,     0,     0,     0,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    65,    66,   230,     0,     0,     0,
       0,     0,     0,    67,    68,     0,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    65,    66,     0,     0,     0,     0,     0,     0,
       0,    67,    68,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,     0,   200,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,   212,    65,    66,
       0,     0,     0,     0,     0,     0,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,   197,    65,    66,     0,     0,     0,
       0,     0,     0,     0,    67,    68,     0,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82
};

static const yytype_int16 yycheck[] =
{
      17,    18,    16,     1,     2,     3,     7,     8,     9,    10,
      11,    12,     2,     3,    15,    16,    17,    18,    63,    28,
      29,    22,    10,    11,    12,    10,    63,    28,    29,    13,
      49,    32,    10,    11,    22,    49,    28,    29,    14,    58,
      28,    29,    51,    14,    32,    49,     0,    64,    15,    16,
      17,    18,    53,    63,    58,    56,    51,    58,    59,    51,
      61,    62,    63,    63,    56,    53,    54,    52,    56,    58,
      84,    26,    27,    61,    62,    63,    88,    89,    95,    15,
      16,    17,    18,    63,    61,    99,   100,    60,   102,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    15,    16,    17,
      18,    15,    16,    17,    18,    19,    62,    10,    11,    12,
      10,    57,    23,    24,    25,    85,    86,    87,    20,    22,
      49,    20,   149,   150,    56,    28,    29,    52,    56,    32,
      63,   158,    52,    10,    11,    12,    58,   145,   146,    57,
      20,    58,    58,    48,    59,    22,    49,    59,   175,   176,
      53,    58,    60,    56,   178,    59,   180,    63,    61,    62,
      63,    55,   148,    60,    10,    11,    12,    58,   192,    58,
      60,    50,    50,    59,    59,    47,    22,   204,    49,    56,
     207,    50,    28,    29,    61,    62,    32,   214,   212,    50,
     217,    50,   219,    49,    48,    50,    60,   224,    60,    49,
     227,    58,   229,   133,    49,    58,    49,    53,    59,    58,
      56,    57,    49,    60,   241,    61,    62,    63,    10,    11,
      12,    59,    58,    49,    58,    49,    59,    58,    60,    59,
      22,    58,    60,    -1,    59,    58,    28,    29,    59,    59,
      32,    10,    11,    12,    59,    -1,    60,    60,    58,    60,
      -1,    60,    60,    22,    59,    47,    60,    59,    -1,    28,
      29,    53,    -1,    32,    56,    -1,    -1,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    56,    10,    11,
      12,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      22,    10,    11,    12,    -1,    -1,    28,    29,    -1,    -1,
      32,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    32,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    63,    -1,    -1,    53,    -1,    -1,    56,    21,    22,
      -1,    -1,    61,    62,    63,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    21,    22,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    21,    22,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    48,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    15,    16,    17,
      18,    22,    28,    29,    32,    53,    56,    58,    59,    61,
      62,    63,    65,    66,    67,    68,    69,    72,    73,    74,
      76,    78,    81,    83,    84,    85,    86,    87,    19,    68,
      67,    68,    67,    68,    10,    11,    63,    63,    83,    71,
      63,    81,    65,    65,    13,    14,    28,    29,    51,    56,
      80,     0,    63,    51,    58,    21,    22,    30,    31,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    23,    24,    25,    26,    27,
      63,    63,    54,    81,    57,    60,    61,    62,    10,    71,
      20,    82,    20,    10,    52,    65,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    49,    49,    81,    84,    84,    84,
      85,    85,    56,    56,    55,    65,    52,    57,    81,    63,
      81,    52,    58,    58,    49,    70,    70,    58,    20,    59,
      59,    58,    57,    68,    57,    83,    65,    65,    59,    49,
      58,    63,    49,    58,    60,    60,    65,    58,    55,    58,
      50,    79,    50,    75,    60,    59,    59,    47,    50,    48,
      50,    50,    77,    65,    65,    49,    47,    81,    49,    48,
      81,    48,    50,    60,    60,    58,    49,    47,    58,    49,
      48,    49,    48,    81,    59,    58,    49,    59,    58,    49,
      58,    49,    48,    65,    59,    58,    65,    59,    58,    59,
      58,    81,    60,    65,    59,    60,    65,    59,    65,    59,
      49,    60,    65,    60,    65,    60,    65,    58,    60,    60,
      60,    59,    65,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    65,    65,    65,    66,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    72,    72,    73,    74,    74,    74,    75,    75,
      76,    76,    76,    77,    77,    78,    78,    78,    79,    79,
      80,    81,    82,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      83,    83,    83,    83,    84,    84,    84,    85,    85,    86,
      86,    86,    86,    86,    86,    86,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     4,     0,     2,     2,     1,     2,
       2,     1,     4,     3,     1,     1,     1,     1,     2,     4,
       1,     1,     1,     1,     1,     1,     4,     0,     3,     0,
      11,    11,     7,     7,     5,    15,    14,     7,     9,     0,
      16,    15,     8,    10,     0,    15,    14,     7,     9,     0,
       3,     1,     0,     6,     4,     3,     3,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       2,     1,     2,     1,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 6:
#line 93 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    wic::entry_data* entry_d = reinterpret_cast<wic::entry_data *>(yyvsp[0]);
						    entry_d->var.global = true;
						    entry_d->var.stat = false;
						    entry_d->var.local = false;
						    yyval = entry_d;
						  }
#line 1534 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 100 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    wic::entry_data* entry_d = reinterpret_cast<wic::entry_data *>(yyvsp[0]);
						    entry_d->var.global = false;
						    entry_d->var.stat = true;
						    entry_d->var.local = false;
						    yyval = entry_d;
    						  }
#line 1546 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 107 "flex-bison/wic.y" /* yacc.c:1652  */
    {
    						    wic::entry_data* entry_d = reinterpret_cast<wic::entry_data *>(yyvsp[0]);
    						    entry_d->var.global = false;
    						    entry_d->var.stat = false;
    						    entry_d->var.local = true;
    						    yyval = entry_d;
     						  }
#line 1558 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 121 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    wic::entry_data* entry_d = new wic::entry_data();
						    entry_d->var.type = wic::INT;
						    entry_d->var.size = 4;
						    yyval = entry_d;
						  }
#line 1569 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 15:
#line 127 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    wic::entry_data* entry_d = new wic::entry_data();
						    entry_d->var.type = wic::REAL;
						    entry_d->var.size = 4;
						    yyval = entry_d;
						  }
#line 1580 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 133 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    wic::entry_data* entry_d = new wic::entry_data();
						    entry_d->var.type = wic::BOOL;
						    entry_d->var.size = 1;
						    yyval = entry_d;
						  }
#line 1591 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 139 "flex-bison/wic.y" /* yacc.c:1652  */
    {
    						    wic::entry_data* entry_d = new wic::entry_data();
    						    entry_d->var.type = wic::CHAR;
    						    entry_d->var.size = 1;
    						    yyval = entry_d;
    						  }
#line 1602 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 146 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    std::cout << "Instrucción (DECLARE VAR)\n" << std::endl;
						    yyval = ast->tree_build(yyvsp[-1], yyvsp[0]);
						  }
#line 1611 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 150 "flex-bison/wic.y" /* yacc.c:1652  */
    {
    						    std::cout << "Instrucción (=)\n" << std::endl;
    						    wic::ASTNode* node = ast->tree_build(yyvsp[-3], yyvsp[-2]);

    						    wic::ASTNode* expr = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);
    						    wic::ASTAssignNode* assign = new wic::ASTAssignNode(node->get_data_type(), node, expr);

    						    yyval = ast->tree_build(assign);
    						    ast->print();
    						  }
#line 1626 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 160 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción (IF-IFELSE-ELSE)\n"); }
#line 1632 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 161 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción (FOR-FORELSE-ELSE)\n"); }
#line 1638 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 162 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción (WHILE-WHILEELSE-ELSE)\n"); }
#line 1644 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 163 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    printf("Instrucción EXPR\n");
                                                    //ast->print();
                                                    //$$ = ast->get_root();
                                                  }
#line 1654 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 168 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción FUN (declaration)\n"); }
#line 1660 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 169 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción FUN (call)\n"); }
#line 1666 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 171 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (,%s %s,)\n"); }
#line 1672 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 174 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Función llamada (,)\n"); }
#line 1678 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 179 "flex-bison/wic.y" /* yacc.c:1652  */
    {
        // TODO: Pendiente
        // wic::ASTLeafNode* node = reinterpret_cast<wic::ASTIDNode *>($3);
        // printf("Función (nombre=%s)\n", node->get_id());
     }
#line 1688 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 186 "flex-bison/wic.y" /* yacc.c:1652  */
    {
        // TODO: Pendiente
        // wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($3);
        // printf("Función (nombre=%s)\n", node->get_id());
      }
#line 1698 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 191 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Función declaración void\n"); }
#line 1704 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 192 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Función declaración\n"); }
#line 1710 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 194 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Función llamada PRINT\n"); }
#line 1716 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 249 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                          wic::ASTIDNode* id = reinterpret_cast<wic::ASTIDNode *>(yyvsp[0]);
                                                          std::cout << "Factor : ID (name=" << id->get_id() << ")" << std::endl;

                                                          if (!id->is_registered()) {
                                                          	std::cout << termcolor::red << termcolor::bold
                                                          	<< "[!] Error: " << termcolor::reset << "\'" << id->get_id()
                                                          	<< "\' was not declared in this scope"
                                                          	<< std::endl;
                                                          	exit(-1);
                                                          }
                                                          yyval = id;
                                                        }
#line 1734 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 262 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Término (VectorVal)");}
#line 1740 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 263 "flex-bison/wic.y" /* yacc.c:1652  */
    {
						    std::cout << "Expresión (=)" << std::endl;

						    wic::ASTIDNode* id = reinterpret_cast<wic::ASTIDNode *>(yyvsp[-5]);

						    if (!id->is_registered()) {
						    	std::cout << termcolor::red << termcolor::bold
						    	<< "[!] Error: " << termcolor::reset << "\'" << id->get_id()
						    	<< "\' was not declared in this scope"
						    	<< std::endl;
						    	exit(-1);
						    }

						    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[-3]);
						    wic::ASTAssignNode* assign = new wic::ASTAssignNode(id->get_data_type(), id, term);

						    ast->tree_build(assign);
						    yyval = assign;
						    lst->show(id->get_id());
						  }
#line 1765 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 283 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Instrucción acceso array\n"); }
#line 1771 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 284 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (Suma)" << std::endl;

                                                    wic::ASTNode* expr = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTSumNode* sum = new wic::ASTSumNode(wic::UNKNOWN, expr, term);

                                                    yyval = ast->tree_build(sum);
                                                  }
#line 1786 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 294 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (Resta)" << std::endl;

                                                    wic::ASTNode* expr = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTSubNode* sub = new wic::ASTSubNode(wic::UNKNOWN, expr, term);

                                                    yyval = ast->tree_build(sub);
                                                  }
#line 1801 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 304 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (++ID)" << std::endl;
                                                  }
#line 1809 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 307 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (ID++)\n"); }
#line 1815 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 308 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (--ID)\n"); }
#line 1821 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 309 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (ID--)\n"); }
#line 1827 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 310 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (<)\n"); }
#line 1833 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 311 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (<=)\n"); }
#line 1839 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 312 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (>)\n"); }
#line 1845 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 313 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (>=)\n"); }
#line 1851 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 314 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (==)\n"); }
#line 1857 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 315 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (!=)\n"); }
#line 1863 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 316 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (&&)\n"); }
#line 1869 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 317 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (||)\n"); }
#line 1875 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 318 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (!)\n"); }
#line 1881 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 319 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (&)\n"); }
#line 1887 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 320 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (|)\n"); }
#line 1893 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 321 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (^)\n"); }
#line 1899 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 322 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (<<)\n"); }
#line 1905 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 323 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (>>)\n"); }
#line 1911 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 324 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (U)\n"); }
#line 1917 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 325 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (D)\n"); }
#line 1923 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 326 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (I)\n"); }
#line 1929 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 327 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión\n"); yyval = yyvsp[0]; }
#line 1935 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 328 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Expresión (vector)\n"); }
#line 1941 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 330 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (Producto)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTProdNode* prod = new wic::ASTProdNode(wic::UNKNOWN, term, power);

                                                    yyval = ast->tree_build(prod);
                                                  }
#line 1956 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 340 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (División)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTDivNode* div = new wic::ASTDivNode(wic::UNKNOWN, term, power);

                                                    yyval = ast->tree_build(div);
                                                  }
#line 1971 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 350 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (Módulo)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTModNode* mod = new wic::ASTModNode(wic::INT, term, power);

                                                    yyval = ast->tree_build(mod);
                                                  }
#line 1986 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 360 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Término\n"); yyval = yyvsp[0]; }
#line 1992 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 362 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    std::cout << "Expresión (Radical)" << std::endl;

                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>(yyvsp[-2]);
                                                    wic::ASTNode* factor = reinterpret_cast<wic::ASTNode *>(yyvsp[0]);

                                                    wic::ASTRadicalNode* radical = new wic::ASTRadicalNode(wic::UNKNOWN, power, factor);

                                                    yyval = ast->tree_build(radical);
                                                  }
#line 2007 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 372 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Potencia/Raiz (Potencia)"); yyval = yyvsp[-2]; }
#line 2013 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 373 "flex-bison/wic.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2019 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 87:
#line 375 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Factor (Expresión parentesis)\n"); yyval = yyvsp[-1]; }
#line 2025 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 376 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Factor (DATA_VALUE)\n"); yyval = yyvsp[0]; }
#line 2031 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 89:
#line 378 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[0]);
                                                    std::cout << "Factor : INT(value=" << node->get_data_value().int_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2041 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 90:
#line 383 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[0]);
                                                    int val = -node->get_data_value().int_val;
                                                    node->set_data_value((void*)&val);
                                                    std::cout << "Factor: NEG_INT(value=" << node->get_data_value().int_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2053 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 390 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[0]);
                                                    std::cout << "Factor : REAL(value=" << node->get_data_value().real_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2063 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 395 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[0]);
                                                    float val = -node->get_data_value().real_val;
                                                    node->set_data_value((void*)&val);
                                                    std::cout << "Factor: NEG_REAL(value=" << node->get_data_value().real_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2075 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 402 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[0]);
                                                    std::cout << "Factor : BOOL(value=" << node->get_data_value().bool_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2085 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 407 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[-1]);
                                                    std::cout << "Factor : CHAR(value=" << node->get_data_value().char_val << ",ascii="
                                                    << (int)node->get_data_value().char_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2096 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 413 "flex-bison/wic.y" /* yacc.c:1652  */
    {
                                                    wic::ASTLeafNode* node = reinterpret_cast<wic::ASTLeafNode *>(yyvsp[-1]);
                                                    std::cout << "Factor : STRING(value=" << node->get_data_value().str_val << ")" << std::endl;
                                                    yyval = reinterpret_cast<void *>(node);
                                                  }
#line 2106 "wic.tab.c" /* yacc.c:1652  */
    break;

  case 96:
#line 419 "flex-bison/wic.y" /* yacc.c:1652  */
    { printf("Factor (VECTOR)\n"); }
#line 2112 "wic.tab.c" /* yacc.c:1652  */
    break;


#line 2116 "wic.tab.c" /* yacc.c:1652  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 421 "flex-bison/wic.y" /* yacc.c:1918  */


/*wic::data_type promote_to_float(wic::ASTNode* elem1, wic::ASTNode* elem2)
{
    if (elem1->get_data_type() == wic::REAL && elem2->get_data_type() == wic::REAL) return wic::REAL;
    else if (elem1->get_data_type() == wic::INT && elem2->get_data_type() == wic::INT) return wic::INT;
    else if (elem1->get_data_type() == wic::INT && elem2->get_data_type() == wic::REAL)
    {
       float val = static_cast<float>(elem1->get_data_value().int_val);
       elem1->set_data_type(wic::REAL);
       elem1->set_data_value((void*)&val);
    }
    else if (elem1->get_data_type() == wic::REAL && elem2->get_data_type() == wic::INT)
    {
       float val = static_cast<float>(elem2->get_data_value().int_val);
       elem2->set_data_type(wic::REAL);
       elem2->set_data_value((void*)&val);
    }
    return wic::REAL;
}*/
