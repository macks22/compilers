/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "uncool.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "lib/errors.h"
#include "lib/core.h"
#include "logging.h"

void error(int errtoken, ...);
int wdeclare_attribute(char *name, int type);
int wdeclare_method(char *name, int type, int argcount);
void wend_method(int flag);

char *containing_class_name();
int check_array_index(int type);
int check_method_types(char *name, int type1, int type2);
int type_check_attr(char *name, int correct_type, int assign_type);
int type_check_int_arr_assign(char *name, int assign_type);
int get_attribute_type(char *name);
char *type_name_from_token(int token);
int check_method_ref(char *class_name, char *method_name, int argcount);
int make_new_class(char *class_name, int argcount);

extern int verbose;
extern int linect;

int num_errors;

char *cname;
int cflag, dflag, flag, typetoken;
ScopeStack *stack;
Symbol *method, attr;


#line 103 "uncool.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "uncool.tab.h".  */
#ifndef YY_YY_UNCOOL_TAB_H_INCLUDED
# define YY_YY_UNCOOL_TAB_H_INCLUDED
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
    CLASS_T = 258,
    INT_T = 259,
    BOOL_T = 260,
    STRING_T = 261,
    IN_T = 262,
    TEL_T = 263,
    INT_ARR_T = 264,
    VOID_T = 265,
    THEN_T = 266,
    ELSE_T = 267,
    FI_T = 268,
    LOOP_T = 269,
    POOL_T = 270,
    NEW_T = 271,
    ISVOID_T = 272,
    SELF_T = 273,
    LE = 274,
    LT = 275,
    GT = 276,
    GE = 277,
    NE = 278,
    EQ = 279,
    NOT_T = 280,
    OUT_STRING = 281,
    OUT_INT = 282,
    IN_INT = 283,
    TRUE_T = 284,
    FALSE_T = 285,
    INT_CONST = 286,
    LET_T = 287,
    IF_T = 288,
    WHILE_T = 289,
    STRING_CONST = 290,
    TYPE = 291,
    ID = 292,
    ASSIGN = 293,
    UC = 294,
    UM = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 56 "uncool.y" /* yacc.c:355  */

    int type;
    char *str;

#line 189 "uncool.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_UNCOOL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 204 "uncool.tab.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   380

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    48,    43,    41,    52,    42,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,    54,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    76,    76,    77,    81,    80,   100,   101,   105,   118,
     104,   128,   127,   136,   141,   140,   151,   150,   160,   166,
     167,   168,   169,   181,   182,   183,   186,   190,   196,   200,
     206,   214,   227,   237,   247,   260,   276,   282,   292,   301,
     309,   324,   341,   340,   351,   358,   357,   375,   381,   391,
     401,   406,   416,   426,   436,   446,   455,   465,   474,   483,
     492,   501,   511,   517,   521,   525,   529,   533,   539,   547,
     557,   559
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS_T", "INT_T", "BOOL_T", "STRING_T",
  "IN_T", "TEL_T", "INT_ARR_T", "VOID_T", "THEN_T", "ELSE_T", "FI_T",
  "LOOP_T", "POOL_T", "NEW_T", "ISVOID_T", "SELF_T", "LE", "LT", "GT",
  "GE", "NE", "EQ", "NOT_T", "OUT_STRING", "OUT_INT", "IN_INT", "TRUE_T",
  "FALSE_T", "INT_CONST", "LET_T", "IF_T", "WHILE_T", "STRING_CONST",
  "TYPE", "ID", "ASSIGN", "UC", "UM", "'+'", "'-'", "'*'", "'{'", "'}'",
  "';'", "'('", "')'", "':'", "'['", "']'", "','", "'.'", "'~'", "$accept",
  "program", "class", "$@1", "feature_list", "feature", "$@2", "$@3",
  "$@4", "$@5", "$@6", "typename", "simple_constant", "formal_list",
  "formal", "expr", "$@7", "$@8", "actual_list", "expr_list", YY_NULLPTR
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
     295,    43,    45,    42,   123,   125,    59,    40,    41,    58,
      91,    93,    44,    46,   126
};
# endif

#define YYPACT_NINF -88

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-88)))

