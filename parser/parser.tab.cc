/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PARCLASS_KEYWORD = 258,
     CLASS_KEYWORD = 259,
     CLASSID = 260,
     ID = 261,
     ID1 = 262,
     INTEGER = 263,
     REAL = 264,
     STRING = 265,
     PUBLIC_KEYWORD = 266,
     PROTECTED_KEYWORD = 267,
     PRIVATE_KEYWORD = 268,
     VIRTUAL_KEYWORD = 269,
     CONST_KEYWORD = 270,
     STRUCT_KEYWORD = 271,
     TYPEDEF_KEYWORD = 272,
     SYNC_INVOKE = 273,
     ASYNC_INVOKE = 274,
     INPUT = 275,
     OUTPUT = 276,
     CONCURRENT = 277,
     SEQUENTIAL = 278,
     MUTEX = 279,
     HIDDEN = 280,
     PROC = 281,
     SIZE = 282,
     THIS_KEYWORD = 283,
     INCLUDE = 284,
     DIRECTIVE = 285,
     OD = 286,
     AUTO_KEYWORD = 287,
     REGISTER_KEYWORD = 288,
     VOLATILE_KEYWORD = 289,
     PACK_KEYWORD = 290,
     AND_OP = 291,
     OR_OP = 292,
     EQUAL_OP = 293,
     NOTEQUAL_OP = 294,
     GREATEREQUAL_OP = 295,
     LESSEQUAL_OP = 296,
     NONSTRICT_OD_OP = 297,
     EOFCODE = 298,
     SCOPE = 299,
     ENUM = 300,
     CLASS = 301,
     STRUCTURE = 302,
     UMINUS = 303
   };
#endif
/* Tokens.  */
#define PARCLASS_KEYWORD 258
#define CLASS_KEYWORD 259
#define CLASSID 260
#define ID 261
#define ID1 262
#define INTEGER 263
#define REAL 264
#define STRING 265
#define PUBLIC_KEYWORD 266
#define PROTECTED_KEYWORD 267
#define PRIVATE_KEYWORD 268
#define VIRTUAL_KEYWORD 269
#define CONST_KEYWORD 270
#define STRUCT_KEYWORD 271
#define TYPEDEF_KEYWORD 272
#define SYNC_INVOKE 273
#define ASYNC_INVOKE 274
#define INPUT 275
#define OUTPUT 276
#define CONCURRENT 277
#define SEQUENTIAL 278
#define MUTEX 279
#define HIDDEN 280
#define PROC 281
#define SIZE 282
#define THIS_KEYWORD 283
#define INCLUDE 284
#define DIRECTIVE 285
#define OD 286
#define AUTO_KEYWORD 287
#define REGISTER_KEYWORD 288
#define VOLATILE_KEYWORD 289
#define PACK_KEYWORD 290
#define AND_OP 291
#define OR_OP 292
#define EQUAL_OP 293
#define NOTEQUAL_OP 294
#define GREATEREQUAL_OP 295
#define LESSEQUAL_OP 296
#define NONSTRICT_OD_OP 297
#define EOFCODE 298
#define SCOPE 299
#define ENUM 300
#define CLASS 301
#define STRUCTURE 302
#define UMINUS 303




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>

#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"


  //Declaration in parser.lex:
  
  int  PutToken(char *str);
  int PutToken(char chr);
  char *GetToken(int yyval);

  void errormsg(const  char *s);
  void setReturnParam(int pointer, int ref, int const_virtual); // Methode to group code that set C++ specific C++ Param attributes
  void setPOPCMethodeModifier(int settings); // mehtode to group code that set/controlle Methode attributes (sync, conc, ...)
  void errorGlobalMehtode(bool isGlobal);
  
extern "C"
{
  int yywrap();
}
  void yyerror(const  char *s);
  int yylex();

  extern int linenumber;
  extern char filename[1024];

CArrayCharPtr incl[1000];
CArrayCharPtr sources;
CArrayCharPtr searchpath; 

 int indexsource=0;  //the index of source file and the include directive


  extern CArrayChar othercodes;
  extern bool insideClass;
  extern int startPos;


 CodeFile *thisCodeFile;
 Class *currentClass;
 DataType *currenttype;
 DataType *returntype;
 
 std::vector<bool> constPointerPositions; // counter variables who contains order of conts possition in pointers

 TypeClassStruct *seqclass;

 Param *currentparam;

 PackObject *currentPack;

 Method *method;
 // Param *param;

 int n,t;
 char tmp[10240];
 char tmpProc[10240];
 char tmpSize[10240];
 int parsingclass=0;

 void UpdateMarshalParam(int flags, Param *t);

 int ParseFile(char *infile, char *outfile, bool client, bool broker);
 char *CheckAndCreateDir(char *fname,char *name);
 bool CheckAndInsert(CArrayCharPtr &source, CArrayCharPtr &searchpath, char *fname);

 int AfterParsing(int status, char *classname, char *stubproc, bool gen_stub);


 paroc_list<TypeClassStruct *>  typestack;
 TypeClassStruct *currentstruct;
 void CleanStack();
 void Push(TypeClassStruct *x);
 TypeClassStruct *Pop();
 TypeClassStruct *Peek();

 int counter=0;
 int errorcode=0;

 AccessType  accessmodifier=PUBLIC;


struct TemplateArgument
{
  DataType *type;
  bool isRef;
};



