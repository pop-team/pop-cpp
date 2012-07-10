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
	Structure *structContainer;

	Method *method;
	// Param *param;

 int n,t;
 bool isNamespace = false;
 
 bool isInStruct = false;
 
 bool isParclassDeclared = false;
 
 bool hadParclass = false; 
 
 char holdnamespace[500];
 char tmp[10240];
 char typetmp[100];
 char tmpProc[10240];
 char tmpSize[10240];
 int parsingclass=0;

 void UpdateMarshalParam(int flags, Param *t);

 int ParseFile(char *infile, char *outfile, bool client, bool broker, bool warning);
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
#line 321 "parser.tab.c"

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
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  210
/* YYNRULES -- Number of states.  */
#define YYNSTATES  442

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
      23,    26,    29,    31,    34,    37,    40,    45,    47,    50,
      51,    58,    59,    62,    64,    66,    68,    70,    75,    78,
      81,    83,    84,    88,    91,    96,    97,   100,   106,   113,
     120,   126,   132,   135,   138,   139,   142,   144,   148,   150,
     153,   157,   161,   164,   170,   174,   177,   178,   181,   183,
     187,   189,   192,   196,   200,   202,   204,   206,   207,   210,
     211,   214,   215,   220,   223,   226,   229,   232,   235,   238,
     240,   246,   252,   254,   258,   260,   264,   267,   269,   273,
     278,   279,   284,   287,   289,   291,   293,   295,   297,   302,
     304,   307,   309,   313,   318,   319,   323,   324,   326,   327,
     329,   331,   333,   336,   337,   340,   346,   348,   353,   359,
     361,   370,   380,   390,   401,   413,   414,   429,   430,   446,
     448,   451,   453,   455,   457,   459,   461,   463,   465,   467,
     470,   473,   474,   476,   478,   481,   484,   486,   487,   492,
     493,   506,   517,   526,   533,   534,   537,   538,   540,   542,
     546,   556,   557,   561,   563,   567,   569,   571,   575,   579,
     580,   582,   584,   585,   587,   588,   591,   594,   596,   598,
     602,   606,   610,   614,   618,   622,   626,   630,   634,   638,
     642,   646,   652,   656,   660,   664,   668,   672,   675,   679,
     683,   688,   691,   694,   697,   700,   702,   704,   706,   710,
     712
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    77,    75,    -1,    -1,    82,    -1,    -1,
     100,    76,    75,    -1,    99,    75,    -1,    30,    75,    -1,
      79,    75,    -1,    85,    75,    -1,    78,    75,    -1,    28,
      -1,     1,    65,    -1,     1,    66,    -1,     1,    43,    -1,
      80,    64,    81,    67,    -1,    35,    -1,     6,    84,    -1,
      -1,    47,     6,    83,    68,    75,    66,    -1,    -1,    69,
      81,    -1,    87,    -1,    93,    -1,    94,    -1,     4,    -1,
      88,    68,    89,    66,    -1,    88,    78,    -1,    16,     6,
      -1,    16,    -1,    -1,    90,    65,    89,    -1,   118,    91,
      -1,   123,     6,   117,    92,    -1,    -1,    69,    91,    -1,
      17,     6,   123,     6,   117,    -1,    17,    16,     6,   123,
       6,   117,    -1,    17,     4,     6,   123,     6,   117,    -1,
      17,    87,   123,     6,   117,    -1,    95,    96,    68,     1,
      66,    -1,    95,    65,    -1,     4,     6,    -1,    -1,    61,
      97,    -1,    98,    -1,    97,    69,    98,    -1,     6,    -1,
     106,     6,    -1,    14,   106,     6,    -1,   106,    14,     6,
      -1,   102,    65,    -1,   101,    68,   108,    66,    65,    -1,
     102,   107,   103,    -1,     3,     6,    -1,    -1,    61,   104,
      -1,   105,    -1,   104,    69,   105,    -1,     6,    -1,   106,
       6,    -1,    14,   106,     6,    -1,   106,    14,     6,    -1,
      13,    -1,    11,    -1,    12,    -1,    -1,    58,     8,    -1,
      -1,   110,   108,    -1,    -1,   106,   109,    61,   108,    -1,
     111,    65,    -1,    87,    65,    -1,   126,    65,    -1,    86,
      65,    -1,    93,    65,    -1,   114,    65,    -1,    30,    -1,
       5,    64,     8,    67,    65,    -1,    45,     6,    68,   112,
      66,    -1,   113,    -1,   113,    69,   112,    -1,     6,    -1,
       6,    58,     8,    -1,   118,   115,    -1,   116,    -1,   116,
      69,   115,    -1,   123,   125,     6,   117,    -1,    -1,    70,
     152,    71,   117,    -1,   119,   120,    -1,   120,    -1,    32,
      -1,    33,    -1,     6,    -1,     7,    -1,     6,    60,   121,
      59,    -1,    87,    -1,    16,     6,    -1,   122,    -1,   122,
      69,   121,    -1,   120,   123,   117,   125,    -1,    -1,    50,
     124,   123,    -1,    -1,    15,    -1,    -1,    53,    -1,   128,
      -1,   130,    -1,   132,   127,    -1,    -1,    58,     8,    -1,
     129,    64,   143,    67,   140,    -1,     6,    -1,    56,   131,
      64,    67,    -1,    14,    56,   131,    64,    67,    -1,     6,
      -1,   118,   123,   125,   139,    64,   143,    67,   124,    -1,
     137,   118,   123,   125,   139,    64,   143,    67,   124,    -1,
     118,   137,   123,   125,   139,    64,   143,    67,   124,    -1,
     137,   118,   137,   123,   125,   139,    64,   143,    67,   124,
      -1,   135,   138,   118,   138,   123,   125,   139,    64,   143,
      67,   124,    -1,    -1,    70,   147,    71,   138,   118,   138,
     123,   125,   139,   133,    64,   143,    67,   124,    -1,    -1,
     135,    70,   147,    71,   138,   118,   138,   123,   125,   139,
     134,    64,   143,    67,   124,    -1,   136,    -1,   135,   136,
      -1,    18,    -1,    19,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    14,    -1,    15,    -1,    15,    14,    -1,
      14,    15,    -1,    -1,    14,    -1,    15,    -1,    15,    14,
      -1,    14,    15,    -1,     6,    -1,    -1,    72,    68,   141,
      66,    -1,    -1,     6,    73,     6,    64,   152,    69,   152,
      69,   152,    67,    65,   141,    -1,     6,    73,     6,    64,
     152,    69,   152,    67,    65,   141,    -1,     6,    73,     6,
      64,   152,    67,    65,   141,    -1,     6,    58,   152,   142,
      65,   141,    -1,    -1,    42,   152,    -1,    -1,   144,    -1,
     145,    -1,   145,    69,   144,    -1,   146,   149,   118,   149,
     123,   125,   150,   117,   151,    -1,    -1,    70,   147,    71,
      -1,   148,    -1,   148,    69,   147,    -1,    20,    -1,    21,
      -1,    27,    58,   152,    -1,    26,    58,     6,    -1,    -1,
      15,    -1,    34,    -1,    -1,     6,    -1,    -1,    58,   152,
      -1,   154,   117,    -1,   153,    -1,    10,    -1,   152,    48,
     152,    -1,   152,    49,   152,    -1,   152,    50,   152,    -1,
     152,    51,   152,    -1,   152,    52,   152,    -1,   152,    53,
     152,    -1,   152,    54,   152,    -1,   152,    55,   152,    -1,
     152,    36,   152,    -1,   152,    37,   152,    -1,   152,    38,
     152,    -1,   152,    58,   152,    -1,   152,    62,   152,    61,
     152,    -1,   152,    39,   152,    -1,   152,    59,   152,    -1,
     152,    60,   152,    -1,   152,    40,   152,    -1,   152,    41,
     152,    -1,    49,   152,    -1,    64,   152,    67,    -1,   154,
      64,    67,    -1,   154,    64,   155,    67,    -1,    50,   152,
      -1,    53,   152,    -1,    57,   152,    -1,    56,   152,    -1,
       8,    -1,     9,    -1,     6,    -1,     6,    44,     6,    -1,
     152,    -1,   155,    69,   152,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   140,   150,   151,   151,   152,   153,   154,
     155,   156,   162,   170,   183,   196,   212,   221,   238,   248,
     246,   272,   274,   282,   286,   287,   298,   315,   323,   329,
     363,   372,   373,   376,   379,   407,   408,   417,   447,   471,
     495,   520,   524,   526,   547,   548,   552,   553,   556,   580,
     605,   630,   660,   681,   689,   698,   724,   725,   728,   729,
     732,   746,   761,   778,   797,   801,   805,   813,   816,   825,
     826,   827,   827,   831,   832,   833,   834,   834,   850,   861,
     866,   877,   888,   892,   899,   903,   914,   916,   917,   920,
     952,   955,   970,   974,   982,   986,   992,  1003,  1019,  1038,
    1044,  1057,  1064,  1073,  1146,  1150,  1159,  1162,  1169,  1172,
    1184,  1185,  1186,  1189,  1190,  1196,  1212,  1221,  1230,  1243,
    1373,  1380,  1387,  1394,  1401,  1409,  1409,  1416,  1416,  1426,
    1430,  1476,  1480,  1484,  1488,  1492,  1496,  1503,  1507,  1511,
    1515,  1523,  1526,  1530,  1534,  1538,  1544,  1556,  1559,  1566,
    1570,  1587,  1603,  1618,  1711,  1714,  1722,  1723,  1725,  1726,
    1729,  1766,  1769,  1775,  1779,  1785,  1789,  1793,  1798,  1807,
    1810,  1814,  1821,  1824,  1831,  1834,  1847,  1856,  1860,  1864,
    1869,  1874,  1879,  1884,  1889,  1894,  1899,  1904,  1909,  1914,
    1919,  1924,  1929,  1934,  1939,  1944,  1949,  1954,  1959,  1964,
    1969,  1975,  1980,  1985,  1990,  1997,  2001,  2007,  2011,  2019,
    2023
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
  "startlist", "@1", "handle_this", "not_care_code", "pack_directive",
  "pack_header", "object_list", "namespace_declaration", "@2",
  "rest_object_list", "type_definition", "innerclass_definition",
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
      75,    75,    77,    78,    78,    78,    79,    80,    81,    83,
      82,    84,    84,    85,    85,    85,    86,    87,    87,    88,
      88,    89,    89,    90,    91,    92,    92,    93,    93,    93,
      93,    94,    94,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    99,   100,   101,   102,   103,   103,   104,   104,
     105,   105,   105,   105,   106,   106,   106,   107,   107,   108,
     108,   109,   108,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   120,   120,
     120,   121,   121,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   126,   127,   127,   128,   129,   130,   130,   131,
     132,   132,   132,   132,   132,   133,   132,   134,   132,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   137,
     137,   138,   138,   138,   138,   138,   139,   140,   140,   141,
     141,   141,   141,   141,   142,   142,   143,   143,   144,   144,
     145,   146,   146,   147,   147,   148,   148,   148,   148,   149,
     149,   149,   150,   150,   151,   151,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   153,   153,   154,   154,   155,
     155
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     0,     3,     2,     2,     2,
       2,     2,     1,     2,     2,     2,     4,     1,     2,     0,
       6,     0,     2,     1,     1,     1,     1,     4,     2,     2,
       1,     0,     3,     2,     4,     0,     2,     5,     6,     6,
       5,     5,     2,     2,     0,     2,     1,     3,     1,     2,
       3,     3,     2,     5,     3,     2,     0,     2,     1,     3,
       1,     2,     3,     3,     1,     1,     1,     0,     2,     0,
       2,     0,     4,     2,     2,     2,     2,     2,     2,     1,
       5,     5,     1,     3,     1,     3,     2,     1,     3,     4,
       0,     4,     2,     1,     1,     1,     1,     1,     4,     1,
       2,     1,     3,     4,     0,     3,     0,     1,     0,     1,
       1,     1,     2,     0,     2,     5,     1,     4,     5,     1,
       8,     9,     9,    10,    11,     0,    14,     0,    15,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     0,     1,     1,     2,     2,     1,     0,     4,     0,
      12,    10,     8,     6,     0,     2,     0,     1,     1,     3,
       9,     0,     3,     1,     3,     1,     1,     3,     3,     0,
       1,     1,     0,     1,     0,     2,     2,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     3,     3,     3,     3,     3,     2,     3,     3,
       4,     2,     2,     2,     2,     1,     1,     1,     3,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    30,     0,    12,     0,    17,     0,
       0,     0,     0,     0,     0,     4,     0,    23,     0,    24,
      25,    44,     0,     5,     0,    67,    15,    13,    14,    55,
      43,    29,     0,   104,    30,   104,     8,    19,     1,     2,
      11,     9,     0,    10,    31,    28,     0,    42,     0,     7,
       0,    69,     0,    52,    56,   104,   106,     0,    29,     0,
       0,    21,     0,    96,    97,    30,    94,    95,    99,     0,
       0,   104,     0,    93,    48,    65,    66,    64,     0,    45,
      46,     0,     0,     6,    26,     0,    96,   137,   138,   131,
     132,   133,   134,   135,   136,    79,     0,     0,     0,     0,
      99,     0,    71,     0,    69,     0,     0,   104,     0,   110,
       0,   111,   113,   141,   129,     0,    68,     0,    54,     0,
     107,   104,    90,     0,    90,     0,     0,    18,    16,     0,
     100,    27,    31,    33,     0,    92,     0,     0,    49,     0,
       0,     0,   140,     0,   139,     0,   119,     0,   165,   166,
       0,     0,     0,   163,    76,    74,    77,     0,     0,    70,
      73,    78,   137,    86,    87,   108,   104,    75,   161,     0,
     112,   142,   143,     0,   130,     0,   104,    60,     0,    57,
      58,     0,    90,   105,     0,    37,    90,    40,     0,    22,
     104,     0,   101,    32,    90,    50,    47,    51,    41,     0,
       0,     0,     0,     0,     0,   141,     0,    69,    53,   104,
     109,     0,   108,     0,     0,   157,   158,   169,   114,   145,
     144,     0,   141,   108,   104,     0,     0,    61,     0,    39,
     207,   205,   206,   178,     0,     0,     0,     0,     0,     0,
       0,   177,    90,    38,    20,    90,    98,     0,    35,     0,
       0,    84,     0,    82,   117,   168,   167,     0,   164,    72,
      88,   108,    90,     0,     0,     0,   147,   161,   170,   171,
       0,   141,   104,     0,   108,    62,    59,    63,     0,   197,
     201,   202,   204,   203,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,     0,   176,   108,   102,   104,    34,
      80,   118,     0,    81,     0,   141,     0,    89,   161,   146,
       0,   162,     0,   115,   159,   169,     0,   108,     0,     0,
     208,   198,   187,   188,   189,   192,   195,   196,   179,   180,
     181,   182,   183,   184,   185,   186,   190,   193,   194,     0,
      91,   199,   209,     0,   103,    36,    85,    83,   104,    90,
       0,   161,   149,   104,   141,     0,   161,     0,     0,   200,
       0,   108,   106,     0,     0,     0,   108,   104,     0,     0,
     161,   191,   210,     0,   120,   106,     0,     0,   148,   172,
     108,   161,   106,     0,   125,   122,   154,     0,   173,    90,
       0,     0,   121,   106,     0,     0,     0,     0,   174,   127,
     106,   123,   161,   155,   149,     0,     0,   160,     0,   124,
       0,   153,     0,     0,   175,   161,   106,   149,     0,     0,
     126,   152,     0,     0,   106,   149,     0,   128,   151,     0,
     149,   150
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    50,    11,    12,    13,    14,    62,    15,    60,
     127,    16,    99,    68,    18,    69,    70,   133,   309,    19,
      20,    21,    48,    79,    80,    22,    23,    24,    25,   118,
     179,   180,   102,    54,   103,   157,   104,   105,   252,   253,
     106,   163,   164,   317,   107,    72,    73,   191,   192,   134,
     121,   211,   108,   170,   109,   110,   111,   147,   112,   404,
     418,   113,   114,   115,   175,   263,   323,   375,   406,   214,
     215,   216,   217,   152,   153,   270,   399,   417,   240,   241,
     242,   353
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -236
static const yytype_int16 yypact[] =
{
      36,    19,    24,    48,    59,    75,  -236,   274,  -236,    63,
      70,   274,   274,   274,    26,  -236,   274,  -236,    10,  -236,
    -236,   -44,   274,  -236,    60,   -42,  -236,  -236,  -236,  -236,
    -236,  -236,    86,    84,   121,    84,  -236,  -236,  -236,  -236,
    -236,  -236,   132,  -236,    25,  -236,   197,  -236,    74,  -236,
     274,   240,   137,  -236,    95,    84,   151,   161,     1,   171,
     113,   116,   122,   130,  -236,   187,  -236,  -236,  -236,   131,
     139,    84,   144,  -236,  -236,  -236,  -236,  -236,   159,   136,
    -236,    20,   205,  -236,  -236,   149,    53,     0,   204,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,   214,   219,   174,   164,
     166,   169,  -236,   170,   240,   172,   173,     5,   175,  -236,
     177,  -236,   184,   337,  -236,    25,  -236,   210,  -236,   229,
    -236,    84,   178,   244,   178,   311,   132,  -236,  -236,   144,
      12,  -236,    25,  -236,   254,  -236,   255,   197,  -236,   260,
     202,   261,  -236,   219,  -236,   203,  -236,   212,  -236,  -236,
     221,   223,   211,   215,  -236,  -236,  -236,   225,   222,  -236,
    -236,  -236,   277,  -236,   220,   241,    84,  -236,    77,   285,
    -236,   280,   283,   174,  -236,    25,     5,  -236,   159,   230,
    -236,    54,   178,  -236,   326,  -236,   178,  -236,   232,  -236,
      84,   246,   231,  -236,   178,  -236,  -236,  -236,  -236,   236,
     242,   301,   249,   305,   326,    28,   174,   240,  -236,    84,
    -236,   307,   241,   174,   250,  -236,   264,    -6,  -236,  -236,
    -236,   247,    28,   241,    84,   323,   210,  -236,   331,  -236,
     294,  -236,  -236,  -236,   326,   326,   326,   326,   326,   326,
     360,  -236,    23,  -236,  -236,   178,  -236,   144,   276,   278,
     281,   289,   287,   288,  -236,  -236,   573,    25,  -236,  -236,
    -236,   241,    52,   290,   343,   295,   293,   298,  -236,  -236,
      25,    28,    84,   343,   241,  -236,  -236,  -236,   363,  -236,
     600,   427,   427,   427,   455,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   178,   314,  -236,   241,  -236,    84,  -236,
    -236,  -236,   364,  -236,   301,    28,   367,  -236,    77,  -236,
     310,  -236,   312,  -236,  -236,    -6,    25,   241,   320,   343,
    -236,  -236,   324,   324,   324,   324,   324,   324,   600,   600,
     600,   600,   600,   427,   427,   427,   427,   324,   324,   519,
    -236,  -236,   573,    94,  -236,  -236,  -236,  -236,    84,   178,
     318,    77,   381,    84,    28,   343,    77,   325,   326,  -236,
     326,   241,   151,   321,   -40,   327,   241,    84,   328,   335,
      77,  -236,   573,   343,  -236,   151,   326,   385,  -236,   388,
     241,    77,   151,   336,  -236,  -236,   546,   340,  -236,   178,
     343,   338,  -236,   151,   342,   326,   330,   326,   358,  -236,
     151,  -236,    77,   573,   381,   387,   326,  -236,   353,  -236,
     354,  -236,   365,   326,   573,    77,   151,   381,   421,   362,
    -236,  -236,   368,   326,   151,   381,   487,  -236,  -236,   369,
     381,  -236
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -236,   142,  -236,  -236,   414,  -236,  -236,   317,  -236,  -236,
    -236,  -236,  -236,   124,  -236,   316,  -236,   143,  -236,   -45,
    -236,  -236,  -236,  -236,   313,  -236,  -236,  -236,  -236,  -236,
    -236,   218,     4,  -236,   -92,  -236,  -236,  -236,   138,  -236,
    -236,   268,  -236,  -119,   -43,  -236,   -68,   206,  -236,   -33,
     -84,  -188,  -236,  -236,  -236,  -236,  -236,   339,  -236,  -236,
    -236,  -236,   371,   -99,  -195,  -235,  -236,  -228,  -236,  -193,
     188,  -236,  -236,   -54,  -236,   153,  -236,  -236,  -190,  -236,
    -236,  -236
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -157
static const yytype_int16 yytable[] =
{
      57,    71,    59,   185,   135,   187,   101,  -104,   166,   268,
     257,     1,   159,   -29,   256,   142,    52,    46,   386,   162,
      88,    47,   119,    53,   264,   123,   138,   272,   269,   320,
      29,    63,    64,   387,   139,   273,    -3,     1,   328,     2,
       3,    65,   171,   172,   279,   280,   281,   282,   283,   284,
      81,    56,     4,     5,    30,    56,   143,    66,    67,   101,
     227,   190,    26,   229,     6,    31,     7,   243,   228,    37,
      38,     8,   176,   316,   165,   248,   326,   224,    44,    32,
     -29,    33,   136,     9,    27,    28,   329,   304,   183,    71,
      42,    34,    55,   184,   367,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   129,   352,   259,  -146,  -116,   354,   221,
     358,   181,   184,   305,    17,   360,   306,    58,    51,    35,
     378,    17,   222,   212,    56,    17,    17,    17,    61,   365,
      17,    81,    82,   223,  -156,   116,    17,   213,   394,    36,
      63,    64,   258,    39,    40,    41,   117,   245,    43,   265,
      65,   369,   101,   370,    49,   409,   120,   122,   373,   377,
      75,    76,    77,   379,    17,   100,   261,   124,   381,   190,
     382,   125,   225,   383,   350,   126,   421,   393,   389,   128,
     129,   274,    83,   130,   148,   149,   396,   131,   401,   431,
     150,   151,   400,    74,   132,   137,   140,   438,    75,    76,
      77,    78,   441,   141,   315,   413,   177,   415,   144,   420,
     145,    75,    76,    77,   178,   146,   424,   325,   100,   154,
     181,   155,   429,   428,   156,   182,   158,   160,   161,   327,
     167,   168,   169,   436,    84,    85,    86,    64,   184,    17,
     186,    75,    76,    77,    87,    88,    65,     5,    89,    90,
     194,   195,    91,    92,    93,    94,   197,   188,   198,   199,
      95,   201,    66,    67,    -3,     1,   202,     2,     3,   203,
     408,   204,   205,   364,   206,    96,   207,   208,   384,   209,
       4,     5,   142,   218,   210,   219,    97,   220,   244,   226,
     247,   395,     6,   249,     7,   246,   250,   251,   402,     8,
      98,   255,     1,   262,     2,     3,   254,   266,   271,   411,
     230,     9,   231,   232,   233,   371,   419,     4,     5,   275,
     376,   100,   230,   267,   231,   232,   233,   277,   278,     6,
      -3,     7,   430,   310,   390,   308,     8,   312,   311,   319,
     437,   171,   172,   313,   318,    89,    90,   314,     9,    91,
      92,    93,    94,   234,   235,   322,   321,   236,   213,   330,
     237,   238,   356,   359,   361,   234,   235,    -3,   239,   236,
     362,   351,   237,   238,   366,   372,   302,   374,   385,   380,
     239,   397,   391,   388,   398,   414,   285,   286,   287,   288,
     289,   290,   392,   403,   407,   410,   412,   173,   291,   292,
     293,   294,   295,   296,   297,   298,   416,   425,   299,   300,
     301,   426,   302,   285,   286,   287,   288,   289,   290,   434,
     427,   303,    45,   435,   440,   291,   292,   293,   294,   295,
     296,   297,   298,   189,   276,   299,   300,   301,   193,   302,
     196,   355,   357,   307,   422,   324,   423,   285,   286,   287,
     288,   289,   290,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   260,   363,   299,
     300,   301,   200,   302,   174,     0,   300,   301,   432,   302,
     433,   285,   286,   287,   288,   289,   290,     0,     0,     0,
       0,     0,     0,   291,   292,   293,   294,   295,   296,   297,
     298,     0,     0,   299,   300,   301,     0,   302,     0,     0,
       0,     0,   331,   285,   286,   287,   288,   289,   290,     0,
       0,     0,     0,     0,     0,   291,   292,   293,   294,   295,
     296,   297,   298,     0,     0,   299,   300,   301,     0,   302,
       0,     0,     0,     0,   439,   285,   286,   287,   288,   289,
     290,     0,     0,     0,     0,     0,     0,   291,   292,   293,
     294,   295,   296,   297,   298,     0,     0,   299,   300,   301,
     368,   302,   285,   286,   287,   288,   289,   290,   405,     0,
       0,     0,     0,     0,   291,   292,   293,   294,   295,   296,
     297,   298,     0,     0,   299,   300,   301,     0,   302,   285,
     286,   287,   288,   289,   290,     0,     0,     0,     0,     0,
       0,   291,   292,   293,   294,   295,   296,   297,   298,     0,
       0,   299,   300,   301,     0,   302,   285,   286,   287,   288,
     289,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   296,   297,   298,     0,     0,   299,   300,
     301,     0,   302
};

static const yytype_int16 yycheck[] =
{
      33,    44,    35,   122,    72,   124,    51,     6,   107,    15,
     205,     1,   104,     1,   204,    15,    58,    61,    58,    14,
      15,    65,    55,    65,   212,    58,     6,   222,    34,   264,
       6,     6,     7,    73,    14,   223,     0,     1,   273,     3,
       4,    16,    14,    15,   234,   235,   236,   237,   238,   239,
      46,    50,    16,    17,     6,    50,    56,    32,    33,   104,
       6,   129,    43,   182,    28,     6,    30,   186,    14,     6,
       0,    35,   115,   261,   107,   194,   271,   176,    68,     4,
      68,     6,    78,    47,    65,    66,   274,    64,   121,   132,
      64,    16,     6,    70,   329,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,    60,   304,   207,    64,    64,   306,   173,
     315,   117,    70,   242,     0,   318,   245,     6,    68,     5,
     365,     7,   175,   166,    50,    11,    12,    13,     6,   327,
      16,   137,    68,   176,    67,     8,    22,    70,   383,     7,
       6,     7,   206,    11,    12,    13,    61,   190,    16,   213,
      16,    67,   207,    69,    22,   400,    15,     6,   361,   364,
      11,    12,    13,   366,    50,    51,   209,     6,   368,   247,
     370,    68,   178,   371,   303,    69,   414,   380,   376,    67,
      60,   224,    50,     6,    20,    21,   386,    66,   391,   427,
      26,    27,   390,     6,    65,    69,     1,   435,    11,    12,
      13,    14,   440,    64,   257,   405,     6,   407,    14,   412,
       6,    11,    12,    13,    14,     6,   416,   270,   104,    65,
     226,    65,   425,   423,    65,     6,    66,    65,    65,   272,
      65,    64,    58,   433,     4,     5,     6,     7,    70,   125,
       6,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       6,     6,    22,    23,    24,    25,     6,   125,    66,     8,
      30,    68,    32,    33,     0,     1,    64,     3,     4,    58,
     399,    58,    71,   326,    69,    45,    61,    65,   372,    69,
      16,    17,    15,     8,    53,    15,    56,    14,    66,    69,
      69,   385,    28,    67,    30,    59,    64,     6,   392,    35,
      70,     6,     1,     6,     3,     4,    67,    67,    71,   403,
       6,    47,     8,     9,    10,   358,   410,    16,    17,     6,
     363,   207,     6,    69,     8,     9,    10,     6,    44,    28,
      66,    30,   426,    65,   377,    69,    35,    58,    67,     6,
     434,    14,    15,    66,    64,    18,    19,    69,    47,    22,
      23,    24,    25,    49,    50,    72,    71,    53,    70,     6,
      56,    57,     8,     6,    64,    49,    50,    66,    64,    53,
      68,    67,    56,    57,    64,    67,    62,     6,    67,    64,
      64,     6,    64,    66,     6,    65,    36,    37,    38,    39,
      40,    41,    67,    67,    64,    67,    64,    70,    48,    49,
      50,    51,    52,    53,    54,    55,    58,    64,    58,    59,
      60,    67,    62,    36,    37,    38,    39,    40,    41,    67,
      65,    71,    18,    65,    65,    48,    49,    50,    51,    52,
      53,    54,    55,   126,   226,    58,    59,    60,   132,    62,
     137,   308,   314,   247,    67,   267,    69,    36,    37,    38,
      39,    40,    41,    36,    37,    38,    39,    40,    41,    48,
      49,    50,    51,    52,    53,    54,    55,   209,   325,    58,
      59,    60,   143,    62,   113,    -1,    59,    60,    67,    62,
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
       0,     1,     3,     4,    16,    17,    28,    30,    35,    47,
      75,    77,    78,    79,    80,    82,    85,    87,    88,    93,
      94,    95,    99,   100,   101,   102,    43,    65,    66,     6,
       6,     6,     4,     6,    16,    87,    75,     6,     0,    75,
      75,    75,    64,    75,    68,    78,    61,    65,    96,    75,
      76,    68,    58,    65,   107,     6,    50,   123,     6,   123,
      83,     6,    81,     6,     7,    16,    32,    33,    87,    89,
      90,   118,   119,   120,     6,    11,    12,    13,    14,    97,
      98,   106,    68,    75,     4,     5,     6,    14,    15,    18,
      19,    22,    23,    24,    25,    30,    45,    56,    70,    86,
      87,    93,   106,   108,   110,   111,   114,   118,   126,   128,
     129,   130,   132,   135,   136,   137,     8,    61,   103,   123,
      15,   124,     6,   123,     6,    68,    69,    84,    67,    60,
       6,    66,    65,    91,   123,   120,   106,    69,     6,    14,
       1,    64,    15,    56,    14,     6,     6,   131,    20,    21,
      26,    27,   147,   148,    65,    65,    65,   109,    66,   108,
      65,    65,    14,   115,   116,   123,   137,    65,    64,    58,
     127,    14,    15,    70,   136,   138,   118,     6,    14,   104,
     105,   106,     6,   123,    70,   117,     6,   117,    75,    81,
     120,   121,   122,    89,     6,     6,    98,     6,    66,     8,
     131,    68,    64,    58,    58,    71,    69,    61,    65,    69,
      53,   125,   123,    70,   143,   144,   145,   146,     8,    15,
      14,   147,   118,   123,   137,   106,    69,     6,    14,   117,
       6,     8,     9,    10,    49,    50,    53,    56,    57,    64,
     152,   153,   154,   117,    66,   123,    59,    69,   117,    67,
      64,     6,   112,   113,    67,     6,   152,   138,   147,   108,
     115,   123,     6,   139,   125,   147,    67,    69,    15,    34,
     149,    71,   138,   125,   123,     6,   105,     6,    44,   152,
     152,   152,   152,   152,   152,    36,    37,    38,    39,    40,
      41,    48,    49,    50,    51,    52,    53,    54,    55,    58,
      59,    60,    62,    71,    64,   117,   117,   121,    69,    92,
      65,    67,    58,    66,    69,   118,   125,   117,    64,     6,
     139,    71,    72,   140,   144,   118,   138,   123,   139,   125,
       6,    67,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     117,    67,   152,   155,   125,    91,     8,   112,   138,     6,
     143,    64,    68,   149,   118,   125,    64,   139,    61,    67,
      69,   123,    67,   143,     6,   141,   123,   138,   139,   143,
      64,   152,   152,   125,   124,    67,    58,    73,    66,   125,
     123,    64,    67,   143,   139,   124,   152,     6,     6,   150,
     125,   143,   124,    67,   133,    42,   142,    64,   117,   139,
      67,   124,    64,   152,    65,   152,    58,   151,   134,   124,
     143,   141,    67,    69,   152,    64,    67,    65,   152,   143,
     124,   141,    67,    69,    67,    65,   152,   124,   141,    67,
      65,   141
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
#line 140 "parser.y"
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

  case 5:
#line 151 "parser.y"
    { insideClass=false; othercodes.SetSize(0); startPos=-1;}
    break;

  case 11:
#line 157 "parser.y"
    {
  CleanStack(); 
}
    break;

  case 12:
#line 163 "parser.y"
    {
	printf("handle at Bison\n");
	othercodes.InsertAt(-1,"\n",strlen("\n"));
}
    break;

  case 13:
#line 171 "parser.y"
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
#line 184 "parser.y"
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

  case 15:
#line 197 "parser.y"
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

  case 16:
#line 213 "parser.y"
    {
	isParclassDeclared = true; 
	currentPack->SetEndLine(linenumber-1);
  	currentPack=NULL;
  	othercodes.SetSize(0);
  	startPos=-1;
}
    break;

  case 17:
#line 222 "parser.y"
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

  case 18:
#line 239 "parser.y"
    {
  		if (currentPack!=NULL) {
			currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
		}
}
    break;

  case 19:
#line 248 "parser.y"
    {
	
	// Avoid handling of standard namespace used in POP-C++
	
	if(strcmp("__gnu_cxx", GetToken((yyvsp[(2) - (2)]))) != 0 &&  strcmp("std", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("__gnu_debug", GetToken((yyvsp[(2) - (2)]))) != 0 && strcmp("rel_ops", GetToken((yyvsp[(2) - (2)]))) != 0  && strcmp("__debug", GetToken((yyvsp[(2) - (2)]))) != 0){
			
		isNamespace = true;
			
		sprintf(holdnamespace, "%s", GetToken((yyvsp[(2) - (2)])));
	
	}

}
    break;

  case 20:
#line 263 "parser.y"
    {
	
	isNamespace = false;

}
    break;

  case 21:
#line 272 "parser.y"
    {
}
    break;

  case 22:
#line 275 "parser.y"
    {
}
    break;

  case 23:
#line 283 "parser.y"
    {
    CleanStack();
}
    break;

  case 26:
#line 299 "parser.y"
    {
	
	sprintf(tmp,"Class declaration inside parclass are not currently supported !\n");
	
	errormsg(tmp);
	exit(1);

}
    break;

  case 27:
#line 316 "parser.y"
    {
  	currentstruct=Pop();
  	if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  	(yyval)=(yyvsp[(1) - (4)]);
  	structContainer = NULL;
  	isInStruct = false;
}
    break;

  case 28:
#line 324 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 29:
#line 330 "parser.y"
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

  case 30:
#line 364 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 34:
#line 380 "parser.y"
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

  case 37:
#line 418 "parser.y"
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

  case 38:
#line 448 "parser.y"
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

  case 39:
#line 472 "parser.y"
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

  case 40:
#line 496 "parser.y"
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

  case 41:
#line 521 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 43:
#line 527 "parser.y"
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

  case 48:
#line 557 "parser.y"
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

  case 49:
#line 581 "parser.y"
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

  case 50:
#line 606 "parser.y"
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

  case 51:
#line 631 "parser.y"
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

  case 52:
#line 661 "parser.y"
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

  case 53:
#line 682 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 54:
#line 690 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 55:
#line 699 "parser.y"
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

  case 60:
#line 733 "parser.y"
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

  case 61:
#line 747 "parser.y"
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

  case 62:
#line 762 "parser.y"
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

  case 63:
#line 779 "parser.y"
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

  case 64:
#line 798 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 65:
#line 802 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 66:
#line 806 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 67:
#line 813 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 68:
#line 817 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 71:
#line 827 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 77:
#line 835 "parser.y"
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

  case 78:
#line 851 "parser.y"
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

  case 79:
#line 862 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 80:
#line 867 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 81:
#line 878 "parser.y"
    {
	assert(currentClass!=NULL);
	Enumeration *t = new Enumeration(currentClass, accessmodifier);
	t->SetLineInfo(linenumber-1);
	currentClass->AddMember(t);
	t->setName(GetToken((yyvsp[(2) - (5)])));
	t->setArgs(GetToken((yyvsp[(4) - (5)])));
}
    break;

  case 82:
#line 889 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);	
}
    break;

  case 83:
#line 893 "parser.y"
    {
	sprintf(tmp,"%s , %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
	(yyval) = PutToken(tmp);
}
    break;

  case 84:
#line 900 "parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
}
    break;

  case 85:
#line 904 "parser.y"
    {      
	sprintf(tmp,"%s = %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
   (yyval)=PutToken(tmp);
}
    break;

  case 89:
#line 921 "parser.y"
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

  case 90:
#line 952 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 91:
#line 956 "parser.y"
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

  case 92:
#line 971 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 93:
#line 975 "parser.y"
    {
	
	
	(yyval)=0;
}
    break;

  case 94:
#line 983 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 95:
#line 987 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 96:
#line 993 "parser.y"
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

  case 97:
#line 1004 "parser.y"
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

  case 98:
#line 1020 "parser.y"
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

  case 99:
#line 1039 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 100:
#line 1045 "parser.y"
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

  case 101:
#line 1058 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 102:
#line 1065 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 103:
#line 1074 "parser.y"
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

  case 104:
#line 1146 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 105:
#line 1151 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 106:
#line 1159 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 107:
#line 1163 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 108:
#line 1169 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 109:
#line 1173 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 114:
#line 1191 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 115:
#line 1197 "parser.y"
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

  case 116:
#line 1213 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 117:
#line 1222 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 118:
#line 1231 "parser.y"
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

  case 119:
#line 1244 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 120:
#line 1374 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 121:
#line 1381 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 122:
#line 1388 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 123:
#line 1395 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 124:
#line 1402 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 125:
#line 1409 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 126:
#line 1410 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 127:
#line 1416 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 128:
#line 1417 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 129:
#line 1427 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 130:
#line 1431 "parser.y"
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

  case 131:
#line 1477 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 132:
#line 1481 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 133:
#line 1485 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 134:
#line 1489 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 135:
#line 1493 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 136:
#line 1497 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 137:
#line 1504 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 138:
#line 1508 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 139:
#line 1512 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 140:
#line 1516 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 141:
#line 1523 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 142:
#line 1527 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 143:
#line 1531 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 144:
#line 1535 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 145:
#line 1539 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 146:
#line 1545 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 147:
#line 1556 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 148:
#line 1560 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 149:
#line 1566 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 150:
#line 1571 "parser.y"
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

  case 151:
#line 1588 "parser.y"
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

  case 152:
#line 1604 "parser.y"
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

  case 153:
#line 1619 "parser.y"
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

  case 154:
#line 1711 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 155:
#line 1715 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 160:
#line 1730 "parser.y"
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

  case 161:
#line 1766 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 162:
#line 1770 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 163:
#line 1776 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 164:
#line 1780 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 165:
#line 1786 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 166:
#line 1790 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 167:
#line 1794 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 168:
#line 1799 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 169:
#line 1807 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 170:
#line 1811 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 171:
#line 1815 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 172:
#line 1821 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 173:
#line 1825 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 174:
#line 1831 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 175:
#line 1835 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 176:
#line 1848 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 177:
#line 1857 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 178:
#line 1861 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 179:
#line 1865 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 180:
#line 1870 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 181:
#line 1875 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:
#line 1880 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:
#line 1885 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:
#line 1890 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:
#line 1895 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:
#line 1900 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:
#line 1905 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:
#line 1910 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:
#line 1915 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:
#line 1920 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:
#line 1925 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:
#line 1930 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 193:
#line 1935 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 194:
#line 1940 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 195:
#line 1945 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 196:
#line 1950 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 197:
#line 1955 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 198:
#line 1960 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 199:
#line 1965 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 200:
#line 1970 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 201:
#line 1976 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 202:
#line 1981 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 203:
#line 1986 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 204:
#line 1991 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 205:
#line 1998 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 206:
#line 2002 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 207:
#line 2008 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 208:
#line 2012 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 209:
#line 2020 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 210:
#line 2024 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;


/* Line 1267 of yacc.c.  */
#line 3915 "parser.tab.c"
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


#line 2032 "parser.y"


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
	bool warning=true;

	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")!=NULL){
		
		broker=false;
	
	} 	
	
	
	if (paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")!=NULL) {
		
		client=false;
	
	}  
	
	if (paroc_utils::checkremove(&argc,&argv,"-nowarning")!=NULL) {
		
		warning=false;
	
	}  
	
	int ret;
	indexsource=-1;
	errorcode=0;
	if (argc<2){
		Usage();
	} else {
		if ((ret=ParseFile(argv[1], ((argc>2) ? argv[2] : NULL), client, broker, warning))!=0)	{
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

int yywrap()
{
  return(1);
}


int base=1;

int ParseFile(char *infile, char *outfile, bool client, bool broker, bool warning)
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
			if(warning){      
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
										char * objname = new char[parclass_name.size() + 1];
										std::copy(parclass_name.begin(), parclass_name.end(), objname);
										objname[parclass_name.size()] = '\0';
										
										currentPack->AddObject(objname);
										
										delete [] objname;
										isParclassDeclared = true; 
										currentPack->SetEndLine(linenumber-1);
										currentPack=NULL;
										othercodes.SetSize(0);
										startPos=-1;

										// Ok file exists, so we will find the parclass name and add the pack directive with it
										std::cout << filename << ":" << linenumber << ": Warning: Pack directive was not present! Implicit declaration has been added from ";
										std::cout << ph_file << std::endl;
																
									}
								}
							}
						}
					}
				}	
			}
			/* End of @pack handling */
			
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