#define YYTABLE_NINF -22

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-22)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,    17,    89,   -88,   -88,   -88,   -88,    35,   -88,    10,
     -35,   -88,    37,    33,     1,   -88,    46,    48,    56,   -88,
      72,   -88,    84,    16,    74,   -39,   -88,    73,    87,    90,
     -88,   -88,   -88,    58,    78,    48,   -88,    99,    36,    91,
      88,   -88,    16,   -88,   -88,   -88,   -88,   -88,   -88,   148,
      86,   -88,    -1,   148,   -88,   148,    92,   104,   106,   -88,
     -88,   -88,   -88,   148,   148,   -88,   253,   148,   148,   148,
     312,    12,   -88,   110,   105,   109,   312,    60,   148,   148,
     112,    48,   177,   312,   148,    43,   148,   120,    59,   254,
      60,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     -88,   148,   148,   148,    82,   266,   296,   -88,    -3,   148,
     144,   312,   -88,   312,   -29,   191,   114,   -88,   -88,   337,
     337,   337,   337,   337,   337,   124,   124,   -88,   312,    75,
     216,   -88,   -24,   -88,   -88,   148,   229,   148,   -88,   148,
     130,   115,   -88,   -88,   -88,   185,   148,   306,   312,   148,
     -88,   -18,   -88,   241,   -88,   312,   -88,   -88
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     4,     1,     2,     0,     7,     0,
       0,     5,     0,     8,     0,     6,     0,     0,    19,    20,
      16,    22,    13,     0,     0,     0,    27,     0,     0,     0,
      19,    21,    11,     0,     0,     0,    18,     0,     0,     0,
      19,    28,     0,    26,    17,    24,    25,    23,    15,     0,
       0,     9,     0,     0,    67,     0,     0,     0,     0,    63,
      64,    65,    45,     0,     0,    66,    39,     0,     0,     0,
      71,     0,    29,     0,     0,     0,    50,    55,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,    30,    34,    69,     0,     0,     0,    44,    62,    60,
      59,    57,    58,    56,    61,    51,    52,    53,    70,     0,
       0,    47,     0,    37,    38,     0,     0,     0,    35,     0,
      40,     0,    10,    49,    48,     0,     0,     0,    68,     0,
      32,     0,    46,     0,    43,    31,    33,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   168,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -15,   -88,   103,   136,   -53,   -88,   -88,   -87,   -66
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     7,     9,    12,    17,    73,    39,    29,
      28,    22,    48,    25,    26,    70,   110,    81,   114,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,    88,    77,    74,   135,    18,    19,    20,    32,    34,
      82,    83,    13,    35,    14,    89,    90,   132,    41,   138,
      30,    19,    31,   139,   144,   105,   106,    51,   139,     1,
     156,   111,   113,   115,   139,    75,   129,    21,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    10,   128,    35,
     130,   113,    21,     4,   151,    11,   136,   100,   101,    52,
      53,    54,    40,    19,    31,    45,    46,    47,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     8,
      66,    16,   145,    15,   147,    24,   148,    67,   113,     5,
      68,   112,     1,   153,    21,    23,   155,    69,    52,    53,
      54,    97,    98,    99,   117,   101,    27,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   -21,    66,
     142,   101,   -14,    33,    36,    37,    67,    42,    38,    68,
     131,    52,    53,    54,    44,    49,    69,    72,    50,    78,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    79,    66,    80,   102,   103,   104,   116,   137,    67,
     107,   141,    68,   150,    52,    53,    54,    99,   149,    69,
       6,    43,     0,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   108,    66,     0,     0,   109,     0,
       0,     0,    67,   152,     0,    68,    91,    92,    93,    94,
      95,    96,    69,     0,    91,    92,    93,    94,    95,    96,
      91,    92,    93,    94,    95,    96,     0,     0,    97,    98,
      99,     0,     0,     0,     0,     0,    97,    98,    99,     0,
       0,     0,    97,    98,    99,    91,    92,    93,    94,    95,
      96,   146,   140,     0,     0,     0,     0,     0,    91,    92,
      93,    94,    95,    96,   157,     0,     0,    97,    98,    99,
      91,    92,    93,    94,    95,    96,     0,   143,     0,     0,
      97,    98,    99,    91,    92,    93,    94,    95,    96,     0,
       0,     0,    97,    98,    99,    91,    92,    93,    94,    95,
      96,    84,     0,     0,     0,    97,    98,    99,     0,     0,
      85,     0,   118,    86,     0,     0,    87,    97,    98,    99,
       0,     0,     0,     0,   133,    91,    92,    93,    94,    95,
      96,   154,     0,     0,     0,    91,    92,    93,    94,    95,
      96,    91,    92,    93,    94,    95,    96,    97,    98,    99,
       0,     0,     0,     0,   134,     0,     0,    97,    98,    99,
       0,     0,     0,    97,    98,    99,   -22,   -22,   -22,   -22,
     -22,   -22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    98,
      99
};