#define YYMAXDEPTH 100000
#define YYINITDEPTH 2000


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 307 "parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   600

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  447

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,    52,    53,     2,
      64,    67,    50,    48,    68,    49,    73,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    65,
      60,    58,    59,    62,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    54,    66,    56,     2,     2,     2,
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
      45,    46,    47,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     8,    12,    15,    18,    21,
      24,    27,    29,    32,    35,    38,    43,    45,    48,    49,
      52,    54,    56,    58,    63,    66,    69,    71,    72,    76,
      79,    84,    85,    88,    94,   101,   108,   114,   120,   123,
     126,   127,   130,   132,   136,   138,   141,   145,   149,   152,
     158,   162,   165,   166,   169,   171,   175,   177,   180,   184,
     188,   190,   192,   194,   195,   198,   199,   202,   203,   208,
     211,   214,   217,   220,   222,   228,   234,   236,   240,   242,
     246,   253,   254,   256,   260,   262,   266,   268,   273,   276,
     278,   282,   287,   288,   293,   296,   298,   300,   302,   304,
     306,   311,   313,   316,   318,   322,   327,   328,   332,   333,
     335,   336,   338,   340,   342,   345,   346,   349,   355,   357,
     362,   368,   370,   379,   389,   399,   410,   422,   423,   438,
     439,   455,   457,   460,   462,   464,   466,   468,   470,   472,
     474,   476,   479,   482,   483,   485,   487,   490,   493,   495,
     496,   501,   502,   515,   526,   535,   542,   543,   546,   547,
     549,   551,   555,   565,   566,   570,   572,   576,   578,   580,
     584,   588,   589,   591,   593,   594,   596,   597,   600,   603,
     605,   607,   611,   615,   619,   623,   627,   631,   635,   639,
     643,   647,   651,   655,   661,   665,   669,   673,   677,   681,
     684,   688,   692,   697,   700,   703,   706,   709,   711,   713,
     715,   719,   721
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    77,    75,    -1,    -1,    -1,    97,    76,
      75,    -1,    96,    75,    -1,    30,    75,    -1,    79,    75,
      -1,    83,    75,    -1,    78,    75,    -1,    28,    -1,     1,
      65,    -1,     1,    66,    -1,     1,    43,    -1,    80,    64,
      81,    67,    -1,    35,    -1,     6,    82,    -1,    -1,    68,
      81,    -1,    84,    -1,    90,    -1,    91,    -1,    85,    69,
      86,    66,    -1,    85,    78,    -1,    16,     6,    -1,    16,
      -1,    -1,    87,    65,    86,    -1,   120,    88,    -1,   125,
       6,   119,    89,    -1,    -1,    68,    88,    -1,    17,     6,
     125,     6,   119,    -1,    17,    16,     6,   125,     6,   119,
      -1,    17,     4,     6,   125,     6,   119,    -1,    17,    84,
     125,     6,   119,    -1,    92,    93,    69,     1,    66,    -1,
      92,    65,    -1,     4,     6,    -1,    -1,    61,    94,    -1,
      95,    -1,    94,    68,    95,    -1,     6,    -1,   103,     6,
      -1,    14,   103,     6,    -1,   103,    14,     6,    -1,    99,
      65,    -1,    98,    69,   105,    66,    65,    -1,    99,   104,
     100,    -1,     3,     6,    -1,    -1,    61,   101,    -1,   102,
      -1,   101,    68,   102,    -1,     6,    -1,   103,     6,    -1,
      14,   103,     6,    -1,   103,    14,     6,    -1,    13,    -1,
      11,    -1,    12,    -1,    -1,    58,     8,    -1,    -1,   107,
     105,    -1,    -1,   103,   106,    61,   105,    -1,   108,    65,
      -1,   111,    65,    -1,   128,    65,    -1,   116,    65,    -1,
      30,    -1,     5,    64,     8,    67,    65,    -1,    45,     6,
      69,   109,    66,    -1,   110,    -1,   110,    68,   109,    -1,
       6,    -1,     6,    58,     8,    -1,    47,     6,    69,   112,
      66,   114,    -1,    -1,   113,    -1,     6,     6,    65,    -1,
     115,    -1,   115,    68,   114,    -1,     6,    -1,     6,    70,
       6,    71,    -1,   120,   117,    -1,   118,    -1,   118,    68,
     117,    -1,   125,   127,     6,   119,    -1,    -1,    70,   154,
      71,   119,    -1,   121,   122,    -1,   122,    -1,    32,    -1,
      33,    -1,     6,    -1,     7,    -1,     6,    60,   123,    59,
      -1,    84,    -1,    16,     6,    -1,   124,    -1,   124,    68,
     123,    -1,   122,   125,   119,   127,    -1,    -1,    50,   126,
     125,    -1,    -1,    15,    -1,    -1,    53,    -1,   130,    -1,
     132,    -1,   134,   129,    -1,    -1,    58,     8,    -1,   131,
      64,   145,    67,   142,    -1,     6,    -1,    56,   133,    64,
      67,    -1,    14,    56,   133,    64,    67,    -1,     6,    -1,
     120,   125,   127,   141,    64,   145,    67,   126,    -1,   139,
     120,   125,   127,   141,    64,   145,    67,   126,    -1,   120,
     139,   125,   127,   141,    64,   145,    67,   126,    -1,   139,
     120,   139,   125,   127,   141,    64,   145,    67,   126,    -1,
     137,   140,   120,   140,   125,   127,   141,    64,   145,    67,
     126,    -1,    -1,    70,   149,    71,   140,   120,   140,   125,
     127,   141,   135,    64,   145,    67,   126,    -1,    -1,   137,
      70,   149,    71,   140,   120,   140,   125,   127,   141,   136,
      64,   145,    67,   126,    -1,   138,    -1,   137,   138,    -1,
      18,    -1,    19,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    14,    -1,    15,    -1,    15,    14,    -1,    14,
      15,    -1,    -1,    14,    -1,    15,    -1,    15,    14,    -1,
      14,    15,    -1,     6,    -1,    -1,    72,    69,   143,    66,
      -1,    -1,     6,    73,     6,    64,   154,    68,   154,    68,
     154,    67,    65,   143,    -1,     6,    73,     6,    64,   154,
      68,   154,    67,    65,   143,    -1,     6,    73,     6,    64,
     154,    67,    65,   143,    -1,     6,    58,   154,   144,    65,
     143,    -1,    -1,    42,   154,    -1,    -1,   146,    -1,   147,
      -1,   147,    68,   146,    -1,   148,   151,   120,   151,   125,
     127,   152,   119,   153,    -1,    -1,    70,   149,    71,    -1,
     150,    -1,   150,    68,   149,    -1,    20,    -1,    21,    -1,
      27,    58,   154,    -1,    26,    58,     6,    -1,    -1,    15,
      -1,    34,    -1,    -1,     6,    -1,    -1,    58,   154,    -1,
     156,   119,    -1,   155,    -1,    10,    -1,   154,    48,   154,
      -1,   154,    49,   154,    -1,   154,    50,   154,    -1,   154,
      51,   154,    -1,   154,    52,   154,    -1,   154,    53,   154,
      -1,   154,    54,   154,    -1,   154,    55,   154,    -1,   154,
      36,   154,    -1,   154,    37,   154,    -1,   154,    38,   154,
      -1,   154,    58,   154,    -1,   154,    62,   154,    61,   154,
      -1,   154,    39,   154,    -1,   154,    59,   154,    -1,   154,
      60,   154,    -1,   154,    40,   154,    -1,   154,    41,   154,
      -1,    49,   154,    -1,    64,   154,    67,    -1,   156,    64,
      67,    -1,   156,    64,   157,    67,    -1,    50,   154,    -1,
      53,   154,    -1,    57,   154,    -1,    56,   154,    -1,     8,
      -1,     9,    -1,     6,    -1,     6,    44,     6,    -1,   154,
      -1,   157,    68,   154,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   124,   124,   126,   136,   136,   137,   138,   139,   140,
     141,   147,   155,   168,   181,   197,   208,   226,   236,   238,
     246,   250,   251,   258,   264,   270,   297,   306,   307,   309,
     312,   333,   334,   343,   367,   391,   415,   440,   444,   446,
     467,   468,   472,   473,   476,   500,   525,   550,   580,   601,
     609,   619,   644,   645,   648,   649,   652,   666,   681,   698,
     717,   721,   725,   733,   736,   745,   746,   747,   747,   751,
     752,   753,   770,   781,   786,   797,   808,   812,   819,   823,
     832,   843,   845,   851,   858,   862,   868,   873,   884,   886,
     887,   890,   922,   925,   940,   944,   950,   954,   960,   975,
     991,  1010,  1016,  1029,  1036,  1045,  1118,  1122,  1131,  1134,
    1141,  1144,  1156,  1157,  1158,  1161,  1162,  1168,  1184,  1193,
    1202,  1215,  1345,  1352,  1359,  1366,  1373,  1381,  1381,  1388,
    1388,  1398,  1402,  1448,  1452,  1456,  1460,  1464,  1468,  1475,
    1479,  1483,  1487,  1495,  1498,  1502,  1506,  1510,  1516,  1528,
    1531,  1538,  1542,  1559,  1575,  1590,  1683,  1686,  1694,  1695,
    1697,  1698,  1701,  1738,  1741,  1747,  1751,  1757,  1761,  1765,
    1770,  1779,  1782,  1786,  1793,  1796,  1803,  1806,  1819,  1828,
    1832,  1836,  1841,  1846,  1851,  1856,  1861,  1866,  1871,  1876,
    1881,  1886,  1891,  1896,  1901,  1906,  1911,  1916,  1921,  1926,
    1931,  1936,  1941,  1947,  1952,  1957,  1962,  1969,  1973,  1979,
    1983,  1991,  1995
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PARCLASS_KEYWORD", "CLASS_KEYWORD",
  "CLASSID", "ID", "ID1", "INTEGER", "REAL", "STRING", "PUBLIC_KEYWORD",
  "PROTECTED_KEYWORD", "PRIVATE_KEYWORD", "VIRTUAL_KEYWORD",
  "CONST_KEYWORD", "STRUCT_KEYWORD", "TYPEDEF_KEYWORD", "SYNC_INVOKE",
  "ASYNC_INVOKE", "INPUT", "OUTPUT", "CONCURRENT", "SEQUENTIAL", "MUTEX",
  "HIDDEN", "PROC", "SIZE", "THIS_KEYWORD", "INCLUDE", "DIRECTIVE", "OD",
  "AUTO_KEYWORD", "REGISTER_KEYWORD", "VOLATILE_KEYWORD", "PACK_KEYWORD",
  "AND_OP", "OR_OP", "EQUAL_OP", "NOTEQUAL_OP", "GREATEREQUAL_OP",
  "LESSEQUAL_OP", "NONSTRICT_OD_OP", "EOFCODE", "SCOPE", "ENUM", "CLASS",
  "STRUCTURE", "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'|'", "'^'",
  "'~'", "'!'", "'='", "'>'", "'<'", "':'", "'?'", "UMINUS", "'('", "';'",
  "'}'", "')'", "','", "'{'", "'['", "']'", "'@'", "'.'", "$accept",
  "startlist", "@1", "handle_this", "not_care_code", "pack_directive",
  "pack_header", "object_list", "rest_object_list", "type_definition",
  "struct_definition", "struct_head", "struct_body", "struct_element",
  "struct_elname_list", "struct_elname_other", "typedef_definition",
  "seqclass_definition", "seqclass_header", "seqbase_spec", "seqbase_list",
  "seqbase_specifier", "class_prototype", "class_declaration",
  "class_head", "class_key", "base_spec", "base_list", "base_specifier",
  "access_specifier", "pure_class_decl", "member_list", "@2",
  "member_declaration", "enum_declaration", "enum_members", "enum_member",
  "structure_declaration", "structure_elements", "structure_element",
  "structure_objects", "structure_object", "attribute_definition",
  "attribute_name_list", "attribute_name", "array_declarator",
  "decl_specifier", "storage_class_specifier", "type_specifier",
  "template_arguments", "template_arg", "pointer_specifier",
  "const_specifier", "ref_specifier", "function_definition",
  "pure_virtual_decl", "constructor_definition", "constructor_name",
  "destructor_definition", "destructor_name", "method_definition", "@3",
  "@4", "fct_specifier", "fct_spec", "const_virutal_specifier",
  "const_virutal_empty_specifier", "function_name", "od_specifier",
  "od_exprlist", "od_expr_nonstrict", "argument_declaration",
  "argument_list", "arg_declaration", "marshal_decl", "marshal_opt_list",
  "marshal_opt", "cv_qualifier", "argument_name", "arg_default_value",
  "expr_decl", "number", "expr_name", "expr_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,    43,    45,
      42,    47,    37,    38,   124,    94,   126,    33,    61,    62,
      60,    58,    63,   303,    40,    59,   125,    41,    44,   123,
      91,    93,    64,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    75,    75,    75,    75,    75,
      75,    77,    78,    78,    78,    79,    80,    81,    82,    82,
      83,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      88,    89,    89,    90,    90,    90,    90,    91,    91,    92,
      93,    93,    94,    94,    95,    95,    95,    95,    96,    97,
      98,    99,   100,   100,   101,   101,   102,   102,   102,   102,
     103,   103,   103,   104,   104,   105,   105,   106,   105,   107,
     107,   107,   107,   107,   107,   108,   109,   109,   110,   110,
     111,   112,   112,   113,   114,   114,   115,   115,   116,   117,
     117,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   122,   122,   123,   123,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   128,   129,   129,   130,   131,   132,
     132,   133,   134,   134,   134,   134,   134,   135,   134,   136,
     134,   137,   137,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   140,   140,   140,   141,   142,
     142,   143,   143,   143,   143,   143,   144,   144,   145,   145,
     146,   146,   147,   148,   148,   149,   149,   150,   150,   150,
     150,   151,   151,   151,   152,   152,   153,   153,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   155,   155,   156,
     156,   157,   157
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     3,     2,     2,     2,     2,
       2,     1,     2,     2,     2,     4,     1,     2,     0,     2,
       1,     1,     1,     4,     2,     2,     1,     0,     3,     2,
       4,     0,     2,     5,     6,     6,     5,     5,     2,     2,
       0,     2,     1,     3,     1,     2,     3,     3,     2,     5,
       3,     2,     0,     2,     1,     3,     1,     2,     3,     3,
       1,     1,     1,     0,     2,     0,     2,     0,     4,     2,
       2,     2,     2,     1,     5,     5,     1,     3,     1,     3,
       6,     0,     1,     3,     1,     3,     1,     4,     2,     1,
       3,     4,     0,     4,     2,     1,     1,     1,     1,     1,
       4,     1,     2,     1,     3,     4,     0,     3,     0,     1,
       0,     1,     1,     1,     2,     0,     2,     5,     1,     4,
       5,     1,     8,     9,     9,    10,    11,     0,    14,     0,
      15,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     0,     1,     1,     2,     2,     1,     0,
       4,     0,    12,    10,     8,     6,     0,     2,     0,     1,
       1,     3,     9,     0,     3,     1,     3,     1,     1,     3,
       3,     0,     1,     1,     0,     1,     0,     2,     2,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     3,     3,     3,     3,     2,
       3,     3,     4,     2,     2,     2,     2,     1,     1,     1,
       3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    26,     0,    11,     0,    16,     0,
       0,     0,     0,     0,     0,    20,     0,    21,    22,    40,
       0,     4,     0,    63,    14,    12,    13,    51,    39,    25,
       0,   106,    26,   106,     7,     1,     2,    10,     8,     0,
       9,    27,    24,     0,    38,     0,     6,     0,    65,     0,
      48,    52,   106,   108,     0,    25,     0,    18,     0,    98,
      99,    26,    96,    97,   101,     0,     0,   106,     0,    95,
      44,    61,    62,    60,     0,    41,    42,     0,     0,     5,
       0,    98,   139,   140,   133,   134,   135,   136,   137,   138,
      73,     0,     0,     0,     0,    67,     0,    65,     0,     0,
       0,   106,     0,   112,     0,   113,   115,   143,   131,     0,
      64,     0,    50,     0,   109,   106,    92,     0,    92,     0,
      17,    15,     0,   102,    23,    27,    29,     0,    94,     0,
       0,    45,     0,     0,     0,   142,     0,   141,     0,     0,
     121,     0,   167,   168,     0,     0,     0,   165,     0,     0,
      66,    69,    70,    72,   139,    88,    89,   110,   106,    71,
     163,     0,   114,   144,   145,     0,   132,     0,   106,    56,
       0,    53,    54,     0,    92,   107,     0,    33,    92,    36,
      19,   106,     0,   103,    28,    92,    46,    43,    47,    37,
       0,     0,     0,    81,     0,     0,     0,   143,     0,    65,
      49,   106,   111,     0,   110,     0,     0,   159,   160,   171,
     116,   147,   146,     0,   143,   110,   106,     0,     0,    57,
       0,    35,   209,   207,   208,   180,     0,     0,     0,     0,
       0,     0,     0,   179,    92,    34,    92,   100,     0,    31,
       0,     0,    78,     0,    76,     0,     0,    82,   119,   170,
     169,     0,   166,    68,    90,   110,    92,     0,     0,     0,
     149,   163,   172,   173,     0,   143,   106,     0,   110,    58,
      55,    59,     0,   199,   203,   204,   206,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,   178,
     110,   104,   106,    30,    74,   120,     0,    75,     0,     0,
       0,   143,     0,    91,   163,   148,     0,   164,     0,   117,
     161,   171,     0,   110,     0,     0,   210,   200,   189,   190,
     191,   194,   197,   198,   181,   182,   183,   184,   185,   186,
     187,   188,   192,   195,   196,     0,    93,   201,   211,     0,
     105,    32,    79,    77,    83,    86,    80,    84,   106,    92,
       0,   163,   151,   106,   143,     0,   163,     0,     0,   202,
       0,     0,     0,   110,   108,     0,     0,     0,   110,   106,
       0,     0,   163,   193,   212,     0,    85,     0,   122,   108,
       0,     0,   150,   174,   110,   163,   108,     0,    87,   127,
     124,   156,     0,   175,    92,     0,     0,   123,   108,     0,
       0,     0,     0,   176,   129,   108,   125,   163,   157,   151,
       0,     0,   162,     0,   126,     0,   155,     0,     0,   177,
     163,   108,   151,     0,     0,   128,   154,     0,     0,   108,
     151,     0,   130,   153,     0,   151,   152
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    47,    10,    11,    12,    13,    58,   120,    14,
      64,    16,    65,    66,   126,   303,    17,    18,    19,    45,
      75,    76,    20,    21,    22,    23,   112,   171,   172,    95,
      51,    96,   148,    97,    98,   243,   244,    99,   246,   247,
     356,   357,   100,   155,   156,   313,   101,    68,    69,   182,
     183,   127,   115,   203,   102,   162,   103,   104,   105,   141,
     106,   409,   423,   107,   108,   109,   167,   257,   319,   377,
     411,   206,   207,   208,   209,   146,   147,   264,   404,   422,
     232,   233,   234,   349
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -257
static const yytype_int16 yypact[] =
{
     197,   -21,    14,    30,    41,    21,  -257,   197,  -257,    64,
     197,   197,   197,    19,   197,  -257,     6,  -257,  -257,    24,
     197,  -257,     2,   -32,  -257,  -257,  -257,  -257,  -257,  -257,
     109,    67,   123,    67,  -257,  -257,  -257,  -257,  -257,   125,
    -257,   128,  -257,   256,  -257,    70,  -257,   197,   241,   138,
    -257,    90,    67,   143,   160,     7,   166,    95,   106,   121,
    -257,   181,  -257,  -257,  -257,   124,   134,    67,    71,  -257,
    -257,  -257,  -257,  -257,   142,   140,  -257,    46,   208,  -257,
     146,    60,    -1,   198,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,   205,   209,   211,   292,  -257,   153,   241,   155,   156,
     158,    16,   163,  -257,   175,  -257,   172,   280,  -257,   128,
    -257,   295,  -257,   235,  -257,    67,   173,   236,   173,   125,
    -257,  -257,    71,    10,  -257,   128,  -257,   238,  -257,   239,
     256,  -257,   243,   185,   250,  -257,   211,  -257,   192,   203,
    -257,   212,  -257,  -257,   217,   221,   218,   214,   219,   225,
    -257,  -257,  -257,  -257,   268,  -257,   232,   240,    67,  -257,
      55,   288,  -257,   299,   296,   292,  -257,   128,    16,  -257,
     142,   247,  -257,   105,   173,  -257,   228,  -257,   173,  -257,
    -257,    67,   257,   249,  -257,   173,  -257,  -257,  -257,  -257,
     253,   264,   323,   324,   274,   325,   228,   127,   292,   241,
    -257,    67,  -257,   336,   240,   292,   279,  -257,   281,     1,
    -257,  -257,  -257,   282,   127,   240,    67,   345,   295,  -257,
     346,  -257,   310,  -257,  -257,  -257,   228,   228,   228,   228,
     228,   228,   285,  -257,   -16,  -257,   173,  -257,    71,   287,
     298,   297,   307,   300,   309,   361,   302,  -257,  -257,  -257,
     505,   128,  -257,  -257,  -257,   240,     3,   314,   376,   313,
     315,   316,  -257,  -257,   128,   127,    67,   376,   240,  -257,
    -257,  -257,   379,  -257,   532,   538,   538,   538,   387,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   173,   139,  -257,
     240,  -257,    67,  -257,  -257,  -257,   388,  -257,   323,   332,
     392,   127,   393,  -257,    55,  -257,   337,  -257,   331,  -257,
    -257,     1,   128,   240,   347,   376,  -257,  -257,   348,   348,
     348,   348,   348,   348,   532,   532,   532,   532,   532,   538,
     538,   538,   538,   348,   348,   451,  -257,  -257,   505,   126,
    -257,  -257,  -257,  -257,  -257,   349,  -257,   350,    67,   173,
     353,    55,   409,    67,   127,   376,    55,   365,   228,  -257,
     228,   411,   392,   240,   143,   363,   -39,   366,   240,    67,
     367,   377,    55,  -257,   505,   362,  -257,   376,  -257,   143,
     228,   428,  -257,   437,   240,    55,   143,   381,  -257,  -257,
    -257,   478,   386,  -257,   173,   376,   384,  -257,   143,   389,
     228,   396,   228,   394,  -257,   143,  -257,    55,   505,   409,
     321,   228,  -257,   398,  -257,   397,  -257,   400,   228,   505,
      55,   143,   409,   354,   399,  -257,  -257,   410,   228,   143,
     409,   419,  -257,  -257,   415,   409,  -257
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -257,    39,  -257,  -257,   447,  -257,  -257,   357,  -257,  -257,
     157,  -257,   358,  -257,   180,  -257,  -257,  -257,  -257,  -257,
    -257,   355,  -257,  -257,  -257,  -257,  -257,  -257,   266,   -42,
    -257,   -87,  -257,  -257,  -257,   186,  -257,  -257,  -257,  -257,
     135,  -257,  -257,   294,  -257,  -113,   -35,  -257,   -64,   255,
    -257,   -31,  -256,  -187,  -257,  -257,  -257,  -257,  -257,   360,
    -257,  -257,  -257,  -257,   390,   -86,  -185,  -249,  -257,  -214,
    -257,  -252,   237,  -257,  -257,  -142,  -257,   187,  -257,  -257,
    -188,  -257,  -257,  -257
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -159
static const yytype_int16 yytable[] =
{
      54,    77,    56,   177,   128,   179,    67,     1,   250,   316,
     150,   -25,   251,  -106,   135,   158,   262,   258,   324,   390,
      27,   113,    24,   213,   117,    30,    49,    31,   267,   266,
     154,    83,   129,    50,   391,   263,    28,    32,   273,   274,
     275,   276,   277,   278,    25,    26,    34,    29,   298,    36,
      37,    38,   131,    40,   176,   136,   252,    53,   181,    46,
     132,   221,   360,   259,    35,   235,    53,  -148,   312,   173,
     157,    48,   239,   176,   168,    41,   367,    59,    60,   -25,
     322,   325,   216,    39,   175,    43,    79,    61,    77,    44,
      67,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   375,
     348,   219,   253,   350,   381,    52,   380,    53,   388,   220,
     122,   299,  -158,   300,  -118,   205,   358,   204,   217,    55,
     397,    57,   214,   400,    59,    60,   365,   215,   399,    78,
     407,   163,   164,   406,    61,   222,   110,   223,   224,   225,
     236,   111,   416,    71,    72,    73,   414,    15,   114,   424,
      62,    63,    33,   119,    15,   425,   116,    15,    15,    15,
     255,    15,   118,   121,   181,   435,   173,    15,   434,   379,
     383,   122,   384,   442,   346,   268,   387,   123,   226,   227,
     124,   393,   228,   369,   370,   229,   230,    -3,     1,   125,
       2,     3,   401,   231,    15,   426,   347,   405,   130,   133,
     134,   138,   137,     4,     5,   139,   311,   140,   436,   149,
     151,   152,   418,   153,   420,     6,   443,     7,   159,   321,
     161,   446,     8,   429,   222,   323,   223,   224,   225,   160,
     433,   174,   178,   176,   185,   186,    80,    81,    60,   188,
     441,   189,    71,    72,    73,    82,    83,    61,   190,    84,
      85,   192,    70,    86,    87,    88,    89,    71,    72,    73,
      74,    90,   193,    62,    63,   195,   194,   226,   227,   196,
     199,   228,   198,   135,   229,   230,    91,   364,    92,   197,
     200,   413,   231,   202,   163,   164,   210,    93,    84,    85,
     201,   169,    86,    87,    88,    89,    71,    72,    73,   170,
     212,    94,   142,   143,   211,   218,   237,   238,   144,   145,
     240,   279,   280,   281,   282,   283,   284,   373,   241,   242,
     245,   249,   378,   285,   286,   287,   288,   289,   290,   291,
     292,   248,   256,   293,   294,   295,   260,   296,   394,   261,
     165,   269,   271,   265,   272,   302,   297,   279,   280,   281,
     282,   283,   284,   304,   305,   306,   307,   309,   310,   285,
     286,   287,   288,   289,   290,   291,   292,   308,   314,   293,
     294,   295,   315,   296,   317,   326,   205,   318,   427,   428,
     279,   280,   281,   282,   283,   284,   352,   354,   355,   359,
     362,   361,   285,   286,   287,   288,   289,   290,   291,   292,
     296,   366,   293,   294,   295,   376,   296,   385,   372,   371,
     374,   437,   438,   279,   280,   281,   282,   283,   284,   382,
     389,   395,   392,   398,   402,   285,   286,   287,   288,   289,
     290,   291,   292,   403,   396,   293,   294,   295,   408,   296,
     412,   415,   421,   417,   327,   279,   280,   281,   282,   283,
     284,   419,   430,    42,   431,   432,   439,   285,   286,   287,
     288,   289,   290,   291,   292,   440,   180,   293,   294,   295,
     445,   296,   351,   184,   270,   187,   444,   279,   280,   281,
     282,   283,   284,   301,   353,   254,   191,   166,   320,   285,
     286,   287,   288,   289,   290,   291,   292,   386,   363,   293,
     294,   295,   368,   296,   279,   280,   281,   282,   283,   284,
     410,     0,     0,     0,     0,     0,   285,   286,   287,   288,
     289,   290,   291,   292,     0,     0,   293,   294,   295,     0,
     296,   279,   280,   281,   282,   283,   284,     0,     0,     0,
       0,     0,     0,   285,   286,   287,   288,   289,   290,   291,
     292,     0,     0,   293,   294,   295,     0,   296,   279,   280,
     281,   282,   283,   284,   279,   280,   281,   282,   283,   284,
       0,     0,     0,     0,     0,   290,   291,   292,     0,     0,
     293,   294,   295,     0,   296,     0,     0,   294,   295,     0,
     296
};

static const yytype_int16 yycheck[] =
{
      31,    43,    33,   116,    68,   118,    41,     1,   196,   258,
      97,     1,   197,     6,    15,   101,    15,   204,   267,    58,
       6,    52,    43,   165,    55,     4,    58,     6,   215,   214,
      14,    15,    74,    65,    73,    34,     6,    16,   226,   227,
     228,   229,   230,   231,    65,    66,     7,     6,    64,    10,
      11,    12,     6,    14,    70,    56,   198,    50,   122,    20,
      14,   174,   314,   205,     0,   178,    50,    64,   255,   111,
     101,    69,   185,    70,   109,    69,   325,     6,     7,    69,
     265,   268,   168,    64,   115,    61,    47,    16,   130,    65,
     125,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   361,
     298,     6,   199,   300,   366,     6,   365,    50,   374,    14,
      60,   234,    67,   236,    64,    70,   311,   158,   170,     6,
     382,     6,   167,   389,     6,     7,   323,   168,   387,    69,
     396,    14,    15,   395,    16,     6,     8,     8,     9,    10,
     181,    61,   408,    11,    12,    13,   405,     0,    15,   415,
      32,    33,     5,    68,     7,   417,     6,    10,    11,    12,
     201,    14,     6,    67,   238,   431,   218,    20,   430,   364,
     368,    60,   370,   439,   297,   216,   373,     6,    49,    50,
      66,   378,    53,    67,    68,    56,    57,     0,     1,    65,
       3,     4,   390,    64,    47,   419,    67,   394,    68,     1,
      64,     6,    14,    16,    17,     6,   251,     6,   432,    66,
      65,    65,   410,    65,   412,    28,   440,    30,    65,   264,
      58,   445,    35,   421,     6,   266,     8,     9,    10,    64,
     428,     6,     6,    70,     6,     6,     5,     6,     7,     6,
     438,    66,    11,    12,    13,    14,    15,    16,     8,    18,
      19,    69,     6,    22,    23,    24,    25,    11,    12,    13,
      14,    30,    69,    32,    33,    58,    64,    49,    50,    58,
      61,    53,    68,    15,    56,    57,    45,   322,    47,    71,
      65,   404,    64,    53,    14,    15,     8,    56,    18,    19,
      68,     6,    22,    23,    24,    25,    11,    12,    13,    14,
      14,    70,    20,    21,    15,    68,    59,    68,    26,    27,
      67,    36,    37,    38,    39,    40,    41,   358,    64,     6,
       6,     6,   363,    48,    49,    50,    51,    52,    53,    54,
      55,    67,     6,    58,    59,    60,    67,    62,   379,    68,
      70,     6,     6,    71,    44,    68,    71,    36,    37,    38,
      39,    40,    41,    65,    67,    58,    66,     6,    66,    48,
      49,    50,    51,    52,    53,    54,    55,    68,    64,    58,
      59,    60,     6,    62,    71,     6,    70,    72,    67,    68,
      36,    37,    38,    39,    40,    41,     8,    65,     6,     6,
      69,    64,    48,    49,    50,    51,    52,    53,    54,    55,
      62,    64,    58,    59,    60,     6,    62,     6,    68,    70,
      67,    67,    68,    36,    37,    38,    39,    40,    41,    64,
      67,    64,    66,    71,     6,    48,    49,    50,    51,    52,
      53,    54,    55,     6,    67,    58,    59,    60,    67,    62,
      64,    67,    58,    64,    67,    36,    37,    38,    39,    40,
      41,    65,    64,    16,    67,    65,    67,    48,    49,    50,
      51,    52,    53,    54,    55,    65,   119,    58,    59,    60,
      65,    62,   302,   125,   218,   130,    67,    36,    37,    38,
      39,    40,    41,   238,   308,   201,   136,   107,   261,    48,
      49,    50,    51,    52,    53,    54,    55,   372,   321,    58,
      59,    60,    61,    62,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    58,    59,    60,    -1,
      62,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    58,    59,    60,    -1,    62,    36,    37,
      38,    39,    40,    41,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,
      58,    59,    60,    -1,    62,    -1,    -1,    59,    60,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    16,    17,    28,    30,    35,    75,
      77,    78,    79,    80,    83,    84,    85,    90,    91,    92,
      96,    97,    98,    99,    43,    65,    66,     6,     6,     6,
       4,     6,    16,    84,    75,     0,    75,    75,    75,    64,
      75,    69,    78,    61,    65,    93,    75,    76,    69,    58,
      65,   104,     6,    50,   125,     6,   125,     6,    81,     6,
       7,    16,    32,    33,    84,    86,    87,   120,   121,   122,
       6,    11,    12,    13,    14,    94,    95,   103,    69,    75,
       5,     6,    14,    15,    18,    19,    22,    23,    24,    25,
      30,    45,    47,    56,    70,   103,   105,   107,   108,   111,
     116,   120,   128,   130,   131,   132,   134,   137,   138,   139,
       8,    61,   100,   125,    15,   126,     6,   125,     6,    68,
      82,    67,    60,     6,    66,    65,    88,   125,   122,   103,
      68,     6,    14,     1,    64,    15,    56,    14,     6,     6,
       6,   133,    20,    21,    26,    27,   149,   150,   106,    66,
     105,    65,    65,    65,    14,   117,   118,   125,   139,    65,
      64,    58,   129,    14,    15,    70,   138,   140,   120,     6,
      14,   101,   102,   103,     6,   125,    70,   119,     6,   119,
      81,   122,   123,   124,    86,     6,     6,    95,     6,    66,
       8,   133,    69,    69,    64,    58,    58,    71,    68,    61,
      65,    68,    53,   127,   125,    70,   145,   146,   147,   148,
       8,    15,    14,   149,   120,   125,   139,   103,    68,     6,
      14,   119,     6,     8,     9,    10,    49,    50,    53,    56,
      57,    64,   154,   155,   156,   119,   125,    59,    68,   119,
      67,    64,     6,   109,   110,     6,   112,   113,    67,     6,
     154,   140,   149,   105,   117,   125,     6,   141,   127,   149,
      67,    68,    15,    34,   151,    71,   140,   127,   125,     6,
     102,     6,    44,   154,   154,   154,   154,   154,   154,    36,
      37,    38,    39,    40,    41,    48,    49,    50,    51,    52,
      53,    54,    55,    58,    59,    60,    62,    71,    64,   119,
     119,   123,    68,    89,    65,    67,    58,    66,    68,     6,
      66,   120,   127,   119,    64,     6,   141,    71,    72,   142,
     146,   120,   140,   125,   141,   127,     6,    67,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   119,    67,   154,   157,
     127,    88,     8,   109,    65,     6,   114,   115,   140,     6,
     145,    64,    69,   151,   120,   127,    64,   141,    61,    67,
      68,    70,    68,   125,    67,   145,     6,   143,   125,   140,
     141,   145,    64,   154,   154,     6,   114,   127,   126,    67,
      58,    73,    66,   127,   125,    64,    67,   145,    71,   141,
     126,   154,     6,     6,   152,   127,   145,   126,    67,   135,
      42,   144,    64,   119,   141,    67,   126,    64,   154,    65,
     154,    58,   153,   136,   126,   145,   143,    67,    68,   154,
      64,    67,    65,   154,   145,   126,   143,    67,    68,    67,
      65,   154,   126,   143,    67,    65,   143
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 126 "parser.y"
    {
  if (othercodes.GetSize())
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode(othercodes);
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    }
}
    break;

  case 4:
#line 136 "parser.y"
    { insideClass=false; othercodes.SetSize(0); startPos=-1;}
    break;

  case 10:
#line 142 "parser.y"
    {
  CleanStack();
}
    break;

  case 11:
#line 148 "parser.y"
    {
	printf("handle at Bison\n");
	othercodes.InsertAt(-1,"\n",strlen("\n"));
}
    break;

  case 12:
#line 156 "parser.y"
    {
  startPos=-1;
  insideClass=false;
  if (othercodes.GetSize())
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,othercodes.GetSize());
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    }  
}
    break;

  case 13:
#line 169 "parser.y"
    {
  startPos=-1;
  insideClass=false;
  if (othercodes.GetSize())
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,othercodes.GetSize());
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    }  
}
    break;

  case 14:
#line 182 "parser.y"
    {
  startPos=-1;
  insideClass=false;
  if (othercodes.GetSize())
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,othercodes.GetSize());
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    } 
  YYACCEPT;
}
    break;

  case 15:
#line 198 "parser.y"
    {
  currentPack->SetEndLine(linenumber-1);

  currentPack=NULL;
  othercodes.SetSize(0);
  startPos=-1;
  
}
    break;

  case 16:
#line 209 "parser.y"
    {
  if (othercodes.GetSize() && startPos>0)
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,startPos);
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    }  
  startPos=-1;
  currentPack=new PackObject(thisCodeFile);
  currentPack->SetStartLine(linenumber-1);

  thisCodeFile->AddCodeData(currentPack);  
}
    break;

  case 17:
#line 227 "parser.y"
    {
  if (currentPack!=NULL)
    {
      currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
    }
}
    break;

  case 18:
#line 236 "parser.y"
    {
}
    break;

  case 19:
#line 239 "parser.y"
    {
}
    break;

  case 20:
#line 247 "parser.y"
    {
    CleanStack();
}
    break;

  case 23:
#line 259 "parser.y"
    {
  currentstruct=Pop();
  if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  (yyval)=(yyvsp[(1) - (4)]);
}
    break;

  case 24:
#line 265 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 25:
#line 271 "parser.y"
    {
  char *tname=GetToken((yyvsp[(2) - (2)]));
  DataType *type=thisCodeFile->FindDataType(tname);
  TypeClassStruct *t;
  if (type!=NULL)
    {
      t=dynamic_cast<TypeClassStruct *>(type);
      if (t==NULL)
	{
	  //	  	  thisCodeFile->RemoveDataType(type);
	  //	  	  delete type;
	  t=new TypeClassStruct(tname, false);
	  thisCodeFile->AddDataType(t);
	  //	  sprintf(tmp,"data type \"%s\" has been redefined!\n",tname);
	  //	  errormsg(tmp);
	  //	  exit(1);
	}
    } 
  else
    { 
      t=new TypeClassStruct(tname,false);
      thisCodeFile->AddDataType(t);
    }
  Push(t);
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 26:
#line 298 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 30:
#line 313 "parser.y"
    {
  DataType *type1=currenttype;
  if ((yyvsp[(1) - (4)])>0)
    {
      //type1=new TypePtr(NULL,$1, type1);
      type1=new TypePtr(NULL, (yyvsp[(1) - (4)]), type1, constPointerPositions);
      thisCodeFile->AddDataType(type1);
    }
  if ((yyvsp[(3) - (4)])!=-1)
    {
      type1=new TypeArray(NULL,GetToken((yyvsp[(3) - (4)])), type1);
      thisCodeFile->AddDataType(type1);     
    }  
  TypeClassStruct *t=Peek();
  assert(t!=NULL);
  t->Add(type1, GetToken((yyvsp[(2) - (4)])));

}
    break;

  case 33:
#line 344 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[(2) - (5)]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new DataType(orgtype);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(3) - (5)])>0)
    {
      //type=new TypePtr(NULL,$3, type);
      type=new TypePtr(NULL,(yyvsp[(3) - (5)]), type, constPointerPositions);
      
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(5) - (5)])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[(5) - (5)])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[(4) - (5)])),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 34:
#line 368 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[(3) - (6)]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new TypeClassStruct(orgtype,false);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(4) - (6)])>0)
    {
      //type=new TypePtr(NULL,$4, type);
      type=new TypePtr(NULL, (yyvsp[(4) - (6)]), type, constPointerPositions);
      
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(6) - (6)])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[(6) - (6)])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[(5) - (6)])),type);
  thisCodeFile->AddDataType(type);   
}
    break;

  case 35:
#line 392 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[(3) - (6)]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new TypeClassStruct(orgtype, true);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(4) - (6)])>0)
    {
      //type=new TypePtr(NULL,$4, type);
      type=new TypePtr(NULL, (yyvsp[(4) - (6)]), type, constPointerPositions);
      
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(6) - (6)])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[(6) - (6)])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[(5) - (6)])),type);
  thisCodeFile->AddDataType(type);   
}
    break;

  case 36:
#line 416 "parser.y"
    {
  DataType *type=currentstruct;
  assert(type!=NULL);

  if ((yyvsp[(3) - (5)])>0)
    {
      //type=new TypePtr(NULL,$3, type);
      type=new TypePtr(NULL, (yyvsp[(3) - (5)]), type, constPointerPositions);
      
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[(5) - (5)])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[(5) - (5)])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[(4) - (5)])),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 37:
#line 441 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 39:
#line 447 "parser.y"
    {
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[(2) - (2)])));
  if (t==NULL)
    {
      seqclass=new TypeClassStruct(GetToken((yyvsp[(2) - (2)])),true);
      thisCodeFile->AddDataType(seqclass);
    }
  else if (!t->IsStandardType())
    {
      seqclass=dynamic_cast<TypeClassStruct *>(t);
      if (seqclass==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"%s has been declared as non-class data type", GetToken((yyvsp[(2) - (2)])));
	  errormsg(tmp);
	  exit(1);
	}
    }
}
    break;

  case 44:
#line 477 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[(1) - (1)])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[(1) - (1)])), true);
      seqclass->AddBase(seqbase);  
    }
  else if (!t->IsStandardType())
    {
      /*      seqbase=dynamic_cast<TypeClassStruct *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken($1));
	  errormsg(tmp);
	  exit(1);
	}
      */
      seqclass->AddBase(t);
    }
}
    break;

  case 45:
#line 501 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[(2) - (2)])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[(2) - (2)])), true);
      seqclass->AddBase(seqbase);  
    }
  else  if (!t->IsStandardType())
    {
      /*
      seqbase=dynamic_cast<TypeClassStruct *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken($2));
	  errormsg(tmp);
	  exit(1);
	}
      */
      seqclass->AddBase(t);
    }
}
    break;

  case 46:
#line 526 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[(3) - (3)])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[(3) - (3)])), true);
      seqclass->AddBase(seqbase);  
    }
  else  if (!t->IsStandardType())
    {
      /*
      seqbase=dynamic_cast<TypeClassStruct *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken($3));
	  errormsg(tmp);
	  exit(1);
	}
      */
      seqclass->AddBase(t);
    }
}
    break;

  case 47:
#line 551 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[(3) - (3)])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[(3) - (3)])), true);
      seqclass->AddBase(seqbase);
    }
  else  if (!t->IsStandardType())
    {
      /*      seqbase=dynamic_cast<TypeClassStruct *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken($3));
	  errormsg(tmp);
	  exit(1);
	}
      */
      seqclass->AddBase(t);
    }
}
    break;

  case 48:
#line 581 "parser.y"
    {
  assert(currentClass!=NULL);
  sprintf(tmp,"class %s;",currentClass->GetName());

  assert(thisCodeFile!=NULL);
  OtherCode *dat=new OtherCode(thisCodeFile);
  dat->AddCode(tmp);
  thisCodeFile->AddCodeData(dat);

  othercodes.SetSize(0);

  currentClass=NULL;
  insideClass=false;
}
    break;

  case 49:
#line 602 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 50:
#line 610 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 51:
#line 620 "parser.y"
    {
  if (othercodes.GetSize() && startPos>0)
    {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,startPos);
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
    }
  insideClass=true;
  char *clname=GetToken((yyvsp[(2) - (2)]));
  
  Class *t;
  if ((t=thisCodeFile->FindClass(clname))==NULL)
    {
      t=new Class(clname, thisCodeFile);
      thisCodeFile->AddDataType(t);
    }
  t->SetFileInfo(filename);
  t->SetStartLine(linenumber);
  currentClass=t;
}
    break;

  case 56:
#line 653 "parser.y"
    {
	assert(currentClass!=NULL);
	Class *cl=thisCodeFile->FindClass(GetToken((yyvsp[(1) - (1)])));
	if (cl==NULL) 
	  {
	    char str[1024];
	    sprintf(str,"base class %s not declared",GetToken((yyvsp[(1) - (1)])));
	    errormsg(str);
	    exit(1);
	  }
	BaseClass *t=new BaseClass(cl, PUBLIC, false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 57:
#line 667 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[(1) - (2)]);
	Class *cl=thisCodeFile->FindClass(GetToken((yyvsp[(2) - (2)])));
	if (cl==NULL) 
	  {
	    char str[1024];
	    sprintf(str,"base class %s not declared",GetToken((yyvsp[(2) - (2)])));
	    errormsg(str);
	    exit(1);
	  }
	BaseClass *t=new BaseClass(cl,accessmode,false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 58:
#line 682 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[(2) - (3)]);

	Class *cl=thisCodeFile->FindClass(GetToken((yyvsp[(3) - (3)])));
	if (cl==NULL) 
	  {
	    char str[1024];
	    sprintf(str,"base class %s not declared",GetToken((yyvsp[(3) - (3)])));
	    errormsg(str);
	    exit(1);
	  }

	BaseClass *t=new BaseClass(cl,accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 59:
#line 699 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[(1) - (3)]);

	Class *cl=thisCodeFile->FindClass(GetToken((yyvsp[(3) - (3)])));
	if (cl==NULL) 
	  {
	    char str[1024];
	    sprintf(str,"base class %s not declared",GetToken((yyvsp[(3) - (3)])));
	    errormsg(str);
	    exit(1);
	  }

	BaseClass *t=new BaseClass(cl,accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 60:
#line 718 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 61:
#line 722 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 62:
#line 726 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 63:
#line 733 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 64:
#line 737 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 67:
#line 747 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 71:
#line 754 "parser.y"
    {
  assert(method!=NULL);
  int t=method->CheckMarshal();
  if (t!=0)
    {
      /*      if (t==-1) 
	sprintf(tmp,"In method %s::%s: unable to marshal the return argument.\n", currentClass->GetName(), method->name);
      else 
	sprintf(tmp,"In method %s::%s: unable to marshal argument %d.\n", currentClass->GetName(), method->name,t);

      errormsg(tmp);
      exit(1);*/      
    }
  currenttype=returntype=NULL;
}
    break;

  case 72:
#line 771 "parser.y"
    {
  if (accessmodifier==PUBLIC)
    {
      sprintf(tmp,"%s:%d: attributes of a parallel class must be private or protected.\n",thisCodeFile->GetFileName(), linenumber);
      errormsg(tmp);
      exit(1);
    }
  currenttype=returntype=NULL;  

}
    break;

  case 73:
#line 782 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 74:
#line 787 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 75:
#line 798 "parser.y"
    {
	assert(currentClass!=NULL);
	Enumeration *t = new Enumeration(currentClass, accessmodifier);
	t->SetLineInfo(linenumber-1);
	currentClass->AddMember(t);
	t->setName(GetToken((yyvsp[(2) - (5)])));
	t->setArgs(GetToken((yyvsp[(4) - (5)])));
}
    break;

  case 76:
#line 809 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);	
}
    break;

  case 77:
#line 813 "parser.y"
    {
	sprintf(tmp,"%s , %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 78:
#line 820 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 79:
#line 824 "parser.y"
    {      
	sprintf(tmp,"%s = %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
   (yyval)=PutToken(tmp);
}
    break;

  case 80:
#line 833 "parser.y"
    {
	assert(currentClass!=NULL);
	Structure *t = new Structure(currentClass, accessmodifier);
	t->SetLineInfo(linenumber-1);
	currentClass->AddMember(t);
	t->setName(GetToken((yyvsp[(2) - (6)])));
	t->setInnerDecl(GetToken((yyvsp[(4) - (6)])));
	t->setObjects(GetToken((yyvsp[(6) - (6)])));
}
    break;

  case 82:
#line 846 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 83:
#line 852 "parser.y"
    {
	sprintf(tmp,"%s %s;", GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 84:
#line 859 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 85:
#line 863 "parser.y"
    {
	sprintf(tmp,"%s , %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 86:
#line 869 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 87:
#line 874 "parser.y"
    {
	sprintf(tmp,"%s [%s]",GetToken((yyvsp[(1) - (4)])), GetToken((yyvsp[(3) - (4)])));
   (yyval)=PutToken(tmp);
}
    break;

  case 91:
#line 891 "parser.y"
    {

  assert(currentClass!=NULL);
  Attribute *t=new Attribute(currentClass,accessmodifier);
  t->SetLineInfo(linenumber-1);
  currentClass->AddMember(t);
  Param *tparam=t->NewAttribute();
  DataType *type;
  strcpy(tparam->name,GetToken((yyvsp[(3) - (4)])));
  if ((yyvsp[(1) - (4)])==0)
    {
      type=currenttype;
    }
  else 
    {
      //type=new TypePtr(NULL, $1 , currenttype);
      type=new TypePtr(NULL, (yyvsp[(1) - (4)]) , currenttype, constPointerPositions);
      thisCodeFile->AddDataType(type);
    }

  if ((yyvsp[(4) - (4)])!=-1)
    {
      type=new TypeArray(NULL, GetToken((yyvsp[(4) - (4)])) , type);
      thisCodeFile->AddDataType(type);
    }
  tparam->isRef=(yyvsp[(2) - (4)]);
  tparam->SetType(type);
}
    break;

  case 92:
#line 922 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 93:
#line 926 "parser.y"
    {
  if ((yyvsp[(4) - (4)])==-1)
    {
      sprintf(tmp,"[%s]",GetToken((yyvsp[(2) - (4)])));
      (yyval)=PutToken(tmp);
    }
  else
    {
      sprintf(tmp,"[%s]%s",GetToken((yyvsp[(2) - (4)])),GetToken((yyvsp[(4) - (4)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 94:
#line 941 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 95:
#line 945 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 96:
#line 951 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 97:
#line 955 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 98:
#line 961 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[(1) - (1)])));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken((yyvsp[(1) - (1)])));
      thisCodeFile->AddDataType(currenttype);
      /* 
	 sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	 errormsg(tmp);
	 exit(1);
      */
    }
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 99:
#line 976 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[(1) - (1)])));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken((yyvsp[(1) - (1)])));
      thisCodeFile->AddDataType(currenttype);

      /*
	sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	errormsg(tmp);
	exit(1);
      */
    }
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 100:
#line 992 "parser.y"
    {

  TypeTemplate *type=new TypeTemplate(GetToken((yyvsp[(1) - (4)])));
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (4)]);
  POSITION pos=list->GetHeadPosition();
  while (pos!=NULL)
    {
      TemplateArgument *el=list->GetNext(pos);
      type->AddTemplate(el->type, el->isRef);
      delete el;
    }
  delete list;
 
  thisCodeFile->AddDataType(type);
  currenttype=type;
  (yyval)=(YYSTYPE)currenttype;

}
    break;

  case 101:
#line 1011 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 102:
#line 1017 "parser.y"
    {
  DataType *type=thisCodeFile->FindDataType(GetToken((yyvsp[(2) - (2)])));
  if (type==NULL)
    {
      type=new TypeClassStruct(GetToken((yyvsp[(2) - (2)])), false);
      thisCodeFile->AddDataType(type);
    } 
  currenttype=type;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 103:
#line 1030 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 104:
#line 1037 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 105:
#line 1046 "parser.y"
    {
  TemplateArgument *t=new TemplateArgument;	
  t->type=(DataType *)(yyvsp[(1) - (4)]);
  if ((yyvsp[(2) - (4)])>0)
  {
	//t->type=new TypePtr(NULL,$2,t->type);
	t->type=new TypePtr(NULL, (yyvsp[(2) - (4)]), t->type, constPointerPositions);
  }
  if ((yyvsp[(3) - (4)])!=-1) 
  {
	t->type=new TypeArray(NULL,GetToken((yyvsp[(3) - (4)])), t->type);
  }
  t->isRef=((yyvsp[(4) - (4)])!=0);
  (yyval)=(YYSTYPE)t;
  
}
    break;

  case 106:
#line 1118 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 107:
#line 1123 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 108:
#line 1131 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 109:
#line 1135 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 110:
#line 1141 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 111:
#line 1145 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 116:
#line 1163 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 117:
#line 1169 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of constructor\n");
      exit(1);
    }
  if ((yyvsp[(5) - (5)])!=-1)
    {
      ObjDesc &od=((Constructor *)method)->GetOD();
      od.SetCode(GetToken((yyvsp[(5) - (5)])));
    }
  currentClass->AddMember(method);
}
    break;

  case 118:
#line 1185 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 119:
#line 1194 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 120:
#line 1203 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
	method->isVirtual=true;
	
}
    break;

  case 121:
#line 1216 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 122:
#line 1346 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 123:
#line 1353 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 124:
#line 1360 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 125:
#line 1367 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 126:
#line 1374 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 127:
#line 1381 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 128:
#line 1382 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 129:
#line 1388 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 130:
#line 1389 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 131:
#line 1399 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 132:
#line 1403 "parser.y"
    {
	/* error if multimple time same reserved word */
	if (((yyvsp[(2) - (2)]) & (yyvsp[(1) - (2)])) != 0)
	{
		errormsg("Multiple occurance of same POP-C++ Mehtode modivier!");
		exit(1);
	}
  
	(yyval)=(yyvsp[(1) - (2)]) | (yyvsp[(2) - (2)]);
}
    break;

  case 133:
#line 1449 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 134:
#line 1453 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 135:
#line 1457 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 136:
#line 1461 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 137:
#line 1465 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 138:
#line 1469 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 139:
#line 1476 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 140:
#line 1480 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 141:
#line 1484 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 142:
#line 1488 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 143:
#line 1495 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 144:
#line 1499 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 145:
#line 1503 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 146:
#line 1507 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 147:
#line 1511 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 148:
#line 1517 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 149:
#line 1528 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 150:
#line 1532 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 151:
#line 1538 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 152:
#line 1543 "parser.y"
    {

  char *odtmp=GetToken((yyvsp[(1) - (12)]));
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken((yyvsp[(3) - (12)])));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s,%s,%s);",GetToken((yyvsp[(3) - (12)])),GetToken((yyvsp[(5) - (12)])),GetToken((yyvsp[(7) - (12)])),GetToken((yyvsp[(9) - (12)])));
  if ((yyvsp[(12) - (12)])!=-1) strcat(tmp,GetToken((yyvsp[(12) - (12)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 153:
#line 1560 "parser.y"
    {

  char *odtmp=GetToken((yyvsp[(1) - (10)]));
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken((yyvsp[(3) - (10)])));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s,%s);",GetToken((yyvsp[(3) - (10)])),GetToken((yyvsp[(5) - (10)])),GetToken((yyvsp[(7) - (10)])));
  if ((yyvsp[(10) - (10)])!=-1) strcat(tmp,GetToken((yyvsp[(10) - (10)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 154:
#line 1576 "parser.y"
    {
  char *odtmp=GetToken((yyvsp[(1) - (8)]));
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken((yyvsp[(3) - (8)])));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s);",GetToken((yyvsp[(3) - (8)])),GetToken((yyvsp[(5) - (8)])));
  if ((yyvsp[(8) - (8)])!=-1) strcat(tmp,GetToken((yyvsp[(8) - (8)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 155:
#line 1591 "parser.y"
    {
    char *odtmp=GetToken((yyvsp[(1) - (6)]));
    if (paroc_utils::isEqual(odtmp,"host"))
      {
	sprintf(tmp,"od.url(%s);",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    errormsg("OD: host should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"jobcontact"))
      {
	sprintf(tmp,"od.joburl(%s);",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    errormsg("OD: jobcontact should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"memory"))
      {
	sprintf(tmp,"od.memory(%s",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[(4) - (6)])));
	  }
	strcat(tmp,");");
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
      } 
    else if (paroc_utils::isEqual(odtmp,"power"))
      {
	sprintf(tmp,"od.power(%s",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[(4) - (6)])));
	  }
	strcat(tmp,");");
//Added by clementval
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
      } 
    else if (paroc_utils::isEqual(odtmp,"search"))
      {
	sprintf(tmp,"od.search(%s",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[(4) - (6)])));
	  }
	if ((yyvsp[(5) - (6)])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[(5) - (6)])));
	  }
	strcat(tmp,");");
//End of add
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
      } 
    else if (paroc_utils::isEqual(odtmp,"network"))
    {
	sprintf(tmp,"od.bandwidth(%s",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[(4) - (6)])));
	  }
	strcat(tmp,");");
	if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
    } 
    else if (paroc_utils::isEqual(odtmp,"walltime"))
      {
	sprintf(tmp,"od.walltime(%s);",GetToken((yyvsp[(3) - (6)])));
	if ((yyvsp[(4) - (6)])!=-1)
	  {
	    errormsg("OD: walltime  should be a number expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else
      {
	errormsg("Unknown OD declaration");
	exit(1);
      }
    (yyval)=PutToken(tmp);
}
    break;

  case 156:
#line 1683 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 157:
#line 1687 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 162:
#line 1702 "parser.y"
    {
  Param *t=method->AddNewParam();
  UpdateMarshalParam((yyvsp[(1) - (9)]),t);

  DataType *type=currenttype;
  if ((yyvsp[(5) - (9)])>0)
    {
      //type=new TypePtr(NULL, $5 , type);
      type=new TypePtr(NULL, (yyvsp[(5) - (9)]) , type, constPointerPositions);
      
      thisCodeFile->AddDataType(type);
    }

  if ((yyvsp[(6) - (9)]))
    {
      t->isRef=true;
    }

  if ((yyvsp[(8) - (9)])!=-1)
    {
      type=new TypeArray(NULL, GetToken((yyvsp[(8) - (9)])) , type);
      thisCodeFile->AddDataType(type);
    }

  t->SetType(type);
  if ((yyvsp[(7) - (9)])!=-1) strcpy(t->name,GetToken((yyvsp[(7) - (9)])));
  else   sprintf(t->name,"V_%d",++counter);

  t->isConst=(((yyvsp[(2) - (9)])==1) || ((yyvsp[(4) - (9)])==1));
  if ((yyvsp[(9) - (9)])>=0) t->defaultVal=strdup(GetToken((yyvsp[(9) - (9)])));
  

}
    break;

  case 163:
#line 1738 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 164:
#line 1742 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 165:
#line 1748 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 166:
#line 1752 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 167:
#line 1758 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 168:
#line 1762 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 169:
#line 1766 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 170:
#line 1771 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 171:
#line 1779 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 172:
#line 1783 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 173:
#line 1787 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 174:
#line 1793 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 175:
#line 1797 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 176:
#line 1803 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 177:
#line 1807 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 178:
#line 1820 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 179:
#line 1829 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 180:
#line 1833 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 181:
#line 1837 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:
#line 1842 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:
#line 1847 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:
#line 1852 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:
#line 1857 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:
#line 1862 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:
#line 1867 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:
#line 1872 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:
#line 1877 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:
#line 1882 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:
#line 1887 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:
#line 1892 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 193:
#line 1897 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 194:
#line 1902 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 195:
#line 1907 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 196:
#line 1912 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 197:
#line 1917 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 198:
#line 1922 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 199:
#line 1927 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 200:
#line 1932 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 201:
#line 1937 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 202:
#line 1942 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 203:
#line 1948 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 204:
#line 1953 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 205:
#line 1958 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 206:
#line 1963 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 207:
#line 1970 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 208:
#line 1974 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 209:
#line 1980 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 210:
#line 1984 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 211:
#line 1992 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 212:
#line 1996 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;


/* Line 1267 of yacc.c.  */
#line 3893 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 2004 "parser.y"


#include "config.h"

void Usage()
{
  fprintf(stderr,"POP-C++ preprocessor version %s\nparoccpp [-onlyclient | -onlyserver] [POP-C++ source] [C++ source]\n", VERSION);
  exit(1);
}

void CleanStack()
{
  if (typestack.GetCount()) fprintf(stderr,"STRUCT list: %d elements\n",typestack.GetCount());
  currentstruct=NULL;
  typestack.RemoveAll();
}

void Push(TypeClassStruct *x)
{
  typestack.AddHead(x);
}

TypeClassStruct *Pop()
{
  POSITION pos=typestack.GetHeadPosition();
  if (pos==NULL) return NULL;
  TypeClassStruct *t=typestack.GetAt(pos);
  typestack.RemoveHead();
  return t;
}

TypeClassStruct *Peek()
{
  POSITION pos=typestack.GetHeadPosition();
  if (pos==NULL) return NULL;
  TypeClassStruct *t=typestack.GetAt(pos);
  return t;
}

void UpdateMarshalParam(int flags, Param *t)
{
  if (flags!=0)
    {
      if (flags & PARAM_IN) t->isInput=true;
      if (flags & PARAM_OUT) t->isOutput=true;
      if (flags & USERPROC) t->marshalProc=strdup(tmpProc);
      if (flags & PARAMSIZE) t->paramSize=strdup(tmpSize);
    }
}

extern FILE *yyin;

int main(int argc, char **argv)
{
  bool client=true;
  bool broker=true;

  if (paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")!=NULL) broker=false;
  if (paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")!=NULL) client=false;
  
  int ret;
  indexsource=-1;
  errorcode=0;
  if (argc<2) Usage();
  else
    {
      if ((ret=ParseFile(argv[1], ((argc>2) ? argv[2] : NULL), client, broker))!=0)
	{
	  fprintf(stderr,"Parse POP-C++ code failed (error=%d)\n",ret);
	  exit(ret);
	}
    }
  return (errorcode!=0);
}

void yyerror(const  char *s)
{
  if (insideClass)
    {
      errormsg(s);
    }
}

void errormsg(const  char *s)
{
  fprintf(stderr,"%s:%d: ERROR :%s\n",filename,linenumber-1,s);
  errorcode=1;
}

int yywrap()
{
  return(1);
}


int base=1;

int ParseFile(char *infile, char *outfile, bool client, bool broker)
{
  if (infile==NULL || *infile=='-') yyin=stdin;
  else
    {
      yyin=fopen(infile,"rt");
      if (yyin==NULL)
	{
	  perror(infile);
	  return errno;
	}
      strcpy(filename,infile);
    }
  linenumber=1;
  thisCodeFile=new CodeFile(NULL);
  if (outfile!=NULL) thisCodeFile->SetOutputName(outfile);

  insideClass=false;
  othercodes.SetSize(0);
  startPos=-1;

  int ret=yyparse();
  if (ret==0)
    {
      FILE *outf;
      if (outfile==NULL || *outfile=='-') outf=stdout;
      else 
	{
	  outf=fopen(outfile,"wt");
	  if (outf==NULL)
	    {
	      ret=errno;
	      perror(outfile);
	    }
	}
      if (outf!=NULL)
	{
	  CArrayChar output(0,32000);
	  thisCodeFile->GenerateCode(output, client, broker);
	  fwrite((char *)output,1, output.GetSize(),outf);
	}
      if (outf!=stdout) fclose(outf);
    }
  
  othercodes.SetSize(0);

  if (yyin!=stdin) fclose(yyin);
  delete thisCodeFile;
  thisCodeFile=NULL;
  return ret;
}


/* ---- SET normal C++ function return attributes ----- */
void setReturnParam(int pointer, int ref, int const_virtual)
{
	//Old data:  argument_type function_name 
	strcpy(method->returnparam.name,"_RemoteRet");

	DataType *type=returntype;
	if (pointer>0)
	{
		//type=new TypePtr(NULL, pointer, type);
		type=new TypePtr(NULL, pointer, type, constPointerPositions);
		thisCodeFile->AddDataType(type);
		
		constPointerPositions.clear(); // empty used struct
	}

	if (ref)
	{
		method->returnparam.isRef=true;
	}
	
	method->isVirtual=((const_virtual & 1)!=0);
	method->returnparam.isConst = ((const_virtual & 2)!=0);
	
	method->returnparam.SetType(type);
	
}

/* ---- POPC methode attributes ---- */
void setPOPCMethodeModifier(int settings)
{
	
	// TEST Mutex, prallel, seq or CONC (hinden ??)
	if ((settings & 56)==8) 
		method->isConcurrent=true;
	else if ((settings & 56)==32) 
		method->isConcurrent=false;
	else if ((settings & 56)==16)
		method->isMutex= true;
	else if ((settings & 56)!=0)
	{
		errormsg("Methode can only have one conc, mutex or seq attribute !");
		exit(1);
	}
	
	if ((settings & 64)!=0)
		method->isHidden=true;
	
	// TEST SYNC or ASYNC
	if ((settings & 6)==6) 
	{
		errormsg("Methode can not by sync and async at same time!");
		exit(1);
	}
	else if ((settings & 6)==4) method->invoketype=invokeasync;
	else if ((settings & 6)==2) method->invoketype=invokesync;
	//else method->invoketype=autoselect;
}

void errorGlobalMehtode(bool isGlobal)
{
	if(isGlobal)
	{
		errormsg("inspecotrs/const member functions are not allowed in POP-C++");
		exit(1);
	}
	else
	{
		return;
	}
}


