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
     NAMESPACE = 302,
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
#define NAMESPACE 302
#define UMINUS 303




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <strings.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
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
  
 int PutToken(char *str);
 int PutToken(char chr);
 char *GetToken(int yyval);

 void errormsg(const  char *s);
 void setReturnParam(int pointer, int ref, int const_virtual); // Methode to group code that set C++ specific C++ Param attributes
 void setPOPCMethodeModifier(int settings); // mehtode to group code that set/controlle Methode attributes (sync, conc, ...)
 void errorGlobalMehtode(bool isGlobal);
  
extern "C" {
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
	Structure *structContainer;

	TypeDefinition *typeDefContainer;
	Method *method;
	// Param *param;

 int n,t;
 bool isNamespace = false;
 
 bool isInStruct = false;
 
 bool isParclassDeclared = false;
 
 bool hadParclass = false; 
 
 bool isWarningEnable;
 bool isImplicitPackEnable;
 bool isPOPCPPCompilation; 
 char holdnamespace[500];
 char tmp[10240];
 char typetmp[100];
 char tmpProc[10240];
 char tmpSize[10240];
 int parsingclass=0;

 void UpdateMarshalParam(int flags, Param *t);

 int ParseFile(char *infile, char *outfile, bool client, bool broker, bool isWarningEnable, bool isImplicitPackEnable, bool isPOPCPPCompilation);
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
#line 325 "parser.tab.c"

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
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   687

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNRULES -- Number of states.  */
#define YYNSTATES  445

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
      64,    67,    50,    48,    69,    49,    73,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    65,
      60,    58,    59,    62,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,    54,    66,    56,     2,     2,     2,
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
       0,     0,     3,     6,     7,     9,    10,    14,    17,    20,
      23,    26,    29,    31,    33,    35,    38,    41,    44,    49,
      51,    54,    55,    62,    63,    66,    68,    70,    72,    74,
      79,    82,    85,    87,    88,    92,    95,   100,   101,   104,
     110,   117,   124,   130,   136,   139,   142,   143,   146,   148,
     152,   154,   157,   161,   165,   168,   174,   178,   181,   182,
     185,   187,   191,   193,   196,   200,   204,   206,   208,   210,
     211,   214,   215,   218,   219,   224,   227,   230,   233,   236,
     239,   242,   244,   250,   256,   258,   262,   264,   268,   271,
     273,   277,   282,   283,   286,   291,   294,   296,   298,   300,
     302,   304,   309,   311,   314,   316,   320,   325,   326,   330,
     331,   333,   334,   336,   338,   340,   343,   344,   347,   353,
     355,   360,   366,   368,   377,   387,   397,   408,   420,   421,
     436,   437,   453,   455,   458,   460,   462,   464,   466,   468,
     470,   472,   474,   477,   480,   481,   483,   485,   488,   491,
     493,   494,   499,   500,   513,   524,   533,   540,   541,   544,
     545,   547,   549,   553,   563,   564,   568,   570,   574,   576,
     578,   582,   586,   587,   589,   591,   592,   594,   595,   598,
     601,   603,   605,   609,   613,   617,   621,   625,   629,   633,
     637,   641,   645,   649,   653,   659,   663,   667,   671,   675,
     679,   682,   686,   690,   695,   698,   701,   704,   707,   709,
     711,   713,   717,   719
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    78,    75,    -1,    -1,    83,    -1,    -1,
     101,    76,    75,    -1,   100,    75,    -1,    30,    75,    -1,
      80,    75,    -1,    86,    75,    -1,    79,    75,    -1,    77,
      -1,    43,    -1,    28,    -1,     1,    65,    -1,     1,    66,
      -1,     1,    43,    -1,    81,    64,    82,    67,    -1,    35,
      -1,     6,    85,    -1,    -1,    47,     6,    84,    68,    75,
      66,    -1,    -1,    69,    82,    -1,    88,    -1,    94,    -1,
      95,    -1,     4,    -1,    89,    68,    90,    66,    -1,    89,
      79,    -1,    16,     6,    -1,    16,    -1,    -1,    91,    65,
      90,    -1,   119,    92,    -1,   124,     6,   118,    93,    -1,
      -1,    69,    92,    -1,    17,     6,   124,     6,   118,    -1,
      17,    16,     6,   124,     6,   118,    -1,    17,     4,     6,
     124,     6,   118,    -1,    17,    88,   124,     6,   118,    -1,
      96,    97,    68,     1,    66,    -1,    96,    65,    -1,     4,
       6,    -1,    -1,    61,    98,    -1,    99,    -1,    98,    69,
      99,    -1,     6,    -1,   107,     6,    -1,    14,   107,     6,
      -1,   107,    14,     6,    -1,   103,    65,    -1,   102,    68,
     109,    66,    65,    -1,   103,   108,   104,    -1,     3,     6,
      -1,    -1,    61,   105,    -1,   106,    -1,   105,    69,   106,
      -1,     6,    -1,   107,     6,    -1,    14,   107,     6,    -1,
     107,    14,     6,    -1,    13,    -1,    11,    -1,    12,    -1,
      -1,    58,     8,    -1,    -1,   111,   109,    -1,    -1,   107,
     110,    61,   109,    -1,   112,    65,    -1,    88,    65,    -1,
     127,    65,    -1,    87,    65,    -1,    94,    65,    -1,   115,
      65,    -1,    30,    -1,     5,    64,     8,    67,    65,    -1,
      45,     6,    68,   113,    66,    -1,   114,    -1,   114,    69,
     113,    -1,     6,    -1,     6,    58,     8,    -1,   119,   116,
      -1,   117,    -1,   117,    69,   116,    -1,   124,   126,     6,
     118,    -1,    -1,    70,    71,    -1,    70,   153,    71,   118,
      -1,   120,   121,    -1,   121,    -1,    32,    -1,    33,    -1,
       6,    -1,     7,    -1,     6,    60,   122,    59,    -1,    88,
      -1,    16,     6,    -1,   123,    -1,   123,    69,   122,    -1,
     121,   124,   118,   126,    -1,    -1,    50,   125,   124,    -1,
      -1,    15,    -1,    -1,    53,    -1,   129,    -1,   131,    -1,
     133,   128,    -1,    -1,    58,     8,    -1,   130,    64,   144,
      67,   141,    -1,     6,    -1,    56,   132,    64,    67,    -1,
      14,    56,   132,    64,    67,    -1,     6,    -1,   119,   124,
     126,   140,    64,   144,    67,   125,    -1,   138,   119,   124,
     126,   140,    64,   144,    67,   125,    -1,   119,   138,   124,
     126,   140,    64,   144,    67,   125,    -1,   138,   119,   138,
     124,   126,   140,    64,   144,    67,   125,    -1,   136,   139,
     119,   139,   124,   126,   140,    64,   144,    67,   125,    -1,
      -1,    70,   148,    71,   139,   119,   139,   124,   126,   140,
     134,    64,   144,    67,   125,    -1,    -1,   136,    70,   148,
      71,   139,   119,   139,   124,   126,   140,   135,    64,   144,
      67,   125,    -1,   137,    -1,   136,   137,    -1,    18,    -1,
      19,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      14,    -1,    15,    -1,    15,    14,    -1,    14,    15,    -1,
      -1,    14,    -1,    15,    -1,    15,    14,    -1,    14,    15,
      -1,     6,    -1,    -1,    72,    68,   142,    66,    -1,    -1,
       6,    73,     6,    64,   153,    69,   153,    69,   153,    67,
      65,   142,    -1,     6,    73,     6,    64,   153,    69,   153,
      67,    65,   142,    -1,     6,    73,     6,    64,   153,    67,
      65,   142,    -1,     6,    58,   153,   143,    65,   142,    -1,
      -1,    42,   153,    -1,    -1,   145,    -1,   146,    -1,   146,
      69,   145,    -1,   147,   150,   119,   150,   124,   126,   151,
     118,   152,    -1,    -1,    70,   148,    71,    -1,   149,    -1,
     149,    69,   148,    -1,    20,    -1,    21,    -1,    27,    58,
     153,    -1,    26,    58,     6,    -1,    -1,    15,    -1,    34,
      -1,    -1,     6,    -1,    -1,    58,   153,    -1,   155,   118,
      -1,   154,    -1,    10,    -1,   153,    48,   153,    -1,   153,
      49,   153,    -1,   153,    50,   153,    -1,   153,    51,   153,
      -1,   153,    52,   153,    -1,   153,    53,   153,    -1,   153,
      54,   153,    -1,   153,    55,   153,    -1,   153,    36,   153,
      -1,   153,    37,   153,    -1,   153,    38,   153,    -1,   153,
      58,   153,    -1,   153,    62,   153,    61,   153,    -1,   153,
      39,   153,    -1,   153,    59,   153,    -1,   153,    60,   153,
      -1,   153,    40,   153,    -1,   153,    41,   153,    -1,    49,
     153,    -1,    64,   153,    67,    -1,   155,    64,    67,    -1,
     155,    64,   156,    67,    -1,    50,   153,    -1,    53,   153,
      -1,    57,   153,    -1,    56,   153,    -1,     8,    -1,     9,
      -1,     6,    -1,     6,    44,     6,    -1,   153,    -1,   156,
      69,   153,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   142,   142,   144,   154,   156,   155,   161,   162,   163,
     164,   165,   169,   172,   270,   278,   291,   304,   320,   330,
     347,   359,   357,   383,   385,   393,   397,   398,   409,   426,
     434,   440,   477,   486,   487,   490,   493,   521,   522,   531,
     573,   603,   627,   658,   662,   664,   685,   686,   690,   691,
     694,   718,   743,   768,   798,   819,   827,   836,   867,   868,
     871,   872,   875,   889,   904,   921,   940,   944,   948,   956,
     959,   968,   969,   970,   970,   974,   975,   976,   977,   977,
     993,  1004,  1009,  1020,  1031,  1035,  1042,  1046,  1057,  1059,
    1060,  1063,  1095,  1098,  1102,  1114,  1118,  1126,  1130,  1136,
    1147,  1163,  1182,  1188,  1201,  1208,  1217,  1290,  1294,  1303,
    1306,  1313,  1316,  1326,  1327,  1328,  1331,  1332,  1338,  1354,
    1363,  1372,  1385,  1515,  1522,  1529,  1536,  1543,  1551,  1551,
    1558,  1558,  1568,  1572,  1618,  1622,  1626,  1630,  1634,  1638,
    1645,  1649,  1653,  1657,  1665,  1668,  1672,  1676,  1680,  1686,
    1698,  1701,  1708,  1712,  1729,  1745,  1760,  1853,  1856,  1864,
    1865,  1867,  1868,  1871,  1935,  1938,  1944,  1948,  1954,  1958,
    1962,  1967,  1976,  1979,  1983,  1990,  1993,  2000,  2003,  2016,
    2025,  2029,  2033,  2038,  2043,  2048,  2053,  2058,  2063,  2068,
    2073,  2078,  2083,  2088,  2093,  2098,  2103,  2108,  2113,  2118,
    2123,  2128,  2133,  2138,  2144,  2149,  2154,  2159,  2166,  2170,
    2176,  2180,  2188,  2192
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
  "NAMESPACE", "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'|'", "'^'",
  "'~'", "'!'", "'='", "'>'", "'<'", "':'", "'?'", "UMINUS", "'('", "';'",
  "'}'", "')'", "'{'", "','", "'['", "']'", "'@'", "'.'", "$accept",
  "startlist", "@1", "handle_eof", "handle_this", "not_care_code",
  "pack_directive", "pack_header", "object_list", "namespace_declaration",
  "@2", "rest_object_list", "type_definition", "innerclass_definition",
  "struct_definition", "struct_head", "struct_body", "struct_element",
  "struct_elname_list", "struct_elname_other", "typedef_definition",
  "seqclass_definition", "seqclass_header", "seqbase_spec", "seqbase_list",
  "seqbase_specifier", "class_prototype", "class_declaration",
  "class_head", "class_key", "base_spec", "base_list", "base_specifier",
  "access_specifier", "pure_class_decl", "member_list", "@3",
  "member_declaration", "enum_declaration", "enum_members", "enum_member",
  "attribute_definition", "attribute_name_list", "attribute_name",
  "array_declarator", "decl_specifier", "storage_class_specifier",
  "type_specifier", "template_arguments", "template_arg",
  "pointer_specifier", "const_specifier", "ref_specifier",
  "function_definition", "pure_virtual_decl", "constructor_definition",
  "constructor_name", "destructor_definition", "destructor_name",
  "method_definition", "@4", "@5", "fct_specifier", "fct_spec",
  "const_virutal_specifier", "const_virutal_empty_specifier",
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
     295,   296,   297,   298,   299,   300,   301,   302,    43,    45,
      42,    47,    37,    38,   124,    94,   126,    33,    61,    62,
      60,    58,    63,   303,    40,    59,   125,    41,   123,    44,
      91,    93,    64,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    76,    75,    75,    75,    75,
      75,    75,    75,    77,    78,    79,    79,    79,    80,    81,
      82,    84,    83,    85,    85,    86,    86,    86,    87,    88,
      88,    89,    89,    90,    90,    91,    92,    93,    93,    94,
      94,    94,    94,    95,    95,    96,    97,    97,    98,    98,
      99,    99,    99,    99,   100,   101,   102,   103,   104,   104,
     105,   105,   106,   106,   106,   106,   107,   107,   107,   108,
     108,   109,   109,   110,   109,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   113,   113,   114,   114,   115,   116,
     116,   117,   118,   118,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   121,   122,   122,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   128,   128,   129,   130,
     131,   131,   132,   133,   133,   133,   133,   133,   134,   133,
     135,   133,   136,   136,   137,   137,   137,   137,   137,   137,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   140,
     141,   141,   142,   142,   142,   142,   142,   143,   143,   144,
     144,   145,   145,   146,   147,   147,   148,   148,   149,   149,
     149,   149,   150,   150,   150,   151,   151,   152,   152,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     155,   155,   156,   156
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     0,     3,     2,     2,     2,
       2,     2,     1,     1,     1,     2,     2,     2,     4,     1,
       2,     0,     6,     0,     2,     1,     1,     1,     1,     4,
       2,     2,     1,     0,     3,     2,     4,     0,     2,     5,
       6,     6,     5,     5,     2,     2,     0,     2,     1,     3,
       1,     2,     3,     3,     2,     5,     3,     2,     0,     2,
       1,     3,     1,     2,     3,     3,     1,     1,     1,     0,
       2,     0,     2,     0,     4,     2,     2,     2,     2,     2,
       2,     1,     5,     5,     1,     3,     1,     3,     2,     1,
       3,     4,     0,     2,     4,     2,     1,     1,     1,     1,
       1,     4,     1,     2,     1,     3,     4,     0,     3,     0,
       1,     0,     1,     1,     1,     2,     0,     2,     5,     1,
       4,     5,     1,     8,     9,     9,    10,    11,     0,    14,
       0,    15,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     0,     1,     1,     2,     2,     1,
       0,     4,     0,    12,    10,     8,     6,     0,     2,     0,
       1,     1,     3,     9,     0,     3,     1,     3,     1,     1,
       3,     3,     0,     1,     1,     0,     1,     0,     2,     2,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     3,     3,     3,     3,     3,
       2,     3,     3,     4,     2,     2,     2,     2,     1,     1,
       1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    32,     0,    14,     0,    19,    13,
       0,     0,    12,     0,     0,     0,     0,     4,     0,    25,
       0,    26,    27,    46,     0,     5,     0,    69,    17,    15,
      16,    57,    45,    31,     0,   107,    32,   107,     8,    21,
       1,     2,    11,     9,     0,    10,    33,    30,     0,    44,
       0,     7,     0,    71,     0,    54,    58,   107,   109,     0,
      31,     0,     0,    23,     0,    99,   100,    32,    97,    98,
     102,     0,     0,   107,     0,    96,    50,    67,    68,    66,
       0,    47,    48,     0,     0,     6,    28,     0,    99,   140,
     141,   134,   135,   136,   137,   138,   139,    81,     0,     0,
       0,     0,   102,     0,    73,     0,    71,     0,     0,   107,
       0,   113,     0,   114,   116,   144,   132,     0,    70,     0,
      56,     0,   110,   107,    92,     0,    92,     0,     0,    20,
      18,     0,   103,    29,    33,    35,     0,    95,     0,     0,
      51,     0,     0,     0,   143,     0,   142,     0,   122,     0,
     168,   169,     0,     0,     0,   166,    78,    76,    79,     0,
       0,    72,    75,    80,   140,    88,    89,   111,   107,    77,
     164,     0,   115,   145,   146,     0,   133,     0,   107,    62,
       0,    59,    60,     0,    92,   108,     0,    39,    92,    42,
       0,    24,   107,     0,   104,    34,    92,    52,    49,    53,
      43,     0,     0,     0,     0,     0,     0,   144,     0,    71,
      55,   107,   112,     0,   111,     0,     0,   160,   161,   172,
     117,   148,   147,     0,   144,   111,   107,     0,     0,    63,
       0,    41,   210,   208,   209,   181,     0,     0,     0,     0,
       0,     0,    93,     0,   180,    92,    40,    22,    92,   101,
       0,    37,     0,     0,    86,     0,    84,   120,   171,   170,
       0,   167,    74,    90,   111,    92,     0,     0,     0,   150,
     164,   173,   174,     0,   144,   107,     0,   111,    64,    61,
      65,     0,   200,   204,   205,   207,   206,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,     0,   179,   111,
     105,   107,    36,    82,   121,     0,    83,     0,   144,     0,
      91,   164,   149,     0,   165,     0,   118,   162,   172,     0,
     111,     0,     0,   211,   201,   190,   191,   192,   195,   198,
     199,   182,   183,   184,   185,   186,   187,   188,   189,   193,
     196,   197,     0,    94,   202,   212,     0,   106,    38,    87,
      85,   107,    92,     0,   164,   152,   107,   144,     0,   164,
       0,     0,   203,     0,   111,   109,     0,     0,     0,   111,
     107,     0,     0,   164,   194,   213,     0,   123,   109,     0,
       0,   151,   175,   111,   164,   109,     0,   128,   125,   157,
       0,   176,    92,     0,     0,   124,   109,     0,     0,     0,
       0,   177,   130,   109,   126,   164,   158,   152,     0,     0,
     163,     0,   127,     0,   156,     0,     0,   178,   164,   109,
     152,     0,     0,   129,   155,     0,     0,   109,   152,     0,
     131,   154,     0,   152,   153
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    52,    12,    13,    14,    15,    16,    64,    17,
      62,   129,    18,   101,    70,    20,    71,    72,   135,   312,
      21,    22,    23,    50,    81,    82,    24,    25,    26,    27,
     120,   181,   182,   104,    56,   105,   159,   106,   107,   255,
     256,   108,   165,   166,   320,   109,    74,    75,   193,   194,
     136,   123,   213,   110,   172,   111,   112,   113,   149,   114,
     407,   421,   115,   116,   117,   177,   266,   326,   378,   409,
     216,   217,   218,   219,   154,   155,   273,   402,   420,   243,
     244,   245,   356
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -297
static const yytype_int16 yypact[] =
{
     368,    25,     3,    74,   114,    34,  -297,   285,  -297,  -297,
     140,    19,  -297,   285,   285,   285,    85,  -297,   285,  -297,
      15,  -297,  -297,    -3,   285,  -297,    91,    86,  -297,  -297,
    -297,  -297,  -297,  -297,   155,   119,   165,   119,  -297,  -297,
    -297,  -297,  -297,  -297,   166,  -297,    23,  -297,   207,  -297,
     106,  -297,   285,   247,   170,  -297,   120,   119,   167,   178,
       2,   180,   124,   125,   129,   145,  -297,   200,  -297,  -297,
    -297,   151,   146,   119,   122,  -297,  -297,  -297,  -297,  -297,
     152,   157,  -297,    35,   226,  -297,  -297,   160,    81,    -8,
     216,  -297,  -297,  -297,  -297,  -297,  -297,  -297,   225,   227,
     110,   173,   174,   176,  -297,   177,   247,   181,   182,    21,
     183,  -297,   186,  -297,   187,   185,  -297,    23,  -297,   223,
    -297,   243,  -297,   119,   197,   250,   197,   294,   166,  -297,
    -297,   122,    16,  -297,    23,  -297,   262,  -297,   267,   207,
    -297,   268,   209,   270,  -297,   227,  -297,   208,  -297,   218,
    -297,  -297,   229,   232,   212,   222,  -297,  -297,  -297,   233,
     228,  -297,  -297,  -297,   281,  -297,   230,   251,   119,  -297,
      55,   292,  -297,   291,   298,   110,  -297,    23,    21,  -297,
     152,   245,  -297,    79,   197,  -297,   299,  -297,   197,  -297,
     252,  -297,   119,   257,   254,  -297,   197,  -297,  -297,  -297,
    -297,   258,   255,   315,   260,   324,   356,   153,   110,   247,
    -297,   119,  -297,   327,   251,   110,   275,  -297,   265,    -1,
    -297,  -297,  -297,   264,   153,   251,   119,   337,   223,  -297,
     338,  -297,   302,  -297,  -297,  -297,   356,   356,   356,   356,
     356,   356,  -297,   385,  -297,    53,  -297,  -297,   197,  -297,
     122,   278,   288,   283,   296,   293,   289,  -297,  -297,   598,
      23,  -297,  -297,  -297,   251,    90,   297,   351,   303,   295,
     305,  -297,  -297,    23,   153,   119,   351,   251,  -297,  -297,
    -297,   367,  -297,   625,   452,   452,   452,   480,   356,   356,
     356,   356,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   197,   330,  -297,   251,
    -297,   119,  -297,  -297,  -297,   369,  -297,   315,   153,   370,
    -297,    55,  -297,   314,  -297,   313,  -297,  -297,    -1,    23,
     251,   318,   351,  -297,  -297,   326,   326,   326,   326,   326,
     326,   625,   625,   625,   625,   625,   452,   452,   452,   452,
     326,   326,   544,  -297,  -297,   598,    89,  -297,  -297,  -297,
    -297,   119,   197,   322,    55,   384,   119,   153,   351,    55,
     328,   356,  -297,   356,   251,   167,   332,    -4,   325,   251,
     119,   329,   333,    55,  -297,   598,   351,  -297,   167,   356,
     389,  -297,   395,   251,    55,   167,   335,  -297,  -297,   571,
     340,  -297,   197,   351,   341,  -297,   167,   343,   356,   345,
     356,   358,  -297,   167,  -297,    55,   598,   384,   412,   356,
    -297,   350,  -297,   352,  -297,   353,   356,   598,    55,   167,
     384,   446,   360,  -297,  -297,   363,   356,   167,   384,   512,
    -297,  -297,   364,   384,  -297
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -297,    63,  -297,  -297,  -297,   397,  -297,  -297,   304,  -297,
    -297,  -297,  -297,  -297,    13,  -297,   307,  -297,   131,  -297,
     -47,  -297,  -297,  -297,  -297,   316,  -297,  -297,  -297,  -297,
    -297,  -297,   202,   -27,  -297,   -95,  -297,  -297,  -297,   137,
    -297,  -297,   220,  -297,  -121,   -45,  -297,   -70,   196,  -297,
     -35,  -240,  -191,  -297,  -297,  -297,  -297,  -297,   312,  -297,
    -297,  -297,  -297,   344,   -99,  -192,  -216,  -297,  -296,  -297,
    -171,   188,  -297,  -297,  -151,  -297,   141,  -297,  -297,  -194,
    -297,  -297,  -297
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -160
static const yytype_int16 yytable[] =
{
      59,    73,    61,   187,   137,   189,   103,   144,  -107,    31,
     168,   161,   259,    19,   271,   260,     1,   -31,    37,    40,
      19,    83,   121,   267,   223,   125,    19,    19,    19,    65,
      66,    19,   275,   272,   276,   164,    90,    19,    34,    67,
      35,   140,   282,   283,   284,   285,   286,   287,   145,   141,
      36,   323,    58,   138,   389,    68,    69,   261,    48,   103,
     331,   192,    49,   231,   268,    19,   102,   246,    28,   390,
      38,    58,   178,   319,   167,   251,    41,    42,    43,   226,
      32,    45,   329,    46,   -31,   229,   332,    51,   185,    73,
      29,    30,   183,   230,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,    83,   355,   262,    85,   370,   307,   357,   102,
      33,   424,  -159,   186,   308,   215,   361,   309,    65,    66,
     150,   151,   224,   214,   434,   387,   152,   153,    67,   368,
      19,   131,   441,   225,    54,  -119,    39,   444,   398,    44,
     363,    55,   381,   227,  -149,   405,   372,   248,   373,    53,
     186,    57,   103,    77,    78,    79,   414,   173,   174,    58,
     397,    60,    63,   422,    84,   380,   264,   384,   118,   385,
     192,   119,   122,   386,   124,   353,   126,   412,   392,   433,
     190,   277,   127,   376,   128,   399,   130,   440,   382,   173,
     174,   183,   403,    91,    92,   131,   132,    93,    94,    95,
      96,   134,   396,    76,   416,   318,   418,   133,    77,    78,
      79,    80,   102,   404,   143,   427,   139,   142,   328,   179,
     146,   147,   431,   148,    77,    78,    79,   180,   156,   157,
     330,   158,   439,   160,   423,   171,   162,   163,   169,   184,
     170,    86,    87,    88,    66,   175,   188,   432,    77,    78,
      79,    89,    90,    67,     5,    91,    92,   186,   196,    93,
      94,    95,    96,   197,   199,   200,   203,    97,   201,    68,
      69,   411,   204,   207,   367,    -3,     1,   205,     2,     3,
     206,   208,    98,   210,   209,     1,   144,     2,     3,   211,
     220,     4,     5,    99,   212,   232,   221,   233,   234,   235,
       4,     5,   222,     6,   228,     7,   249,   100,   247,   253,
       8,   254,     6,   250,     7,   252,   374,   257,     9,     8,
     258,   379,    10,   265,   270,   274,   232,     9,   233,   234,
     235,    10,   269,   278,   280,   393,   281,   311,   236,   237,
     314,    -3,   238,   313,   315,   239,   240,   322,   317,   316,
      -3,   321,   232,   241,   233,   234,   235,   325,    -3,     1,
     242,     2,     3,   333,   324,   215,   362,   359,   364,   236,
     237,   365,   369,   238,     4,     5,   239,   240,   305,   375,
     377,   391,   383,   394,   241,   400,     6,   354,     7,   388,
     395,   401,   406,     8,   410,   236,   237,   415,   413,   238,
     417,     9,   239,   240,   428,    10,   419,    47,   430,   429,
     241,   288,   289,   290,   291,   292,   293,   437,   438,   443,
     279,   263,   191,   294,   295,   296,   297,   298,   299,   300,
     301,   195,   358,   302,   303,   304,   310,   305,   288,   289,
     290,   291,   292,   293,   360,   198,   306,   202,   327,   176,
     294,   295,   296,   297,   298,   299,   300,   301,     0,   366,
     302,   303,   304,     0,   305,     0,     0,     0,     0,   425,
       0,   426,   288,   289,   290,   291,   292,   293,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,     0,     0,   302,   303,   304,     0,   305,     0,
       0,   303,   304,   435,   305,   436,   288,   289,   290,   291,
     292,   293,     0,     0,     0,     0,     0,     0,   294,   295,
     296,   297,   298,   299,   300,   301,     0,     0,   302,   303,
     304,     0,   305,     0,     0,     0,     0,   334,   288,   289,
     290,   291,   292,   293,     0,     0,     0,     0,     0,     0,
     294,   295,   296,   297,   298,   299,   300,   301,     0,     0,
     302,   303,   304,     0,   305,     0,     0,     0,     0,   442,
     288,   289,   290,   291,   292,   293,     0,     0,     0,     0,
       0,     0,   294,   295,   296,   297,   298,   299,   300,   301,
       0,     0,   302,   303,   304,   371,   305,   288,   289,   290,
     291,   292,   293,   408,     0,     0,     0,     0,     0,   294,
     295,   296,   297,   298,   299,   300,   301,     0,     0,   302,
     303,   304,     0,   305,   288,   289,   290,   291,   292,   293,
       0,     0,     0,     0,     0,     0,   294,   295,   296,   297,
     298,   299,   300,   301,     0,     0,   302,   303,   304,     0,
     305,   288,   289,   290,   291,   292,   293,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   299,   300,
     301,     0,     0,   302,   303,   304,     0,   305
};

static const yytype_int16 yycheck[] =
{
      35,    46,    37,   124,    74,   126,    53,    15,     6,     6,
     109,   106,   206,     0,    15,   207,     1,     1,     5,     0,
       7,    48,    57,   214,   175,    60,    13,    14,    15,     6,
       7,    18,   224,    34,   225,    14,    15,    24,     4,    16,
       6,     6,   236,   237,   238,   239,   240,   241,    56,    14,
      16,   267,    50,    80,    58,    32,    33,   208,    61,   106,
     276,   131,    65,   184,   215,    52,    53,   188,    43,    73,
       7,    50,   117,   264,   109,   196,    13,    14,    15,   178,
       6,    18,   274,    68,    68,     6,   277,    24,   123,   134,
      65,    66,   119,    14,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   139,   307,   209,    52,   332,    64,   309,   106,
       6,   417,    67,    70,   245,    70,   318,   248,     6,     7,
      20,    21,   177,   168,   430,   375,    26,    27,    16,   330,
     127,    60,   438,   178,    58,    64,     6,   443,   388,    64,
     321,    65,   368,   180,    64,   395,    67,   192,    69,    68,
      70,     6,   209,    11,    12,    13,   406,    14,    15,    50,
     386,     6,     6,   413,    68,   367,   211,   371,     8,   373,
     250,    61,    15,   374,     6,   306,     6,   403,   379,   429,
     127,   226,    68,   364,    69,   389,    67,   437,   369,    14,
      15,   228,   393,    18,    19,    60,     6,    22,    23,    24,
      25,    65,   383,     6,   408,   260,   410,    66,    11,    12,
      13,    14,   209,   394,    64,   419,    69,     1,   273,     6,
      14,     6,   426,     6,    11,    12,    13,    14,    65,    65,
     275,    65,   436,    66,   415,    58,    65,    65,    65,     6,
      64,     4,     5,     6,     7,    70,     6,   428,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    70,     6,    22,
      23,    24,    25,     6,     6,    66,    68,    30,     8,    32,
      33,   402,    64,    71,   329,     0,     1,    58,     3,     4,
      58,    69,    45,    65,    61,     1,    15,     3,     4,    69,
       8,    16,    17,    56,    53,     6,    15,     8,     9,    10,
      16,    17,    14,    28,    69,    30,    59,    70,    66,    64,
      35,     6,    28,    69,    30,    67,   361,    67,    43,    35,
       6,   366,    47,     6,    69,    71,     6,    43,     8,     9,
      10,    47,    67,     6,     6,   380,    44,    69,    49,    50,
      67,    66,    53,    65,    58,    56,    57,     6,    69,    66,
      66,    64,     6,    64,     8,     9,    10,    72,     0,     1,
      71,     3,     4,     6,    71,    70,     6,     8,    64,    49,
      50,    68,    64,    53,    16,    17,    56,    57,    62,    67,
       6,    66,    64,    64,    64,     6,    28,    67,    30,    67,
      67,     6,    67,    35,    64,    49,    50,    64,    67,    53,
      65,    43,    56,    57,    64,    47,    58,    20,    65,    67,
      64,    36,    37,    38,    39,    40,    41,    67,    65,    65,
     228,   211,   128,    48,    49,    50,    51,    52,    53,    54,
      55,   134,   311,    58,    59,    60,   250,    62,    36,    37,
      38,    39,    40,    41,   317,   139,    71,   145,   270,   115,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,   328,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,    67,
      -1,    69,    36,    37,    38,    39,    40,    41,    36,    37,
      38,    39,    40,    41,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    58,    59,    60,    -1,    62,    -1,
      -1,    59,    60,    67,    62,    69,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,    67,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,    67,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    58,    59,    60,    61,    62,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    58,
      59,    60,    -1,    62,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    58,    59,    60,    -1,
      62,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    -1,    -1,    58,    59,    60,    -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    16,    17,    28,    30,    35,    43,
      47,    75,    77,    78,    79,    80,    81,    83,    86,    88,
      89,    94,    95,    96,   100,   101,   102,   103,    43,    65,
      66,     6,     6,     6,     4,     6,    16,    88,    75,     6,
       0,    75,    75,    75,    64,    75,    68,    79,    61,    65,
      97,    75,    76,    68,    58,    65,   108,     6,    50,   124,
       6,   124,    84,     6,    82,     6,     7,    16,    32,    33,
      88,    90,    91,   119,   120,   121,     6,    11,    12,    13,
      14,    98,    99,   107,    68,    75,     4,     5,     6,    14,
      15,    18,    19,    22,    23,    24,    25,    30,    45,    56,
      70,    87,    88,    94,   107,   109,   111,   112,   115,   119,
     127,   129,   130,   131,   133,   136,   137,   138,     8,    61,
     104,   124,    15,   125,     6,   124,     6,    68,    69,    85,
      67,    60,     6,    66,    65,    92,   124,   121,   107,    69,
       6,    14,     1,    64,    15,    56,    14,     6,     6,   132,
      20,    21,    26,    27,   148,   149,    65,    65,    65,   110,
      66,   109,    65,    65,    14,   116,   117,   124,   138,    65,
      64,    58,   128,    14,    15,    70,   137,   139,   119,     6,
      14,   105,   106,   107,     6,   124,    70,   118,     6,   118,
      75,    82,   121,   122,   123,    90,     6,     6,    99,     6,
      66,     8,   132,    68,    64,    58,    58,    71,    69,    61,
      65,    69,    53,   126,   124,    70,   144,   145,   146,   147,
       8,    15,    14,   148,   119,   124,   138,   107,    69,     6,
      14,   118,     6,     8,     9,    10,    49,    50,    53,    56,
      57,    64,    71,   153,   154,   155,   118,    66,   124,    59,
      69,   118,    67,    64,     6,   113,   114,    67,     6,   153,
     139,   148,   109,   116,   124,     6,   140,   126,   148,    67,
      69,    15,    34,   150,    71,   139,   126,   124,     6,   106,
       6,    44,   153,   153,   153,   153,   153,   153,    36,    37,
      38,    39,    40,    41,    48,    49,    50,    51,    52,    53,
      54,    55,    58,    59,    60,    62,    71,    64,   118,   118,
     122,    69,    93,    65,    67,    58,    66,    69,   119,   126,
     118,    64,     6,   140,    71,    72,   141,   145,   119,   139,
     124,   140,   126,     6,    67,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   118,    67,   153,   156,   126,    92,     8,
     113,   139,     6,   144,    64,    68,   150,   119,   126,    64,
     140,    61,    67,    69,   124,    67,   144,     6,   142,   124,
     139,   140,   144,    64,   153,   153,   126,   125,    67,    58,
      73,    66,   126,   124,    64,    67,   144,   140,   125,   153,
       6,     6,   151,   126,   144,   125,    67,   134,    42,   143,
      64,   118,   140,    67,   125,    64,   153,    65,   153,    58,
     152,   135,   125,   144,   142,    67,    69,   153,    64,    67,
      65,   153,   144,   125,   142,    67,    69,    67,    65,   153,
     125,   142,    67,    65,   142
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
#line 144 "parser.y"
    {
	if (othercodes.GetSize()) {
		assert(thisCodeFile!=NULL);
		OtherCode *dat=new OtherCode(thisCodeFile);
		dat->AddCode(othercodes);
		thisCodeFile->AddCodeData(dat);
		othercodes.SetSize(0);
	}
}
    break;

  case 5:
#line 156 "parser.y"
    { 
	insideClass=false; 
	othercodes.SetSize(0); 
	startPos=-1;
}
    break;

  case 11:
#line 166 "parser.y"
    {
	CleanStack(); 
}
    break;

  case 13:
#line 173 "parser.y"
    {
	if(isImplicitPackEnable){      
		/* The following code handles the implicit @pack directive if it's not specified by the developer */
		std::string fname(filename);
				
		std::size_t cc = fname.find(".cc");
		std::size_t cpp = fname.find(".cpp");
		std::size_t cxx = fname.find(".cxx");			
			
		if((cc != std::string::npos || cpp != std::string::npos || cxx != std::string::npos) && !isParclassDeclared){	
			std::size_t pos;		
			if(cc != std::string::npos){
				pos = cc;
			} else if (cpp != std::string::npos){ // Extension is
				pos = cpp;				
			} else if (cxx != std::string::npos){	// Extension is .cxx
				pos = cxx;
			}
				
			// Try to find the according .ph file
			std::string ph_file(fname);
			std::string ph_extension(".ph");
					ph_file.replace(pos, std::string::npos, ph_extension);
					// Check if file exists
					std::fstream ph_real_file;
					ph_real_file.open(ph_file.c_str(), std::ios_base::out | std::ios_base::in);
					if (ph_real_file.is_open()){
						// Find name of the parclass
						char line[256]; 
						bool notFound = true;
						while (notFound){
							ph_real_file.getline(line, 256);
							if(ph_real_file.eof()){
								notFound = false;
								ph_real_file.close();
							} else {
								std::string str_line(line);
								std::size_t parclass_pos = str_line.find("parclass"); 
								if(parclass_pos != std::string::npos){
									std::size_t parclass_name_start = str_line.find(" ", parclass_pos); 
									std::size_t parclass_name_stop = str_line.find(" ", parclass_name_start+1); 
									if(parclass_name_stop == std::string::npos)
										parclass_name_stop = str_line.find(";", parclass_name_start+1); 
									if(parclass_name_stop == std::string::npos)
										parclass_name_stop = str_line.find("{", parclass_name_start+1); 																	
									if(parclass_name_stop == std::string::npos)								
										parclass_name_stop = str_line.find("\n", parclass_name_start+1); 		
									if(parclass_name_stop != std::string::npos && parclass_name_start != std::string::npos){
										std::string parclass_name = str_line.substr(parclass_name_start, (parclass_name_stop - parclass_name_start));

										notFound = false; 
										ph_real_file.close();


										/* Same code as "pack_header" */
										if (othercodes.GetSize() && startPos>0) {
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
										parclass_name.erase(std::remove(parclass_name.begin(), parclass_name.end(), ' '), parclass_name.end());
										char * objname = new char[parclass_name.size() + 1];
										std::copy(parclass_name.begin(), parclass_name.end(), objname);
										objname[parclass_name.size()] = '\0';
										if (currentPack!=NULL) {
											currentPack->AddObject(objname);
										}

										isParclassDeclared = true; 
										currentPack->SetEndLine(linenumber-1);
										currentPack=NULL;
										othercodes.SetSize(0);
										startPos=-1;
										
										delete [] objname;
										
										// Ok file exists, so we will find the parclass name and add the pack directive with it
										if(isWarningEnable){
											std::cout << filename << ":" << linenumber << ": Warning: Pack directive was not present! Implicit declaration has been added from ";
											std::cout << ph_file << std::endl;
																
										}
									}
								}
							}
						}
					}
				}	
			}	
}
    break;

  case 14:
#line 271 "parser.y"
    {
	printf("handle at Bison\n");
	othercodes.InsertAt(-1,"\n",strlen("\n"));
}
    break;

  case 15:
#line 279 "parser.y"
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

  case 16:
#line 292 "parser.y"
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

  case 17:
#line 305 "parser.y"
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

  case 18:
#line 321 "parser.y"
    {
	
	isParclassDeclared = true; 
	currentPack->SetEndLine(linenumber-1);
  	currentPack=NULL;
  	othercodes.SetSize(0);
  	startPos=-1;
}
    break;

  case 19:
#line 331 "parser.y"
    {
  	if (othercodes.GetSize() && startPos>0) {
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

  case 20:
#line 348 "parser.y"
    {
  		if (currentPack!=NULL) {
			currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
		}
}
    break;

  case 21:
#line 359 "parser.y"
    {
	
	// Avoid handling of standard namespace used in POP-C++
	
	if(strcmp("__gnu_cxx", GetToken((yyvsp[(2) - (2)]))) != 0 &&  strcmp("std", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("__gnu_debug", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("rel_ops", GetToken((yyvsp[(2) - (2)]))) != 0  && strcmp("__debug", GetToken((yyvsp[(2) - (2)]))) != 0){
			
		isNamespace = true;
			
		sprintf(holdnamespace, "%s", GetToken((yyvsp[(2) - (2)])));
	
	}

}
    break;

  case 22:
#line 374 "parser.y"
    {
	
	isNamespace = false;

}
    break;

  case 23:
#line 383 "parser.y"
    {
}
    break;

  case 24:
#line 386 "parser.y"
    {
}
    break;

  case 25:
#line 394 "parser.y"
    {
    CleanStack();
}
    break;

  case 28:
#line 410 "parser.y"
    {
	
	sprintf(tmp,"Class declaration inside parclass are not currently supported !\n");
	
	errormsg(tmp);
	exit(1);

}
    break;

  case 29:
#line 427 "parser.y"
    {
  	currentstruct=Pop();
  	if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  	(yyval)=(yyvsp[(1) - (4)]);
  	structContainer = NULL;
  	isInStruct = false;
}
    break;

  case 30:
#line 435 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 31:
#line 441 "parser.y"
    {
	
	if(currentClass!=NULL){
		
		isInStruct = true;
		
		structContainer = new Structure(currentClass, accessmodifier);
		
		structContainer->SetLineInfo(linenumber-1);
		
		currentClass->AddMember(structContainer);
      
		structContainer->setName(GetToken((yyvsp[(2) - (2)])));	
	
	}
  	char *tname=GetToken((yyvsp[(2) - (2)]));
	DataType *type=thisCodeFile->FindDataType(tname);
  	TypeClassStruct *t;
  	if (type!=NULL){
		t=dynamic_cast<TypeClassStruct *>(type);
		if (t==NULL) {
	  //	  	  thisCodeFile->RemoveDataType(type);
	  //	  	  delete type;
	  t=new TypeClassStruct(tname, false);
	  thisCodeFile->AddDataType(t);
	  //	  sprintf(tmp,"data type \"%s\" has been redefined!\n",tname);
	  //	  errormsg(tmp);
	  //	  exit(1);
		}
	} else { 
      t=new TypeClassStruct(tname,false);
      thisCodeFile->AddDataType(t);	
   }
	Push(t);
	(yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 32:
#line 478 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 36:
#line 494 "parser.y"
    {
	// Save the attribute in the Strcuture object to be able to produce code
	if(structContainer!=NULL) {
		std::string attribute;
		attribute.append(typetmp);
		attribute.append(" ");
		attribute.append(GetToken((yyvsp[(2) - (4)])));
		attribute.append(";");	
		structContainer->setInnerDecl(attribute);			
	}

	DataType *type1=currenttype;
	if ((yyvsp[(1) - (4)])>0) {
		//type1=new TypePtr(NULL,$1, type1);
      type1=new TypePtr(NULL, (yyvsp[(1) - (4)]), type1, constPointerPositions);
      thisCodeFile->AddDataType(type1);
   }
  	if ((yyvsp[(3) - (4)])!=-1){
      type1=new TypeArray(NULL,GetToken((yyvsp[(3) - (4)])), type1);
      thisCodeFile->AddDataType(type1);     
   }  
	TypeClassStruct *t=Peek();
	assert(t!=NULL);
	t->Add(type1, GetToken((yyvsp[(2) - (4)])));
}
    break;

  case 39:
#line 532 "parser.y"
    {
	if(currentClass!=NULL){
			
		typeDefContainer = new TypeDefinition(currentClass, accessmodifier);
		
		typeDefContainer->SetLineInfo(linenumber-1);
		
		currentClass->AddMember(typeDefContainer);
      
		typeDefContainer->setName(GetToken((yyvsp[(2) - (5)])));	
	
		typeDefContainer->setBaseType(GetToken((yyvsp[(4) - (5)])));	
	
		if ((yyvsp[(3) - (5)])>0) {
			typeDefContainer->setAsPtr();	

		}
		if ((yyvsp[(5) - (5)])!=-1) {
			typeDefContainer->setAsArray();	

    	}
	}
	char *orgtype=GetToken((yyvsp[(2) - (5)]));
	DataType *type=thisCodeFile->FindDataType(orgtype);
	if (type==NULL) {
		type=new DataType(orgtype);
      thisCodeFile->AddDataType(type);
	}
	if ((yyvsp[(3) - (5)])>0) {
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

  case 40:
#line 574 "parser.y"
    {
	if(insideClass){
		sprintf(tmp,"typedef definition with structure inside a parclass is not currently supported !\n");
	
		errormsg(tmp);
		exit(1);
	}
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

  case 41:
#line 604 "parser.y"
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

  case 42:
#line 628 "parser.y"
    {
	if(insideClass){
		sprintf(tmp,"typedef definition with structure inside a parclass is not currently supported !\n");
	
		errormsg(tmp);
		exit(1);
	}
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

  case 43:
#line 659 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 45:
#line 665 "parser.y"
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

  case 50:
#line 695 "parser.y"
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

  case 51:
#line 719 "parser.y"
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

  case 52:
#line 744 "parser.y"
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

  case 53:
#line 769 "parser.y"
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

  case 54:
#line 799 "parser.y"
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

  case 55:
#line 820 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 56:
#line 828 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 57:
#line 837 "parser.y"
    {
	hadParclass = true; 
	if (othercodes.GetSize() && startPos>0) {
      assert(thisCodeFile!=NULL);
      OtherCode *dat=new OtherCode(thisCodeFile);
      dat->AddCode((char *)othercodes,startPos);
      thisCodeFile->AddCodeData(dat);
      othercodes.SetSize(0);
	}
	insideClass=true;
	char *clname=GetToken((yyvsp[(2) - (2)]));
  
	Class *t;
	if ((t=thisCodeFile->FindClass(clname))==NULL) {
      t=new Class(clname, thisCodeFile);
      thisCodeFile->AddDataType(t);
      if(thisCodeFile->IsCoreCompilation())
      	t->SetAsCoreCompilation();
      if(isWarningEnable)
      	t->EnableWarning();
      
	}
	t->SetFileInfo(filename);
	t->SetStartLine(linenumber);
	currentClass=t;
	if(isNamespace) {
		t->SetNamespace(holdnamespace);
	}
}
    break;

  case 62:
#line 876 "parser.y"
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

  case 63:
#line 890 "parser.y"
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

  case 64:
#line 905 "parser.y"
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

  case 65:
#line 922 "parser.y"
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

  case 66:
#line 941 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 67:
#line 945 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 68:
#line 949 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 69:
#line 956 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 70:
#line 960 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 73:
#line 970 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 79:
#line 978 "parser.y"
    {
	assert(method!=NULL);
	int t=method->CheckMarshal();
	if (t!=0)
	{      
		if (t==-1) 
			sprintf(tmp,"In method %s::%s: unable to marshal the return argument.\n", currentClass->GetName(), method->name);
      else 
			sprintf(tmp,"In method %s::%s: unable to marshal argument %d.\n", currentClass->GetName(), method->name,t);
      errormsg(tmp);
      exit(1);
    }
  currenttype=returntype=NULL;
}
    break;

  case 80:
#line 994 "parser.y"
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

  case 81:
#line 1005 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 82:
#line 1010 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 83:
#line 1021 "parser.y"
    {
	assert(currentClass!=NULL);
	Enumeration *t = new Enumeration(currentClass, accessmodifier);
	t->SetLineInfo(linenumber-1);
	currentClass->AddMember(t);
	t->setName(GetToken((yyvsp[(2) - (5)])));
	t->setArgs(GetToken((yyvsp[(4) - (5)])));
}
    break;

  case 84:
#line 1032 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);	
}
    break;

  case 85:
#line 1036 "parser.y"
    {
	sprintf(tmp,"%s , %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 86:
#line 1043 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 87:
#line 1047 "parser.y"
    {      
	sprintf(tmp,"%s = %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
   (yyval)=PutToken(tmp);
}
    break;

  case 91:
#line 1064 "parser.y"
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
#line 1095 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 93:
#line 1099 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 94:
#line 1103 "parser.y"
    {
	if ((yyvsp[(4) - (4)])==-1) {
		sprintf(tmp,"[%s]",GetToken((yyvsp[(2) - (4)])));
		(yyval)=PutToken(tmp);
	} else {
      sprintf(tmp,"[%s]%s",GetToken((yyvsp[(2) - (4)])),GetToken((yyvsp[(4) - (4)])));
      (yyval)=PutToken(tmp);
	}
}
    break;

  case 95:
#line 1115 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 96:
#line 1119 "parser.y"
    {
	
	
	(yyval)=0;
}
    break;

  case 97:
#line 1127 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 98:
#line 1131 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 99:
#line 1137 "parser.y"
    {
	if(isInStruct)
		sprintf(typetmp, "%s", GetToken((yyvsp[(1) - (1)]))); // Save the type specifier for struct attribute
	currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[(1) - (1)])));
	if (currenttype==NULL) {
	   currenttype=new DataType(GetToken((yyvsp[(1) - (1)])));
      thisCodeFile->AddDataType(currenttype);
   }
	(yyval)=(YYSTYPE)currenttype;
}
    break;

  case 100:
#line 1148 "parser.y"
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

  case 101:
#line 1164 "parser.y"
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

  case 102:
#line 1183 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 103:
#line 1189 "parser.y"
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

  case 104:
#line 1202 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 105:
#line 1209 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 106:
#line 1218 "parser.y"
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

  case 107:
#line 1290 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 108:
#line 1295 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 109:
#line 1303 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 110:
#line 1307 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 111:
#line 1313 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 112:
#line 1317 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 117:
#line 1333 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 118:
#line 1339 "parser.y"
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

  case 119:
#line 1355 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 120:
#line 1364 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 121:
#line 1373 "parser.y"
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

  case 122:
#line 1386 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 123:
#line 1516 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 124:
#line 1523 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 125:
#line 1530 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 126:
#line 1537 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 127:
#line 1544 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 128:
#line 1551 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 129:
#line 1552 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 130:
#line 1558 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 131:
#line 1559 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 132:
#line 1569 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 133:
#line 1573 "parser.y"
    {
	/* error if multimple time same reserved word */
	if (((yyvsp[(2) - (2)]) & (yyvsp[(1) - (2)])) != 0)
	{
		errormsg("Multiple semantics keyword");
		exit(1);
	}
  
	(yyval)=(yyvsp[(1) - (2)]) | (yyvsp[(2) - (2)]);
}
    break;

  case 134:
#line 1619 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 135:
#line 1623 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 136:
#line 1627 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 137:
#line 1631 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 138:
#line 1635 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 139:
#line 1639 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 140:
#line 1646 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 141:
#line 1650 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 142:
#line 1654 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 143:
#line 1658 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 144:
#line 1665 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 145:
#line 1669 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 146:
#line 1673 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 147:
#line 1677 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 148:
#line 1681 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 149:
#line 1687 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 150:
#line 1698 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 151:
#line 1702 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 152:
#line 1708 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 153:
#line 1713 "parser.y"
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

  case 154:
#line 1730 "parser.y"
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

  case 155:
#line 1746 "parser.y"
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

  case 156:
#line 1761 "parser.y"
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

  case 157:
#line 1853 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 158:
#line 1857 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 163:
#line 1872 "parser.y"
    {
	Param *t=method->AddNewParam();
	UpdateMarshalParam((yyvsp[(1) - (9)]),t);
	
	
	DataType *type=currenttype;
	if ((yyvsp[(5) - (9)])>0) {
      type=new TypePtr(NULL, (yyvsp[(5) - (9)]) , type, constPointerPositions);
      thisCodeFile->AddDataType(type);
	}

	if ((yyvsp[(6) - (9)])) {
		t->isRef=true;
	}
	
	// Handle standard array passing declaration
	if((yyvsp[(8) - (9)]) == 0){
		t->isArray=true;
		//Find last int as size of array
		int nb=method->params.GetSize()-1;
		
		std::string size_variable_name;
		
		for (int j=0;j<nb;j++) {
			Param &p=*(method->params[j]);
			if(strcmp("int", p.GetType()->GetName())==0){
				size_variable_name.clear();
				size_variable_name.append(p.GetName());
			}
		}
		if(size_variable_name.length() == 0){
			//
			sprintf(tmp,"Could not find size to marshall array: %s\n", GetToken((yyvsp[(7) - (9)])));
			errormsg(tmp);
			exit(1);
		}
		strcpy(tmpSize, size_variable_name.c_str());
		UpdateMarshalParam(67,t);
      type=new TypePtr(NULL, 1, type, constPointerPositions);
      thisCodeFile->AddDataType(type);
	} else if ((yyvsp[(8) - (9)]) != -1) {
		type=new TypeArray(NULL, GetToken((yyvsp[(8) - (9)])) , type);
		thisCodeFile->AddDataType(type);
	}

	t->SetType(type);
	if ((yyvsp[(7) - (9)]) != -1) {
		strcpy(t->name,GetToken((yyvsp[(7) - (9)])));
	} else {
		if(strcmp("void", t->GetType()->GetName()) == 0){
			t->isVoid = true;
		} else {
			sprintf(t->name,"V_%d",++counter);
		}
	}

	t->isConst=(((yyvsp[(2) - (9)])==1) || ((yyvsp[(4) - (9)])==1));
	if ((yyvsp[(9) - (9)]) >= 0) 
		t->defaultVal=strdup(GetToken((yyvsp[(9) - (9)])));
}
    break;

  case 164:
#line 1935 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 165:
#line 1939 "parser.y"
    {
	(yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 166:
#line 1945 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 167:
#line 1949 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 168:
#line 1955 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 169:
#line 1959 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 170:
#line 1963 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 171:
#line 1968 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 172:
#line 1976 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 173:
#line 1980 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 174:
#line 1984 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 175:
#line 1990 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 176:
#line 1994 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 177:
#line 2000 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 178:
#line 2004 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 179:
#line 2017 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 180:
#line 2026 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 181:
#line 2030 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 182:
#line 2034 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:
#line 2039 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:
#line 2044 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:
#line 2049 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:
#line 2054 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:
#line 2059 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:
#line 2064 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:
#line 2069 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:
#line 2074 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:
#line 2079 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:
#line 2084 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 193:
#line 2089 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 194:
#line 2094 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 195:
#line 2099 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 196:
#line 2104 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 197:
#line 2109 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 198:
#line 2114 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 199:
#line 2119 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 200:
#line 2124 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 201:
#line 2129 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 202:
#line 2134 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 203:
#line 2139 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 204:
#line 2145 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 205:
#line 2150 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 206:
#line 2155 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 207:
#line 2160 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 208:
#line 2167 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 209:
#line 2171 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 210:
#line 2177 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 211:
#line 2181 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 212:
#line 2189 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 213:
#line 2193 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;


/* Line 1267 of yacc.c.  */
#line 4091 "parser.tab.c"
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


#line 2201 "parser.y"


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
  structContainer=NULL;
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

// Update marshall options for a specific parameter
void UpdateMarshalParam(int flags, Param *t)
{
	if (flags!=0) {
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
	isWarningEnable=true;
	isImplicitPackEnable=true;
	isPOPCPPCompilation=false;

	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")!=NULL){
		
		broker=false;
	
	} 	
	
	
	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")!=NULL) {
		
		client=false;
	
	}  
	
	if (paroc_utils::checkremove(&argc,&argv,"-no-warning")!=NULL) {
		
		isWarningEnable=false;
	
	}  

	if (paroc_utils::checkremove(&argc,&argv,"-popcpp-compilation")!=NULL) {
		
		isPOPCPPCompilation=true;
	
	}  
	
	if (paroc_utils::checkremove(&argc,&argv,"-no-implicit-pack")!=NULL) {

		isImplicitPackEnable=false;
	
	}  
			
	int ret;
	indexsource=-1;
	errorcode=0;
	if (argc<2){
		
		Usage();
	
	} else {
		if ((ret=ParseFile(argv[1], ((argc>2) ? argv[2] : NULL), client, broker, isWarningEnable, isImplicitPackEnable, isPOPCPPCompilation))!=0)	{
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
  fprintf(stderr,"%s:%d: ERROR: %s\n",filename,linenumber-1,s);
  errorcode=1;
}

int yywrap() {
	return(1);
}


int base=1;

int ParseFile(char *infile, char *outfile, bool client, bool broker, bool isWarningEnable, bool isImplicitPackEnable, bool isPOPCPPCompilation)
{
	if (infile==NULL || *infile=='-'){
		yyin=stdin;
	} else {
      yyin=fopen(infile,"rt");
      if (yyin==NULL) {
	   	perror(infile);
	   	return errno;
		}
      strcpy(filename,infile);
	}
	
	linenumber=1;
	thisCodeFile=new CodeFile(NULL);
	if (outfile!=NULL) {
		
		thisCodeFile->SetOutputName(outfile);	

	}
	
	if(isPOPCPPCompilation)
		thisCodeFile->SetAsCoreCompilation();
		
	insideClass=false;
	othercodes.SetSize(0);
	startPos=-1;
	

	int ret=yyparse();
	if (ret==0) {
		FILE *outf;
      if (outfile==NULL || *outfile=='-'){
     		
      	outf=stdout;
      
      } else {
			outf=fopen(outfile,"wt");
	  		if (outf==NULL){
		      ret=errno;
		      perror(outfile);
	   	}
		}
      if (outf!=NULL) {
			CArrayChar output(0,32000);
			thisCodeFile->GenerateCode(output, client, broker);
			fwrite((char *)output,1, output.GetSize(),outf);
      }
      if (outf!=stdout) {
			fclose(outf);
      
		}
	}
  
	othercodes.SetSize(0);

	if (yyin!=stdin) {
		
		fclose(yyin);
	
	}
	delete thisCodeFile;
	thisCodeFile=NULL;
	
	isParclassDeclared = false; 
	
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
		errormsg("Multiple seq, conc or mutex keyword");
		exit(1);
	}
	
	if ((settings & 64)!=0)
		method->isHidden=true;
	
	// TEST SYNC or ASYNC
	if ((settings & 6)==6) 
	{
		errormsg("Multiple sync, async keyword");
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
		errormsg("inspectors/const member functions are supported in the current version of POP-C++");
		exit(1);
	}
	else
	{
		return;
	}
}