static const yytype_int16 yycheck[] =
{
      53,    67,    55,     4,     7,     4,     5,     6,    23,    48,
      63,    64,    47,    52,    49,    68,    69,   104,    33,    48,
       4,     5,     6,    52,    48,    78,    79,    42,    52,     3,
      48,    84,    85,    86,    52,    36,   102,    36,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    37,   101,    52,
     103,   104,    36,    36,   141,    45,   109,    45,    46,    16,
      17,    18,     4,     5,     6,    29,    30,    31,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    44,
      37,    48,   135,    46,   137,    37,   139,    44,   141,     0,
      47,    48,     3,   146,    36,    49,   149,    54,    16,    17,
      18,    41,    42,    43,    45,    46,    50,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    46,    37,
      45,    46,    38,    49,    51,    38,    44,    49,    38,    47,
      48,    16,    17,    18,    35,    44,    54,    51,    50,    47,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    47,    37,    47,    44,    50,    47,    37,    14,    44,
      48,    47,    47,    48,    16,    17,    18,    43,    38,    54,
       2,    35,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    81,    37,    -1,    -1,    11,    -1,
      -1,    -1,    44,     8,    -1,    47,    19,    20,    21,    22,
      23,    24,    54,    -1,    19,    20,    21,    22,    23,    24,
      19,    20,    21,    22,    23,    24,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,
      -1,    -1,    41,    42,    43,    19,    20,    21,    22,    23,
      24,    12,    51,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    13,    -1,    -1,    41,    42,    43,
      19,    20,    21,    22,    23,    24,    -1,    51,    -1,    -1,
      41,    42,    43,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    41,    42,    43,    19,    20,    21,    22,    23,
      24,    38,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      47,    -1,    48,    50,    -1,    -1,    53,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    19,    20,    21,    22,    23,
      24,    15,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    19,    20,    21,    22,    23,    24,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    41,    42,    43,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    56,    57,    36,     0,    57,    58,    44,    59,
      37,    45,    60,    47,    49,    46,    48,    61,     4,     5,
       6,    36,    66,    49,    37,    68,    69,    50,    65,    64,
       4,     6,    66,    49,    48,    52,    51,    38,    38,    63,
       4,    66,    49,    69,    35,    29,    30,    31,    67,    44,
      50,    66,    16,    17,    18,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    37,    44,    47,    54,
      70,    74,    51,    62,     4,    36,    70,    70,    47,    47,
      47,    72,    70,    70,    38,    47,    50,    53,    74,    70,
      70,    19,    20,    21,    22,    23,    24,    41,    42,    43,
      45,    46,    44,    50,    47,    70,    70,    48,    68,    11,
      71,    70,    48,    70,    73,    70,    37,    45,    48,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    74,
      70,    48,    73,    48,    48,     7,    70,    14,    48,    52,
      51,    47,    45,    51,    48,    70,    12,    70,    70,    38,
      48,    73,     8,    70,    15,    70,    48,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    58,    57,    59,    59,    61,    62,
      60,    63,    60,    60,    64,    60,    65,    60,    60,    66,
      66,    66,    66,    67,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    70,    70,    72,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    73,    73,
      74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     6,     3,     0,     0,     0,
      11,     0,     9,     3,     0,     6,     0,     6,     5,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     5,
       3,     6,     5,     6,     3,     4,     3,     4,     4,     1,
       4,     7,     0,     6,     3,     0,     6,     4,     5,     5,
       2,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     3,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

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
| yyreduce -- Do a reduction.  |
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
        case 4:
#line 81 "uncool.y" /* yacc.c:1646  */
    {/* Class declaration
                      * New type being created.
                      */
                      cflag = begin_class_declaration(stack, (yyvsp[0].str));
                      if (cflag == CLASS_DECL_INSIDE_CLASS_DECL) {
                          error(cflag, (yyvsp[0].str), (yyvsp[0].str));
                      } else if (cflag) {
                          error(cflag, (yyvsp[0].str));
                      } else {
                          log_info("created new class: %s\n", (yyvsp[0].str));
                      }
                    }
#line 1441 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 94 "uncool.y" /* yacc.c:1646  */
    { if (!cflag) {
                          end_class_declaration(stack);
                      }
                    }
#line 1450 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "uncool.y" /* yacc.c:1646  */
    {/* Method declaration with 1+ params. */
                        if (in_method_scope(stack)) {
                            error(METHOD_DECL_INSIDE_METHOD_DECL, (yyvsp[-1].str));
                        } else if (!in_class_scope(stack)) {
                            error(METHOD_DECL_OUTSIDE_CLASS_SCOPE, (yyvsp[-1].str));
                        } else if (method_exists(stack->local, (yyvsp[-1].str))) {
                            error(DUPLICATE_METHOD, (yyvsp[-1].str));
                        } else {  // Houston, we have lift off
                            enter_scope(stack, METHOD_SCOPE, (yyvsp[-1].str));
                        }

                    }
#line 1467 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 118 "uncool.y" /* yacc.c:1646  */
    { log_info("begin method decl '%s' of type %s & argcnt %d\n",
                               (yyvsp[-6].str), type_name_from_token((yyvsp[0].type)), (yyvsp[-3].type));
                      scope_add_method(stack->scopes[stack->size-2], (yyvsp[-6].str), (yyvsp[0].type), (yyvsp[-3].type));
                    }
#line 1476 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 123 "uncool.y" /* yacc.c:1646  */
    {/* type check declaration and return type of expr_list */
                      wend_method(dflag);
                      check_method_types((yyvsp[-10].str), (yyvsp[-4].type), (yyvsp[-1].type));
                    }
#line 1485 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 128 "uncool.y" /* yacc.c:1646  */
    {/* Method declaration with 0 params. */
                      dflag = wdeclare_method((yyvsp[-4].str), (yyvsp[0].type), 0);
                    }
#line 1493 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 132 "uncool.y" /* yacc.c:1646  */
    {/* type check declaration and return type of expr_list */
                      wend_method(dflag);
                      check_method_types((yyvsp[-8].str), (yyvsp[-4].type), (yyvsp[-1].type));
                    }
#line 1502 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 137 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration, no assignment. */
                      flag = wdeclare_attribute((yyvsp[-2].str), (yyvsp[0].type));
                    }
#line 1510 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 141 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute((yyvsp[-2].str), (yyvsp[0].type));
                    }
#line 1518 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 145 "uncool.y" /* yacc.c:1646  */
    {/* Assign to the attribute just created. */
                      if (!flag) {
                          type_check_attr((yyvsp[-5].str), (yyvsp[-3].type), (yyvsp[0].type));
                      }
                    }
#line 1528 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 151 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration, assignment to string. */
                      flag = wdeclare_attribute((yyvsp[-2].str), STRING_T);
                    }
#line 1536 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 155 "uncool.y" /* yacc.c:1646  */
    {/* Assign string constant to attribute just created. */
                      if (!flag) {
                          // nothing to do here; string_const always string_t
                      }
                    }
#line 1546 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 161 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute((yyvsp[-4].str), INT_ARR_T);
                    }
