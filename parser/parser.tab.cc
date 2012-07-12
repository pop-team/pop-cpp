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

	Method *method;
	// Param *param;

 int n,t;
 bool isNamespace = false;
 
 bool isInStruct = false;
 
 bool isParclassDeclared = false;
 
 bool hadParclass = false; 
 
 bool isWarningEnable;
 bool isImplicitPackEnable;
 char holdnamespace[500];
 char tmp[10240];
 char typetmp[100];
 char tmpProc[10240];
 char tmpSize[10240];
 int parsingclass=0;

 void UpdateMarshalParam(int flags, Param *t);

 int ParseFile(char *infile, char *outfile, bool client, bool broker, bool isWarningEnable, bool isImplicitPackEnable);
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
#line 323 "parser.tab.c"

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
#define YYLAST   672

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  444

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
     273,   277,   282,   283,   288,   291,   293,   295,   297,   299,
     301,   306,   308,   311,   313,   317,   322,   323,   327,   328,
     330,   331,   333,   335,   337,   340,   341,   344,   350,   352,
     357,   363,   365,   374,   384,   394,   405,   417,   418,   433,
     434,   450,   452,   455,   457,   459,   461,   463,   465,   467,
     469,   471,   474,   477,   478,   480,   482,   485,   488,   490,
     491,   496,   497,   510,   521,   530,   537,   538,   541,   542,
     544,   546,   550,   560,   561,   565,   567,   571,   573,   575,
     579,   583,   584,   586,   588,   589,   591,   592,   595,   598,
     600,   602,   606,   610,   614,   618,   622,   626,   630,   634,
     638,   642,   646,   650,   656,   660,   664,   668,   672,   676,
     679,   683,   687,   692,   695,   698,   701,   704,   706,   708,
     710,   714,   716
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
     118,    -1,    -1,    70,   153,    71,   118,    -1,   120,   121,
      -1,   121,    -1,    32,    -1,    33,    -1,     6,    -1,     7,
      -1,     6,    60,   122,    59,    -1,    88,    -1,    16,     6,
      -1,   123,    -1,   123,    69,   122,    -1,   121,   124,   118,
     126,    -1,    -1,    50,   125,   124,    -1,    -1,    15,    -1,
      -1,    53,    -1,   129,    -1,   131,    -1,   133,   128,    -1,
      -1,    58,     8,    -1,   130,    64,   144,    67,   141,    -1,
       6,    -1,    56,   132,    64,    67,    -1,    14,    56,   132,
      64,    67,    -1,     6,    -1,   119,   124,   126,   140,    64,
     144,    67,   125,    -1,   138,   119,   124,   126,   140,    64,
     144,    67,   125,    -1,   119,   138,   124,   126,   140,    64,
     144,    67,   125,    -1,   138,   119,   138,   124,   126,   140,
      64,   144,    67,   125,    -1,   136,   139,   119,   139,   124,
     126,   140,    64,   144,    67,   125,    -1,    -1,    70,   148,
      71,   139,   119,   139,   124,   126,   140,   134,    64,   144,
      67,   125,    -1,    -1,   136,    70,   148,    71,   139,   119,
     139,   124,   126,   140,   135,    64,   144,    67,   125,    -1,
     137,    -1,   136,   137,    -1,    18,    -1,    19,    -1,    22,
      -1,    23,    -1,    24,    -1,    25,    -1,    14,    -1,    15,
      -1,    15,    14,    -1,    14,    15,    -1,    -1,    14,    -1,
      15,    -1,    15,    14,    -1,    14,    15,    -1,     6,    -1,
      -1,    72,    68,   142,    66,    -1,    -1,     6,    73,     6,
      64,   153,    69,   153,    69,   153,    67,    65,   142,    -1,
       6,    73,     6,    64,   153,    69,   153,    67,    65,   142,
      -1,     6,    73,     6,    64,   153,    67,    65,   142,    -1,
       6,    58,   153,   143,    65,   142,    -1,    -1,    42,   153,
      -1,    -1,   145,    -1,   146,    -1,   146,    69,   145,    -1,
     147,   150,   119,   150,   124,   126,   151,   118,   152,    -1,
      -1,    70,   148,    71,    -1,   149,    -1,   149,    69,   148,
      -1,    20,    -1,    21,    -1,    27,    58,   153,    -1,    26,
      58,     6,    -1,    -1,    15,    -1,    34,    -1,    -1,     6,
      -1,    -1,    58,   153,    -1,   155,   118,    -1,   154,    -1,
      10,    -1,   153,    48,   153,    -1,   153,    49,   153,    -1,
     153,    50,   153,    -1,   153,    51,   153,    -1,   153,    52,
     153,    -1,   153,    53,   153,    -1,   153,    54,   153,    -1,
     153,    55,   153,    -1,   153,    36,   153,    -1,   153,    37,
     153,    -1,   153,    38,   153,    -1,   153,    58,   153,    -1,
     153,    62,   153,    61,   153,    -1,   153,    39,   153,    -1,
     153,    59,   153,    -1,   153,    60,   153,    -1,   153,    40,
     153,    -1,   153,    41,   153,    -1,    49,   153,    -1,    64,
     153,    67,    -1,   155,    64,    67,    -1,   155,    64,   156,
      67,    -1,    50,   153,    -1,    53,   153,    -1,    57,   153,
      -1,    56,   153,    -1,     8,    -1,     9,    -1,     6,    -1,
       6,    44,     6,    -1,   153,    -1,   156,    69,   153,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   142,   152,   154,   153,   159,   160,   161,
     162,   163,   167,   170,   268,   276,   289,   302,   318,   329,
     347,   360,   358,   384,   386,   394,   398,   399,   410,   427,
     435,   441,   475,   484,   485,   488,   491,   519,   520,   529,
     559,   583,   607,   632,   636,   638,   659,   660,   664,   665,
     668,   692,   717,   742,   772,   793,   801,   810,   836,   837,
     840,   841,   844,   858,   873,   890,   909,   913,   917,   925,
     928,   937,   938,   939,   939,   943,   944,   945,   946,   946,
     962,   973,   978,   989,  1000,  1004,  1011,  1015,  1026,  1028,
    1029,  1032,  1064,  1067,  1082,  1086,  1094,  1098,  1104,  1115,
    1131,  1150,  1156,  1169,  1176,  1185,  1258,  1262,  1271,  1274,
    1281,  1284,  1296,  1297,  1298,  1301,  1302,  1308,  1324,  1333,
    1342,  1355,  1485,  1492,  1499,  1506,  1513,  1521,  1521,  1528,
    1528,  1538,  1542,  1588,  1592,  1596,  1600,  1604,  1608,  1615,
    1619,  1623,  1627,  1635,  1638,  1642,  1646,  1650,  1656,  1668,
    1671,  1678,  1682,  1699,  1715,  1730,  1823,  1826,  1834,  1835,
    1837,  1838,  1841,  1878,  1881,  1887,  1891,  1897,  1901,  1905,
    1910,  1919,  1922,  1926,  1933,  1936,  1943,  1946,  1959,  1968,
    1972,  1976,  1981,  1986,  1991,  1996,  2001,  2006,  2011,  2016,
    2021,  2026,  2031,  2036,  2041,  2046,  2051,  2056,  2061,  2066,
    2071,  2076,  2081,  2087,  2092,  2097,  2102,  2109,  2113,  2119,
    2123,  2131,  2135
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
     116,   117,   118,   118,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   122,   122,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   128,   128,   129,   130,   131,
     131,   132,   133,   133,   133,   133,   133,   134,   133,   135,
     133,   136,   136,   137,   137,   137,   137,   137,   137,   138,
     138,   138,   138,   139,   139,   139,   139,   139,   140,   141,
     141,   142,   142,   142,   142,   142,   143,   143,   144,   144,
     145,   145,   146,   147,   147,   148,   148,   149,   149,   149,
     149,   150,   150,   150,   151,   151,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   156,   156
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
       0,     0,     0,     0,    32,     0,    14,     0,    19,    13,
       0,     0,    12,     0,     0,     0,     0,     4,     0,    25,
       0,    26,    27,    46,     0,     5,     0,    69,    17,    15,
      16,    57,    45,    31,     0,   106,    32,   106,     8,    21,
       1,     2,    11,     9,     0,    10,    33,    30,     0,    44,
       0,     7,     0,    71,     0,    54,    58,   106,   108,     0,
      31,     0,     0,    23,     0,    98,    99,    32,    96,    97,
     101,     0,     0,   106,     0,    95,    50,    67,    68,    66,
       0,    47,    48,     0,     0,     6,    28,     0,    98,   139,
     140,   133,   134,   135,   136,   137,   138,    81,     0,     0,
       0,     0,   101,     0,    73,     0,    71,     0,     0,   106,
       0,   112,     0,   113,   115,   143,   131,     0,    70,     0,
      56,     0,   109,   106,    92,     0,    92,     0,     0,    20,
      18,     0,   102,    29,    33,    35,     0,    94,     0,     0,
      51,     0,     0,     0,   142,     0,   141,     0,   121,     0,
     167,   168,     0,     0,     0,   165,    78,    76,    79,     0,
       0,    72,    75,    80,   139,    88,    89,   110,   106,    77,
     163,     0,   114,   144,   145,     0,   132,     0,   106,    62,
       0,    59,    60,     0,    92,   107,     0,    39,    92,    42,
       0,    24,   106,     0,   103,    34,    92,    52,    49,    53,
      43,     0,     0,     0,     0,     0,     0,   143,     0,    71,
      55,   106,   111,     0,   110,     0,     0,   159,   160,   171,
     116,   147,   146,     0,   143,   110,   106,     0,     0,    63,
       0,    41,   209,   207,   208,   180,     0,     0,     0,     0,
       0,     0,     0,   179,    92,    40,    22,    92,   100,     0,
      37,     0,     0,    86,     0,    84,   119,   170,   169,     0,
     166,    74,    90,   110,    92,     0,     0,     0,   149,   163,
     172,   173,     0,   143,   106,     0,   110,    64,    61,    65,
       0,   199,   203,   204,   206,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,     0,   178,   110,   104,
     106,    36,    82,   120,     0,    83,     0,   143,     0,    91,
     163,   148,     0,   164,     0,   117,   161,   171,     0,   110,
       0,     0,   210,   200,   189,   190,   191,   194,   197,   198,
     181,   182,   183,   184,   185,   186,   187,   188,   192,   195,
     196,     0,    93,   201,   211,     0,   105,    38,    87,    85,
     106,    92,     0,   163,   151,   106,   143,     0,   163,     0,
       0,   202,     0,   110,   108,     0,     0,     0,   110,   106,
       0,     0,   163,   193,   212,     0,   122,   108,     0,     0,
     150,   174,   110,   163,   108,     0,   127,   124,   156,     0,
     175,    92,     0,     0,   123,   108,     0,     0,     0,     0,
     176,   129,   108,   125,   163,   157,   151,     0,     0,   162,
       0,   126,     0,   155,     0,     0,   177,   163,   108,   151,
       0,     0,   128,   154,     0,     0,   108,   151,     0,   130,
     153,     0,   151,   152
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    52,    12,    13,    14,    15,    16,    64,    17,
      62,   129,    18,   101,    70,    20,    71,    72,   135,   311,
      21,    22,    23,    50,    81,    82,    24,    25,    26,    27,
     120,   181,   182,   104,    56,   105,   159,   106,   107,   254,
     255,   108,   165,   166,   319,   109,    74,    75,   193,   194,
     136,   123,   213,   110,   172,   111,   112,   113,   149,   114,
     406,   420,   115,   116,   117,   177,   265,   325,   377,   408,
     216,   217,   218,   219,   154,   155,   272,   401,   419,   242,
     243,   244,   355
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -300
static const yytype_int16 yypact[] =
{
     369,   -27,    24,    86,    87,    75,  -300,   274,  -300,  -300,
     111,     8,  -300,   274,   274,   274,    66,  -300,   274,  -300,
      16,  -300,  -300,    77,   274,  -300,   -49,   -22,  -300,  -300,
    -300,  -300,  -300,  -300,   139,   115,   162,   115,  -300,  -300,
    -300,  -300,  -300,  -300,   163,  -300,   118,  -300,   207,  -300,
      78,  -300,   274,   240,   164,  -300,   114,   115,   170,   171,
       3,   183,   127,   128,   134,   143,  -300,   198,  -300,  -300,
    -300,   145,   147,   115,    64,  -300,  -300,  -300,  -300,  -300,
      45,   154,  -300,    48,   215,  -300,  -300,   160,    84,    -4,
     211,  -300,  -300,  -300,  -300,  -300,  -300,  -300,   226,   228,
     173,   172,   175,   176,  -300,   182,   240,   177,   184,    18,
     185,  -300,   174,  -300,   178,   314,  -300,   118,  -300,   365,
    -300,   229,  -300,   115,   190,   255,   190,   265,   163,  -300,
    -300,    64,    22,  -300,   118,  -300,   270,  -300,   273,   207,
    -300,   278,   205,   279,  -300,   228,  -300,   218,  -300,   224,
    -300,  -300,   231,   234,   223,   230,  -300,  -300,  -300,   236,
     233,  -300,  -300,  -300,   286,  -300,   242,   260,   115,  -300,
      96,   306,  -300,   300,   308,   173,  -300,   118,    18,  -300,
      45,   254,  -300,    71,   190,  -300,   310,  -300,   190,  -300,
     258,  -300,   115,   267,   266,  -300,   190,  -300,  -300,  -300,
    -300,   275,   263,   328,   276,   335,   310,    27,   173,   240,
    -300,   115,  -300,   339,   260,   173,   281,  -300,   280,     0,
    -300,  -300,  -300,   284,    27,   260,   115,   345,   365,  -300,
     346,  -300,   312,  -300,  -300,  -300,   310,   310,   310,   310,
     310,   310,   370,  -300,    65,  -300,  -300,   190,  -300,    64,
     288,   293,   295,   307,   302,   311,  -300,  -300,   583,   118,
    -300,  -300,  -300,   260,    67,   317,   376,   304,   315,   313,
    -300,  -300,   118,    27,   115,   376,   260,  -300,  -300,  -300,
     382,  -300,   610,   169,   169,   169,   465,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   190,   297,  -300,   260,  -300,
     115,  -300,  -300,  -300,   381,  -300,   328,    27,   384,  -300,
      96,  -300,   327,  -300,   324,  -300,  -300,     0,   118,   260,
     329,   376,  -300,  -300,   332,   332,   332,   332,   332,   332,
     610,   610,   610,   610,   610,   169,   169,   169,   169,   332,
     332,   529,  -300,  -300,   583,    92,  -300,  -300,  -300,  -300,
     115,   190,   331,    96,   389,   115,    27,   376,    96,   336,
     310,  -300,   310,   260,   170,   334,   -18,   330,   260,   115,
     338,   347,    96,  -300,   583,   376,  -300,   170,   310,   399,
    -300,   407,   260,    96,   170,   348,  -300,  -300,   556,   353,
    -300,   190,   376,   359,  -300,   170,   363,   310,   366,   310,
     385,  -300,   170,  -300,    96,   583,   389,   397,   310,  -300,
     375,  -300,   373,  -300,   377,   310,   583,    96,   170,   389,
     431,   386,  -300,  -300,   379,   310,   170,   389,   497,  -300,
    -300,   393,   389,  -300
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -300,   140,  -300,  -300,  -300,   383,  -300,  -300,   326,  -300,
    -300,  -300,  -300,  -300,    13,  -300,   340,  -300,   150,  -300,
     -47,  -300,  -300,  -300,  -300,   322,  -300,  -300,  -300,  -300,
    -300,  -300,   235,     2,  -300,   -96,  -300,  -300,  -300,   146,
    -300,  -300,   262,  -300,  -121,   -45,  -300,   -70,   216,  -300,
     -35,  -238,  -190,  -300,  -300,  -300,  -300,  -300,   333,  -300,
    -300,  -300,  -300,   360,  -102,  -195,  -215,  -300,  -256,  -300,
    -299,   208,  -300,  -300,   -88,  -300,   149,  -300,  -300,  -192,
    -300,  -300,  -300
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -159
static const yytype_int16 yytable[] =
{
      59,    73,    61,   187,   137,   189,   103,   168,    40,  -106,
     161,   144,   259,    19,   258,   270,    28,     1,    37,    53,
      19,   362,   121,   -31,   266,   125,    19,    19,    19,   274,
      31,    19,   164,    90,   271,   275,    54,    19,    29,    30,
     388,   173,   174,    55,   281,   282,   283,   284,   285,   286,
      83,   322,   145,    58,   140,   389,    77,    78,    79,   103,
     330,   192,   141,   231,   375,    19,   102,   245,    58,   381,
      65,    66,   178,   318,   167,   250,   226,   229,   328,    34,
      67,    35,   138,   395,    46,   230,   331,   223,   185,    73,
     -31,    36,    32,    33,   403,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   261,   354,   422,   369,    39,   356,   102,
     260,   183,   360,   307,    65,    66,   308,   267,   431,   306,
      44,  -148,   224,   214,    67,   186,   386,   186,    48,   367,
      19,    83,    49,   225,   131,    57,    84,    38,  -118,   397,
      68,    69,   380,    41,    42,    43,   404,   247,    45,   371,
     423,   372,   103,  -158,    51,    58,   215,   413,    60,    63,
     396,   379,   118,   433,   421,   119,   263,   124,   383,   192,
     384,   440,   227,   385,   352,   122,   443,   411,   391,   126,
     432,   276,    85,   150,   151,   127,   398,   128,   439,   152,
     153,   130,   402,   131,   132,   287,   288,   289,   290,   291,
     292,   133,   134,    76,   317,   415,   142,   417,    77,    78,
      79,    80,   102,   139,   143,   146,   426,   327,   302,   303,
     183,   304,   147,   430,   148,   184,   171,   156,   170,   329,
     157,   158,   162,   438,    86,    87,    88,    66,   160,   163,
     169,    77,    78,    79,    89,    90,    67,     5,    91,    92,
     186,   188,    93,    94,    95,    96,     1,   190,     2,     3,
      97,   200,    68,    69,    -3,     1,   196,     2,     3,   197,
     410,     4,     5,   366,   199,    98,   203,   201,   204,   205,
       4,     5,   206,     6,   207,     7,    99,   209,   210,   208,
       8,   144,     6,   232,     7,   233,   234,   235,     9,     8,
     100,   211,    10,   212,   220,   221,   232,     9,   233,   234,
     235,    10,   222,   228,   246,   373,   248,   252,   173,   174,
     378,    -3,    91,    92,   253,   249,    93,    94,    95,    96,
      -3,   257,   251,   256,   392,   264,   236,   237,   268,   269,
     238,   277,   279,   239,   240,   273,   280,   310,   312,   236,
     237,   241,   313,   238,   353,   314,   239,   240,   315,    -3,
       1,   179,     2,     3,   241,   323,    77,    78,    79,   180,
     316,   320,   321,   215,   175,     4,     5,   324,   332,   358,
     361,   363,   364,   368,   304,   376,   390,     6,   374,     7,
     382,   387,   393,    47,     8,   399,   287,   288,   289,   290,
     291,   292,     9,   400,   394,   405,    10,   409,   293,   294,
     295,   296,   297,   298,   299,   300,   412,   414,   301,   302,
     303,   416,   304,   287,   288,   289,   290,   291,   292,   427,
     428,   305,   429,   418,   437,   293,   294,   295,   296,   297,
     298,   299,   300,   436,   191,   301,   302,   303,   442,   304,
     357,   198,   359,   278,   424,   309,   425,   287,   288,   289,
     290,   291,   292,   262,   195,   176,   365,   326,   202,   293,
     294,   295,   296,   297,   298,   299,   300,     0,     0,   301,
     302,   303,     0,   304,     0,     0,     0,     0,   434,     0,
     435,   287,   288,   289,   290,   291,   292,     0,     0,     0,
       0,     0,     0,   293,   294,   295,   296,   297,   298,   299,
     300,     0,     0,   301,   302,   303,     0,   304,     0,     0,
       0,     0,   333,   287,   288,   289,   290,   291,   292,     0,
       0,     0,     0,     0,     0,   293,   294,   295,   296,   297,
     298,   299,   300,     0,     0,   301,   302,   303,     0,   304,
       0,     0,     0,     0,   441,   287,   288,   289,   290,   291,
     292,     0,     0,     0,     0,     0,     0,   293,   294,   295,
     296,   297,   298,   299,   300,     0,     0,   301,   302,   303,
     370,   304,   287,   288,   289,   290,   291,   292,   407,     0,
       0,     0,     0,     0,   293,   294,   295,   296,   297,   298,
     299,   300,     0,     0,   301,   302,   303,     0,   304,   287,
     288,   289,   290,   291,   292,     0,     0,     0,     0,     0,
       0,   293,   294,   295,   296,   297,   298,   299,   300,     0,
       0,   301,   302,   303,     0,   304,   287,   288,   289,   290,
     291,   292,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   298,   299,   300,     0,     0,   301,   302,
     303,     0,   304
};

static const yytype_int16 yycheck[] =
{
      35,    46,    37,   124,    74,   126,    53,   109,     0,     6,
     106,    15,   207,     0,   206,    15,    43,     1,     5,    68,
       7,   320,    57,     1,   214,    60,    13,    14,    15,   224,
       6,    18,    14,    15,    34,   225,    58,    24,    65,    66,
      58,    14,    15,    65,   236,   237,   238,   239,   240,   241,
      48,   266,    56,    50,     6,    73,    11,    12,    13,   106,
     275,   131,    14,   184,   363,    52,    53,   188,    50,   368,
       6,     7,   117,   263,   109,   196,   178,     6,   273,     4,
      16,     6,    80,   382,    68,    14,   276,   175,   123,   134,
      68,    16,     6,     6,   393,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   209,   306,   414,   331,     6,   308,   106,
     208,   119,   317,   244,     6,     7,   247,   215,   427,    64,
      64,    64,   177,   168,    16,    70,   374,    70,    61,   329,
     127,   139,    65,   178,    60,     6,    68,     7,    64,   387,
      32,    33,   367,    13,    14,    15,   394,   192,    18,    67,
     416,    69,   209,    67,    24,    50,    70,   405,     6,     6,
     385,   366,     8,   429,   412,    61,   211,     6,   370,   249,
     372,   437,   180,   373,   305,    15,   442,   402,   378,     6,
     428,   226,    52,    20,    21,    68,   388,    69,   436,    26,
      27,    67,   392,    60,     6,    36,    37,    38,    39,    40,
      41,    66,    65,     6,   259,   407,     1,   409,    11,    12,
      13,    14,   209,    69,    64,    14,   418,   272,    59,    60,
     228,    62,     6,   425,     6,     6,    58,    65,    64,   274,
      65,    65,    65,   435,     4,     5,     6,     7,    66,    65,
      65,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      70,     6,    22,    23,    24,    25,     1,   127,     3,     4,
      30,    66,    32,    33,     0,     1,     6,     3,     4,     6,
     401,    16,    17,   328,     6,    45,    68,     8,    64,    58,
      16,    17,    58,    28,    71,    30,    56,    61,    65,    69,
      35,    15,    28,     6,    30,     8,     9,    10,    43,    35,
      70,    69,    47,    53,     8,    15,     6,    43,     8,     9,
      10,    47,    14,    69,    66,   360,    59,    64,    14,    15,
     365,    66,    18,    19,     6,    69,    22,    23,    24,    25,
      66,     6,    67,    67,   379,     6,    49,    50,    67,    69,
      53,     6,     6,    56,    57,    71,    44,    69,    65,    49,
      50,    64,    67,    53,    67,    58,    56,    57,    66,     0,
       1,     6,     3,     4,    64,    71,    11,    12,    13,    14,
      69,    64,     6,    70,    70,    16,    17,    72,     6,     8,
       6,    64,    68,    64,    62,     6,    66,    28,    67,    30,
      64,    67,    64,    20,    35,     6,    36,    37,    38,    39,
      40,    41,    43,     6,    67,    67,    47,    64,    48,    49,
      50,    51,    52,    53,    54,    55,    67,    64,    58,    59,
      60,    65,    62,    36,    37,    38,    39,    40,    41,    64,
      67,    71,    65,    58,    65,    48,    49,    50,    51,    52,
      53,    54,    55,    67,   128,    58,    59,    60,    65,    62,
     310,   139,   316,   228,    67,   249,    69,    36,    37,    38,
      39,    40,    41,   211,   134,   115,   327,   269,   145,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    67,    -1,
      69,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    58,    59,    60,    -1,    62,    -1,    -1,
      -1,    -1,    67,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    58,    59,    60,    -1,    62,
      -1,    -1,    -1,    -1,    67,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    58,    59,    60,
      61,    62,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    58,    59,    60,    -1,    62,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    58,    59,    60,    -1,    62,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    -1,    -1,    58,    59,
      60,    -1,    62
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
      57,    64,   153,   154,   155,   118,    66,   124,    59,    69,
     118,    67,    64,     6,   113,   114,    67,     6,   153,   139,
     148,   109,   116,   124,     6,   140,   126,   148,    67,    69,
      15,    34,   150,    71,   139,   126,   124,     6,   106,     6,
      44,   153,   153,   153,   153,   153,   153,    36,    37,    38,
      39,    40,    41,    48,    49,    50,    51,    52,    53,    54,
      55,    58,    59,    60,    62,    71,    64,   118,   118,   122,
      69,    93,    65,    67,    58,    66,    69,   119,   126,   118,
      64,     6,   140,    71,    72,   141,   145,   119,   139,   124,
     140,   126,     6,    67,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   118,    67,   153,   156,   126,    92,     8,   113,
     139,     6,   144,    64,    68,   150,   119,   126,    64,   140,
      61,    67,    69,   124,    67,   144,     6,   142,   124,   139,
     140,   144,    64,   153,   153,   126,   125,    67,    58,    73,
      66,   126,   124,    64,    67,   144,   140,   125,   153,     6,
       6,   151,   126,   144,   125,    67,   134,    42,   143,    64,
     118,   140,    67,   125,    64,   153,    65,   153,    58,   152,
     135,   125,   144,   142,    67,    69,   153,    64,    67,    65,
     153,   144,   125,   142,    67,    69,    67,    65,   153,   125,
     142,    67,    65,   142
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
#line 142 "parser.y"
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
#line 154 "parser.y"
    { 
	insideClass=false; 
	othercodes.SetSize(0); 
	startPos=-1;
}
    break;

  case 11:
#line 164 "parser.y"
    {
	CleanStack(); 
}
    break;

  case 13:
#line 171 "parser.y"
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
#line 269 "parser.y"
    {
	printf("handle at Bison\n");
	othercodes.InsertAt(-1,"\n",strlen("\n"));
}
    break;

  case 15:
#line 277 "parser.y"
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
#line 290 "parser.y"
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
#line 303 "parser.y"
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
#line 319 "parser.y"
    {
	
	printf("PACK IS HANDLE HERE %s\n", filename);
	isParclassDeclared = true; 
	currentPack->SetEndLine(linenumber-1);
  	currentPack=NULL;
  	othercodes.SetSize(0);
  	startPos=-1;
}
    break;

  case 19:
#line 330 "parser.y"
    {
	printf("PACK_KEYWORD\n");
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
			printf("PACK %s\n", GetToken((yyvsp[(1) - (2)])));			
		}
}
    break;

  case 21:
#line 360 "parser.y"
    {
	
	// Avoid handling of standard namespace used in POP-C++
	
	if(strcmp("__gnu_cxx", GetToken((yyvsp[(2) - (2)]))) != 0 &&  strcmp("std", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("__gnu_debug", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("rel_ops", GetToken((yyvsp[(2) - (2)]))) != 0  && strcmp("__debug", GetToken((yyvsp[(2) - (2)]))) != 0){
			
		isNamespace = true;
			
		sprintf(holdnamespace, "%s", GetToken((yyvsp[(2) - (2)])));
	
	}

}
    break;

  case 22:
#line 375 "parser.y"
    {
	
	isNamespace = false;

}
    break;

  case 23:
#line 384 "parser.y"
    {
}
    break;

  case 24:
#line 387 "parser.y"
    {
}
    break;

  case 25:
#line 395 "parser.y"
    {
    CleanStack();
}
    break;

  case 28:
#line 411 "parser.y"
    {
	
	sprintf(tmp,"Class declaration inside parclass are not currently supported !\n");
	
	errormsg(tmp);
	exit(1);

}
    break;

  case 29:
#line 428 "parser.y"
    {
  	currentstruct=Pop();
  	if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  	(yyval)=(yyvsp[(1) - (4)]);
  	structContainer = NULL;
  	isInStruct = false;
}
    break;

  case 30:
#line 436 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 31:
#line 442 "parser.y"
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

  case 32:
#line 476 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 36:
#line 492 "parser.y"
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
#line 530 "parser.y"
    {
	if(insideClass){
		sprintf(tmp,"typedef definition inside parclass are not currently supported !\n");
	
		errormsg(tmp);
		exit(1);
	}
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

  case 40:
#line 560 "parser.y"
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

  case 41:
#line 584 "parser.y"
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
#line 608 "parser.y"
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

  case 43:
#line 633 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 45:
#line 639 "parser.y"
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
#line 669 "parser.y"
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
#line 693 "parser.y"
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
#line 718 "parser.y"
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
#line 743 "parser.y"
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
#line 773 "parser.y"
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
#line 794 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 56:
#line 802 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 57:
#line 811 "parser.y"
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
#line 845 "parser.y"
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
#line 859 "parser.y"
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
#line 874 "parser.y"
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
#line 891 "parser.y"
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
#line 910 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 67:
#line 914 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 68:
#line 918 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 69:
#line 925 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 70:
#line 929 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 73:
#line 939 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 79:
#line 947 "parser.y"
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
#line 963 "parser.y"
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
#line 974 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 82:
#line 979 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 83:
#line 990 "parser.y"
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
#line 1001 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);	
}
    break;

  case 85:
#line 1005 "parser.y"
    {
	sprintf(tmp,"%s , %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 86:
#line 1012 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 87:
#line 1016 "parser.y"
    {      
	sprintf(tmp,"%s = %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
   (yyval)=PutToken(tmp);
}
    break;

  case 91:
#line 1033 "parser.y"
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
#line 1064 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 93:
#line 1068 "parser.y"
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
#line 1083 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 95:
#line 1087 "parser.y"
    {
	
	
	(yyval)=0;
}
    break;

  case 96:
#line 1095 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 97:
#line 1099 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 98:
#line 1105 "parser.y"
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

  case 99:
#line 1116 "parser.y"
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
#line 1132 "parser.y"
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
#line 1151 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 102:
#line 1157 "parser.y"
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
#line 1170 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 104:
#line 1177 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 105:
#line 1186 "parser.y"
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
#line 1258 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 107:
#line 1263 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 108:
#line 1271 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 109:
#line 1275 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 110:
#line 1281 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 111:
#line 1285 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 116:
#line 1303 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 117:
#line 1309 "parser.y"
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
#line 1325 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 119:
#line 1334 "parser.y"
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
#line 1343 "parser.y"
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
#line 1356 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 122:
#line 1486 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 123:
#line 1493 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 124:
#line 1500 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 125:
#line 1507 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 126:
#line 1514 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 127:
#line 1521 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 128:
#line 1522 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 129:
#line 1528 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 130:
#line 1529 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 131:
#line 1539 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 132:
#line 1543 "parser.y"
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

  case 133:
#line 1589 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 134:
#line 1593 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 135:
#line 1597 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 136:
#line 1601 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 137:
#line 1605 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 138:
#line 1609 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 139:
#line 1616 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 140:
#line 1620 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 141:
#line 1624 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 142:
#line 1628 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 143:
#line 1635 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 144:
#line 1639 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 145:
#line 1643 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 146:
#line 1647 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 147:
#line 1651 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 148:
#line 1657 "parser.y"
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
#line 1668 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 150:
#line 1672 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 151:
#line 1678 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 152:
#line 1683 "parser.y"
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
#line 1700 "parser.y"
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
#line 1716 "parser.y"
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
#line 1731 "parser.y"
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
#line 1823 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 157:
#line 1827 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 162:
#line 1842 "parser.y"
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
#line 1878 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 164:
#line 1882 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 165:
#line 1888 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 166:
#line 1892 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 167:
#line 1898 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 168:
#line 1902 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 169:
#line 1906 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 170:
#line 1911 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 171:
#line 1919 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 172:
#line 1923 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 173:
#line 1927 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 174:
#line 1933 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 175:
#line 1937 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 176:
#line 1943 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 177:
#line 1947 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 178:
#line 1960 "parser.y"
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
#line 1969 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 180:
#line 1973 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 181:
#line 1977 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:
#line 1982 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:
#line 1987 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:
#line 1992 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:
#line 1997 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:
#line 2002 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:
#line 2007 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:
#line 2012 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:
#line 2017 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:
#line 2022 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:
#line 2027 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:
#line 2032 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 193:
#line 2037 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 194:
#line 2042 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 195:
#line 2047 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 196:
#line 2052 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 197:
#line 2057 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 198:
#line 2062 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 199:
#line 2067 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 200:
#line 2072 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 201:
#line 2077 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 202:
#line 2082 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 203:
#line 2088 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 204:
#line 2093 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 205:
#line 2098 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 206:
#line 2103 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 207:
#line 2110 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 208:
#line 2114 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 209:
#line 2120 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 210:
#line 2124 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 211:
#line 2132 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 212:
#line 2136 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;


/* Line 1267 of yacc.c.  */
#line 4026 "parser.tab.c"
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


#line 2144 "parser.y"


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
	isWarningEnable=true;
	isImplicitPackEnable=true;

	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")!=NULL){
		
		broker=false;
	
	} 	
	
	
	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")!=NULL) {
		
		client=false;
	
	}  
	
	if (paroc_utils::checkremove(&argc,&argv,"-no-warning")!=NULL) {
		
		isWarningEnable=false;
	
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
		if ((ret=ParseFile(argv[1], ((argc>2) ? argv[2] : NULL), client, broker, isWarningEnable, isImplicitPackEnable))!=0)	{
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

int ParseFile(char *infile, char *outfile, bool client, bool broker, bool isWarningEnable, bool isImplicitPackEnable)
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


