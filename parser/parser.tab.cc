
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
  void setReturnParam(int pointer, int ref, int const_virtual); // Methode to group code that set C++ specific C++ Param attributes
  void setPOPCMethodeModifier(int settings); // mehtode to group code that set/controlle Methode attributes (sync, conc, ...)
  
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
#line 175 "parser.tab.c"

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
#line 305 "parser.tab.c"

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
#define YYLAST   566

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNRULES -- Number of states.  */
#define YYNSTATES  410

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
     272,   276,   277,   279,   280,   282,   284,   286,   289,   290,
     293,   299,   301,   306,   312,   314,   323,   333,   343,   354,
     366,   367,   382,   383,   397,   399,   402,   404,   406,   408,
     410,   412,   414,   416,   418,   421,   424,   425,   427,   429,
     432,   435,   437,   438,   443,   444,   457,   468,   477,   484,
     485,   488,   489,   491,   493,   497,   507,   508,   512,   514,
     518,   520,   522,   526,   530,   531,   533,   535,   536,   538,
     539,   542,   545,   547,   549,   553,   557,   561,   565,   569,
     573,   577,   581,   585,   589,   593,   597,   603,   607,   611,
     615,   619,   623,   626,   630,   634,   639,   642,   645,   648,
     651,   653,   655,   657,   661,   663
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
      57,   100,    -1,   115,    61,    -1,   103,    61,    -1,    29,
      -1,     5,    60,     8,    63,    61,    -1,   107,   104,    -1,
     105,    -1,   105,    64,   104,    -1,   112,   114,     6,   106,
      -1,    -1,    66,   141,    67,   106,    -1,   108,   109,    -1,
     109,    -1,    31,    -1,    32,    -1,     6,    -1,     7,    -1,
       6,    56,   110,    55,    -1,    79,    -1,    16,     6,    -1,
     111,    -1,   111,    64,   110,    -1,   109,   112,   106,   114,
      -1,    -1,    46,   113,   112,    -1,    -1,    15,    -1,    -1,
      49,    -1,   117,    -1,   119,    -1,   121,   116,    -1,    -1,
      54,     8,    -1,   118,    60,   132,    63,   129,    -1,     6,
      -1,    52,   120,    60,    63,    -1,    14,    52,   120,    60,
      63,    -1,     6,    -1,   107,   112,   114,   128,    60,   132,
      63,   113,    -1,   107,   126,   112,   114,   128,    60,   132,
      63,   113,    -1,   126,   107,   112,   114,   128,    60,   132,
      63,   113,    -1,   126,   107,   126,   112,   114,   128,    60,
     132,    63,   113,    -1,   124,   127,   107,   127,   112,   114,
     128,    60,   132,    63,   113,    -1,    -1,    66,   136,    67,
     127,   107,   127,   112,   114,   128,   122,    60,   132,    63,
     113,    -1,    -1,   124,    66,   136,    67,   107,   112,   114,
     128,   123,    60,   132,    63,   113,    -1,   125,    -1,   124,
     125,    -1,    18,    -1,    19,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    14,    -1,    15,    -1,    15,    14,
      -1,    14,    15,    -1,    -1,    14,    -1,    15,    -1,    15,
      14,    -1,    14,    15,    -1,     6,    -1,    -1,    68,    65,
     130,    62,    -1,    -1,     6,    69,     6,    60,   141,    64,
     141,    64,   141,    63,    61,   130,    -1,     6,    69,     6,
      60,   141,    64,   141,    63,    61,   130,    -1,     6,    69,
       6,    60,   141,    63,    61,   130,    -1,     6,    54,   141,
     131,    61,   130,    -1,    -1,    41,   141,    -1,    -1,   133,
      -1,   134,    -1,   134,    64,   133,    -1,   135,   138,   107,
     138,   112,   114,   139,   106,   140,    -1,    -1,    66,   136,
      67,    -1,   137,    -1,   137,    64,   136,    -1,    20,    -1,
      21,    -1,    27,    54,   141,    -1,    26,    54,     6,    -1,
      -1,    15,    -1,    33,    -1,    -1,     6,    -1,    -1,    54,
     141,    -1,   143,   106,    -1,   142,    -1,    10,    -1,   141,
      44,   141,    -1,   141,    45,   141,    -1,   141,    46,   141,
      -1,   141,    47,   141,    -1,   141,    48,   141,    -1,   141,
      49,   141,    -1,   141,    50,   141,    -1,   141,    51,   141,
      -1,   141,    35,   141,    -1,   141,    36,   141,    -1,   141,
      37,   141,    -1,   141,    54,   141,    -1,   141,    58,   141,
      57,   141,    -1,   141,    38,   141,    -1,   141,    55,   141,
      -1,   141,    56,   141,    -1,   141,    39,   141,    -1,   141,
      40,   141,    -1,    45,   141,    -1,    60,   141,    63,    -1,
     143,    60,    63,    -1,   143,    60,   144,    63,    -1,    46,
     141,    -1,    49,   141,    -1,    53,   141,    -1,    52,   141,
      -1,     8,    -1,     9,    -1,     6,    -1,     6,    43,     6,
      -1,   141,    -1,   144,    64,   141,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   131,   131,   132,   133,   134,   135,   136,
     142,   155,   168,   184,   195,   213,   223,   225,   233,   237,
     238,   245,   251,   257,   284,   293,   294,   296,   299,   319,
     320,   329,   351,   373,   395,   418,   422,   424,   445,   446,
     450,   451,   454,   478,   503,   528,   558,   579,   587,   597,
     622,   623,   626,   627,   630,   644,   659,   676,   695,   699,
     703,   711,   714,   723,   724,   725,   725,   728,   744,   755,
     760,   770,   772,   773,   776,   807,   810,   825,   829,   835,
     839,   845,   860,   876,   895,   901,   914,   921,   930,   989,
     992,  1000,  1003,  1010,  1013,  1025,  1026,  1027,  1030,  1031,
    1037,  1053,  1062,  1071,  1084,  1098,  1102,  1106,  1110,  1114,
    1119,  1119,  1123,  1123,  1187,  1191,  1204,  1208,  1212,  1216,
    1220,  1224,  1231,  1235,  1239,  1243,  1250,  1253,  1257,  1261,
    1265,  1271,  1283,  1286,  1293,  1297,  1314,  1330,  1345,  1438,
    1441,  1449,  1450,  1452,  1453,  1456,  1491,  1494,  1500,  1504,
    1510,  1514,  1518,  1523,  1532,  1535,  1539,  1546,  1549,  1556,
    1559,  1572,  1581,  1585,  1589,  1594,  1599,  1604,  1609,  1614,
    1619,  1624,  1629,  1634,  1639,  1644,  1649,  1654,  1659,  1664,
    1669,  1674,  1679,  1684,  1689,  1694,  1700,  1705,  1710,  1715,
    1722,  1726,  1732,  1736,  1744,  1748
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
  "template_arg", "pointer_specifier", "const_specifier", "ref_specifier",
  "function_definition", "pure_virtual_decl", "constructor_definition",
  "constructor_name", "destructor_definition", "destructor_name",
  "method_definition", "$@3", "@4", "fct_specifier", "fct_spec",
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
     112,   113,   113,   114,   114,   115,   115,   115,   116,   116,
     117,   118,   119,   119,   120,   121,   121,   121,   121,   121,
     122,   121,   123,   121,   124,   124,   125,   125,   125,   125,
     125,   125,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   128,   129,   129,   130,   130,   130,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   135,   135,   136,   136,
     137,   137,   137,   137,   138,   138,   138,   139,   139,   140,
     140,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     142,   142,   143,   143,   144,   144
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
       3,     0,     1,     0,     1,     1,     1,     2,     0,     2,
       5,     1,     4,     5,     1,     8,     9,     9,    10,    11,
       0,    14,     0,    13,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     1,     1,     2,
       2,     1,     0,     4,     0,    12,    10,     8,     6,     0,
       2,     0,     1,     1,     3,     9,     0,     3,     1,     3,
       1,     1,     3,     3,     0,     1,     1,     0,     1,     0,
       2,     2,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     3,     3,
       3,     3,     2,     3,     3,     4,     2,     2,     2,     2,
       1,     1,     1,     3,     1,     3
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
      91,     0,    23,     0,    16,     0,    81,    82,    24,    79,
      80,    84,     0,     0,    89,     0,    78,    42,    59,    60,
      58,     0,    39,    40,     0,     0,     4,     0,    81,   122,
     123,   116,   117,   118,   119,   120,   121,    69,     0,     0,
      65,     0,    63,     0,    89,     0,    95,     0,    96,    98,
     126,   114,     0,    62,     0,    48,     0,    92,    89,    75,
       0,    75,     0,    15,    13,     0,    85,    21,    25,    27,
       0,    77,     0,     0,    43,     0,     0,     0,   125,     0,
     124,   104,     0,   150,   151,     0,     0,     0,   148,     0,
       0,    64,    68,   122,    71,    72,    93,    89,    67,   146,
       0,    97,   127,   128,     0,   115,     0,    89,    54,     0,
      51,    52,     0,    75,    90,     0,    31,    75,    34,    17,
      89,     0,    86,    26,    75,    44,    41,    45,    35,     0,
       0,     0,     0,     0,   126,     0,    63,    47,    89,    94,
       0,    93,     0,     0,   142,   143,   154,    99,   130,   129,
       0,   126,    93,    89,     0,     0,    55,     0,    33,   192,
     190,   191,   163,     0,     0,     0,     0,     0,     0,     0,
     162,    75,    32,    75,    83,     0,    29,     0,     0,   102,
     153,   152,     0,   149,    66,    73,    93,    75,     0,     0,
       0,   132,   146,   155,   156,     0,     0,    89,     0,    93,
      56,    53,    57,     0,   182,   186,   187,   189,   188,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
     161,    93,    87,    89,    28,    70,   103,   126,     0,    74,
     146,   131,     0,   147,     0,   100,   144,   154,    89,    93,
       0,     0,   193,   183,   172,   173,   174,   177,   180,   181,
     164,   165,   166,   167,   168,   169,   170,   171,   175,   178,
     179,     0,    76,   184,   194,     0,    88,    30,    89,    75,
       0,   146,   134,    89,    93,     0,   146,     0,     0,   185,
       0,    93,    91,     0,     0,     0,    93,     0,     0,     0,
     146,   176,   195,     0,   105,    91,     0,     0,   133,   157,
     112,   146,    91,     0,   110,   106,   139,     0,   158,    75,
       0,     0,   107,    91,     0,     0,     0,     0,   159,   146,
      91,   108,   146,   140,   134,     0,     0,   145,     0,   109,
       0,   138,     0,     0,   160,    91,    91,   134,     0,   113,
     111,   137,     0,     0,   134,     0,   136,     0,   134,   135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,    44,     9,    10,    11,    55,   113,    12,    61,
      14,    62,    63,   119,   284,    15,    16,    17,    42,    72,
      73,    18,    19,    20,    21,   105,   160,   161,    90,    48,
      91,   139,    92,    93,   144,   145,   289,    94,    65,    66,
     171,   172,   120,   108,   190,    95,   151,    96,    97,    98,
     132,    99,   374,   370,   100,   101,   102,   156,   238,   295,
     345,   376,   193,   194,   195,   196,   137,   138,   245,   369,
     387,   219,   220,   221,   325
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -266
static const yytype_int16 yypact[] =
{
      28,    64,    19,    24,    47,   140,    28,  -266,    18,    28,
      28,     0,    28,  -266,     7,  -266,  -266,    77,    28,  -266,
      40,   -40,  -266,  -266,  -266,  -266,  -266,  -266,    72,    65,
     123,    65,  -266,  -266,  -266,  -266,   139,  -266,    45,  -266,
     198,  -266,    89,  -266,    28,   216,    62,  -266,   106,    65,
     156,   167,    10,   173,   119,   127,   130,  -266,   185,  -266,
    -266,  -266,   132,   141,    65,   115,  -266,  -266,  -266,  -266,
    -266,   155,   136,  -266,    57,   204,  -266,   147,    13,    -2,
     199,  -266,  -266,  -266,  -266,  -266,  -266,  -266,   208,   259,
    -266,   154,   216,   159,    12,   163,  -266,   157,  -266,   172,
     252,  -266,    45,  -266,   299,  -266,   227,  -266,    65,   170,
     236,   170,   139,  -266,  -266,   115,     9,  -266,    45,  -266,
     237,  -266,   238,   198,  -266,   240,   187,   244,  -266,   208,
    -266,  -266,   193,  -266,  -266,   201,   205,   195,   196,   206,
     203,  -266,  -266,   250,  -266,   209,   223,    65,  -266,    74,
     273,  -266,   274,   277,   259,  -266,    45,    12,  -266,   155,
     228,  -266,   102,   170,  -266,   248,  -266,   170,  -266,  -266,
      65,   243,   231,  -266,   170,  -266,  -266,  -266,  -266,   239,
     246,   251,   297,   248,   133,   259,   216,  -266,    65,  -266,
     301,   223,   259,   253,  -266,   245,    31,  -266,  -266,  -266,
     254,   133,   223,    65,   309,   299,  -266,   311,  -266,   276,
    -266,  -266,  -266,   248,   248,   248,   248,   248,   248,   288,
    -266,   -19,  -266,   170,  -266,   115,   256,   268,   267,  -266,
    -266,   478,    45,  -266,  -266,  -266,   223,    67,   271,   334,
     286,   296,   275,  -266,  -266,    45,    45,    65,   334,   223,
    -266,  -266,  -266,   339,  -266,   502,   508,   508,   508,   372,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   170,   143,
    -266,   223,  -266,    65,  -266,  -266,  -266,   133,   348,  -266,
      74,  -266,   305,  -266,   304,  -266,  -266,    31,    65,   223,
     313,   334,  -266,  -266,   314,   314,   314,   314,   314,   314,
     502,   502,   502,   502,   502,   508,   508,   508,   508,   314,
     314,   430,  -266,  -266,   478,   112,  -266,  -266,    65,   170,
     308,    74,   368,    65,   223,   334,    74,   323,   248,  -266,
     248,   223,   156,   321,   -35,   332,   223,   334,   325,   336,
      74,  -266,   478,   334,  -266,   156,   248,   389,  -266,   395,
    -266,    74,   156,   340,  -266,  -266,   454,   344,  -266,   170,
     353,   351,  -266,   156,   355,   248,   341,   248,   370,    74,
     156,  -266,    74,   478,   368,   312,   248,  -266,   362,  -266,
     366,  -266,   371,   248,   478,   156,   156,   368,   342,  -266,
    -266,  -266,   373,   248,   368,   401,  -266,   381,   368,  -266
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -266,   175,  -266,   417,  -266,  -266,   331,  -266,  -266,   278,
    -266,   315,  -266,   161,  -266,  -266,  -266,  -266,  -266,  -266,
     330,  -266,  -266,  -266,  -266,  -266,  -266,   249,   -23,  -266,
     -83,  -266,  -266,  -266,   270,  -266,  -108,     5,  -266,   -61,
     235,  -266,   -29,  -238,  -169,  -266,  -266,  -266,  -266,  -266,
     333,  -266,  -266,  -266,  -266,   361,   -82,  -177,  -233,  -266,
    -265,  -266,  -181,   221,  -266,  -266,  -143,  -266,   174,  -266,
    -266,  -178,  -266,  -266,  -266
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -142
static const yytype_int16 yytable[] =
{
      51,   166,    53,   168,   121,   231,   292,   232,     1,   141,
     -23,   200,   147,   128,    46,   300,   -89,    74,    33,   356,
     106,    47,   239,   110,   247,    25,   143,    80,    -2,     1,
      26,     2,     3,   248,   357,   254,   255,   256,   257,   258,
     259,   279,   233,    64,     4,     5,   243,   165,   122,   240,
     129,    56,    57,    27,   170,   208,    50,     6,    50,   222,
      36,    58,     7,   124,   244,   146,   226,   288,   337,   115,
     103,   125,    38,  -101,   -23,   203,    59,    60,    49,   164,
     301,   162,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
      74,   324,   348,   234,   354,    45,    22,   157,   206,   330,
     328,    50,   326,   280,   360,   281,   207,   365,   191,   391,
     364,    56,    57,    64,   372,    23,    24,  -131,   202,    52,
     335,    58,   401,   165,    40,   381,   204,  -141,    41,   406,
     192,   223,   389,   409,    28,    54,    29,   152,   153,   209,
     343,   210,   211,   212,    75,   349,    30,   399,   400,   236,
     351,   201,   352,   104,   170,   347,    68,    69,    70,   363,
     322,   107,   353,   109,   249,   339,   340,   359,   366,   111,
     371,    32,   162,   112,    34,    35,   115,    37,   213,   214,
     114,   116,   215,    43,   117,   216,   217,   383,   388,   385,
     123,   390,   118,   218,    67,   126,   323,   127,   394,    68,
      69,    70,    71,   130,   131,   398,   140,   149,   299,    76,
     142,    77,    78,    57,   148,   405,   150,    68,    69,    70,
      79,    80,    58,   163,    81,    82,   165,   287,    83,    84,
      85,    86,   167,   174,   175,    87,   177,    59,    60,   178,
     297,   298,   179,   181,   209,   182,   210,   211,   212,   183,
     185,   378,   184,   186,   187,   128,   152,   153,    88,   334,
      81,    82,   189,   188,    83,    84,    85,    86,    13,   133,
     134,   197,    89,    31,    13,   135,   136,    13,    13,   198,
      13,   199,   205,   213,   214,   225,    13,   215,   224,   341,
     216,   217,   227,   230,   346,   158,   228,   237,   218,   242,
      68,    69,    70,   159,   229,   250,   241,   252,   154,   253,
     283,   246,    13,   260,   261,   262,   263,   264,   265,   285,
     286,   290,   266,   267,   268,   269,   270,   271,   272,   273,
     291,   192,   274,   275,   276,   302,   277,   260,   261,   262,
     263,   264,   265,   293,   329,   278,   266,   267,   268,   269,
     270,   271,   272,   273,   294,   331,   274,   275,   276,   332,
     277,   342,   277,   336,   344,   392,   393,   260,   261,   262,
     263,   264,   265,   350,   355,   361,   266,   267,   268,   269,
     270,   271,   272,   273,   358,   367,   274,   275,   276,   362,
     277,   368,   384,   373,   377,   402,   403,   260,   261,   262,
     263,   264,   265,   379,   380,   382,   266,   267,   268,   269,
     270,   271,   272,   273,   386,   395,   274,   275,   276,   396,
     277,    39,   397,   173,   404,   303,   260,   261,   262,   263,
     264,   265,   408,   169,   327,   266,   267,   268,   269,   270,
     271,   272,   273,   176,   251,   274,   275,   276,   235,   277,
     282,   155,   180,   296,   407,   260,   261,   262,   263,   264,
     265,   333,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,     0,     0,   274,   275,   276,   338,   277,   260,
     261,   262,   263,   264,   265,   375,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,     0,     0,   274,   275,
     276,     0,   277,   260,   261,   262,   263,   264,   265,     0,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
       0,     0,   274,   275,   276,     0,   277,   260,   261,   262,
     263,   264,   265,   260,   261,   262,   263,   264,   265,     0,
       0,   271,   272,   273,     0,     0,   274,   275,   276,     0,
     277,     0,     0,   275,   276,     0,   277
};

static const yytype_int16 yycheck[] =
{
      29,   109,    31,   111,    65,   183,   239,   184,     1,    92,
       1,   154,    94,    15,    54,   248,     6,    40,     0,    54,
      49,    61,   191,    52,   201,     6,    14,    15,     0,     1,
       6,     3,     4,   202,    69,   213,   214,   215,   216,   217,
     218,    60,   185,    38,    16,    17,    15,    66,    71,   192,
      52,     6,     7,     6,   115,   163,    46,    29,    46,   167,
      60,    16,    34,     6,    33,    94,   174,   236,   301,    56,
       8,    14,    65,    60,    65,   157,    31,    32,     6,   108,
     249,   104,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     123,   279,   335,   186,   342,    65,    42,   102,     6,   290,
     287,    46,   281,   221,   347,   223,    14,   355,   147,   384,
     353,     6,     7,   118,   362,    61,    62,    60,   157,     6,
     299,    16,   397,    66,    57,   373,   159,    63,    61,   404,
      66,   170,   380,   408,     4,     6,     6,    14,    15,     6,
     331,     8,     9,    10,    65,   336,    16,   395,   396,   188,
     338,   156,   340,    57,   225,   334,    11,    12,    13,   350,
     278,    15,   341,     6,   203,    63,    64,   346,   356,     6,
     361,     6,   205,    64,     9,    10,    56,    12,    45,    46,
      63,     6,    49,    18,    62,    52,    53,   375,   379,   377,
      64,   382,    61,    60,     6,     1,    63,    60,   386,    11,
      12,    13,    14,    14,     6,   393,    62,    60,   247,    44,
      61,     5,     6,     7,    61,   403,    54,    11,    12,    13,
      14,    15,    16,     6,    18,    19,    66,   232,    22,    23,
      24,    25,     6,     6,     6,    29,     6,    31,    32,    62,
     245,   246,     8,    60,     6,    54,     8,     9,    10,    54,
      64,   369,    67,    57,    61,    15,    14,    15,    52,   298,
      18,    19,    49,    64,    22,    23,    24,    25,     0,    20,
      21,     8,    66,     5,     6,    26,    27,     9,    10,    15,
      12,    14,    64,    45,    46,    64,    18,    49,    55,   328,
      52,    53,    63,     6,   333,     6,    60,     6,    60,    64,
      11,    12,    13,    14,    63,     6,    63,     6,    66,    43,
      64,    67,    44,    35,    36,    37,    38,    39,    40,    61,
      63,    60,    44,    45,    46,    47,    48,    49,    50,    51,
       6,    66,    54,    55,    56,     6,    58,    35,    36,    37,
      38,    39,    40,    67,     6,    67,    44,    45,    46,    47,
      48,    49,    50,    51,    68,    60,    54,    55,    56,    65,
      58,    63,    58,    60,     6,    63,    64,    35,    36,    37,
      38,    39,    40,    60,    63,    60,    44,    45,    46,    47,
      48,    49,    50,    51,    62,     6,    54,    55,    56,    63,
      58,     6,    61,    63,    60,    63,    64,    35,    36,    37,
      38,    39,    40,    60,    63,    60,    44,    45,    46,    47,
      48,    49,    50,    51,    54,    63,    54,    55,    56,    63,
      58,    14,    61,   118,    61,    63,    35,    36,    37,    38,
      39,    40,    61,   112,   283,    44,    45,    46,    47,    48,
      49,    50,    51,   123,   205,    54,    55,    56,   188,    58,
     225,   100,   129,   242,    63,    35,    36,    37,    38,    39,
      40,   297,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    54,    55,    56,    57,    58,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    -1,    54,    55,
      56,    -1,    58,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    54,    55,    56,    -1,    58,    35,    36,    37,
      38,    39,    40,    35,    36,    37,    38,    39,    40,    -1,
      -1,    49,    50,    51,    -1,    -1,    54,    55,    56,    -1,
      58,    -1,    -1,    55,    56,    -1,    58
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
      15,    18,    19,    22,    23,    24,    25,    29,    52,    66,
      98,   100,   102,   103,   107,   115,   117,   118,   119,   121,
     124,   125,   126,     8,    57,    95,   112,    15,   113,     6,
     112,     6,    64,    77,    63,    56,     6,    62,    61,    83,
     112,   109,    98,    64,     6,    14,     1,    60,    15,    52,
      14,     6,   120,    20,    21,    26,    27,   136,   137,   101,
      62,   100,    61,    14,   104,   105,   112,   126,    61,    60,
      54,   116,    14,    15,    66,   125,   127,   107,     6,    14,
      96,    97,    98,     6,   112,    66,   106,     6,   106,    76,
     109,   110,   111,    81,     6,     6,    90,     6,    62,     8,
     120,    60,    54,    54,    67,    64,    57,    61,    64,    49,
     114,   112,    66,   132,   133,   134,   135,     8,    15,    14,
     136,   107,   112,   126,    98,    64,     6,    14,   106,     6,
       8,     9,    10,    45,    46,    49,    52,    53,    60,   141,
     142,   143,   106,   112,    55,    64,   106,    63,    60,    63,
       6,   141,   127,   136,   100,   104,   112,     6,   128,   114,
     136,    63,    64,    15,    33,   138,    67,   127,   114,   112,
       6,    97,     6,    43,   141,   141,   141,   141,   141,   141,
      35,    36,    37,    38,    39,    40,    44,    45,    46,    47,
      48,    49,    50,    51,    54,    55,    56,    58,    67,    60,
     106,   106,   110,    64,    84,    61,    63,   107,   114,   106,
      60,     6,   128,    67,    68,   129,   133,   107,   107,   112,
     128,   114,     6,    63,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   106,    63,   141,   144,   114,    83,   127,     6,
     132,    60,    65,   138,   112,   114,    60,   128,    57,    63,
      64,   112,    63,   132,     6,   130,   112,   114,   128,   132,
      60,   141,   141,   114,   113,    63,    54,    69,    62,   114,
     128,    60,    63,   132,   128,   113,   141,     6,     6,   139,
     123,   132,   113,    63,   122,    41,   131,    60,   106,    60,
      63,   113,    60,   141,    61,   141,    54,   140,   132,   113,
     132,   130,    63,    64,   141,    63,    63,    61,   141,   113,
     113,   130,    63,    64,    61,   141,   130,    63,    61,   130
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
#line 121 "parser.y"
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
#line 131 "parser.y"
    { insideClass=false; othercodes.SetSize(0); startPos=-1;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {
  CleanStack();
}
    break;

  case 10:

/* Line 1455 of yacc.c  */
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

  case 11:

/* Line 1455 of yacc.c  */
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

  case 12:

/* Line 1455 of yacc.c  */
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
  YYACCEPT;
}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    {
  currentPack->SetEndLine(linenumber-1);

  currentPack=NULL;
  othercodes.SetSize(0);
  startPos=-1;
  
}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
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
#line 214 "parser.y"
    {
  if (currentPack!=NULL)
    {
      currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
    }
}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 223 "parser.y"
    {
}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 226 "parser.y"
    {
}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    {
    CleanStack();
}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    {
  currentstruct=Pop();
  if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  (yyval)=(yyvsp[(1) - (4)]);
}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
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
#line 285 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
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
#line 330 "parser.y"
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
#line 352 "parser.y"
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
#line 374 "parser.y"
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
#line 396 "parser.y"
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
#line 419 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 425 "parser.y"
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
#line 455 "parser.y"
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
#line 479 "parser.y"
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
#line 504 "parser.y"
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
#line 529 "parser.y"
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
#line 559 "parser.y"
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
#line 580 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 588 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 598 "parser.y"
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
#line 631 "parser.y"
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
#line 645 "parser.y"
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
#line 660 "parser.y"
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
#line 677 "parser.y"
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
#line 696 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 700 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 704 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 711 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 715 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 725 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 729 "parser.y"
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
#line 745 "parser.y"
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
#line 756 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 761 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 777 "parser.y"
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
#line 807 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 811 "parser.y"
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
#line 826 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 830 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 836 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 840 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 846 "parser.y"
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
#line 861 "parser.y"
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
#line 877 "parser.y"
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
#line 896 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 902 "parser.y"
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
#line 915 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 922 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 931 "parser.y"
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
#line 989 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 993 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1000 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1004 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1010 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1014 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1032 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1038 "parser.y"
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

  case 101:

/* Line 1455 of yacc.c  */
#line 1054 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1063 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1072 "parser.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 1085 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1099 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1103 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1107 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]),(yyvsp[(1) - (9)]));
}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1111 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)])|(yyvsp[(3) - (10)])));
}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1115 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]),((yyvsp[(2) - (11)]) | (yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1119 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1120 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]),((yyvsp[(4) - (14)])|(yyvsp[(6) - (14)])));
}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1123 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (8)]),&(method->returnparam) ); }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1124 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (13)]),(yyvsp[(9) - (13)]), ((yyvsp[(5) - (13)])|(yyvsp[(6) - (13)])));
	setPOPCMethodeModifier((yyvsp[(1) - (13)]));
}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1188 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1192 "parser.y"
    {
	/* error if multimple time same reserved word */
	if (((yyvsp[(2) - (2)]) & (yyvsp[(1) - (2)])) != 0)
	{
		errormsg("Multiple occurance of same POP-C++ Mehtode modivier!");
		exit(1);
	}
	
	(yyval)=(yyvsp[(2) - (2)]) | (yyvsp[(1) - (2)]);
}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1205 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1209 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1213 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1217 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1221 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1225 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1232 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1236 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1240 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1244 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1250 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1254 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1258 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1262 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1266 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1272 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1283 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1287 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1293 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1298 "parser.y"
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

  case 136:

/* Line 1455 of yacc.c  */
#line 1315 "parser.y"
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

  case 137:

/* Line 1455 of yacc.c  */
#line 1331 "parser.y"
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

  case 138:

/* Line 1455 of yacc.c  */
#line 1346 "parser.y"
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

  case 139:

/* Line 1455 of yacc.c  */
#line 1438 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1442 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1457 "parser.y"
    {
  Param *t=method->AddNewParam();
  UpdateMarshalParam((yyvsp[(1) - (9)]),t);

  DataType *type=currenttype;
  if ((yyvsp[(5) - (9)])>0)
    {
      type=new TypePtr(NULL, (yyvsp[(5) - (9)]) , type);
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

  t->isConst=((yyvsp[(2) - (9)])==1 || (yyvsp[(4) - (9)])==1);
  if ((yyvsp[(9) - (9)])>=0) t->defaultVal=strdup(GetToken((yyvsp[(9) - (9)])));
  

}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1491 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1495 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1501 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1505 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1511 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1515 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1519 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1524 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1532 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1536 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1540 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1546 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1550 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1556 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1560 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1573 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1582 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1586 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1590 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1595 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1600 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1605 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1610 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1615 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1620 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1625 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1630 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1635 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1640 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1645 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1650 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1655 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1660 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1665 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1670 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1675 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1680 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1685 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1690 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1695 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1701 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1706 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1711 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1716 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1723 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1727 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1733 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1737 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1745 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1749 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;



/* Line 1455 of yacc.c  */
#line 4022 "parser.tab.c"
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
#line 1757 "parser.y"


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
  fprintf(stderr,"%s:%d: ERROR in Parser: %s \n",filename,linenumber-1,s);
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
		type=new TypePtr(NULL, pointer, type);
		thisCodeFile->AddDataType(type);
	}

	if (ref)
	{
		method->returnparam.isRef=true;
	}
	
	method->isVirtual=((const_virtual & 1)!=0);
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
  /*	else method->invoketype=autoselect; */
}