#line 1554 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 166 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = INT_T; }
#line 1560 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 167 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = BOOL_T; }
#line 1566 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 168 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = STRING_T; }
#line 1572 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "uncool.y" /* yacc.c:1646  */
    {/* At this point, the class will have been defined. */
                      Scope *class = lookup_class(stack, (yyvsp[0].str));
                      if (class == NULL) {
                          error(NO_SUCH_CLASS, (yyvsp[0].str));
                          (yyval.type) = INVALID_TYPE;
                      } else {
                          (yyval.type) = class->typetoken;
                      }
                    }
#line 1586 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 181 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = INT_T; }
#line 1592 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 182 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = BOOL_T; }
#line 1598 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 183 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = BOOL_T; }
#line 1604 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 187 "uncool.y" /* yacc.c:1646  */
    {/* Return parameter count. */
                            (yyval.type) = (yyvsp[-2].type) + 1;
                        }
#line 1612 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 191 "uncool.y" /* yacc.c:1646  */
    {/* Return parameter count. */
                            (yyval.type) = 1;
                        }
#line 1620 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration, assignment to int or bool. */
                      flag = wdeclare_attribute((yyvsp[-2].str), (yyvsp[0].type));
                    }
#line 1628 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 201 "uncool.y" /* yacc.c:1646  */
    {/* Attribute declaration for int array. */
                      flag = wdeclare_attribute((yyvsp[-4].str), INT_ARR_T);
                    }
#line 1636 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 207 "uncool.y" /* yacc.c:1646  */
    {/* Assignment to attribute.
                      * return val of expr must be same type as ID
                      */
                      flag = get_attribute_type((yyvsp[-2].str));
                      type_check_attr((yyvsp[-2].str), flag, (yyvsp[0].type));
                      (yyval.type) = (yyvsp[0].type);
                    }
#line 1648 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 215 "uncool.y" /* yacc.c:1646  */
    {/* Assignment to int array
                      * First expr must return int type.
                      * Second expr must return int type.
                      */
                      flag = get_attribute_type((yyvsp[-5].str));
                      if (flag != INT_ARR_T) {
                          error(INDEXING_NON_ARRAY, (yyvsp[-5].str));
                      }
                      check_array_index((yyvsp[-3].type));
                      type_check_int_arr_assign((yyvsp[-5].str), (yyvsp[0].type));
                      (yyval.type) = (yyvsp[0].type);
                    }
#line 1665 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 228 "uncool.y" /* yacc.c:1646  */
    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class to get type and arg count.
                      * If arg count not equal to 0, raise error.
                      */
                      typetoken = get_attribute_type((yyvsp[-4].str));
                      cname = type_name_from_token(typetoken);
                      (yyval.type) = check_method_ref(cname, (yyvsp[-2].str), 0);
                    }
#line 1679 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 238 "uncool.y" /* yacc.c:1646  */
    {/* Method call using obj name prefix.
                      * Look up object with first ID to get class scope.
                      * Look up method in class scope to get type & arg count.
                      * Figure out size of actual_list & compare w arg count.
                      */
                      typetoken = get_attribute_type((yyvsp[-5].str));
                      cname = type_name_from_token(typetoken);
                      (yyval.type) = check_method_ref(cname, (yyvsp[-3].str), (yyvsp[-1].type));
                    }
#line 1693 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 248 "uncool.y" /* yacc.c:1646  */
    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * If arg count not 0, raise.
                      */
                      cname = containing_class_name(stack);
                      if (cname == NULL) {
                          error(SELF_REFERENCE_OUTSIDE_CLASS);
                          (yyval.type) = INVALID_TYPE;
                      } else {
                          (yyval.type) = check_method_ref(cname, (yyvsp[-2].str), 0);
                      }
                    }
#line 1710 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 261 "uncool.y" /* yacc.c:1646  */
    {/* Method call w/o obj name prefix.
                      * Look up ID in current scope. If not present, raise.
                      * Figure out size of actual_list & compare w arg count.
                      */
                      cname = containing_class_name(stack);
                      log_debug("containing class name for 'self' ref: %s\n",
                                cname);
                      if (cname == NULL) {
                          error(SELF_REFERENCE_OUTSIDE_CLASS);
                          (yyval.type) = INVALID_TYPE;
                      } else {
                          log_info("%s called with %d argument(s)\n", (yyvsp[-3].str), (yyvsp[-1].type));
                          (yyval.type) = check_method_ref(cname, (yyvsp[-3].str), (yyvsp[-1].type));
                      }
                    }
#line 1730 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 277 "uncool.y" /* yacc.c:1646  */
    {/* Request int from user.
                      * Returns an int.
                      */
                      (yyval.type) = INT_T;
                    }
#line 1740 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 283 "uncool.y" /* yacc.c:1646  */
    {/* Print out a string.
                      * expr must return a string constant
                      * OUT_STRING returns an int.
                      */
                      (yyval.type) = INT_T;
                      if ((yyvsp[-1].type) != STRING_T) {
                          error(OUT_STRING_EXPECTS_STRING, (yyvsp[-1].type));
                      }
                    }
#line 1754 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 293 "uncool.y" /* yacc.c:1646  */
    {/* Output an int.
                      * expr must be an int. Returns an int.
                      */
                      (yyval.type) = INT_T;
                      if ((yyvsp[-1].type) != INT_T) {
                          error(OUT_INT_EXPECTS_INT, (yyvsp[-1].type));
                      }
                    }
#line 1767 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 302 "uncool.y" /* yacc.c:1646  */
    {/* Simple ID reference.
                      * Look up in scope stack.
                      * If not present, raise.
                      */
                      flag = get_attribute_type((yyvsp[0].str));
                      (yyval.type) = flag;  // whether valid or invalid, this works
                    }
