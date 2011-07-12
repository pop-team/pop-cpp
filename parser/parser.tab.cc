/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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

#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"


  //Declaration in parser.lex:
  
  int  PutToken(char *str);
  int PutToken(char chr);
  char *GetToken(int yyval);

  void errormsg(const  char *s);

  int yywrap();
  void yyerror(const  char *s);
  int yylex();
  int yywrap();

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

 TypeSeqClass *seqclass;


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


 paroc_list<TypeStruct *>  typestack;
 TypeStruct *currentstruct;
 void CleanStack();
 void Push(TypeStruct *x);
 TypeStruct *Pop();
 TypeStruct *Peek();

 int counter=0;
 int errorcode=0;

 AccessType  accessmodifier=PUBLIC;

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
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 264 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   495

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  70
/* YYNRULES -- Number of rules. */
#define YYNRULES  176
/* YYNRULES -- Number of states. */
#define YYNSTATES  350

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     5,     9,    12,    15,    18,    21,
      24,    27,    30,    33,    38,    40,    43,    44,    47,    49,
      51,    53,    58,    61,    64,    66,    67,    71,    74,    79,
      80,    83,    89,    95,    98,   104,   107,   110,   111,   114,
     116,   120,   122,   125,   129,   133,   139,   142,   145,   146,
     149,   151,   155,   157,   160,   164,   168,   170,   172,   174,
     175,   178,   179,   184,   187,   190,   192,   198,   201,   203,
     207,   212,   213,   218,   221,   223,   225,   227,   229,   231,
     236,   238,   241,   243,   247,   252,   257,   258,   261,   262,
     264,   266,   268,   270,   276,   278,   283,   289,   291,   299,
     308,   309,   321,   322,   335,   337,   340,   342,   344,   346,
     348,   350,   352,   354,   356,   357,   362,   363,   374,   383,
     390,   391,   394,   395,   397,   399,   403,   412,   413,   417,
     419,   423,   425,   427,   431,   435,   436,   438,   440,   441,
     443,   444,   447,   450,   452,   454,   458,   462,   466,   470,
     474,   478,   482,   486,   490,   494,   498,   502,   508,   512,
     516,   520,   524,   528,   531,   535,   539,   544,   547,   550,
     553,   556,   558,   560,   562,   566,   568
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      71,     0,    -1,    -1,    -1,    92,    72,    71,    -1,    86,
      71,    -1,    29,    71,    -1,    74,    71,    -1,    78,    71,
      -1,    73,    71,    -1,     1,    61,    -1,     1,    62,    -1,
       1,    42,    -1,    75,    60,    76,    63,    -1,    34,    -1,
       6,    77,    -1,    -1,    64,    76,    -1,    79,    -1,    85,
      -1,    87,    -1,    80,    65,    81,    62,    -1,    80,    73,
      -1,    16,     6,    -1,    16,    -1,    -1,    82,    61,    81,
      -1,   106,    83,    -1,   111,     6,   105,    84,    -1,    -1,
      64,    83,    -1,    17,     6,   111,     6,   105,    -1,    17,
      79,   111,     6,   105,    -1,    94,    61,    -1,    88,    89,
      65,     1,    62,    -1,    88,    61,    -1,     4,     6,    -1,
      -1,    57,    90,    -1,    91,    -1,    90,    64,    91,    -1,
       6,    -1,    98,     6,    -1,    14,    98,     6,    -1,    98,
      14,     6,    -1,    93,    65,    99,    62,    61,    -1,    94,
      95,    -1,     3,     6,    -1,    -1,    57,    96,    -1,    97,
      -1,    96,    64,    97,    -1,     6,    -1,    98,     6,    -1,
      14,    98,     6,    -1,    98,    14,     6,    -1,    13,    -1,
      11,    -1,    12,    -1,    -1,   101,    99,    -1,    -1,    98,
     100,    57,    99,    -1,   113,    61,    -1,   102,    61,    -1,
      29,    -1,     5,    60,     8,    63,    61,    -1,   106,   103,
      -1,   104,    -1,   104,    64,   103,    -1,   111,   112,     6,
     105,    -1,    -1,    66,   136,    67,   105,    -1,   107,   108,
      -1,   108,    -1,    31,    -1,    32,    -1,     6,    -1,     7,
      -1,     6,    56,   109,    55,    -1,    79,    -1,    16,     6,
      -1,   110,    -1,   110,    64,   109,    -1,     6,   111,   105,
     112,    -1,     7,   111,   105,   112,    -1,    -1,    46,   111,
      -1,    -1,    49,    -1,   114,    -1,   116,    -1,   118,    -1,
     115,    60,   127,    63,   124,    -1,     6,    -1,    52,   117,
      60,    63,    -1,    14,    52,   117,    60,    63,    -1,     6,
      -1,   106,   111,   112,   123,    60,   127,    63,    -1,   121,
     106,   111,   112,   123,    60,   127,    63,    -1,    -1,    66,
     131,    67,   106,   111,   112,   123,   119,    60,   127,    63,
      -1,    -1,   121,    66,   131,    67,   106,   111,   112,   123,
     120,    60,   127,    63,    -1,   122,    -1,   121,   122,    -1,
      14,    -1,    18,    -1,    19,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,     6,    -1,    -1,    68,    65,   125,
      62,    -1,    -1,     6,    69,     6,    60,   136,    64,   136,
      63,    61,   125,    -1,     6,    69,     6,    60,   136,    63,
      61,   125,    -1,     6,    54,   136,   126,    61,   125,    -1,
      -1,    41,   136,    -1,    -1,   128,    -1,   129,    -1,   129,
      64,   128,    -1,   130,   133,   106,   111,   112,   134,   105,
     135,    -1,    -1,    66,   131,    67,    -1,   132,    -1,   132,
      64,   131,    -1,    20,    -1,    21,    -1,    27,    54,   136,
      -1,    26,    54,     6,    -1,    -1,    15,    -1,    33,    -1,
      -1,     6,    -1,    -1,    54,   136,    -1,   138,   105,    -1,
     137,    -1,    10,    -1,   136,    44,   136,    -1,   136,    45,
     136,    -1,   136,    46,   136,    -1,   136,    47,   136,    -1,
     136,    48,   136,    -1,   136,    49,   136,    -1,   136,    50,
     136,    -1,   136,    51,   136,    -1,   136,    35,   136,    -1,
     136,    36,   136,    -1,   136,    37,   136,    -1,   136,    54,
     136,    -1,   136,    58,   136,    57,   136,    -1,   136,    38,
     136,    -1,   136,    55,   136,    -1,   136,    56,   136,    -1,
     136,    39,   136,    -1,   136,    40,   136,    -1,    45,   136,
      -1,    60,   136,    63,    -1,   138,    60,    63,    -1,   138,
      60,   139,    63,    -1,    46,   136,    -1,    49,   136,    -1,
      53,   136,    -1,    52,   136,    -1,     8,    -1,     9,    -1,
       6,    -1,     6,    43,     6,    -1,   136,    -1,   139,    64,
     136,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   108,   108,   118,   118,   119,   120,   121,   122,   123,
     129,   142,   155,   171,   182,   200,   210,   212,   220,   224,
     225,   232,   237,   243,   269,   278,   279,   281,   284,   304,
     305,   313,   335,   359,   379,   380,   382,   403,   404,   408,
     409,   412,   435,   458,   481,   510,   518,   526,   551,   552,
     555,   556,   559,   565,   572,   579,   588,   592,   596,   606,
     607,   608,   608,   611,   627,   638,   643,   653,   655,   656,
     659,   690,   693,   708,   712,   718,   722,   728,   742,   757,
     772,   777,   794,   798,   805,   820,   839,   843,   850,   853,
     865,   866,   867,   870,   885,   895,   904,   917,   926,   945,
     974,   974,   991,   991,  1022,  1026,  1032,  1036,  1040,  1044,
    1048,  1052,  1056,  1062,  1074,  1077,  1084,  1087,  1103,  1118,
    1193,  1196,  1204,  1205,  1207,  1208,  1211,  1246,  1249,  1255,
    1259,  1265,  1269,  1273,  1278,  1286,  1289,  1293,  1300,  1303,
    1310,  1313,  1326,  1335,  1339,  1343,  1348,  1353,  1358,  1363,
    1368,  1373,  1378,  1383,  1388,  1393,  1398,  1403,  1408,  1413,
    1418,  1423,  1428,  1433,  1438,  1443,  1448,  1454,  1459,  1464,
    1469,  1477,  1481,  1487,  1491,  1498,  1502
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
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
  "'.'", "$accept", "startlist", "@1", "not_care_code", "pack_directive",
  "pack_header", "object_list", "rest_object_list", "type_definition",
  "struct_definition", "struct_head", "struct_body", "struct_element",
  "struct_elname_list", "struct_elname_other", "typedef_definition",
  "class_prototype", "seqclass_definition", "seqclass_header",
  "seqbase_spec", "seqbase_list", "seqbase_specifier", "class_declaration",
  "class_head", "class_key", "base_spec", "base_list", "base_specifier",
  "access_specifier", "member_list", "@2", "member_declaration",
  "attribute_definition", "attribute_name_list", "attribute_name",
  "array_declarator", "decl_specifier", "storage_class_specifier",
  "type_specifier", "template_arguments", "template_arg",
  "pointer_specifier", "ref_specifier", "function_definition",
  "constructor_definition", "constructor_name", "destructor_definition",
  "destructor_name", "method_definition", "@3", "@4", "fct_specifier",
  "fct_spec", "function_name", "od_specifier", "od_exprlist",
  "od_expr_nonstrict", "argument_declaration", "argument_list",
  "arg_declaration", "marshal_decl", "marshal_opt_list", "marshal_opt",
  "cv_qualifier", "argument_name", "arg_default_value", "expr_decl",
  "number", "expr_name", "expr_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
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
static const unsigned char yyr1[] =
{
       0,    70,    71,    72,    71,    71,    71,    71,    71,    71,
      73,    73,    73,    74,    75,    76,    77,    77,    78,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    83,    84,
      84,    85,    85,    86,    87,    87,    88,    89,    89,    90,
      90,    91,    91,    91,    91,    92,    93,    94,    95,    95,
      96,    96,    97,    97,    97,    97,    98,    98,    98,    99,
      99,   100,    99,   101,   101,   101,   101,   102,   103,   103,
     104,   105,   105,   106,   106,   107,   107,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   113,   114,   115,   116,   116,   117,   118,   118,
     119,   118,   120,   118,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   123,   124,   124,   125,   125,   125,   125,
     126,   126,   127,   127,   128,   128,   129,   130,   130,   131,
     131,   132,   132,   132,   132,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   137,   137,   138,   138,   139,   139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     1,     2,     0,     2,     1,     1,
       1,     4,     2,     2,     1,     0,     3,     2,     4,     0,
       2,     5,     5,     2,     5,     2,     2,     0,     2,     1,
       3,     1,     2,     3,     3,     5,     2,     2,     0,     2,
       1,     3,     1,     2,     3,     3,     1,     1,     1,     0,
       2,     0,     4,     2,     2,     1,     5,     2,     1,     3,
       4,     0,     4,     2,     1,     1,     1,     1,     1,     4,
       1,     2,     1,     3,     4,     4,     0,     2,     0,     1,
       1,     1,     1,     5,     1,     4,     5,     1,     7,     8,
       0,    11,     0,    12,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,    10,     8,     6,
       0,     2,     0,     1,     1,     3,     8,     0,     3,     1,
       3,     1,     1,     3,     3,     0,     1,     1,     0,     1,
       0,     2,     2,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     3,
       3,     3,     3,     2,     3,     3,     4,     2,     2,     2,
       2,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,    24,     0,     0,    14,     0,     0,
       0,     0,     0,    18,     0,    19,     0,    20,    37,     3,
       0,    48,    12,    10,    11,    47,    36,    23,    86,    86,
       6,     1,     9,     7,     0,     8,    25,    22,     5,     0,
      35,     0,     0,    59,     0,    33,    46,    86,     0,     0,
      16,     0,    77,    78,    24,    75,    76,    80,     0,     0,
      86,     0,    74,    41,    57,    58,    56,     0,    38,    39,
       0,     0,     4,     0,    77,   106,   107,   108,   109,   110,
     111,   112,    65,     0,     0,    61,     0,    59,     0,    86,
       0,    90,     0,    91,    92,     0,   104,    52,     0,    49,
      50,     0,    87,    71,    71,     0,    15,    13,     0,    81,
      21,    25,    27,     0,    73,     0,     0,    42,     0,     0,
       0,     0,    97,     0,   131,   132,     0,     0,     0,   129,
       0,     0,    60,    64,    67,    68,    88,    63,   127,   106,
       0,    86,   105,     0,     0,    53,     0,     0,    31,    32,
      17,    86,    86,     0,    82,    26,    71,    43,    40,    44,
      34,     0,     0,     0,     0,     0,     0,     0,    59,    45,
      86,    89,     0,     0,     0,   123,   124,   135,     0,    88,
      54,    51,    55,   173,   171,   172,   144,     0,     0,     0,
       0,     0,     0,     0,   143,    71,    71,    71,    79,     0,
      29,     0,     0,    95,   134,   133,    86,   130,    62,    69,
      88,    71,     0,     0,   114,   127,   136,   137,     0,     0,
       0,     0,   163,   167,   168,   170,   169,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,   142,    88,
      88,    83,    86,    28,    66,    96,    88,     0,    70,   127,
     128,     0,    93,   125,    86,    86,   113,     0,   174,   164,
     153,   154,   155,   158,   161,   162,   145,   146,   147,   148,
     149,   150,   151,   152,   156,   159,   160,     0,    72,   165,
     175,     0,    84,    85,    30,     0,    71,     0,   116,    88,
      88,   127,     0,   166,     0,   100,    98,     0,     0,   138,
       0,     0,   157,   176,     0,     0,     0,   115,   139,    71,
     102,    99,   127,   120,     0,   140,     0,     0,     0,     0,
       0,     0,   126,   127,   101,   121,   116,     0,   141,     0,
     119,     0,     0,   103,   116,     0,   118,     0,   116,   117
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     8,    42,     9,    10,    11,    51,   106,    12,    57,
      14,    58,    59,   112,   253,    15,    16,    17,    18,    41,
      68,    69,    19,    20,    21,    46,    99,   100,    85,    86,
     130,    87,    88,   134,   135,   258,    89,    61,    62,   153,
     154,   113,   172,    90,    91,    92,    93,   123,    94,   314,
     326,    95,    96,   212,   262,   308,   329,   174,   175,   176,
     177,   128,   129,   218,   319,   332,   193,   194,   195,   291
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -253
static const short yypact[] =
{
      30,   -18,    42,    45,    78,    46,    30,  -253,    99,    30,
      30,    37,    30,  -253,     7,  -253,    30,  -253,    10,  -253,
      36,    17,  -253,  -253,  -253,  -253,  -253,  -253,    58,    58,
    -253,  -253,  -253,  -253,   106,  -253,    34,  -253,  -253,   158,
    -253,    62,    30,   177,   260,  -253,  -253,    58,   127,   133,
      77,    81,   112,  -253,   169,  -253,  -253,  -253,   115,   120,
      58,   160,  -253,  -253,  -253,  -253,  -253,   192,   121,  -253,
      74,   191,  -253,   134,    13,   145,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,   201,   153,  -253,   136,   177,   149,    58,
     156,  -253,   159,  -253,  -253,   245,  -253,  -253,   192,   157,
    -253,    97,  -253,   162,   162,   106,  -253,  -253,   109,    12,
    -253,    34,  -253,   217,  -253,   218,   158,  -253,   229,   178,
     230,   201,  -253,   179,  -253,  -253,   187,   188,   180,   181,
     193,   183,  -253,  -253,  -253,   190,   209,  -253,   -48,  -253,
     153,    58,  -253,   256,   260,  -253,   259,    83,  -253,  -253,
    -253,    58,    58,   220,   214,  -253,   162,  -253,  -253,  -253,
    -253,   216,   221,   219,   274,    83,    34,   153,   177,  -253,
      58,  -253,   278,   153,   222,  -253,   223,    23,   224,   209,
    -253,  -253,  -253,   240,  -253,  -253,  -253,    83,    83,    83,
      83,    83,    83,   277,  -253,   -31,   162,   162,  -253,   109,
     225,   227,   231,  -253,  -253,   437,    58,  -253,  -253,  -253,
     209,    -6,   226,   228,   233,   232,  -253,  -253,    34,    34,
     284,   291,  -253,   176,    82,    82,    82,   331,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,   162,   247,  -253,   209,
     209,  -253,    58,  -253,  -253,  -253,   209,   296,  -253,   -48,
    -253,   238,  -253,  -253,    58,    58,  -253,   244,  -253,  -253,
     248,   248,   248,   248,   248,   248,   176,   176,   176,   176,
     176,    82,    82,    82,    82,   248,   248,   389,  -253,  -253,
     437,    67,  -253,  -253,  -253,   284,   162,   242,   302,   209,
     209,   -48,    83,  -253,    83,  -253,  -253,   -12,   257,   303,
     284,   255,  -253,   437,   269,    83,   314,  -253,  -253,   162,
    -253,  -253,   -48,   413,   270,   280,   282,   290,    83,   293,
      83,    83,  -253,   -48,  -253,   437,   302,   301,   437,   295,
    -253,   299,    83,  -253,   302,   360,  -253,   300,   302,  -253
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -253,    16,  -253,   329,  -253,  -253,   258,  -253,  -253,    11,
    -253,   251,  -253,   122,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,   267,  -253,  -253,  -253,  -253,  -253,   246,   -30,   -81,
    -253,  -253,  -253,   202,  -253,  -101,   -32,  -253,   312,   185,
    -253,   -28,  -174,  -253,  -253,  -253,  -253,   271,  -253,  -253,
    -253,  -253,   298,  -210,  -253,  -246,  -253,  -252,   173,  -253,
    -253,  -128,  -253,  -253,  -253,  -253,   -82,  -253,  -253,  -253
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -123
static const short yytable[] =
{
      48,    49,   148,   149,    60,   220,   132,   297,     1,    70,
     267,    13,   178,   -23,   101,  -122,    29,    13,   173,   102,
      13,    13,    30,    13,    22,    32,    33,    13,    35,   247,
      -2,     1,    38,     2,     3,   147,   257,   115,   216,   207,
      52,    53,   315,    23,    24,   213,     4,     5,    25,   311,
      54,    26,    28,    13,  -113,   200,   217,   316,    72,     6,
     147,   136,     4,   141,     7,    55,    56,    39,   143,   108,
     327,    40,    36,   -94,    44,   292,   293,   -23,    45,    60,
     117,   339,   295,   205,    27,   305,    70,   208,   118,   183,
     340,   184,   185,   186,   248,   249,   250,    34,   346,    31,
     320,    43,   349,   145,    47,   222,   223,   224,   225,   226,
     227,   146,    50,   179,   101,   151,   152,   228,   229,   230,
     231,   232,   233,   196,   197,   309,   310,    71,   187,   188,
     303,   304,   189,   103,   206,   190,   191,   243,   244,   104,
     245,   105,   210,   192,   107,   288,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,    63,   290,    52,    53,   108,    64,
      65,    66,    67,   124,   125,   109,    54,   110,   256,   126,
     127,   111,    73,    74,    53,   116,   264,   265,    64,    65,
      66,    75,   119,    54,   120,    76,    77,   121,   131,    78,
      79,    80,    81,    64,    65,    66,    82,   122,    55,    56,
     133,   228,   229,   230,   231,   232,   233,   137,   325,   138,
     312,   144,   313,   156,   157,   239,   240,   241,   147,    83,
     242,   243,   244,   323,   245,   159,   299,   300,   161,   163,
     160,   164,   165,    84,   169,   167,   335,   166,   337,   338,
     168,    52,    53,   183,   170,   184,   185,   186,   171,   139,
     345,    54,   180,    76,    77,   182,    97,    78,    79,    80,
      81,    64,    65,    66,    98,   198,    55,    56,   199,   201,
     204,   202,   203,   221,   211,   214,   259,   215,   254,   252,
     266,   219,   187,   188,   255,   260,   189,   268,   173,   190,
     191,   261,   296,   298,   301,   306,   245,   192,   307,   318,
     289,   140,   228,   229,   230,   231,   232,   233,   321,   317,
     324,   234,   235,   236,   237,   238,   239,   240,   241,   322,
     330,   242,   243,   244,   331,   245,   228,   229,   230,   231,
     232,   233,   333,    37,   246,   234,   235,   236,   237,   238,
     239,   240,   241,   334,   336,   242,   243,   244,   343,   245,
     344,   348,   155,   150,   341,   342,   228,   229,   230,   231,
     232,   233,   209,   114,   294,   234,   235,   236,   237,   238,
     239,   240,   241,   158,   251,   242,   243,   244,   263,   245,
     181,     0,   162,   142,   269,   228,   229,   230,   231,   232,
     233,     0,     0,     0,   234,   235,   236,   237,   238,   239,
     240,   241,     0,     0,   242,   243,   244,     0,   245,     0,
       0,     0,     0,   347,   228,   229,   230,   231,   232,   233,
       0,     0,     0,   234,   235,   236,   237,   238,   239,   240,
     241,     0,     0,   242,   243,   244,   302,   245,   228,   229,
     230,   231,   232,   233,   328,     0,     0,   234,   235,   236,
     237,   238,   239,   240,   241,     0,     0,   242,   243,   244,
       0,   245,   228,   229,   230,   231,   232,   233,     0,     0,
       0,   234,   235,   236,   237,   238,   239,   240,   241,     0,
       0,   242,   243,   244,     0,   245
};

static const short yycheck[] =
{
      28,    29,   103,   104,    36,   179,    87,   259,     1,    39,
     220,     0,   140,     1,    44,    63,     5,     6,    66,    47,
       9,    10,     6,    12,    42,     9,    10,    16,    12,    60,
       0,     1,    16,     3,     4,    66,   210,    67,    15,   167,
       6,     7,    54,    61,    62,   173,    16,    17,     6,   301,
      16,     6,     6,    42,    60,   156,    33,    69,    42,    29,
      66,    89,    16,    95,    34,    31,    32,    57,    98,    56,
     322,    61,    65,    60,    57,   249,   250,    65,    61,   111,
       6,   333,   256,   165,     6,   295,   116,   168,    14,     6,
     336,     8,     9,    10,   195,   196,   197,    60,   344,     0,
     310,    65,   348,     6,    46,   187,   188,   189,   190,   191,
     192,    14,     6,   141,   144,     6,     7,    35,    36,    37,
      38,    39,    40,   151,   152,   299,   300,    65,    45,    46,
      63,    64,    49,     6,   166,    52,    53,    55,    56,     6,
      58,    64,   170,    60,    63,   246,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,     6,   247,     6,     7,    56,    11,
      12,    13,    14,    20,    21,     6,    16,    62,   206,    26,
      27,    61,     5,     6,     7,    64,   218,   219,    11,    12,
      13,    14,     1,    16,    60,    18,    19,    52,    62,    22,
      23,    24,    25,    11,    12,    13,    29,     6,    31,    32,
      61,    35,    36,    37,    38,    39,    40,    61,   319,    60,
     302,    64,   304,     6,     6,    49,    50,    51,    66,    52,
      54,    55,    56,   315,    58,     6,   264,   265,     8,    60,
      62,    54,    54,    66,    61,    64,   328,    67,   330,   331,
      57,     6,     7,     6,    64,     8,     9,    10,    49,    14,
     342,    16,     6,    18,    19,     6,     6,    22,    23,    24,
      25,    11,    12,    13,    14,    55,    31,    32,    64,    63,
       6,    60,    63,    43,     6,    63,    60,    64,    61,    64,
       6,    67,    45,    46,    63,    67,    49,     6,    66,    52,
      53,    68,     6,    65,    60,    63,    58,    60,     6,     6,
      63,    66,    35,    36,    37,    38,    39,    40,    63,    62,
       6,    44,    45,    46,    47,    48,    49,    50,    51,    60,
      60,    54,    55,    56,    54,    58,    35,    36,    37,    38,
      39,    40,    60,    14,    67,    44,    45,    46,    47,    48,
      49,    50,    51,    63,    61,    54,    55,    56,    63,    58,
      61,    61,   111,   105,    63,    64,    35,    36,    37,    38,
      39,    40,   170,    61,   252,    44,    45,    46,    47,    48,
      49,    50,    51,   116,   199,    54,    55,    56,   215,    58,
     144,    -1,   121,    95,    63,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    54,    55,    56,    -1,    58,    -1,
      -1,    -1,    -1,    63,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    54,    55,    56,    57,    58,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    -1,    54,    55,    56,
      -1,    58,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    54,    55,    56,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,     4,    16,    17,    29,    34,    71,    73,
      74,    75,    78,    79,    80,    85,    86,    87,    88,    92,
      93,    94,    42,    61,    62,     6,     6,     6,     6,    79,
      71,     0,    71,    71,    60,    71,    65,    73,    71,    57,
      61,    89,    72,    65,    57,    61,    95,    46,   111,   111,
       6,    76,     6,     7,    16,    31,    32,    79,    81,    82,
     106,   107,   108,     6,    11,    12,    13,    14,    90,    91,
      98,    65,    71,     5,     6,    14,    18,    19,    22,    23,
      24,    25,    29,    52,    66,    98,    99,   101,   102,   106,
     113,   114,   115,   116,   118,   121,   122,     6,    14,    96,
      97,    98,   111,     6,     6,    64,    77,    63,    56,     6,
      62,    61,    83,   111,   108,    98,    64,     6,    14,     1,
      60,    52,     6,   117,    20,    21,    26,    27,   131,   132,
     100,    62,    99,    61,   103,   104,   111,    61,    60,    14,
      66,   106,   122,    98,    64,     6,    14,    66,   105,   105,
      76,     6,     7,   109,   110,    81,     6,     6,    91,     6,
      62,     8,   117,    60,    54,    54,    67,    64,    57,    61,
      64,    49,   112,    66,   127,   128,   129,   130,   131,   111,
       6,    97,     6,     6,     8,     9,    10,    45,    46,    49,
      52,    53,    60,   136,   137,   138,   111,   111,    55,    64,
     105,    63,    60,    63,     6,   136,   106,   131,    99,   103,
     111,     6,   123,   131,    63,    64,    15,    33,   133,    67,
     112,    43,   136,   136,   136,   136,   136,   136,    35,    36,
      37,    38,    39,    40,    44,    45,    46,    47,    48,    49,
      50,    51,    54,    55,    56,    58,    67,    60,   105,   105,
     105,   109,    64,    84,    61,    63,   111,   112,   105,    60,
      67,    68,   124,   128,   106,   106,     6,   123,     6,    63,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   105,    63,
     136,   139,   112,   112,    83,   112,     6,   127,    65,   111,
     111,    60,    57,    63,    64,   123,    63,     6,   125,   112,
     112,   127,   136,   136,   119,    54,    69,    62,     6,   134,
     123,    63,    60,   136,     6,   105,   120,   127,    41,   126,
      60,    54,   135,    60,    63,   136,    61,   136,   136,   127,
     125,    63,    64,    63,    61,   136,   125,    63,    61,   125
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 108 "parser.y"
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
#line 118 "parser.y"
    { insideClass=false; othercodes.SetSize(0); startPos=-1;}
    break;

  case 9:
#line 124 "parser.y"
    {
  CleanStack();
}
    break;

  case 10:
#line 130 "parser.y"
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
#line 143 "parser.y"
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
  YYACCEPT;
}
    break;

  case 13:
#line 172 "parser.y"
    {
  currentPack->SetEndLine(linenumber-1);

  currentPack=NULL;
  othercodes.SetSize(0);
  startPos=-1;
  
}
    break;

  case 14:
#line 183 "parser.y"
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
#line 201 "parser.y"
    {
  if (currentPack!=NULL)
    {
      currentPack->AddObject(GetToken(yyvsp[-1]));
    }
}
    break;

  case 16:
#line 210 "parser.y"
    {
}
    break;

  case 17:
#line 213 "parser.y"
    {
}
    break;

  case 18:
#line 221 "parser.y"
    {
    CleanStack();
}
    break;

  case 21:
#line 233 "parser.y"
    {
  currentstruct=Pop();
  yyval=yyvsp[-3];
}
    break;

  case 22:
#line 238 "parser.y"
    {
  currentstruct=Pop();
  yyval=yyvsp[-1];
}
    break;

  case 23:
#line 244 "parser.y"
    {
  char *tname=GetToken(yyvsp[0]);
  DataType *type=thisCodeFile->FindDataType(tname);
  TypeStruct *t;
  if (type!=NULL)
    {
      t=dynamic_cast<TypeStruct *>(type);
      if (t==NULL)
	{
	  thisCodeFile->RemoveDataType(type);
	  delete type;
	  t=new TypeStruct(tname);
	  thisCodeFile->AddDataType(t);
	  //	  sprintf(tmp,"data type \"%s\" has been redefined!\n",tname);
	  //	  errormsg(tmp);
	}
    } 
  else
    { 
      t=new TypeStruct(tname);
      thisCodeFile->AddDataType(t);
    }
  Push(t);
  yyval=yyvsp[0];
}
    break;

  case 24:
#line 270 "parser.y"
    {
  TypeStruct *t=new TypeStruct(NULL);
  thisCodeFile->AddDataType(t);
  Push(t);
  yyval=-1;
}
    break;

  case 28:
#line 285 "parser.y"
    {
  DataType *type1=currenttype;
  if (yyvsp[-3]>0)
    {
      type1=new TypePtr(NULL,yyvsp[-3], type1);
      thisCodeFile->AddDataType(type1);
    }
  if (yyvsp[-1]!=-1)
    {
      type1=new TypeArray(NULL,GetToken(yyvsp[-1]), type1);
      thisCodeFile->AddDataType(type1);     
    }  
  TypeStruct *t=Peek();
  assert(t!=NULL);
  t->Add(type1, GetToken(yyvsp[-2]));

}
    break;

  case 31:
#line 314 "parser.y"
    {
  char *orgtype=GetToken(yyvsp[-3]);
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new DataType(orgtype);
      thisCodeFile->AddDataType(type);
    }
  if (yyvsp[-2]>0)
    {
      type=new TypePtr(NULL,yyvsp[-2], type);
      thisCodeFile->AddDataType(type);
    }
  if (yyvsp[0]!=-1)
    {
      type=new TypeArray(NULL,GetToken(yyvsp[0]), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken(yyvsp[-1]),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 32:
#line 336 "parser.y"
    {
  DataType *type=currentstruct;
  assert(type!=NULL);

  if (yyvsp[-2]>0)
    {
      type=new TypePtr(NULL,yyvsp[-2], type);
      thisCodeFile->AddDataType(type);
    }
  if (yyvsp[0]!=-1)
    {
      type=new TypeArray(NULL,GetToken(yyvsp[0]), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken(yyvsp[-1]),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 33:
#line 360 "parser.y"
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

  case 36:
#line 383 "parser.y"
    {
  DataType *t=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (t==NULL)
    {
      seqclass=new TypeSeqClass(GetToken(yyvsp[0]));
      thisCodeFile->AddDataType(seqclass);
    }
  else if (!t->IsStandardType())
    {
      seqclass=dynamic_cast<TypeSeqClass *>(t);
      if (seqclass==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"%s has been declared as non-class data type", GetToken(yyvsp[0]));
	  errormsg(tmp);
	  exit(1);
	}
    }
}
    break;

  case 41:
#line 413 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeSeqClass *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (t==NULL)
    {
      seqbase=new TypeSeqClass(GetToken(yyvsp[0]));
      seqclass->AddBase(seqbase);  
    }
  else if (!t->IsStandardType())
    {
      seqbase=dynamic_cast<TypeSeqClass *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken(yyvsp[0]));
	  errormsg(tmp);
	  exit(1);
	}
      seqclass->AddBase(seqbase);
    }
}
    break;

  case 42:
#line 436 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeSeqClass *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (t==NULL)
    {
      seqbase=new TypeSeqClass(GetToken(yyvsp[0]));
      seqclass->AddBase(seqbase);  
    }
  else  if (!t->IsStandardType())
    {
      seqbase=dynamic_cast<TypeSeqClass *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken(yyvsp[0]));
	  errormsg(tmp);
	  exit(1);
	}
      seqclass->AddBase(seqbase);
    }
}
    break;

  case 43:
#line 459 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeSeqClass *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (t==NULL)
    {
      seqbase=new TypeSeqClass(GetToken(yyvsp[0]));
      seqclass->AddBase(seqbase);  
    }
  else  if (!t->IsStandardType())
    {
      seqbase=dynamic_cast<TypeSeqClass *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken(yyvsp[0]));
	  errormsg(tmp);
	  exit(1);
	}
      seqclass->AddBase(seqbase);
    }
}
    break;

  case 44:
#line 482 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeSeqClass *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (t==NULL)
    {
      seqbase=new TypeSeqClass(GetToken(yyvsp[0]));
      seqclass->AddBase(seqbase);
    }
  else  if (!t->IsStandardType())
    {
      seqbase=dynamic_cast<TypeSeqClass *>(t);
      if (seqbase==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"base class %s has been declared as non-class data type", GetToken(yyvsp[0]));
	  errormsg(tmp);
	  exit(1);
	}
      seqclass->AddBase(seqbase);
    }
}
    break;

  case 45:
#line 511 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 46:
#line 519 "parser.y"
    {
  accessmodifier=PUBLIC;
  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 47:
#line 527 "parser.y"
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
  char *clname=GetToken(yyvsp[0]);
  
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

  case 52:
#line 560 "parser.y"
    {
	assert(currentClass!=NULL);
	BaseClass *t=new BaseClass(GetToken(yyvsp[0]),PUBLIC,false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 53:
#line 566 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)yyvsp[-1];
	BaseClass *t=new BaseClass(GetToken(yyvsp[0]),accessmode,false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 54:
#line 573 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)yyvsp[-1];
	BaseClass *t=new BaseClass(GetToken(yyvsp[0]),accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 55:
#line 580 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)yyvsp[-2];
	BaseClass *t=new BaseClass(GetToken(yyvsp[0]),accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 56:
#line 589 "parser.y"
    {
	yyval=PRIVATE;
}
    break;

  case 57:
#line 593 "parser.y"
    {
	yyval=PUBLIC;
}
    break;

  case 58:
#line 597 "parser.y"
    {
	yyval=PROTECTED;
}
    break;

  case 61:
#line 608 "parser.y"
    { accessmodifier=(AccessType)yyvsp[0]; }
    break;

  case 63:
#line 612 "parser.y"
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

  case 64:
#line 628 "parser.y"
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

  case 65:
#line 639 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 66:
#line 644 "parser.y"
    {
  currentClass->SetClassID(GetToken(yyvsp[-2]));
}
    break;

  case 70:
#line 660 "parser.y"
    {

  assert(currentClass!=NULL);
  Attribute *t=new Attribute(currentClass,accessmodifier);
  t->SetLineInfo(linenumber-1);
  currentClass->AddMember(t);
  Param *tparam=t->NewAttribute();
  DataType *type;
  strcpy(tparam->name,GetToken(yyvsp[-1]));
  if (yyvsp[-3]==0)
    {
      type=currenttype;
    }
  else 
    {
      type=new TypePtr(NULL, yyvsp[-3] , currenttype);
      thisCodeFile->AddDataType(type);
    }

  if (yyvsp[0]!=-1)
    {
      type=new TypeArray(NULL, GetToken(yyvsp[0]) , type);
      thisCodeFile->AddDataType(type);
    }
  tparam->isRef=yyvsp[-2];
  tparam->SetType(type);
}
    break;

  case 71:
#line 690 "parser.y"
    {
  yyval=-1;
}
    break;

  case 72:
#line 694 "parser.y"
    {
  if (yyvsp[0]==-1)
    {
      sprintf(tmp,"[%s]",GetToken(yyvsp[-2]));
      yyval=PutToken(tmp);
    }
  else
    {
      sprintf(tmp,"[%s]%s",GetToken(yyvsp[-2]),GetToken(yyvsp[0]));
      yyval=PutToken(tmp);
    }
}
    break;

  case 73:
#line 709 "parser.y"
    {
  yyval=yyvsp[-1];
}
    break;

  case 74:
#line 713 "parser.y"
    {
  yyval=0;
}
    break;

  case 75:
#line 719 "parser.y"
    {
  yyval=1;  
}
    break;

  case 76:
#line 723 "parser.y"
    {
  yyval=2;
}
    break;

  case 77:
#line 729 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken(yyvsp[0]));
      thisCodeFile->AddDataType(currenttype);
      /* 
	 sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	 errormsg(tmp);
	 exit(1);
      */
    }
}
    break;

  case 78:
#line 743 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken(yyvsp[0]));
      thisCodeFile->AddDataType(currenttype);

      /*
	sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	errormsg(tmp);
	exit(1);
      */
    }
}
    break;

  case 79:
#line 758 "parser.y"
    {
  sprintf(tmp,"%s<%s>",GetToken(yyvsp[-3]), GetToken(yyvsp[-1]));
  currenttype=thisCodeFile->FindDataType(GetToken(yyvsp[-3]));
  if (currenttype==NULL)
    {
      currenttype=new DataType(tmp);
      thisCodeFile->AddDataType(currenttype);
      /*
	sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	errormsg(tmp);
	exit(1);
      */
    }
}
    break;

  case 80:
#line 773 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
}
    break;

  case 81:
#line 778 "parser.y"
    {
  DataType *type=thisCodeFile->FindDataType(GetToken(yyvsp[0]));
  if (type==NULL)
    {
      type=new TypeStruct(GetToken(yyvsp[0]));
      thisCodeFile->AddDataType(type);
      /*
	sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	errormsg(tmp);
	exit(1);
      */
    } 
  currenttype=type;
}
    break;

  case 82:
#line 795 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 83:
#line 799 "parser.y"
    {
  sprintf(tmp,"%s,%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 84:
#line 806 "parser.y"
    {
  if (yyvsp[-2]==0 && yyvsp[-1]==-1 && yyvsp[0]==0)
    {
      yyval=yyvsp[-3];
    }
  else
    {
      strcpy(tmp, GetToken(yyvsp[-3]));
      for (int i=0;i<yyvsp[-2]; i++) strcat(tmp, "*"); 
      if (yyvsp[-1]!=-1) strcat(tmp,GetToken(yyvsp[-1]));
      if (yyvsp[0]) strcat(tmp,"&");
      yyval=PutToken(tmp);
    }
}
    break;

  case 85:
#line 821 "parser.y"
    {
  if (yyvsp[-2]==0 && yyvsp[-1]==-1 && yyvsp[0]==0)
    {
      yyval=yyvsp[-3];
    }
  else
    {
      strcpy(tmp, GetToken(yyvsp[-3]));
      for (int i=0;i<yyvsp[-2]; i++) strcat(tmp, "*"); 
      if (yyvsp[-1]!=-1) strcat(tmp,GetToken(yyvsp[-1]));
      if (yyvsp[0]) strcat(tmp,"&");
      yyval=PutToken(tmp);
    }
}
    break;

  case 86:
#line 839 "parser.y"
    {
  yyval=0;
  
}
    break;

  case 87:
#line 844 "parser.y"
    {
  yyval=yyvsp[0]+1;
}
    break;

  case 88:
#line 850 "parser.y"
    {
  yyval=0;
}
    break;

  case 89:
#line 854 "parser.y"
    {
  yyval=1;
}
    break;

  case 93:
#line 871 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of constructor\n");
      exit(1);
    }
  if (yyvsp[0]!=-1)
    {
      ObjDesc &od=((Constructor *)method)->GetOD();
      od.SetCode(GetToken(yyvsp[0]));
    }
}
    break;

  case 94:
#line 886 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  currentClass->AddMember(method);
  strcpy(method->name,GetToken(yyvsp[0]));
}
    break;

  case 95:
#line 896 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 96:
#line 905 "parser.y"
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

  case 97:
#line 918 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken(yyvsp[0]));
}
    break;

  case 98:
#line 927 "parser.y"
    {
  //Old data:  argument_type function_name 
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if (yyvsp[-5]>0)
    {
      type=new TypePtr(NULL, yyvsp[-5] , type);
      thisCodeFile->AddDataType(type);
    }

  if (yyvsp[-4])
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);

}
    break;

  case 99:
#line 946 "parser.y"
    {
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if (yyvsp[-5]>0)
    {
      type=new TypePtr(NULL, yyvsp[-5] , type);
      thisCodeFile->AddDataType(type);
    }
  
  if (yyvsp[-4])
    {
      method->returnparam.isRef=true;
    }

  method->returnparam.SetType(type);

  method->isVirtual=((yyvsp[-7] & 1)!=0);
  if ((yyvsp[-7] & 8)!=0) method->isConcurrent=true;
  else if ((yyvsp[-7] & 32)!=0) method->isConcurrent=false;

  method->isHidden=((yyvsp[-7] & 64)!=0);
  method->isMutex=((yyvsp[-7] & 16)!=0);

  if ((yyvsp[-7] & 6)==2) method->invoketype=invokesync;
  else if ((yyvsp[-7] & 6)==4) method->invoketype=invokeasync;
  /*	else method->invoketype=autoselect; */
}
    break;

  case 100:
#line 974 "parser.y"
    { UpdateMarshalParam(yyvsp[-5],&(method->returnparam) ); }
    break;

  case 101:
#line 975 "parser.y"
    {
  DataType *type=returntype;
  if (yyvsp[-6]>0)
    {
      type=new TypePtr(NULL, yyvsp[-6] , type);
      thisCodeFile->AddDataType(type);
    }
  
  if (yyvsp[-5])
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);
  
  strcpy(method->returnparam.name,"_RemoteRet");
}
    break;

  case 102:
#line 991 "parser.y"
    { UpdateMarshalParam(yyvsp[-5],&(method->returnparam) ); }
    break;

  case 103:
#line 992 "parser.y"
    {
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if (yyvsp[-6]>0)
    {
      type=new TypePtr(NULL, yyvsp[-6] , type);
      thisCodeFile->AddDataType(type);
    }
  
  if (yyvsp[-5])
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);

  method->isVirtual=((yyvsp[-11] & 1)!=0);

  if ((yyvsp[-11] & 8)!=0) method->isConcurrent=true;
  else if ((yyvsp[-11] & 32)!=0) method->isConcurrent=false;
  
  method->isMutex=((yyvsp[-11] & 16)!=0);
  method->isHidden=((yyvsp[-11] & 64)!=0);
  
  if ((yyvsp[-11] & 6)==2) method->invoketype=invokesync;
  else if ((yyvsp[-11] & 6)==4) method->invoketype=invokeasync;
  /* else method->invoketype=autoselect; */
}
    break;

  case 104:
#line 1023 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 105:
#line 1027 "parser.y"
    {
  yyval=yyvsp[-1] | yyvsp[0];
}
    break;

  case 106:
#line 1033 "parser.y"
    {
	yyval=1;
}
    break;

  case 107:
#line 1037 "parser.y"
    {
	yyval=2;
}
    break;

  case 108:
#line 1041 "parser.y"
    {
	yyval=4;
}
    break;

  case 109:
#line 1045 "parser.y"
    {
	yyval=8;
}
    break;

  case 110:
#line 1049 "parser.y"
    {
	yyval=32;
}
    break;

  case 111:
#line 1053 "parser.y"
    {
  yyval=16;
}
    break;

  case 112:
#line 1057 "parser.y"
    {
  yyval=64;
}
    break;

  case 113:
#line 1063 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken(yyvsp[0]));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 114:
#line 1074 "parser.y"
    {
  yyval=-1;
}
    break;

  case 115:
#line 1078 "parser.y"
    {
  yyval=yyvsp[-1];
}
    break;

  case 116:
#line 1084 "parser.y"
    {
  yyval=-1;
}
    break;

  case 117:
#line 1088 "parser.y"
    {

  char *odtmp=GetToken(yyvsp[-9]);
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken(yyvsp[-7]));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s,%s);",GetToken(yyvsp[-7]),GetToken(yyvsp[-5]),GetToken(yyvsp[-3]));
  if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 118:
#line 1104 "parser.y"
    {
  char *odtmp=GetToken(yyvsp[-7]);
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken(yyvsp[-5]));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s);",GetToken(yyvsp[-5]),GetToken(yyvsp[-3]));
  if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 119:
#line 1119 "parser.y"
    {
    char *odtmp=GetToken(yyvsp[-5]);
    if (paroc_utils::isEqual(odtmp,"host"))
      {
	sprintf(tmp,"od.url(%s);",GetToken(yyvsp[-3]));
	if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
	if (yyvsp[-2]!=-1)
	  {
	    errormsg("OD: host should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"jobcontact"))
      {
	sprintf(tmp,"od.joburl(%s);",GetToken(yyvsp[-3]));
	if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
	if (yyvsp[-2]!=-1)
	  {
	    errormsg("OD: jobcontact should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"memory"))
      {
	sprintf(tmp,"od.memory(%s",GetToken(yyvsp[-3]));
	if (yyvsp[-2]!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken(yyvsp[-2]));
	  }
	strcat(tmp,");");
	if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
      } 
    else if (paroc_utils::isEqual(odtmp,"power"))
      {
	sprintf(tmp,"od.power(%s",GetToken(yyvsp[-3]));
	if (yyvsp[-2]!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken(yyvsp[-2]));
	  }
	strcat(tmp,");");
	if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
      } 
    else if (paroc_utils::isEqual(odtmp,"network"))
    {
	sprintf(tmp,"od.bandwidth(%s",GetToken(yyvsp[-3]));
	if (yyvsp[-2]!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken(yyvsp[-2]));
	  }
	strcat(tmp,");");
	if (yyvsp[0]!=-1) strcat(tmp,GetToken(yyvsp[0]));
    } 
    else if (paroc_utils::isEqual(odtmp,"walltime"))
      {
	sprintf(tmp,"od.walltime(%s);",GetToken(yyvsp[-3]));
	if (yyvsp[-2]!=-1)
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
    yyval=PutToken(tmp);
}
    break;

  case 120:
#line 1193 "parser.y"
    {
    yyval=-1;
}
    break;

  case 121:
#line 1197 "parser.y"
    {
    yyval=yyvsp[0];
}
    break;

  case 126:
#line 1212 "parser.y"
    {
  Param *t=method->AddNewParam();
  UpdateMarshalParam(yyvsp[-7],t);

  DataType *type=currenttype;
  if (yyvsp[-4]>0)
    {
      type=new TypePtr(NULL, yyvsp[-4] , type);
      thisCodeFile->AddDataType(type);
    }

  if (yyvsp[-3])
    {
      t->isRef=true;
    }

  if (yyvsp[-1]!=-1)
    {
      type=new TypeArray(NULL, GetToken(yyvsp[-1]) , type);
      thisCodeFile->AddDataType(type);
    }

  t->SetType(type);
  if (yyvsp[-2]!=-1) strcpy(t->name,GetToken(yyvsp[-2]));
  else   sprintf(t->name,"V_%d",++counter);

  t->isConst=(yyvsp[-6]==1);
  if (yyvsp[0]>=0) t->defaultVal=strdup(GetToken(yyvsp[0]));
  

}
    break;

  case 127:
#line 1246 "parser.y"
    {
  yyval=0;
}
    break;

  case 128:
#line 1250 "parser.y"
    {
  yyval=yyvsp[-1];
}
    break;

  case 129:
#line 1256 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 130:
#line 1260 "parser.y"
    {
  yyval=yyvsp[-2] | yyvsp[0] ;
}
    break;

  case 131:
#line 1266 "parser.y"
    {
  yyval=PARAM_IN;
}
    break;

  case 132:
#line 1270 "parser.y"
    {
  yyval=PARAM_OUT;
}
    break;

  case 133:
#line 1274 "parser.y"
    {
  strcpy(tmpSize,GetToken(yyvsp[0]));
  yyval=PARAMSIZE;
}
    break;

  case 134:
#line 1279 "parser.y"
    {
  strcpy(tmpProc,GetToken(yyvsp[0]));
  yyval=USERPROC;
}
    break;

  case 135:
#line 1286 "parser.y"
    {
	yyval=0;
}
    break;

  case 136:
#line 1290 "parser.y"
    {
	yyval=1;
}
    break;

  case 137:
#line 1294 "parser.y"
    {
	yyval=2;
}
    break;

  case 138:
#line 1300 "parser.y"
    {
	yyval=-1;
}
    break;

  case 139:
#line 1304 "parser.y"
    {
	yyval=yyvsp[0];
}
    break;

  case 140:
#line 1310 "parser.y"
    {
  yyval=-1;
}
    break;

  case 141:
#line 1314 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 142:
#line 1327 "parser.y"
    {
  if (yyvsp[0]<0) yyval=yyvsp[-1];
  else 
    {
      sprintf(tmp, "%s%s",GetToken(yyvsp[-1]),GetToken(yyvsp[0]));
      yyval=PutToken(tmp);
    }
}
    break;

  case 143:
#line 1336 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 144:
#line 1340 "parser.y"
    {
    yyval=yyvsp[0];
}
    break;

  case 145:
#line 1344 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 146:
#line 1349 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 147:
#line 1354 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 148:
#line 1359 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 149:
#line 1364 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 150:
#line 1369 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 151:
#line 1374 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 152:
#line 1379 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 153:
#line 1384 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 154:
#line 1389 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 155:
#line 1394 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 156:
#line 1399 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 157:
#line 1404 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken(yyvsp[-4]), GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 158:
#line 1409 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 159:
#line 1414 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 160:
#line 1419 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 161:
#line 1424 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 162:
#line 1429 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken(yyvsp[-2]), GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 163:
#line 1434 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 164:
#line 1439 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken(yyvsp[-1]));
  yyval=PutToken(tmp);
}
    break;

  case 165:
#line 1444 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken(yyvsp[-2]));
  yyval=PutToken(tmp);
}
    break;

  case 166:
#line 1449 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken(yyvsp[-3]),GetToken(yyvsp[-1]));
  yyval=PutToken(tmp);
 
}
    break;

  case 167:
#line 1455 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 168:
#line 1460 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 169:
#line 1465 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 170:
#line 1470 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;

  case 171:
#line 1478 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 172:
#line 1482 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 173:
#line 1488 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 174:
#line 1492 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken(yyvsp[-2]),GetToken(yyvsp[0]));
  yyval=PutToken(tmp);  
}
    break;

  case 175:
#line 1499 "parser.y"
    {
  yyval=yyvsp[0];
}
    break;

  case 176:
#line 1503 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken(yyvsp[-2]),GetToken(yyvsp[0]));
  yyval=PutToken(tmp);
}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 3128 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1511 "parser.y"


#include "config.h"

void Usage()
{
  fprintf(stderr,"ParoC++ preprocessor version %s\nparoccpp [-onlyclient | -onlyserver] [ParoC++ source] [C++ source]\n", VERSION);
  exit(1);
}

void CleanStack()
{
  if (typestack.GetCount()) fprintf(stderr,"STRUCT list: %d elements\n",typestack.GetCount());
  currentstruct=NULL;
  typestack.RemoveAll();
}

void Push(TypeStruct *x)
{
  typestack.AddHead(x);
}

TypeStruct *Pop()
{
  POSITION pos=typestack.GetHeadPosition();
  if (pos==NULL) return NULL;
  TypeStruct *t=typestack.GetAt(pos);
  typestack.RemoveHead();
  return t;
}

TypeStruct *Peek()
{
  POSITION pos=typestack.GetHeadPosition();
  if (pos==NULL) return NULL;
  TypeStruct *t=typestack.GetAt(pos);
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
  int ret;
  indexsource=-1;
  errorcode=0;
  bool client=true;
  bool broker=true;
  if (paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")!=NULL) broker=false;
  if (paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")!=NULL) client=false;

  if (argc<2) Usage();
  else
    {
      if ((ret=ParseFile(argv[1], ((argc>2) ? argv[2] : NULL), client, broker))!=0)
	{
	  fprintf(stderr,"Parse ParoC++ code failed (error=%d)\n",ret);
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



