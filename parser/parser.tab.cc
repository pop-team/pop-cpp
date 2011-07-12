/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 273 "parser.tab.c"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
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
	  YYSIZE_T yyi;				\
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   489

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  70
/* YYNRULES -- Number of rules. */
#define YYNRULES  178
/* YYNRULES -- Number of states. */
#define YYNSTATES  360

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
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
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,     5,     9,    12,    15,    18,    21,
      24,    27,    30,    33,    38,    40,    43,    44,    47,    49,
      51,    53,    58,    61,    64,    66,    67,    71,    74,    79,
      80,    83,    89,    96,   103,   109,   115,   118,   121,   122,
     125,   127,   131,   133,   136,   140,   144,   147,   153,   156,
     159,   160,   163,   165,   169,   171,   174,   178,   182,   184,
     186,   188,   189,   192,   193,   198,   201,   204,   206,   212,
     215,   217,   221,   226,   227,   232,   235,   237,   239,   241,
     243,   245,   250,   252,   255,   257,   261,   266,   271,   272,
     275,   276,   278,   280,   282,   284,   290,   292,   297,   303,
     305,   313,   322,   323,   335,   336,   349,   351,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   371,   376,   377,
     388,   397,   404,   405,   408,   409,   411,   413,   417,   426,
     427,   431,   433,   437,   439,   441,   445,   449,   450,   452,
     454,   455,   457,   458,   461,   464,   466,   468,   472,   476,
     480,   484,   488,   492,   496,   500,   504,   508,   512,   516,
     522,   526,   530,   534,   538,   542,   545,   549,   553,   558,
     561,   564,   567,   570,   572,   574,   576,   580,   582
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      71,     0,    -1,    -1,    -1,    92,    72,    71,    -1,    91,
      71,    -1,    29,    71,    -1,    74,    71,    -1,    78,    71,
      -1,    73,    71,    -1,     1,    61,    -1,     1,    62,    -1,
       1,    42,    -1,    75,    60,    76,    63,    -1,    34,    -1,
       6,    77,    -1,    -1,    64,    76,    -1,    79,    -1,    85,
      -1,    86,    -1,    80,    65,    81,    62,    -1,    80,    73,
      -1,    16,     6,    -1,    16,    -1,    -1,    82,    61,    81,
      -1,   106,    83,    -1,   111,     6,   105,    84,    -1,    -1,
      64,    83,    -1,    17,     6,   111,     6,   105,    -1,    17,
      16,     6,   111,     6,   105,    -1,    17,     4,     6,   111,
       6,   105,    -1,    17,    79,   111,     6,   105,    -1,    87,
      88,    65,     1,    62,    -1,    87,    61,    -1,     4,     6,
      -1,    -1,    57,    89,    -1,    90,    -1,    89,    64,    90,
      -1,     6,    -1,    98,     6,    -1,    14,    98,     6,    -1,
      98,    14,     6,    -1,    94,    61,    -1,    93,    65,    99,
      62,    61,    -1,    94,    95,    -1,     3,     6,    -1,    -1,
      57,    96,    -1,    97,    -1,    96,    64,    97,    -1,     6,
      -1,    98,     6,    -1,    14,    98,     6,    -1,    98,    14,
       6,    -1,    13,    -1,    11,    -1,    12,    -1,    -1,   101,
      99,    -1,    -1,    98,   100,    57,    99,    -1,   113,    61,
      -1,   102,    61,    -1,    29,    -1,     5,    60,     8,    63,
      61,    -1,   106,   103,    -1,   104,    -1,   104,    64,   103,
      -1,   111,   112,     6,   105,    -1,    -1,    66,   136,    67,
     105,    -1,   107,   108,    -1,   108,    -1,    31,    -1,    32,
      -1,     6,    -1,     7,    -1,     6,    56,   109,    55,    -1,
      79,    -1,    16,     6,    -1,   110,    -1,   110,    64,   109,
      -1,     6,   111,   105,   112,    -1,     7,   111,   105,   112,
      -1,    -1,    46,   111,    -1,    -1,    49,    -1,   114,    -1,
     116,    -1,   118,    -1,   115,    60,   127,    63,   124,    -1,
       6,    -1,    52,   117,    60,    63,    -1,    14,    52,   117,
      60,    63,    -1,     6,    -1,   106,   111,   112,   123,    60,
     127,    63,    -1,   121,   106,   111,   112,   123,    60,   127,
      63,    -1,    -1,    66,   131,    67,   106,   111,   112,   123,
     119,    60,   127,    63,    -1,    -1,   121,    66,   131,    67,
     106,   111,   112,   123,   120,    60,   127,    63,    -1,   122,
      -1,   121,   122,    -1,    14,    -1,    18,    -1,    19,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,     6,    -1,
      -1,    68,    65,   125,    62,    -1,    -1,     6,    69,     6,
      60,   136,    64,   136,    63,    61,   125,    -1,     6,    69,
       6,    60,   136,    63,    61,   125,    -1,     6,    54,   136,
     126,    61,   125,    -1,    -1,    41,   136,    -1,    -1,   128,
      -1,   129,    -1,   129,    64,   128,    -1,   130,   133,   106,
     111,   112,   134,   105,   135,    -1,    -1,    66,   131,    67,
      -1,   132,    -1,   132,    64,   131,    -1,    20,    -1,    21,
      -1,    27,    54,   136,    -1,    26,    54,     6,    -1,    -1,
      15,    -1,    33,    -1,    -1,     6,    -1,    -1,    54,   136,
      -1,   138,   105,    -1,   137,    -1,    10,    -1,   136,    44,
     136,    -1,   136,    45,   136,    -1,   136,    46,   136,    -1,
     136,    47,   136,    -1,   136,    48,   136,    -1,   136,    49,
     136,    -1,   136,    50,   136,    -1,   136,    51,   136,    -1,
     136,    35,   136,    -1,   136,    36,   136,    -1,   136,    37,
     136,    -1,   136,    54,   136,    -1,   136,    58,   136,    57,
     136,    -1,   136,    38,   136,    -1,   136,    55,   136,    -1,
     136,    56,   136,    -1,   136,    39,   136,    -1,   136,    40,
     136,    -1,    45,   136,    -1,    60,   136,    63,    -1,   138,
      60,    63,    -1,   138,    60,   139,    63,    -1,    46,   136,
      -1,    49,   136,    -1,    53,   136,    -1,    52,   136,    -1,
       8,    -1,     9,    -1,     6,    -1,     6,    43,     6,    -1,
     136,    -1,   139,    64,   136,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   108,   108,   118,   118,   119,   120,   121,   122,   123,
     129,   142,   155,   171,   182,   200,   210,   212,   220,   224,
     225,   232,   238,   244,   271,   280,   281,   283,   286,   306,
     307,   315,   337,   359,   381,   405,   409,   411,   432,   433,
     437,   438,   441,   465,   490,   515,   550,   568,   576,   584,
     609,   610,   613,   614,   617,   623,   630,   637,   646,   650,
     654,   664,   665,   666,   666,   669,   685,   696,   701,   711,
     713,   714,   717,   748,   751,   766,   770,   776,   780,   786,
     800,   815,   830,   835,   852,   856,   863,   878,   897,   901,
     908,   911,   923,   924,   925,   928,   945,   954,   963,   976,
     985,  1004,  1033,  1033,  1050,  1050,  1081,  1085,  1091,  1095,
    1099,  1103,  1107,  1111,  1115,  1121,  1133,  1136,  1143,  1146,
    1162,  1177,  1252,  1255,  1263,  1264,  1266,  1267,  1270,  1305,
    1308,  1314,  1318,  1324,  1328,  1332,  1337,  1345,  1348,  1352,
    1359,  1362,  1369,  1372,  1385,  1394,  1398,  1402,  1407,  1412,
    1417,  1422,  1427,  1432,  1437,  1442,  1447,  1452,  1457,  1462,
    1467,  1472,  1477,  1482,  1487,  1492,  1497,  1502,  1507,  1513,
    1518,  1523,  1528,  1536,  1540,  1546,  1550,  1557,  1561
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
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
  "seqclass_definition", "seqclass_header", "seqbase_spec", "seqbase_list",
  "seqbase_specifier", "class_prototype", "class_declaration",
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
static const unsigned short int yytoknum[] =
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
      84,    85,    85,    85,    85,    86,    86,    87,    88,    88,
      89,    89,    90,    90,    90,    90,    91,    92,    93,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    98,    98,
      98,    99,    99,   100,    99,   101,   101,   101,   101,   102,
     103,   103,   104,   105,   105,   106,   106,   107,   107,   108,
     108,   108,   108,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   113,   114,   115,   116,   116,   117,
     118,   118,   119,   118,   120,   118,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   123,   124,   124,   125,   125,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   130,
     130,   131,   131,   132,   132,   132,   132,   133,   133,   133,
     134,   134,   135,   135,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   137,   138,   138,   139,   139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     1,     2,     0,     2,     1,     1,
       1,     4,     2,     2,     1,     0,     3,     2,     4,     0,
       2,     5,     6,     6,     5,     5,     2,     2,     0,     2,
       1,     3,     1,     2,     3,     3,     2,     5,     2,     2,
       0,     2,     1,     3,     1,     2,     3,     3,     1,     1,
       1,     0,     2,     0,     4,     2,     2,     1,     5,     2,
       1,     3,     4,     0,     4,     2,     1,     1,     1,     1,
       1,     4,     1,     2,     1,     3,     4,     4,     0,     2,
       0,     1,     1,     1,     1,     5,     1,     4,     5,     1,
       7,     8,     0,    11,     0,    12,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,    10,
       8,     6,     0,     2,     0,     1,     1,     3,     8,     0,
       3,     1,     3,     1,     1,     3,     3,     0,     1,     1,
       0,     1,     0,     2,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       3,     3,     3,     3,     3,     2,     3,     3,     4,     2,
       2,     2,     2,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,    24,     0,     0,    14,     0,     0,
       0,     0,     0,    18,     0,    19,    20,    38,     0,     3,
       0,    50,    12,    10,    11,    49,    37,    23,     0,    88,
      24,    88,     6,     1,     9,     7,     0,     8,    25,    22,
       0,    36,     0,     5,     0,    61,     0,    46,    48,    88,
      88,     0,    23,     0,    16,     0,    79,    80,    24,    77,
      78,    82,     0,     0,    88,     0,    76,    42,    59,    60,
      58,     0,    39,    40,     0,     0,     4,     0,    79,   108,
     109,   110,   111,   112,   113,   114,    67,     0,     0,    63,
       0,    61,     0,    88,     0,    92,     0,    93,    94,     0,
     106,    54,     0,    51,    52,     0,     0,    89,    73,     0,
      73,     0,    15,    13,     0,    83,    21,    25,    27,     0,
      75,     0,     0,    43,     0,     0,     0,     0,    99,     0,
     133,   134,     0,     0,     0,   131,     0,     0,    62,    66,
      69,    70,    90,    65,   129,   108,     0,    88,   107,     0,
       0,    55,     0,    73,     0,    31,    73,    34,    17,    88,
      88,     0,    84,    26,    73,    44,    41,    45,    35,     0,
       0,     0,     0,     0,     0,     0,    61,    47,    88,    91,
       0,     0,     0,   125,   126,   137,     0,    90,    56,    53,
      57,    33,   175,   173,   174,   146,     0,     0,     0,     0,
       0,     0,     0,   145,    73,    32,    73,    73,    81,     0,
      29,     0,     0,    97,   136,   135,    88,   132,    64,    71,
      90,    73,     0,     0,   116,   129,   138,   139,     0,     0,
       0,     0,   165,   169,   170,   172,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,     0,   144,    90,
      90,    85,    88,    28,    68,    98,    90,     0,    72,   129,
     130,     0,    95,   127,    88,    88,   115,     0,   176,   166,
     155,   156,   157,   160,   163,   164,   147,   148,   149,   150,
     151,   152,   153,   154,   158,   161,   162,     0,    74,   167,
     177,     0,    86,    87,    30,     0,    73,     0,   118,    90,
      90,   129,     0,   168,     0,   102,   100,     0,     0,   140,
       0,     0,   159,   178,     0,     0,     0,   117,   141,    73,
     104,   101,   129,   122,     0,   142,     0,     0,     0,     0,
       0,     0,   128,   129,   103,   123,   118,     0,   143,     0,
     121,     0,     0,   105,   118,     0,   120,     0,   118,   119
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     8,    44,     9,    10,    11,    55,   112,    12,    61,
      14,    62,    63,   118,   263,    15,    16,    17,    42,    72,
      73,    18,    19,    20,    21,    48,   103,   104,    89,    90,
     136,    91,    92,   140,   141,   268,    93,    65,    66,   161,
     162,   119,   180,    94,    95,    96,    97,   129,    98,   324,
     336,    99,   100,   222,   272,   318,   339,   182,   183,   184,
     185,   134,   135,   228,   329,   342,   202,   203,   204,   301
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -282
static const short int yypact[] =
{
     172,   -31,    41,    60,    61,     9,   172,  -282,    74,   172,
     172,    16,   172,  -282,     3,  -282,  -282,   -24,   172,  -282,
      56,   -23,  -282,  -282,  -282,  -282,  -282,  -282,   100,    78,
     133,    78,  -282,  -282,  -282,  -282,   136,  -282,   129,  -282,
     228,  -282,    85,  -282,   172,   191,   241,  -282,  -282,    78,
      78,   137,     8,   146,    89,    93,   108,  -282,   159,  -282,
    -282,  -282,   105,   110,    78,    12,  -282,  -282,  -282,  -282,
    -282,   167,   121,  -282,    18,   173,  -282,   126,    19,   138,
    -282,  -282,  -282,  -282,  -282,  -282,  -282,   187,   120,  -282,
     132,   191,   139,    78,   147,  -282,   151,  -282,  -282,   242,
    -282,  -282,   167,   135,  -282,    44,   206,  -282,   152,   211,
     152,   136,  -282,  -282,    50,     6,  -282,   129,  -282,   213,
    -282,   215,   228,  -282,   219,   165,   220,   187,  -282,   169,
    -282,  -282,   176,   179,   170,   186,   194,   198,  -282,  -282,
    -282,   199,   222,  -282,    54,  -282,   120,    78,  -282,   256,
     241,  -282,   262,   152,   117,  -282,   152,  -282,  -282,    78,
      78,   214,   208,  -282,   152,  -282,  -282,  -282,  -282,   218,
     223,   229,   276,   117,   129,   120,   191,  -282,    78,  -282,
     287,   120,   234,  -282,   235,     2,   239,   222,  -282,  -282,
    -282,  -282,   274,  -282,  -282,  -282,   117,   117,   117,   117,
     117,   117,   240,  -282,    45,  -282,   152,   152,  -282,    50,
     254,   261,   263,  -282,  -282,   401,    78,  -282,  -282,  -282,
     222,    72,   264,   258,   259,   270,  -282,  -282,   129,   129,
     331,   332,  -282,   425,   431,   431,   431,   295,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   152,     0,  -282,   222,
     222,  -282,    78,  -282,  -282,  -282,   222,   341,  -282,    54,
    -282,   283,  -282,  -282,    78,    78,  -282,   292,  -282,  -282,
     296,   296,   296,   296,   296,   296,   425,   425,   425,   425,
     425,   431,   431,   431,   431,   296,   296,   353,  -282,  -282,
     401,    65,  -282,  -282,  -282,   331,   152,   293,   349,   222,
     222,    54,   117,  -282,   117,  -282,  -282,   -42,   303,   351,
     331,   304,  -282,   401,   306,   117,   370,  -282,  -282,   152,
    -282,  -282,    54,   377,   317,   327,   323,   321,   117,   325,
     117,   117,  -282,    54,  -282,   401,   349,   265,   401,   322,
    -282,   333,   117,  -282,   349,   324,  -282,   334,   349,  -282
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -282,   104,  -282,   382,  -282,  -282,   294,  -282,  -282,   226,
    -282,   289,  -282,   157,  -282,  -282,  -282,  -282,  -282,  -282,
     298,  -282,  -282,  -282,  -282,  -282,  -282,   279,    32,   -69,
    -282,  -282,  -282,   252,  -282,  -105,   -37,  -282,   369,   233,
    -282,   -29,  -151,  -282,  -282,  -282,  -282,   316,  -282,  -282,
    -282,  -282,   345,  -201,  -282,  -281,  -282,  -199,   247,  -282,
    -282,  -120,  -282,  -282,  -282,  -282,  -157,  -282,  -282,  -282
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -125
static const short int yytable[] =
{
      51,    64,    53,   155,     1,   157,   192,   -23,   193,   194,
     195,    22,   325,    28,   -88,    29,   215,   226,    56,    57,
     106,   107,   138,   109,   123,    30,   186,   326,    58,   277,
      23,    24,   124,    40,    46,   227,   230,    41,    47,   232,
     233,   234,   235,   236,   237,   196,   197,    25,   191,   198,
     151,   205,   199,   200,    50,   217,   159,   160,   152,   210,
     201,   223,   147,   299,   142,   350,    26,    27,    38,   267,
     307,   -23,    74,   356,    33,   114,    36,   359,   105,   -96,
      64,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   258,
     300,   259,   260,   121,   315,   257,    49,   218,   302,   303,
      32,   154,   321,    34,    35,   305,    37,  -124,   187,   330,
     181,    45,    43,   192,    50,   193,   194,   195,   313,   314,
     206,   207,  -115,   337,   149,    56,    57,   216,   154,    52,
     130,   131,    54,   108,   349,    58,   132,   133,    76,   220,
      75,   298,   110,   111,    74,   322,   113,   323,   319,   320,
      59,    60,   196,   197,   114,   115,   198,   116,   333,   199,
     200,   117,    -2,     1,   125,     2,     3,   201,    68,    69,
      70,   345,   105,   347,   348,   122,   126,   266,     4,     5,
     127,   274,   275,   128,   137,   355,    77,    78,    57,   150,
     139,     6,    68,    69,    70,    79,     7,    58,   143,    80,
      81,   144,   153,    82,    83,    84,    85,   156,   154,   164,
      86,   165,    59,    60,   335,   167,    13,   168,   169,   171,
     172,    31,    13,   173,    67,    13,    13,   174,    13,    68,
      69,    70,    71,    87,    13,   309,   310,   101,    56,    57,
     175,   176,    68,    69,    70,   102,   145,    88,    58,   177,
      80,    81,   188,   178,    82,    83,    84,    85,   190,   208,
      13,   179,   209,    59,    60,   238,   239,   240,   241,   242,
     243,   211,   214,   212,   244,   245,   246,   247,   248,   249,
     250,   251,   213,   221,   252,   253,   254,   224,   255,   225,
     238,   239,   240,   241,   242,   243,   229,   256,   146,   244,
     245,   246,   247,   248,   249,   250,   251,   231,   262,   252,
     253,   254,   264,   255,   269,   270,   265,   271,   351,   352,
     238,   239,   240,   241,   242,   243,   181,   276,   278,   244,
     245,   246,   247,   248,   249,   250,   251,   306,   308,   252,
     253,   254,   311,   255,   255,   317,   316,   328,   279,   238,
     239,   240,   241,   242,   243,   327,   332,   331,   244,   245,
     246,   247,   248,   249,   250,   251,   334,   340,   252,   253,
     254,   341,   255,   343,   344,   353,   346,   357,   238,   239,
     240,   241,   242,   243,   354,   358,    39,   244,   245,   246,
     247,   248,   249,   250,   251,   158,   163,   252,   253,   254,
     312,   255,   238,   239,   240,   241,   242,   243,   338,   304,
     166,   244,   245,   246,   247,   248,   249,   250,   251,   189,
     219,   252,   253,   254,   120,   255,   238,   239,   240,   241,
     242,   243,   261,   170,   148,   244,   245,   246,   247,   248,
     249,   250,   251,     0,     0,   252,   253,   254,     0,   255,
     238,   239,   240,   241,   242,   243,   238,   239,   240,   241,
     242,   243,   273,     0,   249,   250,   251,     0,     0,   252,
     253,   254,     0,   255,     0,     0,   253,   254,     0,   255
};

static const short int yycheck[] =
{
      29,    38,    31,   108,     1,   110,     6,     1,     8,     9,
      10,    42,    54,     4,     6,     6,   173,    15,     6,     7,
      49,    50,    91,    52,     6,    16,   146,    69,    16,   230,
      61,    62,    14,    57,    57,    33,   187,    61,    61,   196,
     197,   198,   199,   200,   201,    45,    46,     6,   153,    49,
       6,   156,    52,    53,    46,   175,     6,     7,    14,   164,
      60,   181,    99,    63,    93,   346,     6,     6,    65,   220,
     269,    65,    40,   354,     0,    56,    60,   358,    46,    60,
     117,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   204,
     257,   206,   207,    71,   305,    60,     6,   176,   259,   260,
       6,    66,   311,     9,    10,   266,    12,    63,   147,   320,
      66,    65,    18,     6,    46,     8,     9,    10,    63,    64,
     159,   160,    60,   332,   102,     6,     7,   174,    66,     6,
      20,    21,     6,     6,   343,    16,    26,    27,    44,   178,
      65,   256,     6,    64,   122,   312,    63,   314,   309,   310,
      31,    32,    45,    46,    56,     6,    49,    62,   325,    52,
      53,    61,     0,     1,     1,     3,     4,    60,    11,    12,
      13,   338,   150,   340,   341,    64,    60,   216,    16,    17,
      52,   228,   229,     6,    62,   352,     5,     6,     7,    64,
      61,    29,    11,    12,    13,    14,    34,    16,    61,    18,
      19,    60,     6,    22,    23,    24,    25,     6,    66,     6,
      29,     6,    31,    32,   329,     6,     0,    62,     8,    60,
      54,     5,     6,    54,     6,     9,    10,    67,    12,    11,
      12,    13,    14,    52,    18,   274,   275,     6,     6,     7,
      64,    57,    11,    12,    13,    14,    14,    66,    16,    61,
      18,    19,     6,    64,    22,    23,    24,    25,     6,    55,
      44,    49,    64,    31,    32,    35,    36,    37,    38,    39,
      40,    63,     6,    60,    44,    45,    46,    47,    48,    49,
      50,    51,    63,     6,    54,    55,    56,    63,    58,    64,
      35,    36,    37,    38,    39,    40,    67,    67,    66,    44,
      45,    46,    47,    48,    49,    50,    51,    43,    64,    54,
      55,    56,    61,    58,    60,    67,    63,    68,    63,    64,
      35,    36,    37,    38,    39,    40,    66,     6,     6,    44,
      45,    46,    47,    48,    49,    50,    51,     6,    65,    54,
      55,    56,    60,    58,    58,     6,    63,     6,    63,    35,
      36,    37,    38,    39,    40,    62,    60,    63,    44,    45,
      46,    47,    48,    49,    50,    51,     6,    60,    54,    55,
      56,    54,    58,    60,    63,    63,    61,    63,    35,    36,
      37,    38,    39,    40,    61,    61,    14,    44,    45,    46,
      47,    48,    49,    50,    51,   111,   117,    54,    55,    56,
      57,    58,    35,    36,    37,    38,    39,    40,    41,   262,
     122,    44,    45,    46,    47,    48,    49,    50,    51,   150,
     178,    54,    55,    56,    65,    58,    35,    36,    37,    38,
      39,    40,   209,   127,    99,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    54,    55,    56,    -1,    58,
      35,    36,    37,    38,    39,    40,    35,    36,    37,    38,
      39,    40,   225,    -1,    49,    50,    51,    -1,    -1,    54,
      55,    56,    -1,    58,    -1,    -1,    55,    56,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,     4,    16,    17,    29,    34,    71,    73,
      74,    75,    78,    79,    80,    85,    86,    87,    91,    92,
      93,    94,    42,    61,    62,     6,     6,     6,     4,     6,
      16,    79,    71,     0,    71,    71,    60,    71,    65,    73,
      57,    61,    88,    71,    72,    65,    57,    61,    95,     6,
      46,   111,     6,   111,     6,    76,     6,     7,    16,    31,
      32,    79,    81,    82,   106,   107,   108,     6,    11,    12,
      13,    14,    89,    90,    98,    65,    71,     5,     6,    14,
      18,    19,    22,    23,    24,    25,    29,    52,    66,    98,
      99,   101,   102,   106,   113,   114,   115,   116,   118,   121,
     122,     6,    14,    96,    97,    98,   111,   111,     6,   111,
       6,    64,    77,    63,    56,     6,    62,    61,    83,   111,
     108,    98,    64,     6,    14,     1,    60,    52,     6,   117,
      20,    21,    26,    27,   131,   132,   100,    62,    99,    61,
     103,   104,   111,    61,    60,    14,    66,   106,   122,    98,
      64,     6,    14,     6,    66,   105,     6,   105,    76,     6,
       7,   109,   110,    81,     6,     6,    90,     6,    62,     8,
     117,    60,    54,    54,    67,    64,    57,    61,    64,    49,
     112,    66,   127,   128,   129,   130,   131,   111,     6,    97,
       6,   105,     6,     8,     9,    10,    45,    46,    49,    52,
      53,    60,   136,   137,   138,   105,   111,   111,    55,    64,
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
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
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
  const char *yys = yystr;

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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



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
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



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
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
      currentPack->AddObject(GetToken((yyvsp[-1])));
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
  if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  (yyval)=(yyvsp[-3]);
}
    break;

  case 22:
#line 239 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[-1]);
}
    break;

  case 23:
#line 245 "parser.y"
    {
  char *tname=GetToken((yyvsp[0]));
  DataType *type=thisCodeFile->FindDataType(tname);
  TypeClassStruct *t;
  if (type!=NULL)
    {
      t=dynamic_cast<TypeClassStruct *>(type);
      if (t==NULL)
	{
	  //	  thisCodeFile->RemoveDataType(type);
	  //	  delete type;
	  t=new TypeClassStruct(tname, false);
	  thisCodeFile->AddDataType(t);
	  //	  	  sprintf(tmp,"data type \"%s\" has been redefined!\n",tname);
	  //	  	  errormsg(tmp);
	  //		  exit(1);
	}
    } 
  else
    { 
      t=new TypeClassStruct(tname, false);
      thisCodeFile->AddDataType(t);
    }
  Push(t);
  (yyval)=(yyvsp[0]);
}
    break;

  case 24:
#line 272 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL, false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 28:
#line 287 "parser.y"
    {
  DataType *type1=currenttype;
  if ((yyvsp[-3])>0)
    {
      type1=new TypePtr(NULL,(yyvsp[-3]), type1);
      thisCodeFile->AddDataType(type1);
    }
  if ((yyvsp[-1])!=-1)
    {
      type1=new TypeArray(NULL,GetToken((yyvsp[-1])), type1);
      thisCodeFile->AddDataType(type1);     
    }  
  TypeClassStruct *t=Peek();
  assert(t!=NULL);
  t->Add(type1, GetToken((yyvsp[-2])));

}
    break;

  case 31:
#line 316 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[-3]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new DataType(orgtype);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[-2])>0)
    {
      type=new TypePtr(NULL,(yyvsp[-2]), type);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[0])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[0])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[-1])),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 32:
#line 338 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[-3]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new TypeClassStruct(orgtype, false);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[-2])>0)
    {
      type=new TypePtr(NULL,(yyvsp[-2]), type);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[0])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[0])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[-1])),type);
  thisCodeFile->AddDataType(type);   
}
    break;

  case 33:
#line 360 "parser.y"
    {
  char *orgtype=GetToken((yyvsp[-3]));
  DataType *type=thisCodeFile->FindDataType(orgtype);
  if (type==NULL)
    {
      type=new TypeClassStruct(orgtype, true);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[-2])>0)
    {
      type=new TypePtr(NULL,(yyvsp[-2]), type);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[0])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[0])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[-1])),type);
  thisCodeFile->AddDataType(type);   
}
    break;

  case 34:
#line 382 "parser.y"
    {
  DataType *type=currentstruct;
  assert(type!=NULL);

  if ((yyvsp[-2])>0)
    {
      type=new TypePtr(NULL,(yyvsp[-2]), type);
      thisCodeFile->AddDataType(type);
    }
  if ((yyvsp[0])!=-1)
    {
      type=new TypeArray(NULL,GetToken((yyvsp[0])), type);
      thisCodeFile->AddDataType(type); 
    }
  type=new TypeEqual(GetToken((yyvsp[-1])),type);
  thisCodeFile->AddDataType(type); 
}
    break;

  case 35:
#line 406 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 37:
#line 412 "parser.y"
    {
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (t==NULL)
    {
      seqclass=new TypeClassStruct(GetToken((yyvsp[0])), true);
      thisCodeFile->AddDataType(seqclass);
    }
  else if (!t->IsStandardType())
    {
      seqclass=dynamic_cast<TypeClassStruct *>(t);
      if (seqclass==NULL)
	{
	  char tmp[256];
	  sprintf(tmp,"%s has been declared as non-class data type", GetToken((yyvsp[0])));
	  errormsg(tmp);
	  exit(1);
	}
    }
}
    break;

  case 42:
#line 442 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[0])), true);
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
#line 466 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[0])), true);
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
#line 491 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[0])), true);
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
#line 516 "parser.y"
    {
  assert(seqclass!=NULL);
  TypeClassStruct *seqbase;
  DataType *t=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (t==NULL)
    {
      seqbase=new TypeClassStruct(GetToken((yyvsp[0])), true);
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

  case 46:
#line 551 "parser.y"
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
#line 569 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 48:
#line 577 "parser.y"
    {
  accessmodifier=PUBLIC;
  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 49:
#line 585 "parser.y"
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
  char *clname=GetToken((yyvsp[0]));
  
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
#line 618 "parser.y"
    {
	assert(currentClass!=NULL);
	BaseClass *t=new BaseClass(GetToken((yyvsp[0])),PUBLIC,false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 55:
#line 624 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[-1]);
	BaseClass *t=new BaseClass(GetToken((yyvsp[0])),accessmode,false);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 56:
#line 631 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[-1]);
	BaseClass *t=new BaseClass(GetToken((yyvsp[0])),accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 57:
#line 638 "parser.y"
    {
	assert(currentClass!=NULL);
	AccessType accessmode=(AccessType)(yyvsp[-2]);
	BaseClass *t=new BaseClass(GetToken((yyvsp[0])),accessmode,true);
	currentClass->baseClass.InsertAt(-1,t);
}
    break;

  case 58:
#line 647 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 59:
#line 651 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 60:
#line 655 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 63:
#line 666 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[0]); }
    break;

  case 65:
#line 670 "parser.y"
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

  case 66:
#line 686 "parser.y"
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

  case 67:
#line 697 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 68:
#line 702 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[-2])));
}
    break;

  case 72:
#line 718 "parser.y"
    {

  assert(currentClass!=NULL);
  Attribute *t=new Attribute(currentClass,accessmodifier);
  t->SetLineInfo(linenumber-1);
  currentClass->AddMember(t);
  Param *tparam=t->NewAttribute();
  DataType *type;
  strcpy(tparam->name,GetToken((yyvsp[-1])));
  if ((yyvsp[-3])==0)
    {
      type=currenttype;
    }
  else 
    {
      type=new TypePtr(NULL, (yyvsp[-3]) , currenttype);
      thisCodeFile->AddDataType(type);
    }

  if ((yyvsp[0])!=-1)
    {
      type=new TypeArray(NULL, GetToken((yyvsp[0])) , type);
      thisCodeFile->AddDataType(type);
    }
  tparam->isRef=(yyvsp[-2]);
  tparam->SetType(type);
}
    break;

  case 73:
#line 748 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 74:
#line 752 "parser.y"
    {
  if ((yyvsp[0])==-1)
    {
      sprintf(tmp,"[%s]",GetToken((yyvsp[-2])));
      (yyval)=PutToken(tmp);
    }
  else
    {
      sprintf(tmp,"[%s]%s",GetToken((yyvsp[-2])),GetToken((yyvsp[0])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 75:
#line 767 "parser.y"
    {
  (yyval)=(yyvsp[-1]);
}
    break;

  case 76:
#line 771 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 77:
#line 777 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 78:
#line 781 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 79:
#line 787 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken((yyvsp[0])));
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
#line 801 "parser.y"
    {
  currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (currenttype==NULL)
    {
      currenttype=new DataType(GetToken((yyvsp[0])));
      thisCodeFile->AddDataType(currenttype);

      /*
	sprintf(tmp,"Undeclared type \"%s\"\n",GetToken($1)); 
	errormsg(tmp);
	exit(1);
      */
    }
}
    break;

  case 81:
#line 816 "parser.y"
    {
  sprintf(tmp,"%s<%s>",GetToken((yyvsp[-3])), GetToken((yyvsp[-1])));
  currenttype=thisCodeFile->FindDataType(GetToken((yyvsp[-3])));
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

  case 82:
#line 831 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
}
    break;

  case 83:
#line 836 "parser.y"
    {
  DataType *type=thisCodeFile->FindDataType(GetToken((yyvsp[0])));
  if (type==NULL)
    {
      type=new TypeClassStruct(GetToken((yyvsp[0])), false);
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

  case 84:
#line 853 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 85:
#line 857 "parser.y"
    {
  sprintf(tmp,"%s,%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 86:
#line 864 "parser.y"
    {
  if ((yyvsp[-2])==0 && (yyvsp[-1])==-1 && (yyvsp[0])==0)
    {
      (yyval)=(yyvsp[-3]);
    }
  else
    {
      strcpy(tmp, GetToken((yyvsp[-3])));
      for (int i=0;i<(yyvsp[-2]); i++) strcat(tmp, "*"); 
      if ((yyvsp[-1])!=-1) strcat(tmp,GetToken((yyvsp[-1])));
      if ((yyvsp[0])) strcat(tmp,"&");
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 87:
#line 879 "parser.y"
    {
  if ((yyvsp[-2])==0 && (yyvsp[-1])==-1 && (yyvsp[0])==0)
    {
      (yyval)=(yyvsp[-3]);
    }
  else
    {
      strcpy(tmp, GetToken((yyvsp[-3])));
      for (int i=0;i<(yyvsp[-2]); i++) strcat(tmp, "*"); 
      if ((yyvsp[-1])!=-1) strcat(tmp,GetToken((yyvsp[-1])));
      if ((yyvsp[0])) strcat(tmp,"&");
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 88:
#line 897 "parser.y"
    {
  (yyval)=0;
  
}
    break;

  case 89:
#line 902 "parser.y"
    {
  (yyval)=(yyvsp[0])+1;
}
    break;

  case 90:
#line 908 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 91:
#line 912 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 95:
#line 929 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of constructor\n");
      exit(1);
    }
  if ((yyvsp[0])!=-1)
    {
      ObjDesc &od=((Constructor *)method)->GetOD();
      od.SetCode(GetToken((yyvsp[0])));
    }
  currentClass->AddMember(method);

}
    break;

  case 96:
#line 946 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[0])));
}
    break;

  case 97:
#line 955 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 98:
#line 964 "parser.y"
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

  case 99:
#line 977 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[0])));
}
    break;

  case 100:
#line 986 "parser.y"
    {
  //Old data:  argument_type function_name 
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if ((yyvsp[-5])>0)
    {
      type=new TypePtr(NULL, (yyvsp[-5]) , type);
      thisCodeFile->AddDataType(type);
    }

  if ((yyvsp[-4]))
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);

}
    break;

  case 101:
#line 1005 "parser.y"
    {
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if ((yyvsp[-5])>0)
    {
      type=new TypePtr(NULL, (yyvsp[-5]) , type);
      thisCodeFile->AddDataType(type);
    }
  
  if ((yyvsp[-4]))
    {
      method->returnparam.isRef=true;
    }

  method->returnparam.SetType(type);

  method->isVirtual=(((yyvsp[-7]) & 1)!=0);
  if (((yyvsp[-7]) & 8)!=0) method->isConcurrent=true;
  else if (((yyvsp[-7]) & 32)!=0) method->isConcurrent=false;

  method->isHidden=(((yyvsp[-7]) & 64)!=0);
  method->isMutex=(((yyvsp[-7]) & 16)!=0);

  if (((yyvsp[-7]) & 6)==2) method->invoketype=invokesync;
  else if (((yyvsp[-7]) & 6)==4) method->invoketype=invokeasync;
  /*	else method->invoketype=autoselect; */
}
    break;

  case 102:
#line 1033 "parser.y"
    { UpdateMarshalParam((yyvsp[-5]),&(method->returnparam) ); }
    break;

  case 103:
#line 1034 "parser.y"
    {
  DataType *type=returntype;
  if ((yyvsp[-6])>0)
    {
      type=new TypePtr(NULL, (yyvsp[-6]) , type);
      thisCodeFile->AddDataType(type);
    }
  
  if ((yyvsp[-5]))
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);
  
  strcpy(method->returnparam.name,"_RemoteRet");
}
    break;

  case 104:
#line 1050 "parser.y"
    { UpdateMarshalParam((yyvsp[-5]),&(method->returnparam) ); }
    break;

  case 105:
#line 1051 "parser.y"
    {
  strcpy(method->returnparam.name,"_RemoteRet");

  DataType *type=returntype;
  if ((yyvsp[-6])>0)
    {
      type=new TypePtr(NULL, (yyvsp[-6]) , type);
      thisCodeFile->AddDataType(type);
    }
  
  if ((yyvsp[-5]))
    {
      method->returnparam.isRef=true;
    }
  method->returnparam.SetType(type);

  method->isVirtual=(((yyvsp[-11]) & 1)!=0);

  if (((yyvsp[-11]) & 8)!=0) method->isConcurrent=true;
  else if (((yyvsp[-11]) & 32)!=0) method->isConcurrent=false;
  
  method->isMutex=(((yyvsp[-11]) & 16)!=0);
  method->isHidden=(((yyvsp[-11]) & 64)!=0);
  
  if (((yyvsp[-11]) & 6)==2) method->invoketype=invokesync;
  else if (((yyvsp[-11]) & 6)==4) method->invoketype=invokeasync;
  /* else method->invoketype=autoselect; */
}
    break;

  case 106:
#line 1082 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 107:
#line 1086 "parser.y"
    {
  (yyval)=(yyvsp[-1]) | (yyvsp[0]);
}
    break;

  case 108:
#line 1092 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 109:
#line 1096 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 110:
#line 1100 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 111:
#line 1104 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 112:
#line 1108 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 113:
#line 1112 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 114:
#line 1116 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 115:
#line 1122 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[0])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 116:
#line 1133 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 117:
#line 1137 "parser.y"
    {
  (yyval)=(yyvsp[-1]);
}
    break;

  case 118:
#line 1143 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 119:
#line 1147 "parser.y"
    {

  char *odtmp=GetToken((yyvsp[-9]));
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken((yyvsp[-7])));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s,%s);",GetToken((yyvsp[-7])),GetToken((yyvsp[-5])),GetToken((yyvsp[-3])));
  if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 120:
#line 1163 "parser.y"
    {
  char *odtmp=GetToken((yyvsp[-7]));
  assert(method!=NULL);
  if (!paroc_utils::isEqual(odtmp,"od"))
    {
      sprintf(tmp,"Invalid OD expression: %s.%s",odtmp,GetToken((yyvsp[-5])));
      errormsg(tmp);
      exit(1);
    }

  sprintf(tmp,"od.%s(%s);",GetToken((yyvsp[-5])),GetToken((yyvsp[-3])));
  if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 121:
#line 1178 "parser.y"
    {
    char *odtmp=GetToken((yyvsp[-5]));
    if (paroc_utils::isEqual(odtmp,"host"))
      {
	sprintf(tmp,"od.url(%s);",GetToken((yyvsp[-3])));
	if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
	if ((yyvsp[-2])!=-1)
	  {
	    errormsg("OD: host should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"jobcontact"))
      {
	sprintf(tmp,"od.joburl(%s);",GetToken((yyvsp[-3])));
	if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
	if ((yyvsp[-2])!=-1)
	  {
	    errormsg("OD: jobcontact should be a string expression. Non-strict description is not allowed");
	    exit(1);
	  }
      } 
    else if (paroc_utils::isEqual(odtmp,"memory"))
      {
	sprintf(tmp,"od.memory(%s",GetToken((yyvsp[-3])));
	if ((yyvsp[-2])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[-2])));
	  }
	strcat(tmp,");");
	if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
      } 
    else if (paroc_utils::isEqual(odtmp,"power"))
      {
	sprintf(tmp,"od.power(%s",GetToken((yyvsp[-3])));
	if ((yyvsp[-2])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[-2])));
	  }
	strcat(tmp,");");
	if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
      } 
    else if (paroc_utils::isEqual(odtmp,"network"))
    {
	sprintf(tmp,"od.bandwidth(%s",GetToken((yyvsp[-3])));
	if ((yyvsp[-2])!=-1)
	  {
	    strcat(tmp,",");
	    strcat(tmp,GetToken((yyvsp[-2])));
	  }
	strcat(tmp,");");
	if ((yyvsp[0])!=-1) strcat(tmp,GetToken((yyvsp[0])));
    } 
    else if (paroc_utils::isEqual(odtmp,"walltime"))
      {
	sprintf(tmp,"od.walltime(%s);",GetToken((yyvsp[-3])));
	if ((yyvsp[-2])!=-1)
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

  case 122:
#line 1252 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 123:
#line 1256 "parser.y"
    {
    (yyval)=(yyvsp[0]);
}
    break;

  case 128:
#line 1271 "parser.y"
    {
  Param *t=method->AddNewParam();
  UpdateMarshalParam((yyvsp[-7]),t);

  DataType *type=currenttype;
  if ((yyvsp[-4])>0)
    {
      type=new TypePtr(NULL, (yyvsp[-4]) , type);
      thisCodeFile->AddDataType(type);
    }

  if ((yyvsp[-3]))
    {
      t->isRef=true;
    }

  if ((yyvsp[-1])!=-1)
    {
      type=new TypeArray(NULL, GetToken((yyvsp[-1])) , type);
      thisCodeFile->AddDataType(type);
    }

  t->SetType(type);
  if ((yyvsp[-2])!=-1) strcpy(t->name,GetToken((yyvsp[-2])));
  else   sprintf(t->name,"V_%d",++counter);

  t->isConst=((yyvsp[-6])==1);
  if ((yyvsp[0])>=0) t->defaultVal=strdup(GetToken((yyvsp[0])));
  

}
    break;

  case 129:
#line 1305 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 130:
#line 1309 "parser.y"
    {
  (yyval)=(yyvsp[-1]);
}
    break;

  case 131:
#line 1315 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 132:
#line 1319 "parser.y"
    {
  (yyval)=(yyvsp[-2]) | (yyvsp[0]) ;
}
    break;

  case 133:
#line 1325 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 134:
#line 1329 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 135:
#line 1333 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[0])));
  (yyval)=PARAMSIZE;
}
    break;

  case 136:
#line 1338 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[0])));
  (yyval)=USERPROC;
}
    break;

  case 137:
#line 1345 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 138:
#line 1349 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 139:
#line 1353 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 140:
#line 1359 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 141:
#line 1363 "parser.y"
    {
	(yyval)=(yyvsp[0]);
}
    break;

  case 142:
#line 1369 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 143:
#line 1373 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 144:
#line 1386 "parser.y"
    {
  if ((yyvsp[0])<0) (yyval)=(yyvsp[-1]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[-1])),GetToken((yyvsp[0])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 145:
#line 1395 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 146:
#line 1399 "parser.y"
    {
    (yyval)=(yyvsp[0]);
}
    break;

  case 147:
#line 1403 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 148:
#line 1408 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 149:
#line 1413 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 150:
#line 1418 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 151:
#line 1423 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 152:
#line 1428 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 153:
#line 1433 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 154:
#line 1438 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 155:
#line 1443 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 156:
#line 1448 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 157:
#line 1453 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 158:
#line 1458 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 159:
#line 1463 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[-4])), GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 160:
#line 1468 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 161:
#line 1473 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 162:
#line 1478 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 163:
#line 1483 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 164:
#line 1488 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[-2])), GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 165:
#line 1493 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 166:
#line 1498 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[-1])));
  (yyval)=PutToken(tmp);
}
    break;

  case 167:
#line 1503 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[-2])));
  (yyval)=PutToken(tmp);
}
    break;

  case 168:
#line 1508 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[-3])),GetToken((yyvsp[-1])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 169:
#line 1514 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 170:
#line 1519 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 171:
#line 1524 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 172:
#line 1529 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;

  case 173:
#line 1537 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 174:
#line 1541 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 175:
#line 1547 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 176:
#line 1551 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[-2])),GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 177:
#line 1558 "parser.y"
    {
  (yyval)=(yyvsp[0]);
}
    break;

  case 178:
#line 1562 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[-2])),GetToken((yyvsp[0])));
  (yyval)=PutToken(tmp);
}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3311 "parser.tab.c"

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
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
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
	  yydestruct ("Error: discarding", yytoken, &yylval);
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
  if (0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1570 "parser.y"


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