#line 1779 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 310 "uncool.y" /* yacc.c:1646  */
    {/* Simple int array reference.
                      * First look up ID in scope stack.
                      * Then make sure expr returns an int.
                      * Return type is always int.
                      */
                      flag = get_attribute_type((yyvsp[-3].str));
                      if (flag != INT_ARR_T) {
                          error(INDEXING_NON_ARRAY, (yyvsp[-3].str));
                      }
                      if (flag >= 0) {  // valid reference
                          check_array_index((yyvsp[-1].type));
                      }
                      (yyval.type) = INT_T;
                    }
#line 1798 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 325 "uncool.y" /* yacc.c:1646  */
    {/* Conditional.
                      * First expr must be bool.
                      * Second and Third expr types must match, and this
                      * is the return type.
                      */
                      if ((yyvsp[-5].type) != BOOL_T) {
                          error(PREDICATE_NOT_BOOL, "if");
                          (yyval.type) = INVALID_TYPE;
                      } else if ((yyvsp[-3].type) != (yyvsp[-1].type)) {
                          error(CONDITIONAL_BRANCH_TYPES_DIFFER, (yyvsp[-3].type), (yyvsp[-1].type));
                          (yyval.type) = (yyvsp[-3].type);
                      } else {
                          (yyval.type) = (yyvsp[-3].type);
                      }
                    }
#line 1818 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 341 "uncool.y" /* yacc.c:1646  */
    {/* Loop.
                      * First expr must be bool.
                      * Return type is always Int.
                      */
                      if ((yyvsp[0].type) != BOOL_T) {
                          error(PREDICATE_NOT_BOOL, "while");
                      }
                    }
#line 1831 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 350 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = INT_T; }
#line 1837 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 352 "uncool.y" /* yacc.c:1646  */
    {/* Series of expr statements.
                      * Return type is return type of last expr.
                      */
                      (yyval.type) = (yyvsp[-1].type);
                    }
#line 1847 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 358 "uncool.y" /* yacc.c:1646  */
    {/* Let statement.
                      * Create new scope to hold formal_list attributes.
                      */
                      enter_let_scope(stack);
                      log_info("entering let scope");
                    }
#line 1858 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 365 "uncool.y" /* yacc.c:1646  */
    {/* These can ONLY be attributes - no methods or classes.
                      * The return type is the return type of expr.
                      */
                      (yyval.type) = (yyvsp[-1].type);
                      if (verbose == LOGGING_LEVEL_DEBUG) {
                          print_let_scope(stack->global, stack->local);
                      }
                      exit_scope(stack);
                      log_info("exiting let scope");
                    }
#line 1873 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 376 "uncool.y" /* yacc.c:1646  */
    {/* Create a new object of class TYPE.
                      * Simply look up class in global scope to ensure exists.
                      */
                      (yyval.type) = make_new_class((yyvsp[-2].str), 0);
                    }
#line 1883 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 382 "uncool.y" /* yacc.c:1646  */
    {/* Create new object of class TYPE using init method.
                      * First look up class in global scope to ensure exists.
                      * Next look up init method to make sure it exists.
                      * If found, get arg count.
                      * Compare arg count to actual_list size.
                      * Raise if different.
                      */
                      (yyval.type) =make_new_class((yyvsp[-3].str), (yyvsp[-1].type));
                    }
#line 1897 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 392 "uncool.y" /* yacc.c:1646  */
    {/* Create a new int array.
                      * Ensure expr returns an int.
                      */
                      check_array_index((yyvsp[-1].type));
                      if ((yyvsp[-1].type) != INT_T) {
                          error(ARRAY_SIZE_NOT_INT, (yyvsp[-1].type));
                      }
                      (yyval.type) = INT_ARR_T;
                    }
#line 1911 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 402 "uncool.y" /* yacc.c:1646  */
    {/* Returns bool and can take any expr.
                      */
                      (yyval.type) = BOOL_T;
                    }
