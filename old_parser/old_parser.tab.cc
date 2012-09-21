
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"


//Declaration in parser.lex:

int  PutToken(char *str);
int PutToken(char chr);
char *GetToken(int yyval);

void errormsg(const  char *s);
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


/* Line 189 of yacc.c  */
#line 172 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
	INCLUDE = 283,
	DIRECTIVE = 284,
	OD = 285,
	AUTO_KEYWORD = 286,
	REGISTER_KEYWORD = 287,
	VOLATILE_KEYWORD = 288,
	PACK_KEYWORD = 289,
	AND_OP = 290,
	OR_OP = 291,
	EQUAL_OP = 292,
	NOTEQUAL_OP = 293,
	GREATEREQUAL_OP = 294,
	LESSEQUAL_OP = 295,
	NONSTRICT_OD_OP = 296,
	EOFCODE = 297,
	SCOPE = 298,
	UMINUS = 299
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
#define INCLUDE 283
#define DIRECTIVE 284
#define OD 285
#define AUTO_KEYWORD 286
#define REGISTER_KEYWORD 287
#define VOLATILE_KEYWORD 288
#define PACK_KEYWORD 289
#define AND_OP 290
#define OR_OP 291
#define EQUAL_OP 292
#define NOTEQUAL_OP 293
#define GREATEREQUAL_OP 294
#define LESSEQUAL_OP 295
#define NONSTRICT_OD_OP 296
#define EOFCODE 297
#define SCOPE 298
#define UMINUS 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 302 "parser.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
int yyi;
#endif
{
	return yyi;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   533

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNRULES -- Number of states.  */
#define YYNSTATES  362

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
	0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,    53,     2,     2,     2,    48,    49,     2,
	60,    63,    46,    44,    64,    45,    69,    47,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,    57,    61,
	56,    54,    55,    58,    68,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,    66,     2,    67,    51,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	2,     2,     2,    65,    50,    62,    52,     2,     2,     2,
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
	35,    36,    37,    38,    39,    40,    41,    42,    43,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
	0,     0,     3,     4,     5,     9,    12,    15,    18,    21,
	24,    27,    30,    33,    38,    40,    43,    44,    47,    49,
	51,    53,    58,    61,    64,    66,    67,    71,    74,    79,
	80,    83,    89,    96,   103,   109,   115,   118,   121,   122,
	125,   127,   131,   133,   136,   140,   144,   147,   153,   157,
	160,   161,   164,   166,   170,   172,   175,   179,   183,   185,
	187,   189,   190,   193,   194,   197,   198,   203,   206,   209,
	211,   217,   220,   222,   226,   231,   232,   237,   240,   242,
	244,   246,   248,   250,   255,   257,   260,   262,   266,   271,
	272,   275,   276,   278,   280,   282,   285,   286,   289,   295,
	297,   302,   308,   310,   318,   327,   328,   340,   341,   354,
	356,   359,   361,   363,   365,   367,   369,   371,   373,   375,
	376,   381,   382,   393,   402,   409,   410,   413,   414,   416,
	418,   422,   431,   432,   436,   438,   442,   444,   446,   450,
	454,   455,   457,   459,   460,   462,   463,   466,   469,   471,
	473,   477,   481,   485,   489,   493,   497,   501,   505,   509,
	513,   517,   521,   527,   531,   535,   539,   543,   547,   550,
	554,   558,   563,   566,   569,   572,   575,   577,   579,   581,
	585,   587
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
	71,     0,    -1,    -1,    -1,    92,    72,    71,    -1,    91,
	71,    -1,    29,    71,    -1,    74,    71,    -1,    78,    71,
	-1,    73,    71,    -1,     1,    61,    -1,     1,    62,    -1,
	1,    42,    -1,    75,    60,    76,    63,    -1,    34,    -1,
	6,    77,    -1,    -1,    64,    76,    -1,    79,    -1,    85,
	-1,    86,    -1,    80,    65,    81,    62,    -1,    80,    73,
	-1,    16,     6,    -1,    16,    -1,    -1,    82,    61,    81,
	-1,   107,    83,    -1,   112,     6,   106,    84,    -1,    -1,
	64,    83,    -1,    17,     6,   112,     6,   106,    -1,    17,
	16,     6,   112,     6,   106,    -1,    17,     4,     6,   112,
	6,   106,    -1,    17,    79,   112,     6,   106,    -1,    87,
	88,    65,     1,    62,    -1,    87,    61,    -1,     4,     6,
	-1,    -1,    57,    89,    -1,    90,    -1,    89,    64,    90,
	-1,     6,    -1,    98,     6,    -1,    14,    98,     6,    -1,
	98,    14,     6,    -1,    94,    61,    -1,    93,    65,   100,
	62,    61,    -1,    94,    99,    95,    -1,     3,     6,    -1,
	-1,    57,    96,    -1,    97,    -1,    96,    64,    97,    -1,
	6,    -1,    98,     6,    -1,    14,    98,     6,    -1,    98,
	14,     6,    -1,    13,    -1,    11,    -1,    12,    -1,    -1,
	54,     8,    -1,    -1,   102,   100,    -1,    -1,    98,   101,
	57,   100,    -1,   114,    61,    -1,   103,    61,    -1,    29,
	-1,     5,    60,     8,    63,    61,    -1,   107,   104,    -1,
	105,    -1,   105,    64,   104,    -1,   112,   113,     6,   106,
	-1,    -1,    66,   138,    67,   106,    -1,   108,   109,    -1,
	109,    -1,    31,    -1,    32,    -1,     6,    -1,     7,    -1,
	6,    56,   110,    55,    -1,    79,    -1,    16,     6,    -1,
	111,    -1,   111,    64,   110,    -1,   109,   112,   106,   113,
	-1,    -1,    46,   112,    -1,    -1,    49,    -1,   116,    -1,
	118,    -1,   120,   115,    -1,    -1,    54,     8,    -1,   117,
	60,   129,    63,   126,    -1,     6,    -1,    52,   119,    60,
	63,    -1,    14,    52,   119,    60,    63,    -1,     6,    -1,
	107,   112,   113,   125,    60,   129,    63,    -1,   123,   107,
	112,   113,   125,    60,   129,    63,    -1,    -1,    66,   133,
	67,   107,   112,   113,   125,   121,    60,   129,    63,    -1,
	-1,   123,    66,   133,    67,   107,   112,   113,   125,   122,
	60,   129,    63,    -1,   124,    -1,   123,   124,    -1,    14,
	-1,    18,    -1,    19,    -1,    22,    -1,    23,    -1,    24,
	-1,    25,    -1,     6,    -1,    -1,    68,    65,   127,    62,
	-1,    -1,     6,    69,     6,    60,   138,    64,   138,    63,
	61,   127,    -1,     6,    69,     6,    60,   138,    63,    61,
	127,    -1,     6,    54,   138,   128,    61,   127,    -1,    -1,
	41,   138,    -1,    -1,   130,    -1,   131,    -1,   131,    64,
	130,    -1,   132,   135,   107,   112,   113,   136,   106,   137,
	-1,    -1,    66,   133,    67,    -1,   134,    -1,   134,    64,
	133,    -1,    20,    -1,    21,    -1,    27,    54,   138,    -1,
	26,    54,     6,    -1,    -1,    15,    -1,    33,    -1,    -1,
	6,    -1,    -1,    54,   138,    -1,   140,   106,    -1,   139,
	-1,    10,    -1,   138,    44,   138,    -1,   138,    45,   138,
	-1,   138,    46,   138,    -1,   138,    47,   138,    -1,   138,
	48,   138,    -1,   138,    49,   138,    -1,   138,    50,   138,
	-1,   138,    51,   138,    -1,   138,    35,   138,    -1,   138,
	36,   138,    -1,   138,    37,   138,    -1,   138,    54,   138,
	-1,   138,    58,   138,    57,   138,    -1,   138,    38,   138,
	-1,   138,    55,   138,    -1,   138,    56,   138,    -1,   138,
	39,   138,    -1,   138,    40,   138,    -1,    45,   138,    -1,
	60,   138,    63,    -1,   140,    60,    63,    -1,   140,    60,
	141,    63,    -1,    46,   138,    -1,    49,   138,    -1,    53,
	138,    -1,    52,   138,    -1,     8,    -1,     9,    -1,     6,
	-1,     6,    43,     6,    -1,   138,    -1,   141,    64,   138,
	-1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
	0,   116,   116,   126,   126,   127,   128,   129,   130,   131,
	137,   150,   163,   179,   190,   208,   218,   220,   228,   232,
	233,   240,   246,   252,   279,   288,   289,   291,   294,   314,
	315,   324,   346,   368,   390,   413,   417,   419,   440,   441,
	445,   446,   449,   473,   498,   523,   553,   574,   582,   592,
	617,   618,   621,   622,   625,   639,   654,   671,   690,   694,
	698,   706,   709,   718,   719,   720,   720,   723,   739,   750,
	755,   765,   767,   768,   771,   802,   805,   820,   824,   830,
	834,   840,   855,   871,   890,   896,   909,   916,   925,   984,
	988,   995,   998,  1010,  1011,  1012,  1015,  1016,  1022,  1038,
	1047,  1056,  1069,  1078,  1097,  1126,  1126,  1143,  1143,  1174,
	1178,  1184,  1188,  1192,  1196,  1200,  1204,  1208,  1214,  1226,
	1229,  1236,  1239,  1255,  1270,  1345,  1348,  1356,  1357,  1359,
	1360,  1363,  1398,  1401,  1407,  1411,  1417,  1421,  1425,  1430,
	1439,  1442,  1446,  1453,  1456,  1463,  1466,  1479,  1488,  1492,
	1496,  1501,  1506,  1511,  1516,  1521,  1526,  1531,  1536,  1541,
	1546,  1551,  1556,  1561,  1566,  1571,  1576,  1581,  1586,  1591,
	1596,  1601,  1607,  1612,  1617,  1622,  1629,  1633,  1639,  1643,
	1651,  1655
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
	"HIDDEN", "PROC", "SIZE", "INCLUDE", "DIRECTIVE", "OD", "AUTO_KEYWORD",
	"REGISTER_KEYWORD", "VOLATILE_KEYWORD", "PACK_KEYWORD", "AND_OP",
	"OR_OP", "EQUAL_OP", "NOTEQUAL_OP", "GREATEREQUAL_OP", "LESSEQUAL_OP",
	"NONSTRICT_OD_OP", "EOFCODE", "SCOPE", "'+'", "'-'", "'*'", "'/'", "'%'",
	"'&'", "'|'", "'^'", "'~'", "'!'", "'='", "'>'", "'<'", "':'", "'?'",
	"UMINUS", "'('", "';'", "'}'", "')'", "','", "'{'", "'['", "']'", "'@'",
	"'.'", "$accept", "startlist", "$@1", "not_care_code", "pack_directive",
	"pack_header", "object_list", "rest_object_list", "type_definition",
	"struct_definition", "struct_head", "struct_body", "struct_element",
	"struct_elname_list", "struct_elname_other", "typedef_definition",
	"seqclass_definition", "seqclass_header", "seqbase_spec", "seqbase_list",
	"seqbase_specifier", "class_prototype", "class_declaration",
	"class_head", "class_key", "base_spec", "base_list", "base_specifier",
	"access_specifier", "pure_class_decl", "member_list", "$@2",
	"member_declaration", "attribute_definition", "attribute_name_list",
	"attribute_name", "array_declarator", "decl_specifier",
	"storage_class_specifier", "type_specifier", "template_arguments",
	"template_arg", "pointer_specifier", "ref_specifier",
	"function_definition", "pure_virtual_decl", "constructor_definition",
	"constructor_name", "destructor_definition", "destructor_name",
	"method_definition", "$@3", "$@4", "fct_specifier", "fct_spec",
	"function_name", "od_specifier", "od_exprlist", "od_expr_nonstrict",
	"argument_declaration", "argument_list", "arg_declaration",
	"marshal_decl", "marshal_opt_list", "marshal_opt", "cv_qualifier",
	"argument_name", "arg_default_value", "expr_decl", "number", "expr_name",
	"expr_list", 0
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
	295,   296,   297,   298,    43,    45,    42,    47,    37,    38,
	124,    94,   126,    33,    61,    62,    60,    58,    63,   299,
	40,    59,   125,    41,    44,   123,    91,    93,    64,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
	0,    70,    71,    72,    71,    71,    71,    71,    71,    71,
	73,    73,    73,    74,    75,    76,    77,    77,    78,    78,
	78,    79,    79,    80,    80,    81,    81,    82,    83,    84,
	84,    85,    85,    85,    85,    86,    86,    87,    88,    88,
	89,    89,    90,    90,    90,    90,    91,    92,    93,    94,
	95,    95,    96,    96,    97,    97,    97,    97,    98,    98,
	98,    99,    99,   100,   100,   101,   100,   102,   102,   102,
	102,   103,   104,   104,   105,   106,   106,   107,   107,   108,
	108,   109,   109,   109,   109,   109,   110,   110,   111,   112,
	112,   113,   113,   114,   114,   114,   115,   115,   116,   117,
	118,   118,   119,   120,   120,   121,   120,   122,   120,   123,
	123,   124,   124,   124,   124,   124,   124,   124,   125,   126,
	126,   127,   127,   127,   127,   128,   128,   129,   129,   130,
	130,   131,   132,   132,   133,   133,   134,   134,   134,   134,
	135,   135,   135,   136,   136,   137,   137,   138,   138,   138,
	138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
	138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
	138,   138,   138,   138,   138,   138,   139,   139,   140,   140,
	141,   141
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
	0,     2,     0,     0,     3,     2,     2,     2,     2,     2,
	2,     2,     2,     4,     1,     2,     0,     2,     1,     1,
	1,     4,     2,     2,     1,     0,     3,     2,     4,     0,
	2,     5,     6,     6,     5,     5,     2,     2,     0,     2,
	1,     3,     1,     2,     3,     3,     2,     5,     3,     2,
	0,     2,     1,     3,     1,     2,     3,     3,     1,     1,
	1,     0,     2,     0,     2,     0,     4,     2,     2,     1,
	5,     2,     1,     3,     4,     0,     4,     2,     1,     1,
	1,     1,     1,     4,     1,     2,     1,     3,     4,     0,
	2,     0,     1,     1,     1,     2,     0,     2,     5,     1,
	4,     5,     1,     7,     8,     0,    11,     0,    12,     1,
	2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
	4,     0,    10,     8,     6,     0,     2,     0,     1,     1,
	3,     8,     0,     3,     1,     3,     1,     1,     3,     3,
	0,     1,     1,     0,     1,     0,     2,     2,     1,     1,
	3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	3,     3,     5,     3,     3,     3,     3,     3,     2,     3,
	3,     4,     2,     2,     2,     2,     1,     1,     1,     3,
	1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
	0,     0,     0,     0,    24,     0,     0,    14,     0,     0,
	0,     0,     0,    18,     0,    19,    20,    38,     0,     3,
	0,    61,    12,    10,    11,    49,    37,    23,     0,    89,
	24,    89,     6,     1,     9,     7,     0,     8,    25,    22,
	0,    36,     0,     5,     0,    63,     0,    46,    50,    89,
	89,     0,    23,     0,    16,     0,    81,    82,    24,    79,
	80,    84,     0,     0,    89,     0,    78,    42,    59,    60,
	58,     0,    39,    40,     0,     0,     4,     0,    81,   111,
	112,   113,   114,   115,   116,   117,    69,     0,     0,    65,
	0,    63,     0,    89,     0,    93,     0,    94,    96,     0,
	109,    62,     0,    48,     0,    90,    75,     0,    75,     0,
	15,    13,     0,    85,    21,    25,    27,     0,    77,     0,
	0,    43,     0,     0,     0,     0,   102,     0,   136,   137,
	0,     0,     0,   134,     0,     0,    64,    68,    71,    72,
	91,    67,   132,     0,    95,   111,     0,    89,   110,    54,
	0,    51,    52,     0,    75,     0,    31,    75,    34,    17,
	89,     0,    86,    26,    75,    44,    41,    45,    35,     0,
	0,     0,     0,     0,     0,     0,    63,    47,    89,    92,
	0,     0,     0,   128,   129,   140,    97,     0,    91,     0,
	0,    55,     0,    33,   178,   176,   177,   149,     0,     0,
	0,     0,     0,     0,     0,   148,    75,    32,    75,    83,
	0,    29,     0,     0,   100,   139,   138,    89,   135,    66,
	73,    91,    75,     0,     0,   119,   132,   141,   142,     0,
	0,     0,    56,    53,    57,     0,   168,   172,   173,   175,
	174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	75,     0,   147,    91,    87,    89,    28,    70,   101,    91,
	0,    74,   132,   133,     0,    98,   130,    89,    89,   118,
	0,   179,   169,   158,   159,   160,   163,   166,   167,   150,
	151,   152,   153,   154,   155,   156,   157,   161,   164,   165,
	0,    76,   170,   180,     0,    88,    30,     0,    75,     0,
	121,    91,    91,   132,     0,   171,     0,   105,   103,     0,
	0,   143,     0,     0,   162,   181,     0,     0,     0,   120,
	144,    75,   107,   104,   132,   125,     0,   145,     0,     0,
	0,     0,     0,     0,   131,   132,   106,   126,   121,     0,
	146,     0,   124,     0,     0,   108,   121,     0,   123,     0,
	121,   122
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
	-1,     8,    44,     9,    10,    11,    55,   110,    12,    61,
	14,    62,    63,   116,   266,    15,    16,    17,    42,    72,
	73,    18,    19,    20,    21,   103,   151,   152,    89,    48,
	90,   134,    91,    92,   138,   139,   271,    93,    65,    66,
	161,   162,   117,   180,    94,   144,    95,    96,    97,   127,
	98,   326,   338,    99,   100,   223,   275,   320,   341,   182,
	183,   184,   185,   132,   133,   229,   331,   344,   204,   205,
	206,   304
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -272
static const yytype_int16 yypact[] =
{
	91,   -24,    33,    42,    51,    52,    91,  -272,    70,    91,
	91,    37,    91,  -272,     9,  -272,  -272,   -31,    91,  -272,
	54,   -11,  -272,  -272,  -272,  -272,  -272,  -272,   118,    95,
	137,    95,  -272,  -272,  -272,  -272,   138,  -272,    29,  -272,
	115,  -272,    80,  -272,    91,   186,   139,  -272,    89,    95,
	95,   142,     8,   144,    88,    90,   120,  -272,   148,  -272,
	-272,  -272,   116,   119,    95,    56,  -272,  -272,  -272,  -272,
	-272,    98,   113,  -272,    65,   178,  -272,   121,    13,   130,
	-272,  -272,  -272,  -272,  -272,  -272,  -272,   177,    79,  -272,
	122,   186,   125,    95,   126,  -272,   129,  -272,   131,   253,
	-272,  -272,   124,  -272,   184,  -272,   128,   195,   128,   138,
	-272,  -272,    56,    10,  -272,    29,  -272,   197,  -272,   200,
	115,  -272,   201,   150,   205,   177,  -272,   154,  -272,  -272,
	162,   165,   153,   157,   166,   161,  -272,  -272,  -272,   160,
	176,  -272,    76,   219,  -272,  -272,    79,    95,  -272,  -272,
	98,   167,  -272,    74,   128,   255,  -272,   128,  -272,  -272,
	95,   174,   168,  -272,   128,  -272,  -272,  -272,  -272,   170,
	175,   171,   230,   255,    29,    79,   186,  -272,    95,  -272,
	231,    79,   182,  -272,   183,     0,  -272,   172,   176,   240,
	124,  -272,   244,  -272,   208,  -272,  -272,  -272,   255,   255,
	255,   255,   255,   255,   285,  -272,    16,  -272,   128,  -272,
	56,   189,   194,   199,  -272,  -272,   445,    95,  -272,  -272,
	-272,   176,    36,   198,   203,   206,   207,  -272,  -272,    29,
	29,   260,  -272,  -272,  -272,   275,  -272,   469,   475,   475,
	475,   339,   255,   255,   255,   255,   255,   255,   255,   255,
	255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	128,   234,  -272,   176,  -272,    95,  -272,  -272,  -272,   176,
	276,  -272,    76,  -272,   223,  -272,  -272,    95,    95,  -272,
	229,  -272,  -272,   232,   232,   232,   232,   232,   232,   469,
	469,   469,   469,   469,   475,   475,   475,   475,   232,   232,
	397,  -272,  -272,   445,    59,  -272,  -272,   260,   128,   228,
	286,   176,   176,    76,   255,  -272,   255,  -272,  -272,   -25,
	233,   287,   260,   235,  -272,   445,   236,   255,   293,  -272,
	-272,   128,  -272,  -272,    76,   421,   242,   249,   245,   243,
	255,   248,   255,   255,  -272,    76,  -272,   445,   286,   309,
	445,   247,  -272,   250,   255,  -272,   286,   368,  -272,   251,
	286,  -272
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
	-272,     7,  -272,   299,  -272,  -272,   209,  -272,  -272,    22,
	-272,   202,  -272,    49,  -272,  -272,  -272,  -272,  -272,  -272,
	196,  -272,  -272,  -272,  -272,  -272,  -272,   136,   -16,  -272,
	-83,  -272,  -272,  -272,   149,  -272,  -105,   -34,  -272,   -59,
	127,  -272,   -29,  -179,  -272,  -272,  -272,  -272,  -272,   213,
	-272,  -272,  -272,  -272,   252,  -224,  -272,  -271,  -272,  -267,
	102,  -272,  -272,  -134,  -272,  -272,  -272,  -272,   -86,  -272,
	-272,  -272
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -128
static const yytype_int16 yytable[] =
{
	51,   156,    53,   158,    64,   309,   118,   280,   136,   231,
	1,   -23,   187,    32,   -89,   227,    34,    35,    22,    37,
	104,   105,    13,   107,    74,    43,    40,    31,    13,   327,
	41,    13,    13,   228,    13,    56,    57,    23,    24,    25,
	13,   218,   270,    46,   328,    58,   323,   224,    26,   193,
	47,    76,   207,   160,    50,   119,    28,    27,    29,   211,
	59,    60,    56,    57,   140,   147,    13,   339,    30,   112,
	33,   121,    58,   -99,    38,   -23,   261,   352,   351,   122,
	191,    64,   155,   317,   305,   358,   153,   216,   192,   361,
	307,    -2,     1,   219,     2,     3,  -118,    36,   332,   128,
	129,   262,   155,   263,    74,   130,   131,     4,     5,    68,
	69,    70,   236,   237,   238,   239,   240,   241,   188,    45,
	6,    67,   315,   316,    49,     7,    68,    69,    70,    71,
	149,   208,   321,   322,   189,    68,    69,    70,   150,  -127,
	217,    50,   181,    52,    54,    75,   102,   101,   106,   221,
	108,   160,   109,   111,   113,   301,   283,   284,   285,   286,
	287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
	297,   298,   299,   300,   153,   303,   112,   120,   114,   123,
	115,   124,   125,   126,   135,   143,   137,   141,   269,   142,
	154,    77,    78,    57,   155,   277,   278,    68,    69,    70,
	79,   157,    58,   164,    80,    81,   165,   167,    82,    83,
	84,    85,   168,   169,   171,    86,   172,    59,    60,   173,
	174,   175,   177,   176,   178,   179,   337,   186,   324,   209,
	325,   190,   210,   212,   214,   213,   215,   222,    87,   230,
	194,   335,   195,   196,   197,   225,   232,   226,   311,   312,
	234,   235,    88,   265,   347,   267,   349,   350,   272,    56,
	57,   194,   268,   195,   196,   197,   279,   145,   357,    58,
	273,    80,    81,   181,   274,    82,    83,    84,    85,   198,
	199,   281,   308,   200,    59,    60,   201,   202,   310,   313,
	259,   318,   319,   330,   203,   329,   334,   302,   333,   336,
	198,   199,   342,   343,   200,   345,   346,   201,   202,   348,
	355,   356,   360,    39,   306,   203,   166,   163,   159,   146,
	242,   243,   244,   245,   246,   247,   233,   220,   276,   248,
	249,   250,   251,   252,   253,   254,   255,   264,   170,   256,
	257,   258,     0,   259,   242,   243,   244,   245,   246,   247,
	0,   148,   260,   248,   249,   250,   251,   252,   253,   254,
	255,     0,     0,   256,   257,   258,     0,   259,     0,     0,
	0,     0,   353,   354,   242,   243,   244,   245,   246,   247,
	0,     0,     0,   248,   249,   250,   251,   252,   253,   254,
	255,     0,     0,   256,   257,   258,     0,   259,     0,     0,
	0,     0,   282,   242,   243,   244,   245,   246,   247,     0,
	0,     0,   248,   249,   250,   251,   252,   253,   254,   255,
	0,     0,   256,   257,   258,     0,   259,     0,     0,     0,
	0,   359,   242,   243,   244,   245,   246,   247,     0,     0,
	0,   248,   249,   250,   251,   252,   253,   254,   255,     0,
	0,   256,   257,   258,   314,   259,   242,   243,   244,   245,
	246,   247,   340,     0,     0,   248,   249,   250,   251,   252,
	253,   254,   255,     0,     0,   256,   257,   258,     0,   259,
	242,   243,   244,   245,   246,   247,     0,     0,     0,   248,
	249,   250,   251,   252,   253,   254,   255,     0,     0,   256,
	257,   258,     0,   259,   242,   243,   244,   245,   246,   247,
	242,   243,   244,   245,   246,   247,     0,     0,   253,   254,
	255,     0,     0,   256,   257,   258,     0,   259,     0,     0,
	257,   258,     0,   259
};

static const yytype_int16 yycheck[] =
{
	29,   106,    31,   108,    38,   272,    65,   231,    91,   188,
	1,     1,   146,     6,     6,    15,     9,    10,    42,    12,
	49,    50,     0,    52,    40,    18,    57,     5,     6,    54,
	61,     9,    10,    33,    12,     6,     7,    61,    62,     6,
	18,   175,   221,    54,    69,    16,   313,   181,     6,   154,
	61,    44,   157,   112,    46,    71,     4,     6,     6,   164,
	31,    32,     6,     7,    93,    99,    44,   334,    16,    56,
	0,     6,    16,    60,    65,    65,    60,   348,   345,    14,
	6,   115,    66,   307,   263,   356,   102,   173,    14,   360,
	269,     0,     1,   176,     3,     4,    60,    60,   322,    20,
	21,   206,    66,   208,   120,    26,    27,    16,    17,    11,
	12,    13,   198,   199,   200,   201,   202,   203,   147,    65,
	29,     6,    63,    64,     6,    34,    11,    12,    13,    14,
	6,   160,   311,   312,   150,    11,    12,    13,    14,    63,
	174,    46,    66,     6,     6,    65,    57,     8,     6,   178,
	6,   210,    64,    63,     6,   260,   242,   243,   244,   245,
	246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
	256,   257,   258,   259,   190,   261,    56,    64,    62,     1,
	61,    60,    52,     6,    62,    54,    61,    61,   217,    60,
	6,     5,     6,     7,    66,   229,   230,    11,    12,    13,
	14,     6,    16,     6,    18,    19,     6,     6,    22,    23,
	24,    25,    62,     8,    60,    29,    54,    31,    32,    54,
	67,    64,    61,    57,    64,    49,   331,     8,   314,    55,
	316,    64,    64,    63,    63,    60,     6,     6,    52,    67,
	6,   327,     8,     9,    10,    63,     6,    64,   277,   278,
	6,    43,    66,    64,   340,    61,   342,   343,    60,     6,
	7,     6,    63,     8,     9,    10,     6,    14,   354,    16,
	67,    18,    19,    66,    68,    22,    23,    24,    25,    45,
	46,     6,     6,    49,    31,    32,    52,    53,    65,    60,
	58,    63,     6,     6,    60,    62,    60,    63,    63,     6,
	45,    46,    60,    54,    49,    60,    63,    52,    53,    61,
	63,    61,    61,    14,   265,    60,   120,   115,   109,    66,
	35,    36,    37,    38,    39,    40,   190,   178,   226,    44,
	45,    46,    47,    48,    49,    50,    51,   210,   125,    54,
	55,    56,    -1,    58,    35,    36,    37,    38,    39,    40,
	-1,    99,    67,    44,    45,    46,    47,    48,    49,    50,
	51,    -1,    -1,    54,    55,    56,    -1,    58,    -1,    -1,
	-1,    -1,    63,    64,    35,    36,    37,    38,    39,    40,
	-1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
	51,    -1,    -1,    54,    55,    56,    -1,    58,    -1,    -1,
	-1,    -1,    63,    35,    36,    37,    38,    39,    40,    -1,
	-1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
	-1,    -1,    54,    55,    56,    -1,    58,    -1,    -1,    -1,
	-1,    63,    35,    36,    37,    38,    39,    40,    -1,    -1,
	-1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
	-1,    54,    55,    56,    57,    58,    35,    36,    37,    38,
	39,    40,    41,    -1,    -1,    44,    45,    46,    47,    48,
	49,    50,    51,    -1,    -1,    54,    55,    56,    -1,    58,
	35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    44,
	45,    46,    47,    48,    49,    50,    51,    -1,    -1,    54,
	55,    56,    -1,    58,    35,    36,    37,    38,    39,    40,
	35,    36,    37,    38,    39,    40,    -1,    -1,    49,    50,
	51,    -1,    -1,    54,    55,    56,    -1,    58,    -1,    -1,
	55,    56,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
	0,     1,     3,     4,    16,    17,    29,    34,    71,    73,
	74,    75,    78,    79,    80,    85,    86,    87,    91,    92,
	93,    94,    42,    61,    62,     6,     6,     6,     4,     6,
	16,    79,    71,     0,    71,    71,    60,    71,    65,    73,
	57,    61,    88,    71,    72,    65,    54,    61,    99,     6,
	46,   112,     6,   112,     6,    76,     6,     7,    16,    31,
	32,    79,    81,    82,   107,   108,   109,     6,    11,    12,
	13,    14,    89,    90,    98,    65,    71,     5,     6,    14,
	18,    19,    22,    23,    24,    25,    29,    52,    66,    98,
	100,   102,   103,   107,   114,   116,   117,   118,   120,   123,
	124,     8,    57,    95,   112,   112,     6,   112,     6,    64,
	77,    63,    56,     6,    62,    61,    83,   112,   109,    98,
	64,     6,    14,     1,    60,    52,     6,   119,    20,    21,
	26,    27,   133,   134,   101,    62,   100,    61,   104,   105,
	112,    61,    60,    54,   115,    14,    66,   107,   124,     6,
	14,    96,    97,    98,     6,    66,   106,     6,   106,    76,
	109,   110,   111,    81,     6,     6,    90,     6,    62,     8,
	119,    60,    54,    54,    67,    64,    57,    61,    64,    49,
	113,    66,   129,   130,   131,   132,     8,   133,   112,    98,
	64,     6,    14,   106,     6,     8,     9,    10,    45,    46,
	49,    52,    53,    60,   138,   139,   140,   106,   112,    55,
	64,   106,    63,    60,    63,     6,   138,   107,   133,   100,
	104,   112,     6,   125,   133,    63,    64,    15,    33,   135,
	67,   113,     6,    97,     6,    43,   138,   138,   138,   138,
	138,   138,    35,    36,    37,    38,    39,    40,    44,    45,
	46,    47,    48,    49,    50,    51,    54,    55,    56,    58,
	67,    60,   106,   106,   110,    64,    84,    61,    63,   112,
	113,   106,    60,    67,    68,   126,   130,   107,   107,     6,
	125,     6,    63,   138,   138,   138,   138,   138,   138,   138,
	138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
	138,   106,    63,   138,   141,   113,    83,   113,     6,   129,
	65,   112,   112,    60,    57,    63,    64,   125,    63,     6,
	127,   113,   113,   129,   138,   138,   121,    54,    69,    62,
	6,   136,   125,    63,    60,   138,     6,   106,   122,   129,
	41,   128,    60,    54,   137,    60,    63,   138,    61,   138,
	138,   129,   127,    63,    64,    63,    61,   138,   127,    63,
	61,   127
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
yytype_int16 *yybottom;
yytype_int16 *yytop;
#endif
{
	YYFPRINTF (stderr, "Stack now");
	for (; yybottom <= yytop; yybottom++)
	{
		int yybot = *yybottom;
		YYFPRINTF (stderr, " %d", yybot);
	}
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
		YYFPRINTF (stderr, "   $%d = ", yyi + 1);
		yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
						 &(yyvsp[(yyi + 1) - (yynrhs)])
						);
		YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
	/* Number of tokens to shift before error messages enabled.  */
	int yyerrstatus;

	/* The stacks and their tools:
	   `yyss': related to states.
	   `yyvs': related to semantic values.

	   Refer to the stacks thru separate pointers, to allow yyoverflow
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
	int yytoken;
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

	yytoken = 0;
	yyss = yyssa;
	yyvs = yyvsa;
	yystacksize = YYINITDEPTH;

	YYDPRINTF ((stderr, "Starting parse\n"));

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY; /* Cause a token to be read.  */

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
	if (yyn == YYPACT_NINF)
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

	/* Count tokens shifted since error; after three, turn off error
	   status.  */
	if (yyerrstatus)
		yyerrstatus--;

	/* Shift the lookahead token.  */
	YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

	/* Discard the shifted token.  */
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
	case 2:

		/* Line 1455 of yacc.c  */
#line 116 "parser.y"
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

	case 3:

		/* Line 1455 of yacc.c  */
#line 126 "parser.y"
		{ insideClass=false; othercodes.SetSize(0); startPos=-1;}
		break;

	case 9:

		/* Line 1455 of yacc.c  */
#line 132 "parser.y"
		{
			CleanStack();
		}
		break;

	case 10:

		/* Line 1455 of yacc.c  */
#line 138 "parser.y"
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

	case 11:

		/* Line 1455 of yacc.c  */
#line 151 "parser.y"
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

	case 12:

		/* Line 1455 of yacc.c  */
#line 164 "parser.y"
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

	case 13:

		/* Line 1455 of yacc.c  */
#line 180 "parser.y"
		{
			currentPack->SetEndLine(linenumber-1);

			currentPack=NULL;
			othercodes.SetSize(0);
			startPos=-1;

		}
		break;

	case 14:

		/* Line 1455 of yacc.c  */
#line 191 "parser.y"
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

	case 15:

		/* Line 1455 of yacc.c  */
#line 209 "parser.y"
		{
			if (currentPack!=NULL)
			{
				currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
			}
		}
		break;

	case 16:

		/* Line 1455 of yacc.c  */
#line 218 "parser.y"
		{
		}
		break;

	case 17:

		/* Line 1455 of yacc.c  */
#line 221 "parser.y"
		{
		}
		break;

	case 18:

		/* Line 1455 of yacc.c  */
#line 229 "parser.y"
		{
			CleanStack();
		}
		break;

	case 21:

		/* Line 1455 of yacc.c  */
#line 241 "parser.y"
		{
			currentstruct=Pop();
			if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
			(yyval)=(yyvsp[(1) - (4)]);
		}
		break;

	case 22:

		/* Line 1455 of yacc.c  */
#line 247 "parser.y"
		{
			currentstruct=Pop();
			(yyval)=(yyvsp[(1) - (2)]);
		}
		break;

	case 23:

		/* Line 1455 of yacc.c  */
#line 253 "parser.y"
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

	case 24:

		/* Line 1455 of yacc.c  */
#line 280 "parser.y"
		{
			TypeClassStruct *t=new TypeClassStruct(NULL,false);
			thisCodeFile->AddDataType(t);
			Push(t);
			(yyval)=-1;
		}
		break;

	case 28:

		/* Line 1455 of yacc.c  */
#line 295 "parser.y"
		{
			DataType *type1=currenttype;
			if ((yyvsp[(1) - (4)])>0)
			{
				type1=new TypePtr(NULL,(yyvsp[(1) - (4)]), type1);
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

	case 31:

		/* Line 1455 of yacc.c  */
#line 325 "parser.y"
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
				type=new TypePtr(NULL,(yyvsp[(3) - (5)]), type);
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

	case 32:

		/* Line 1455 of yacc.c  */
#line 347 "parser.y"
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
				type=new TypePtr(NULL,(yyvsp[(4) - (6)]), type);
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

	case 33:

		/* Line 1455 of yacc.c  */
#line 369 "parser.y"
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
				type=new TypePtr(NULL,(yyvsp[(4) - (6)]), type);
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

	case 34:

		/* Line 1455 of yacc.c  */
#line 391 "parser.y"
		{
			DataType *type=currentstruct;
			assert(type!=NULL);

			if ((yyvsp[(3) - (5)])>0)
			{
				type=new TypePtr(NULL,(yyvsp[(3) - (5)]), type);
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

	case 35:

		/* Line 1455 of yacc.c  */
#line 414 "parser.y"
		{
			if (seqclass!=NULL) seqclass->SetTypeClass(true);
		}
		break;

	case 37:

		/* Line 1455 of yacc.c  */
#line 420 "parser.y"
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

	case 42:

		/* Line 1455 of yacc.c  */
#line 450 "parser.y"
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

	case 43:

		/* Line 1455 of yacc.c  */
#line 474 "parser.y"
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

	case 44:

		/* Line 1455 of yacc.c  */
#line 499 "parser.y"
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

	case 45:

		/* Line 1455 of yacc.c  */
#line 524 "parser.y"
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

	case 46:

		/* Line 1455 of yacc.c  */
#line 554 "parser.y"
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

	case 47:

		/* Line 1455 of yacc.c  */
#line 575 "parser.y"
		{
			currentClass->SetEndLine(linenumber);
			currentClass=NULL;
			insideClass=false;
		}
		break;

	case 48:

		/* Line 1455 of yacc.c  */
#line 583 "parser.y"
		{
			accessmodifier=PUBLIC;
			if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

			thisCodeFile->AddCodeData(currentClass);
		}
		break;

	case 49:

		/* Line 1455 of yacc.c  */
#line 593 "parser.y"
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

	case 54:

		/* Line 1455 of yacc.c  */
#line 626 "parser.y"
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

	case 55:

		/* Line 1455 of yacc.c  */
#line 640 "parser.y"
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

	case 56:

		/* Line 1455 of yacc.c  */
#line 655 "parser.y"
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

	case 57:

		/* Line 1455 of yacc.c  */
#line 672 "parser.y"
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

	case 58:

		/* Line 1455 of yacc.c  */
#line 691 "parser.y"
		{
			(yyval)=PRIVATE;
		}
		break;

	case 59:

		/* Line 1455 of yacc.c  */
#line 695 "parser.y"
		{
			(yyval)=PUBLIC;
		}
		break;

	case 60:

		/* Line 1455 of yacc.c  */
#line 699 "parser.y"
		{
			(yyval)=PROTECTED;
		}
		break;

	case 61:

		/* Line 1455 of yacc.c  */
#line 706 "parser.y"
		{
			(yyval)=0;
		}
		break;

	case 62:

		/* Line 1455 of yacc.c  */
#line 710 "parser.y"
		{
			(yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
		}
		break;

	case 65:

		/* Line 1455 of yacc.c  */
#line 720 "parser.y"
		{ accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
		break;

	case 67:

		/* Line 1455 of yacc.c  */
#line 724 "parser.y"
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

	case 68:

		/* Line 1455 of yacc.c  */
#line 740 "parser.y"
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

	case 69:

		/* Line 1455 of yacc.c  */
#line 751 "parser.y"
		{
			//  Directive *t=new Directive(currentClass, GetToken($1));
			//  currentClass->AddMember(t);
		}
		break;

	case 70:

		/* Line 1455 of yacc.c  */
#line 756 "parser.y"
		{
			currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
		}
		break;

	case 74:

		/* Line 1455 of yacc.c  */
#line 772 "parser.y"
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
				type=new TypePtr(NULL, (yyvsp[(1) - (4)]) , currenttype);
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

	case 75:

		/* Line 1455 of yacc.c  */
#line 802 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 76:

		/* Line 1455 of yacc.c  */
#line 806 "parser.y"
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

	case 77:

		/* Line 1455 of yacc.c  */
#line 821 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (2)]);
		}
		break;

	case 78:

		/* Line 1455 of yacc.c  */
#line 825 "parser.y"
		{
			(yyval)=0;
		}
		break;

	case 79:

		/* Line 1455 of yacc.c  */
#line 831 "parser.y"
		{
			(yyval)=1;
		}
		break;

	case 80:

		/* Line 1455 of yacc.c  */
#line 835 "parser.y"
		{
			(yyval)=2;
		}
		break;

	case 81:

		/* Line 1455 of yacc.c  */
#line 841 "parser.y"
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

	case 82:

		/* Line 1455 of yacc.c  */
#line 856 "parser.y"
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

	case 83:

		/* Line 1455 of yacc.c  */
#line 872 "parser.y"
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

	case 84:

		/* Line 1455 of yacc.c  */
#line 891 "parser.y"
		{
			assert(currenttype!=NULL);
			currenttype=currentstruct;
			(yyval)=(YYSTYPE)currenttype;
		}
		break;

	case 85:

		/* Line 1455 of yacc.c  */
#line 897 "parser.y"
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

	case 86:

		/* Line 1455 of yacc.c  */
#line 910 "parser.y"
		{
			paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
			TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
			list->AddHead(v);
			(yyval)=(YYSTYPE)list;
		}
		break;

	case 87:

		/* Line 1455 of yacc.c  */
#line 917 "parser.y"
		{
			paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
			TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
			list->AddHead(v);
			(yyval)=(YYSTYPE)list;
		}
		break;

	case 88:

		/* Line 1455 of yacc.c  */
#line 926 "parser.y"
		{
			TemplateArgument *t=new TemplateArgument;
			t->type=(DataType *)(yyvsp[(1) - (4)]);
			if ((yyvsp[(2) - (4)])>0)
			{
				t->type=new TypePtr(NULL,(yyvsp[(2) - (4)]),t->type);
			}
			if ((yyvsp[(3) - (4)])!=-1)
			{
				t->type=new TypeArray(NULL,GetToken((yyvsp[(3) - (4)])), t->type);
			}
			t->isRef=((yyvsp[(4) - (4)])!=0);
			(yyval)=(YYSTYPE)t;

		}
		break;

	case 89:

		/* Line 1455 of yacc.c  */
#line 984 "parser.y"
		{
			(yyval)=0;

		}
		break;

	case 90:

		/* Line 1455 of yacc.c  */
#line 989 "parser.y"
		{
			(yyval)=(yyvsp[(2) - (2)])+1;
		}
		break;

	case 91:

		/* Line 1455 of yacc.c  */
#line 995 "parser.y"
		{
			(yyval)=0;
		}
		break;

	case 92:

		/* Line 1455 of yacc.c  */
#line 999 "parser.y"
		{
			(yyval)=1;
		}
		break;

	case 97:

		/* Line 1455 of yacc.c  */
#line 1017 "parser.y"
		{
			method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
		}
		break;

	case 98:

		/* Line 1455 of yacc.c  */
#line 1023 "parser.y"
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

	case 99:

		/* Line 1455 of yacc.c  */
#line 1039 "parser.y"
		{
			method=new Constructor(currentClass,accessmodifier);
			method->SetLineInfo(linenumber-1);

			strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
		}
		break;

	case 100:

		/* Line 1455 of yacc.c  */
#line 1048 "parser.y"
		{
			if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
			{
				errormsg("Bad declaration of destructor\n");
				exit(1);
			}
			strcpy(method->name,currentClass->GetName());
		}
		break;

	case 101:

		/* Line 1455 of yacc.c  */
#line 1057 "parser.y"
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

	case 102:

		/* Line 1455 of yacc.c  */
#line 1070 "parser.y"
		{
			method=new Destructor(currentClass,accessmodifier);
			method->SetLineInfo(linenumber-1);
			currentClass->AddMember(method);
			strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
		}
		break;

	case 103:

		/* Line 1455 of yacc.c  */
#line 1079 "parser.y"
		{
			//Old data:  argument_type function_name
			strcpy(method->returnparam.name,"_RemoteRet");

			DataType *type=returntype;
			if ((yyvsp[(2) - (7)])>0)
			{
				type=new TypePtr(NULL, (yyvsp[(2) - (7)]) , type);
				thisCodeFile->AddDataType(type);
			}

			if ((yyvsp[(3) - (7)]))
			{
				method->returnparam.isRef=true;
			}
			method->returnparam.SetType(type);

		}
		break;

	case 104:

		/* Line 1455 of yacc.c  */
#line 1098 "parser.y"
		{
			strcpy(method->returnparam.name,"_RemoteRet");

			DataType *type=returntype;
			if ((yyvsp[(3) - (8)])>0)
			{
				type=new TypePtr(NULL, (yyvsp[(3) - (8)]) , type);
				thisCodeFile->AddDataType(type);
			}

			if ((yyvsp[(4) - (8)]))
			{
				method->returnparam.isRef=true;
			}

			method->returnparam.SetType(type);

			method->isVirtual=(((yyvsp[(1) - (8)]) & 1)!=0);
			if (((yyvsp[(1) - (8)]) & 8)!=0) method->isConcurrent=true;
			else if (((yyvsp[(1) - (8)]) & 32)!=0) method->isConcurrent=false;

			method->isHidden=(((yyvsp[(1) - (8)]) & 64)!=0);
			method->isMutex=(((yyvsp[(1) - (8)]) & 16)!=0);

			if (((yyvsp[(1) - (8)]) & 6)==2) method->invoketype=invokesync;
			else if (((yyvsp[(1) - (8)]) & 6)==4) method->invoketype=invokeasync;
			/*	else method->invoketype=autoselect; */
		}
		break;

	case 105:

		/* Line 1455 of yacc.c  */
#line 1126 "parser.y"
		{ UpdateMarshalParam((yyvsp[(2) - (7)]),&(method->returnparam) ); }
		break;

	case 106:

		/* Line 1455 of yacc.c  */
#line 1127 "parser.y"
		{
			DataType *type=returntype;
			if ((yyvsp[(5) - (11)])>0)
			{
				type=new TypePtr(NULL, (yyvsp[(5) - (11)]) , type);
				thisCodeFile->AddDataType(type);
			}

			if ((yyvsp[(6) - (11)]))
			{
				method->returnparam.isRef=true;
			}
			method->returnparam.SetType(type);

			strcpy(method->returnparam.name,"_RemoteRet");
		}
		break;

	case 107:

		/* Line 1455 of yacc.c  */
#line 1143 "parser.y"
		{ UpdateMarshalParam((yyvsp[(3) - (8)]),&(method->returnparam) ); }
		break;

	case 108:

		/* Line 1455 of yacc.c  */
#line 1144 "parser.y"
		{
			strcpy(method->returnparam.name,"_RemoteRet");

			DataType *type=returntype;
			if ((yyvsp[(6) - (12)])>0)
			{
				type=new TypePtr(NULL, (yyvsp[(6) - (12)]) , type);
				thisCodeFile->AddDataType(type);
			}

			if ((yyvsp[(7) - (12)]))
			{
				method->returnparam.isRef=true;
			}
			method->returnparam.SetType(type);

			method->isVirtual=(((yyvsp[(1) - (12)]) & 1)!=0);

			if (((yyvsp[(1) - (12)]) & 8)!=0) method->isConcurrent=true;
			else if (((yyvsp[(1) - (12)]) & 32)!=0) method->isConcurrent=false;

			method->isMutex=(((yyvsp[(1) - (12)]) & 16)!=0);
			method->isHidden=(((yyvsp[(1) - (12)]) & 64)!=0);

			if (((yyvsp[(1) - (12)]) & 6)==2) method->invoketype=invokesync;
			else if (((yyvsp[(1) - (12)]) & 6)==4) method->invoketype=invokeasync;
			/* else method->invoketype=autoselect; */
		}
		break;

	case 109:

		/* Line 1455 of yacc.c  */
#line 1175 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 110:

		/* Line 1455 of yacc.c  */
#line 1179 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (2)]) | (yyvsp[(2) - (2)]);
		}
		break;

	case 111:

		/* Line 1455 of yacc.c  */
#line 1185 "parser.y"
		{
			(yyval)=1;
		}
		break;

	case 112:

		/* Line 1455 of yacc.c  */
#line 1189 "parser.y"
		{
			(yyval)=2;
		}
		break;

	case 113:

		/* Line 1455 of yacc.c  */
#line 1193 "parser.y"
		{
			(yyval)=4;
		}
		break;

	case 114:

		/* Line 1455 of yacc.c  */
#line 1197 "parser.y"
		{
			(yyval)=8;
		}
		break;

	case 115:

		/* Line 1455 of yacc.c  */
#line 1201 "parser.y"
		{
			(yyval)=32;
		}
		break;

	case 116:

		/* Line 1455 of yacc.c  */
#line 1205 "parser.y"
		{
			(yyval)=16;
		}
		break;

	case 117:

		/* Line 1455 of yacc.c  */
#line 1209 "parser.y"
		{
			(yyval)=64;
		}
		break;

	case 118:

		/* Line 1455 of yacc.c  */
#line 1215 "parser.y"
		{
			method=new Method(currentClass,accessmodifier);
			method->SetLineInfo(linenumber-1);
			currentClass->AddMember(method);
			strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
			returntype=currenttype;
			currenttype=NULL;
		}
		break;

	case 119:

		/* Line 1455 of yacc.c  */
#line 1226 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 120:

		/* Line 1455 of yacc.c  */
#line 1230 "parser.y"
		{
			(yyval)=(yyvsp[(3) - (4)]);
		}
		break;

	case 121:

		/* Line 1455 of yacc.c  */
#line 1236 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 122:

		/* Line 1455 of yacc.c  */
#line 1240 "parser.y"
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

	case 123:

		/* Line 1455 of yacc.c  */
#line 1256 "parser.y"
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

	case 124:

		/* Line 1455 of yacc.c  */
#line 1271 "parser.y"
		{
			char *odtmp=GetToken((yyvsp[(1) - (7)]));
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
				if ((yyvsp[(6) - (6)])!=-1) strcat(tmp,GetToken((yyvsp[(6) - (6)])));
			}
			//Added by clementval
			else if (paroc_utils::isEqual(odtmp,"search"))
			{
				sprintf(tmp,"od.search(%s",GetToken((yyvsp[(3) - (7)])));
				if ((yyvsp[(4) - (7)])!=-1)
				{
					strcat(tmp,",");
					strcat(tmp,GetToken((yyvsp[(4) - (7)])));
				}
				if ((yyvsp[(5) - (7)])!=-1)
				{
					strcat(tmp,",");
					strcat(tmp,GetToken((yyvsp[(5) - (7)])));
				}
				strcat(tmp,");");
				if ((yyvsp[(7) - (7)])!=-1) strcat(tmp,GetToken((yyvsp[(7) - (7)])));
			}
			//End of add
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

	case 125:

		/* Line 1455 of yacc.c  */
#line 1345 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 126:

		/* Line 1455 of yacc.c  */
#line 1349 "parser.y"
		{
			(yyval)=(yyvsp[(2) - (2)]);
		}
		break;

	case 131:

		/* Line 1455 of yacc.c  */
#line 1364 "parser.y"
		{
			Param *t=method->AddNewParam();
			UpdateMarshalParam((yyvsp[(1) - (8)]),t);

			DataType *type=currenttype;
			if ((yyvsp[(4) - (8)])>0)
			{
				type=new TypePtr(NULL, (yyvsp[(4) - (8)]) , type);
				thisCodeFile->AddDataType(type);
			}

			if ((yyvsp[(5) - (8)]))
			{
				t->isRef=true;
			}

			if ((yyvsp[(7) - (8)])!=-1)
			{
				type=new TypeArray(NULL, GetToken((yyvsp[(7) - (8)])) , type);
				thisCodeFile->AddDataType(type);
			}

			t->SetType(type);
			if ((yyvsp[(6) - (8)])!=-1) strcpy(t->name,GetToken((yyvsp[(6) - (8)])));
			else   sprintf(t->name,"V_%d",++counter);

			t->isConst=((yyvsp[(2) - (8)])==1);
			if ((yyvsp[(8) - (8)])>=0) t->defaultVal=strdup(GetToken((yyvsp[(8) - (8)])));


		}
		break;

	case 132:

		/* Line 1455 of yacc.c  */
#line 1398 "parser.y"
		{
			(yyval)=0;
		}
		break;

	case 133:

		/* Line 1455 of yacc.c  */
#line 1402 "parser.y"
		{
			(yyval)=(yyvsp[(2) - (3)]);
		}
		break;

	case 134:

		/* Line 1455 of yacc.c  */
#line 1408 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 135:

		/* Line 1455 of yacc.c  */
#line 1412 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
		}
		break;

	case 136:

		/* Line 1455 of yacc.c  */
#line 1418 "parser.y"
		{
			(yyval)=PARAM_IN;
		}
		break;

	case 137:

		/* Line 1455 of yacc.c  */
#line 1422 "parser.y"
		{
			(yyval)=PARAM_OUT;
		}
		break;

	case 138:

		/* Line 1455 of yacc.c  */
#line 1426 "parser.y"
		{
			strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
			(yyval)=PARAMSIZE;
		}
		break;

	case 139:

		/* Line 1455 of yacc.c  */
#line 1431 "parser.y"
		{
			strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
			(yyval)=USERPROC;
		}
		break;

	case 140:

		/* Line 1455 of yacc.c  */
#line 1439 "parser.y"
		{
			(yyval)=0;
		}
		break;

	case 141:

		/* Line 1455 of yacc.c  */
#line 1443 "parser.y"
		{
			(yyval)=1;
		}
		break;

	case 142:

		/* Line 1455 of yacc.c  */
#line 1447 "parser.y"
		{
			(yyval)=2;
		}
		break;

	case 143:

		/* Line 1455 of yacc.c  */
#line 1453 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 144:

		/* Line 1455 of yacc.c  */
#line 1457 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 145:

		/* Line 1455 of yacc.c  */
#line 1463 "parser.y"
		{
			(yyval)=-1;
		}
		break;

	case 146:

		/* Line 1455 of yacc.c  */
#line 1467 "parser.y"
		{
			(yyval)=(yyvsp[(2) - (2)]);
		}
		break;

	case 147:

		/* Line 1455 of yacc.c  */
#line 1480 "parser.y"
		{
			if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
			else
			{
				sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
				(yyval)=PutToken(tmp);
			}
		}
		break;

	case 148:

		/* Line 1455 of yacc.c  */
#line 1489 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 149:

		/* Line 1455 of yacc.c  */
#line 1493 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 150:

		/* Line 1455 of yacc.c  */
#line 1497 "parser.y"
		{
			sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 151:

		/* Line 1455 of yacc.c  */
#line 1502 "parser.y"
		{
			sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 152:

		/* Line 1455 of yacc.c  */
#line 1507 "parser.y"
		{
			sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 153:

		/* Line 1455 of yacc.c  */
#line 1512 "parser.y"
		{
			sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 154:

		/* Line 1455 of yacc.c  */
#line 1517 "parser.y"
		{
			sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 155:

		/* Line 1455 of yacc.c  */
#line 1522 "parser.y"
		{
			sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 156:

		/* Line 1455 of yacc.c  */
#line 1527 "parser.y"
		{
			sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 157:

		/* Line 1455 of yacc.c  */
#line 1532 "parser.y"
		{
			sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 158:

		/* Line 1455 of yacc.c  */
#line 1537 "parser.y"
		{
			sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 159:

		/* Line 1455 of yacc.c  */
#line 1542 "parser.y"
		{
			sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 160:

		/* Line 1455 of yacc.c  */
#line 1547 "parser.y"
		{
			sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 161:

		/* Line 1455 of yacc.c  */
#line 1552 "parser.y"
		{
			sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 162:

		/* Line 1455 of yacc.c  */
#line 1557 "parser.y"
		{
			sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 163:

		/* Line 1455 of yacc.c  */
#line 1562 "parser.y"
		{
			sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 164:

		/* Line 1455 of yacc.c  */
#line 1567 "parser.y"
		{
			sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 165:

		/* Line 1455 of yacc.c  */
#line 1572 "parser.y"
		{
			sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 166:

		/* Line 1455 of yacc.c  */
#line 1577 "parser.y"
		{
			sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 167:

		/* Line 1455 of yacc.c  */
#line 1582 "parser.y"
		{
			sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 168:

		/* Line 1455 of yacc.c  */
#line 1587 "parser.y"
		{
			sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 169:

		/* Line 1455 of yacc.c  */
#line 1592 "parser.y"
		{
			sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 170:

		/* Line 1455 of yacc.c  */
#line 1597 "parser.y"
		{
			sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 171:

		/* Line 1455 of yacc.c  */
#line 1602 "parser.y"
		{
			sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
			(yyval)=PutToken(tmp);

		}
		break;

	case 172:

		/* Line 1455 of yacc.c  */
#line 1608 "parser.y"
		{
			sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 173:

		/* Line 1455 of yacc.c  */
#line 1613 "parser.y"
		{
			sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 174:

		/* Line 1455 of yacc.c  */
#line 1618 "parser.y"
		{
			sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 175:

		/* Line 1455 of yacc.c  */
#line 1623 "parser.y"
		{
			sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 176:

		/* Line 1455 of yacc.c  */
#line 1630 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 177:

		/* Line 1455 of yacc.c  */
#line 1634 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 178:

		/* Line 1455 of yacc.c  */
#line 1640 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 179:

		/* Line 1455 of yacc.c  */
#line 1644 "parser.y"
		{
			sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;

	case 180:

		/* Line 1455 of yacc.c  */
#line 1652 "parser.y"
		{
			(yyval)=(yyvsp[(1) - (1)]);
		}
		break;

	case 181:

		/* Line 1455 of yacc.c  */
#line 1656 "parser.y"
		{
			sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
			(yyval)=PutToken(tmp);
		}
		break;



		/* Line 1455 of yacc.c  */
#line 3903 "parser.tab.c"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 1675 of yacc.c  */
#line 1664 "parser.y"


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