#line 1920 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 407 "uncool.y" /* yacc.c:1646  */
    {/* ADD.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "+", (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = INT_T;
                    }
#line 1934 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 417 "uncool.y" /* yacc.c:1646  */
    {/* MINUS.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "-", (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = INT_T;
                    }
#line 1948 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 427 "uncool.y" /* yacc.c:1646  */
    {/* TIMES.
                      * Both expr statements must return int.
                      * Overall return type is int.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(EXPECTED_INT_OPERANDS, "*", (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = INT_T;
                    }
#line 1962 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 437 "uncool.y" /* yacc.c:1646  */
    {/* UNIMINUS.
                      * expr must be int.
                      * Returns an int.
                      */
                      if ((yyvsp[0].type) != INT_T) {
                          error(UNIMINUS_EXPR_NOT_INT, (yyvsp[0].type));
                      }
                      (yyval.type) = INT_T;
                    }
#line 1976 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 447 "uncool.y" /* yacc.c:1646  */
    {/* NOT.
                      * expr must be bool. Returns a bool.
                      */
                      if ((yyvsp[0].type) != BOOL_T) {
                          error(NOT_EXPR_NOT_BOOL, (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 1989 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 456 "uncool.y" /* yacc.c:1646  */
    {/* NOT EQUAL.
                      * 1st expr can have any type. 2nd must match the first.
                      * Returns a bool.
                      */
                      if ((yyvsp[-2].type) != (yyvsp[0].type)) {
                          error(COMPARISON_OP_TYPE_MISMATCH, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2003 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 466 "uncool.y" /* yacc.c:1646  */
    {/* GREATER THAN.
                      * Both expr must return int. Returns a bool.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2016 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 475 "uncool.y" /* yacc.c:1646  */
    {/* GREATER THAN OR EQUAL TO.
                      * Both expr must return int. Returns a bool.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2029 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 484 "uncool.y" /* yacc.c:1646  */
    {/* LESS THAN.
                      * Both expr must return int. Returns a bool.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2042 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 493 "uncool.y" /* yacc.c:1646  */
    {/* LESS THAN OR EQUAL TO.
                      * Both expr must return int. Returns a bool.
                      */
                      if ((yyvsp[-2].type) != INT_T || (yyvsp[0].type) != INT_T) {
                          error(COMPARISON_OP_TYPES_NOT_INT, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2055 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 502 "uncool.y" /* yacc.c:1646  */
    {/* EQUAL TO.
                      * 1st expr can have any type. 2nd must match the first.
                      * Returns a bool.
                      */
                      if ((yyvsp[-2].type) != (yyvsp[0].type)) {
                          error(COMPARISON_OP_TYPE_MISMATCH, (yyvsp[-2].type), (yyvsp[0].type));
                      }
                      (yyval.type) = BOOL_T;
                    }
#line 2069 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 512 "uncool.y" /* yacc.c:1646  */
    {/* Used to indicate precedence.
                      * Return type same as expr.
                      */
                      (yyval.type) = (yyvsp[-1].type);
                    }
#line 2079 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 518 "uncool.y" /* yacc.c:1646  */
    {/* Return type bool. */
                      (yyval.type) = BOOL_T;
                    }
#line 2087 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 522 "uncool.y" /* yacc.c:1646  */
    {/* Return type bool. */
                      (yyval.type) = BOOL_T;
                    }
#line 2095 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 526 "uncool.y" /* yacc.c:1646  */
    {/* Return type int. */
                      (yyval.type) = INT_T;
                    }
#line 2103 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 530 "uncool.y" /* yacc.c:1646  */
    {/* Return type string. */
                      (yyval.type) = STRING_T;
                    }
#line 2111 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 534 "uncool.y" /* yacc.c:1646  */
    {/* Reference to current class. */
                      (yyval.type) = (containing_class(stack))->typetoken;
                    }
#line 2119 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 540 "uncool.y" /* yacc.c:1646  */
    {/* Need to count the number of expr stmts when
                      * this shows up in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                      (yyval.type) = (yyvsp[-2].type) + 1;
                    }
#line 2131 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 548 "uncool.y" /* yacc.c:1646  */
    {/* This would indicate single parameter for param count
                      * in method calls.
                      * Does not show up in declarations.
                      * Occurences in let statements need no special consideration.
                      */
                      (yyval.type) = 1;
                    }
#line 2143 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 558 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = (yyvsp[0].type); }
#line 2149 "uncool.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 560 "uncool.y" /* yacc.c:1646  */
    { (yyval.type) = (yyvsp[0].type); }
#line 2155 "uncool.tab.c" /* yacc.c:1646  */
    break;


#line 2159 "uncool.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 563 "uncool.y" /* yacc.c:1906  */


void
safe_type_create(int token, char *name)
{
    int flag = create_type(stack, token, name);
    if (flag) {
        log_debug("attempt to map token %d to name %s would clobber\n",
                  token, name);
        exit(flag);
    }
    log_info("created new type: %s [token: %d]\n", name, token);
}

main (int argc, char **argv) {
    int flag;
    Scope *class;
    Symbol *method;

    if (argc == 2) {
        if (strcmp(argv[1], "-v") == 0) {
            verbose = LOGGING_LEVEL_INFO;
            printf("continuing with verbose output\n");
        } else if (strcmp(argv[1], "-vv") == 0) {
            verbose = LOGGING_LEVEL_DEBUG;
            printf("continuing with debug level verbose output\n");
        } else {
            verbose = 0;
        }
    }

    num_errors = 0;
    stack = scope_stack_create();

    // create built-in types
    log_info("declaring built-in types\n");
    safe_type_create(INT_T, "Int");
    safe_type_create(STRING_T, "String");
    safe_type_create(BOOL_T, "Bool");
    safe_type_create(INT_ARR_T, "Int[]");
    safe_type_create(VOID_T, "Void");
    log_info("finished type declarations\n");

    yyparse();
    printf("ERRORS FOUND: %d\n", num_errors);

    class = lookup_class(stack, "Main");
    if (class == NULL) {
        error(NO_MAIN_CLASS);
    } else {
        method = lookup_method(stack, "Main", "main");
        if (method == NULL) {
            error(NO_MAIN_METHOD);
        }
    }

    // log end-file scope stack and type info
    if (verbose == LOGGING_LEVEL_DEBUG) {
        print_scope_stack(stack);
        printf("TYPES:\n");
        print_type_map(stack);
    }
    scope_stack_destroy(stack);
}

yyerror(char *s) {
   printf("Line %d: %s",linect, s);
}

int
wdeclare_attribute(char *name, int type)
{   /* Wrapper to simplify args and error handling.
     * Relies on global stack.
     */
    flag = declare_attribute(stack, name, type);
    if (flag) {
        error(flag, name);
    } else {
        log_info("declared attribute '%s' with type: %s\n",
                 name, type_name_from_token(type));
    }
    return flag;
}

int wdeclare_method(char *name, int type, int argcount)
{   /* Wrapper to simplify args and error handling.
     * Relies on global stack.
     */
    flag = begin_method_declaration(stack, name, type, argcount);
    if (flag) {
        error(flag, name);
    } else {
        log_info("begin method decl '%s' with type %s and argcount %d\n", name,
                 type_name_from_token(type), argcount);
    }
    return flag;
}

void
wend_method(int dflag)
{
    log_debug("flag value from method declaration: %d\n", dflag);
    if (!dflag) {
        log_info("end method decl: %s\n", stack->local->name);
        end_method_declaration(stack);
    }
}

int
check_array_index(int type)
{   /* Return 0 if all good, otherwise an error code.
     * The error message is printed by return time.
     */
    if (type != INT_T) {
        error(INDEX_NOT_INT, type);
        return INDEX_NOT_INT;
    }
    return 0;
}

int
check_method_types(char *name, int declared, int returned)
{
    if (declared != returned) {
        error(METHOD_BODY_HAS_CONFLICTING_TYPE, name,
              declared, returned);
        log_debug("declared type token: %d\n", declared);
        log_debug("returned type token: %d\n", returned);
    }
}

int
type_check_attr(char *name, int correct_type, int assign_type)
{   /* Return 0 if mismatch, else 1.
     * Error handling taken care of by return time.
     */

    log_debug("type checking attribute %s\n", name);
    log_debug("compare correct (%s) with assignment type (%s)\n",
              type_name_from_token(correct_type),
              type_name_from_token(assign_type));

    if (correct_type != assign_type) {
        error(CONFLICTING_ATTRIBUTE_TYPE, name, correct_type, assign_type);
        return 1;
    }
    return 0;
}

int
type_check_int_arr_assign(char *name, int assign_type)
{
    log_debug("type checking attribute %s\n", name);
    log_debug("compare correct (%s) with assignment type (%s)\n",
              "Int []", "Int");

    if (assign_type != INT_T) {
        error(CONFLICTING_ATTRIBUTE_TYPE, name, INT_T, assign_type);
    }
}

int
get_attribute_type(char *name)
{
    Symbol *attr = lookup_attribute(stack, name);
    if (attr == NULL) {
        error(NO_SUCH_ATTRIBUTE, name);
        return INVALID_TYPE;
    } else {
        log_info("attribute lookup successful for: %s\n", name);
        return attr->type;
    }
}

char *
type_name_from_token(int token)
{
    if (token < 0) {  // invalid token
        return "NULL";
    } else {
        return type_name(stack, token);
    }
}

int
method_type(char *class_name, char *method_name)
{
    Symbol *method = lookup_method(stack, class_name, method_name);
    if (method == NULL) {
        log_debug("class lookup failed for assigned class type");
        exit(NO_SUCH_CLASS);
    } else {
        return method->type;
    }
}

int
check_method_ref(char *class_name, char *method_name, int argcount)
{   /* Make sure the method exists for the class.
     * Return the type if it does.
     * Otherwise indicate appropriate errors.
     */
    log_debug("checking method argument count\n");
    log_debug("class name: %s\n", class_name);
    log_debug("method name: %s\n", method_name);
    Symbol *method = lookup_method(stack, class_name, method_name);
    if (method == NULL) {
        error(NO_SUCH_METHOD, class_name, method_name);
        return INVALID_TYPE;
    }
    assert(strcmp(method->name, method_name) == 0);
    log_debug("successful lookup for method %s of class %s\n", method->name,
              class_name);
    log_debug("method expects %d arguments\n", method->argcount);

    if (method->argcount != argcount) {
        error(METHOD_INVALID_ARGCOUNT, class_name, method_name,
              method->argcount, argcount);
    }
    return method->type;
}

char *
get_type_name(va_list argp)
{
    int token = va_arg(argp, int);
    if (token < 0) {  // invalid token
        return "NULL";
    } else {
        return type_name(stack, token);
    }
}

char *
containing_class_name()
{
    Scope *class = containing_class(stack);
    if (class == NULL) {
        return NULL;
    }
    return class->name;
}

int
make_new_class(char *name, int argcount)
{
    Scope *class;
    Symbol *method;

    log_info("instantiating new instance of class %s\n", name);
    class = lookup_class(stack, name);
    if (class == NULL) {
        log_info("no class found with name %s; instantiation failed\n", name);
        return INVALID_TYPE;
    } else {
        // look up init method
        log_debug("looking up init method for class %s\n", name);
        method = lookup_method(stack, name, "init");
        if (method == NULL && (argcount > 0)) {
            error(OBJECT_INSTANTIATION_INVALID_ARGCOUNT,
                  name, 0, argcount);
        } else {  // have an init
            log_debug("init method found, argcount should be: %d\n",
                      method->argcount);
            if (method->argcount != argcount) {
                error(OBJECT_INSTANTIATION_INVALID_ARGCOUNT,
                      name, method->argcount, argcount);
            }
        }
        return class->typetoken;
    }
}

void
error(int errtoken, ...)
{
    char *name, *name2, *type1, *type2;
    int t1, t2, t3;
    va_list argp;
    va_start(argp, errtoken);

    num_errors++;
    printf("[LINE %d][ERROR]: ", linect);

    if (errtoken == NO_MAIN_CLASS) {
        printf("no Main class found\n");
        return;
    } else if (errtoken == NO_MAIN_METHOD) {
        printf("no main method found in Main class\n");
        return;
    }

    if (errtoken == DUPLICATE_CLASS) {
        name = va_arg(argp, char *);
        printf("duplicate class declaration \n\t[name: %s]", name);
    } else if (errtoken == DUPLICATE_ATTRIBUTE) {
        name = va_arg(argp, char *);
        printf("duplicate attribute declaration \n\t[name: %s]", name);
    } else if (errtoken == DUPLICATE_METHOD) {
        name = va_arg(argp, char *);
        printf("duplicate method declaration\n\t[name: %s']", name);
    } else if (errtoken == METHOD_DECL_OUTSIDE_CLASS_SCOPE) {
        name = va_arg(argp, char *);
        printf("method declaration outside class scope\n\t[name: %s]", name);
    } else if (errtoken == ATTRIBUTE_DECL_IN_GLOBAL_SCOPE) {
        name = va_arg(argp, char *);
        printf("attribute declaration in global scope\n\t[name: %s]", name);
    } else if (errtoken == CLASS_DECL_INSIDE_CLASS_DECL) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("class declaration inside declaration of class %s\n\t[name: %s]",
               name, name2);
    } else if (errtoken == NO_SUCH_CLASS) {
        name = va_arg(argp, char *);
        printf("invalid type (no such class found)\n\t[name: %s]", name);
    } else if (errtoken == NO_SUCH_ATTRIBUTE) {
        name = va_arg(argp, char *);
        printf("no such attribute declared\n\t[name: %s]", name);
    } else if (errtoken == NO_SUCH_METHOD) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("no such method for class\n\t[class: %s][method: %s]",
               name, name2);
    } else if (errtoken == METHOD_BODY_HAS_CONFLICTING_TYPE) {
        name = va_arg(argp, char *);
        printf("method body has conflicting type\n\t[method: %s]", name);
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("[declared: %s][body: %s]", type1, type2);
    } else if (errtoken == PREDICATE_NOT_BOOL) {
        printf("predicate is not boolean");
    } else if (errtoken == CONDITIONAL_BRANCH_TYPES_DIFFER) {
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("conditional branch types differ\n\t[1st: %s][2nd: %s]",
               type1, type2);
    } else if (errtoken == INDEX_NOT_INT) {
        printf("attempting to index int array with non-int ");
        type1 = get_type_name(argp);
        printf("\n\t[index type: %s]", type1);
    } else if (errtoken == ARRAY_SIZE_NOT_INT) {
        type1 = get_type_name(argp);
        printf("initial array size is not integer\n\t[type: %s]", type1);
    } else if (errtoken == CONFLICTING_ATTRIBUTE_TYPE) {
        printf("assignment type does not match attribute type");
        name = va_arg(argp, char *);
        type1 = get_type_name(argp);
        type2 = get_type_name(argp);
        printf("\n\t[name: %s][correct type: %s][assignment type: %s]",
               name, type1, type2);
    } else if (errtoken == METHOD_DECL_INSIDE_METHOD_DECL) {
        printf("method declaration inside another method declaration");
        name = va_arg(argp, char *);
        printf("\n\t[name: %s]", name);
    } else if (errtoken == METHOD_INVALID_ARGCOUNT) {
        name = va_arg(argp, char *);
        name2 = va_arg(argp, char *);
        printf("invalid argument count for method\n\t[class: %s][method: %s]",
               name, name2);
        t1 = va_arg(argp, int);
        t2 = va_arg(argp, int);
        printf("[expected: %d][got: %d]", t1, t2);
    } else if (errtoken == INDEXING_NON_ARRAY) {
        name = va_arg(argp, char *);
        printf("indexing non array attribute\n\t[name: %s]", name);
    } else if (errtoken == SELF_REFERENCE_OUTSIDE_CLASS) {
        printf("reference to 'self' outside of class scope");
    } else if (errtoken == OUT_INT_EXPECTS_INT) {
        type1 = get_type_name(argp);
        printf("out_int expects integer argument");
        printf("\n\t[got: %s]", type1);
    } else if (errtoken == OBJECT_INSTANTIATION_INVALID_ARGCOUNT) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        t2 = va_arg(argp, int);
        printf("invalid argcount for object instantiation");
        printf("\n\t[class: %s][expected: %d][received: %d]",
               name, t1, t2);
    } else if (errtoken == ARITHMETIC_OP_TYPE_MISMATCH) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("conflicting types for arithmetic operation '%s' ", name);
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == COMPARISON_OP_TYPE_MISMATCH) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("conflicting types for comparison operation");
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == UNIMINUS_EXPR_NOT_INT) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("uniminus expression not an integer");
        printf("\n\t[bad type: %s]", type1);
    } else if (errtoken == NOT_EXPR_NOT_BOOL) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("not expr with non-boolean expression");
        printf("\n\t[bad type: %s]", type1);
    } else if (errtoken == COMPARISON_OP_TYPES_NOT_INT) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("one of comparison operand types is not an integer");
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == EXPECTED_INT_OPERANDS) {
        name = va_arg(argp, char *);
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        t2 = va_arg(argp, int);
        type2 = type_name_from_token(t2);
        printf("'%s' operator expects integer operands", name);
        printf("\n\t[type 1: %s][type 2: %s]", type1, type2);
    } else if (errtoken == OUT_STRING_EXPECTS_STRING) {
        t1 = va_arg(argp, int);
        type1 = type_name_from_token(t1);
        printf("function out_string expects string argument");
        printf("\n\t[got: %s]", type1);
    }
    printf("\n");
    va_end(argp);
}
