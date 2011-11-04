
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


/* Line 189 of yacc.c  */
#line 179 "parser.tab.c"

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
     UMINUS = 300
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
#define UMINUS 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 311 "parser.tab.c"

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
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   578

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNRULES -- Number of states.  */
#define YYNSTATES  415

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,     2,     2,    49,    50,     2,
      61,    64,    47,    45,    65,    46,    70,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    62,
      57,    55,    56,    59,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    67,     2,    68,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,    51,    63,    53,     2,     2,     2,
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
      60
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
     211,   214,   216,   222,   225,   227,   231,   236,   237,   242,
     245,   247,   249,   251,   253,   255,   260,   262,   265,   267,
     271,   276,   277,   281,   282,   284,   285,   287,   289,   291,
     294,   295,   298,   304,   306,   311,   317,   319,   328,   338,
     348,   359,   371,   372,   387,   388,   404,   406,   409,   411,
     413,   415,   417,   419,   421,   423,   425,   428,   431,   432,
     434,   436,   439,   442,   444,   445,   450,   451,   464,   475,
     484,   491,   492,   495,   496,   498,   500,   504,   514,   515,
     519,   521,   525,   527,   529,   533,   537,   538,   540,   542,
     543,   545,   546,   549,   552,   554,   556,   560,   564,   568,
     572,   576,   580,   584,   588,   592,   596,   600,   604,   610,
     614,   618,   622,   626,   630,   633,   637,   641,   646,   649,
     652,   655,   658,   660,   662,   664,   668,   670
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    74,    72,    -1,    -1,    -1,    94,    73,
      72,    -1,    93,    72,    -1,    30,    72,    -1,    76,    72,
      -1,    80,    72,    -1,    75,    72,    -1,    28,    -1,     1,
      62,    -1,     1,    63,    -1,     1,    43,    -1,    77,    61,
      78,    64,    -1,    35,    -1,     6,    79,    -1,    -1,    65,
      78,    -1,    81,    -1,    87,    -1,    88,    -1,    82,    66,
      83,    63,    -1,    82,    75,    -1,    16,     6,    -1,    16,
      -1,    -1,    84,    62,    83,    -1,   109,    85,    -1,   114,
       6,   108,    86,    -1,    -1,    65,    85,    -1,    17,     6,
     114,     6,   108,    -1,    17,    16,     6,   114,     6,   108,
      -1,    17,     4,     6,   114,     6,   108,    -1,    17,    81,
     114,     6,   108,    -1,    89,    90,    66,     1,    63,    -1,
      89,    62,    -1,     4,     6,    -1,    -1,    58,    91,    -1,
      92,    -1,    91,    65,    92,    -1,     6,    -1,   100,     6,
      -1,    14,   100,     6,    -1,   100,    14,     6,    -1,    96,
      62,    -1,    95,    66,   102,    63,    62,    -1,    96,   101,
      97,    -1,     3,     6,    -1,    -1,    58,    98,    -1,    99,
      -1,    98,    65,    99,    -1,     6,    -1,   100,     6,    -1,
      14,   100,     6,    -1,   100,    14,     6,    -1,    13,    -1,
      11,    -1,    12,    -1,    -1,    55,     8,    -1,    -1,   104,
     102,    -1,    -1,   100,   103,    58,   102,    -1,   117,    62,
      -1,   105,    62,    -1,    30,    -1,     5,    61,     8,    64,
      62,    -1,   109,   106,    -1,   107,    -1,   107,    65,   106,
      -1,   114,   116,     6,   108,    -1,    -1,    67,   143,    68,
     108,    -1,   110,   111,    -1,   111,    -1,    32,    -1,    33,
      -1,     6,    -1,     7,    -1,     6,    57,   112,    56,    -1,
      81,    -1,    16,     6,    -1,   113,    -1,   113,    65,   112,
      -1,   111,   114,   108,   116,    -1,    -1,    47,   115,   114,
      -1,    -1,    15,    -1,    -1,    50,    -1,   119,    -1,   121,
      -1,   123,   118,    -1,    -1,    55,     8,    -1,   120,    61,
     134,    64,   131,    -1,     6,    -1,    53,   122,    61,    64,
      -1,    14,    53,   122,    61,    64,    -1,     6,    -1,   109,
     114,   116,   130,    61,   134,    64,   115,    -1,   128,   109,
     114,   116,   130,    61,   134,    64,   115,    -1,   109,   128,
     114,   116,   130,    61,   134,    64,   115,    -1,   128,   109,
     128,   114,   116,   130,    61,   134,    64,   115,    -1,   126,
     129,   109,   129,   114,   116,   130,    61,   134,    64,   115,
      -1,    -1,    67,   138,    68,   129,   109,   129,   114,   116,
     130,   124,    61,   134,    64,   115,    -1,    -1,   126,    67,
     138,    68,   129,   109,   129,   114,   116,   130,   125,    61,
     134,    64,   115,    -1,   127,    -1,   126,   127,    -1,    18,
      -1,    19,    -1,    22,    -1,    23,    -1,    24,    -1,    25,
      -1,    14,    -1,    15,    -1,    15,    14,    -1,    14,    15,
      -1,    -1,    14,    -1,    15,    -1,    15,    14,    -1,    14,
      15,    -1,     6,    -1,    -1,    69,    66,   132,    63,    -1,
      -1,     6,    70,     6,    61,   143,    65,   143,    65,   143,
      64,    62,   132,    -1,     6,    70,     6,    61,   143,    65,
     143,    64,    62,   132,    -1,     6,    70,     6,    61,   143,
      64,    62,   132,    -1,     6,    55,   143,   133,    62,   132,
      -1,    -1,    42,   143,    -1,    -1,   135,    -1,   136,    -1,
     136,    65,   135,    -1,   137,   140,   109,   140,   114,   116,
     141,   108,   142,    -1,    -1,    67,   138,    68,    -1,   139,
      -1,   139,    65,   138,    -1,    20,    -1,    21,    -1,    27,
      55,   143,    -1,    26,    55,     6,    -1,    -1,    15,    -1,
      34,    -1,    -1,     6,    -1,    -1,    55,   143,    -1,   145,
     108,    -1,   144,    -1,    10,    -1,   143,    45,   143,    -1,
     143,    46,   143,    -1,   143,    47,   143,    -1,   143,    48,
     143,    -1,   143,    49,   143,    -1,   143,    50,   143,    -1,
     143,    51,   143,    -1,   143,    52,   143,    -1,   143,    36,
     143,    -1,   143,    37,   143,    -1,   143,    38,   143,    -1,
     143,    55,   143,    -1,   143,    59,   143,    58,   143,    -1,
     143,    39,   143,    -1,   143,    56,   143,    -1,   143,    57,
     143,    -1,   143,    40,   143,    -1,   143,    41,   143,    -1,
      46,   143,    -1,    61,   143,    64,    -1,   145,    61,    64,
      -1,   145,    61,   146,    64,    -1,    47,   143,    -1,    50,
     143,    -1,    54,   143,    -1,    53,   143,    -1,     8,    -1,
       9,    -1,     6,    -1,     6,    44,     6,    -1,   143,    -1,
     146,    65,   143,    -1
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
     717,   721,   725,   733,   736,   745,   746,   747,   747,   750,
     766,   777,   782,   792,   794,   795,   798,   830,   833,   848,
     852,   858,   862,   868,   883,   899,   918,   924,   937,   944,
     953,  1026,  1030,  1039,  1042,  1049,  1052,  1064,  1065,  1066,
    1069,  1070,  1076,  1092,  1101,  1110,  1123,  1253,  1260,  1267,
    1274,  1281,  1289,  1289,  1296,  1296,  1306,  1310,  1356,  1360,
    1364,  1368,  1372,  1376,  1383,  1387,  1391,  1395,  1403,  1406,
    1410,  1414,  1418,  1424,  1436,  1439,  1446,  1450,  1467,  1483,
    1498,  1591,  1594,  1602,  1603,  1605,  1606,  1609,  1646,  1649,
    1655,  1659,  1665,  1669,  1673,  1678,  1687,  1690,  1694,  1701,
    1704,  1711,  1714,  1727,  1736,  1740,  1744,  1749,  1754,  1759,
    1764,  1769,  1774,  1779,  1784,  1789,  1794,  1799,  1804,  1809,
    1814,  1819,  1824,  1829,  1834,  1839,  1844,  1849,  1855,  1860,
    1865,  1870,  1877,  1881,  1887,  1891,  1899,  1903
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
  "LESSEQUAL_OP", "NONSTRICT_OD_OP", "EOFCODE", "SCOPE", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'&'", "'|'", "'^'", "'~'", "'!'", "'='", "'>'",
  "'<'", "':'", "'?'", "UMINUS", "'('", "';'", "'}'", "')'", "','", "'{'",
  "'['", "']'", "'@'", "'.'", "$accept", "startlist", "$@1", "handle_this",
  "not_care_code", "pack_directive", "pack_header", "object_list",
  "rest_object_list", "type_definition", "struct_definition",
  "struct_head", "struct_body", "struct_element", "struct_elname_list",
  "struct_elname_other", "typedef_definition", "seqclass_definition",
  "seqclass_header", "seqbase_spec", "seqbase_list", "seqbase_specifier",
  "class_prototype", "class_declaration", "class_head", "class_key",
  "base_spec", "base_list", "base_specifier", "access_specifier",
  "pure_class_decl", "member_list", "$@2", "member_declaration",
  "attribute_definition", "attribute_name_list", "attribute_name",
  "array_declarator", "decl_specifier", "storage_class_specifier",
  "type_specifier", "template_arguments", "template_arg",
  "pointer_specifier", "const_specifier", "ref_specifier",
  "function_definition", "pure_virtual_decl", "constructor_definition",
  "constructor_name", "destructor_definition", "destructor_name",
  "method_definition", "$@3", "$@4", "fct_specifier", "fct_spec",
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
     295,   296,   297,   298,   299,    43,    45,    42,    47,    37,
      38,   124,    94,   126,    33,    61,    62,    60,    58,    63,
     300,    40,    59,   125,    41,    44,   123,    91,    93,    64,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    72,    73,    72,    72,    72,    72,    72,
      72,    74,    75,    75,    75,    76,    77,    78,    79,    79,
      80,    80,    80,    81,    81,    82,    82,    83,    83,    84,
      85,    86,    86,    87,    87,    87,    87,    88,    88,    89,
      90,    90,    91,    91,    92,    92,    92,    92,    93,    94,
      95,    96,    97,    97,    98,    98,    99,    99,    99,    99,
     100,   100,   100,   101,   101,   102,   102,   103,   102,   104,
     104,   104,   104,   105,   106,   106,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   112,   112,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     118,   118,   119,   120,   121,   121,   122,   123,   123,   123,
     123,   123,   124,   123,   125,   123,   126,   126,   127,   127,
     127,   127,   127,   127,   128,   128,   128,   128,   129,   129,
     129,   129,   129,   130,   131,   131,   132,   132,   132,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   137,   137,
     138,   138,   139,   139,   139,   139,   140,   140,   140,   141,
     141,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   144,   144,   145,   145,   146,   146
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
       2,     1,     5,     2,     1,     3,     4,     0,     4,     2,
       1,     1,     1,     1,     1,     4,     1,     2,     1,     3,
       4,     0,     3,     0,     1,     0,     1,     1,     1,     2,
       0,     2,     5,     1,     4,     5,     1,     8,     9,     9,
      10,    11,     0,    14,     0,    15,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     0,     1,
       1,     2,     2,     1,     0,     4,     0,    12,    10,     8,
       6,     0,     2,     0,     1,     1,     3,     9,     0,     3,
       1,     3,     1,     1,     3,     3,     0,     1,     1,     0,
       1,     0,     2,     2,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     2,     3,     3,     4,     2,     2,
       2,     2,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    26,     0,    11,     0,    16,     0,
       0,     0,     0,     0,     0,    20,     0,    21,    22,    40,
       0,     4,     0,    63,    14,    12,    13,    51,    39,    25,
       0,    91,    26,    91,     7,     1,     2,    10,     8,     0,
       9,    27,    24,     0,    38,     0,     6,     0,    65,     0,
      48,    52,    91,    93,     0,    25,     0,    18,     0,    83,
      84,    26,    81,    82,    86,     0,     0,    91,     0,    80,
      44,    61,    62,    60,     0,    41,    42,     0,     0,     5,
       0,    83,   124,   125,   118,   119,   120,   121,   122,   123,
      71,     0,     0,    67,     0,    65,     0,    91,     0,    97,
       0,    98,   100,   128,   116,     0,    64,     0,    50,     0,
      94,    91,    77,     0,    77,     0,    17,    15,     0,    87,
      23,    27,    29,     0,    79,     0,     0,    45,     0,     0,
       0,   127,     0,   126,   106,     0,   152,   153,     0,     0,
       0,   150,     0,     0,    66,    70,   124,    73,    74,    95,
      91,    69,   148,     0,    99,   129,   130,     0,   117,     0,
      91,    56,     0,    53,    54,     0,    77,    92,     0,    33,
      77,    36,    19,    91,     0,    88,    28,    77,    46,    43,
      47,    37,     0,     0,     0,     0,     0,   128,     0,    65,
      49,    91,    96,     0,    95,     0,     0,   144,   145,   156,
     101,   132,   131,     0,   128,    95,    91,     0,     0,    57,
       0,    35,   194,   192,   193,   165,     0,     0,     0,     0,
       0,     0,     0,   164,    77,    34,    77,    85,     0,    31,
       0,     0,   104,   155,   154,     0,   151,    68,    75,    95,
      77,     0,     0,     0,   134,   148,   157,   158,     0,   128,
      91,     0,    95,    58,    55,    59,     0,   184,   188,   189,
     191,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,     0,   163,    95,    89,    91,    30,    72,   105,
     128,     0,    76,   148,   133,     0,   149,     0,   102,   146,
     156,     0,    95,     0,     0,   195,   185,   174,   175,   176,
     179,   182,   183,   166,   167,   168,   169,   170,   171,   172,
     173,   177,   180,   181,     0,    78,   186,   196,     0,    90,
      32,    91,    77,     0,   148,   136,    91,   128,     0,   148,
       0,     0,   187,     0,    95,    93,     0,     0,     0,    95,
      91,     0,     0,   148,   178,   197,     0,   107,    93,     0,
       0,   135,   159,    95,   148,    93,     0,   112,   109,   141,
       0,   160,    77,     0,     0,   108,    93,     0,     0,     0,
       0,   161,   114,    93,   110,   148,   142,   136,     0,     0,
     147,     0,   111,     0,   140,     0,     0,   162,   148,    93,
     136,     0,     0,   113,   139,     0,     0,    93,   136,     0,
     115,   138,     0,   136,   137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    47,    10,    11,    12,    13,    58,   116,    14,
      64,    16,    65,    66,   122,   287,    17,    18,    19,    45,
      75,    76,    20,    21,    22,    23,   108,   163,   164,    93,
      51,    94,   142,    95,    96,   147,   148,   292,    97,    68,
      69,   174,   175,   123,   111,   193,    98,   154,    99,   100,
     101,   135,   102,   377,   391,   103,   104,   105,   159,   241,
     298,   348,   379,   196,   197,   198,   199,   140,   141,   248,
     372,   390,   222,   223,   224,   328
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -376
static const yytype_int16 yypact[] =
{
     298,    16,    29,    52,    54,    58,  -376,   298,  -376,    67,
     298,   298,   298,    26,   298,  -376,     3,  -376,  -376,    73,
     298,  -376,    44,    21,  -376,  -376,  -376,  -376,  -376,  -376,
     115,    76,   124,    76,  -376,  -376,  -376,  -376,  -376,   137,
    -376,    23,  -376,   126,  -376,    85,  -376,   298,   211,   148,
    -376,   101,    76,   152,   171,     2,   179,   123,   127,   135,
    -376,   191,  -376,  -376,  -376,   136,   145,    76,    11,  -376,
    -376,  -376,  -376,  -376,   151,   133,  -376,    17,   201,  -376,
     150,    84,     1,   214,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,   226,   153,  -376,   174,   211,   176,     5,   177,  -376,
     181,  -376,   185,   257,  -376,    23,  -376,   141,  -376,   239,
    -376,    76,   182,   242,   182,   137,  -376,  -376,    11,     6,
    -376,    23,  -376,   252,  -376,   254,   126,  -376,   256,   188,
     259,  -376,   226,  -376,  -376,   207,  -376,  -376,   215,   218,
     206,   204,   219,   222,  -376,  -376,   270,  -376,   221,   237,
      76,  -376,    18,   281,  -376,   276,   282,   153,  -376,    23,
       5,  -376,   151,   241,  -376,    22,   182,  -376,   200,  -376,
     182,  -376,  -376,    76,   248,   243,  -376,   182,  -376,  -376,
    -376,  -376,   246,   250,   249,   301,   200,    98,   153,   211,
    -376,    76,  -376,   303,   237,   153,   253,  -376,   247,    19,
    -376,  -376,  -376,   255,    98,   237,    76,   310,   141,  -376,
     312,  -376,   277,  -376,  -376,  -376,   200,   200,   200,   200,
     200,   200,   299,  -376,    59,  -376,   182,  -376,    11,   260,
     258,   263,  -376,  -376,   489,    23,  -376,  -376,  -376,   237,
      61,   261,   325,   264,   265,   262,  -376,  -376,    23,    98,
      76,   325,   237,  -376,  -376,  -376,   335,  -376,   513,   519,
     519,   519,   383,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   182,   140,  -376,   237,  -376,    76,  -376,  -376,  -376,
      98,   336,  -376,    18,  -376,   291,  -376,   287,  -376,  -376,
      19,    23,   237,   296,   325,  -376,  -376,   284,   284,   284,
     284,   284,   284,   513,   513,   513,   513,   513,   519,   519,
     519,   519,   284,   284,   441,  -376,  -376,   489,   118,  -376,
    -376,    76,   182,   302,    18,   359,    76,    98,   325,    18,
     315,   200,  -376,   200,   237,   152,   313,    -7,   318,   237,
      76,   322,   320,    18,  -376,   489,   325,  -376,   152,   200,
     379,  -376,   380,   237,    18,   152,   331,  -376,  -376,   465,
     345,  -376,   182,   325,   332,  -376,   152,   346,   200,   349,
     200,   342,  -376,   152,  -376,    18,   489,   359,   323,   200,
    -376,   352,  -376,   350,  -376,   354,   200,   489,    18,   152,
     359,   353,   351,  -376,  -376,   363,   200,   152,   359,   412,
    -376,  -376,   364,   359,  -376
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -376,   245,  -376,  -376,   411,  -376,  -376,   321,  -376,  -376,
     283,  -376,   316,  -376,   155,  -376,  -376,  -376,  -376,  -376,
    -376,   317,  -376,  -376,  -376,  -376,  -376,  -376,   236,     7,
    -376,   -81,  -376,  -376,  -376,   274,  -376,  -109,   -35,  -376,
     -67,   217,  -376,   -31,  -187,  -168,  -376,  -376,  -376,  -376,
    -376,   314,  -376,  -376,  -376,  -376,   367,   -87,  -172,  -229,
    -376,  -375,  -376,  -228,   209,  -376,  -376,  -148,  -376,   156,
    -376,  -376,  -175,  -376,  -376,  -376
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -144
static const yytype_int16 yytable[] =
{
      54,   124,    56,   169,     1,   171,    67,   -25,   -91,   203,
     150,   234,   394,   295,   144,   235,   131,    59,    60,   146,
      83,   109,   303,   127,   113,   404,   242,    61,   209,    59,
      60,   128,   250,   411,   246,    27,   210,   251,   414,    61,
     236,   257,   258,   259,   260,   261,   262,   243,   359,    53,
      77,   173,    53,   247,   132,    62,    63,   211,    28,    24,
      29,   225,    30,   360,    31,   333,   149,    35,   229,    41,
     160,   291,   -25,   206,    32,   340,    49,   301,    25,    26,
     167,   125,  -143,    50,   304,   195,    67,    39,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   346,   327,   237,   351,
      48,   352,   155,   156,   165,   283,   329,   284,   331,   194,
     282,    52,  -133,    53,   204,   366,   168,   367,   168,   205,
      55,    43,    70,    77,   338,    44,   374,    71,    72,    73,
      74,   118,   226,    57,   382,  -103,   212,   161,   213,   214,
     215,    78,    71,    72,    73,   162,   106,   393,   357,   107,
     239,   173,    71,    72,    73,   350,   354,   110,   355,   207,
     402,   368,   325,   136,   137,   252,   356,   112,   375,   138,
     139,   362,   342,   343,   369,   114,   216,   217,   115,   384,
     218,   117,   118,   219,   220,   373,   392,   119,   126,   120,
     290,   221,   129,   386,   326,   388,   212,   121,   213,   214,
     215,   130,   403,   300,   397,   165,    80,    81,    60,   302,
     410,   401,    71,    72,    73,    82,    83,    61,   133,    84,
      85,   409,   134,    86,    87,    88,    89,   143,   145,   151,
     153,    90,   152,    62,    63,   166,   216,   217,   170,   168,
     218,   181,    34,   219,   220,    36,    37,    38,   177,    40,
     178,   221,   180,   381,    91,    46,   337,   182,   184,   188,
     185,   155,   156,   186,   187,    84,    85,   189,    92,    86,
      87,    88,    89,    15,   190,   131,   191,   192,    33,   200,
      15,   201,    79,    15,    15,    15,   202,    15,    -3,     1,
     344,     2,     3,    15,   227,   349,   208,   233,   228,   240,
     230,   231,   245,   232,     4,     5,   253,   244,   255,   363,
     288,   256,   293,   249,   157,   286,     6,   289,     7,   195,
      15,   294,   296,     8,   297,   263,   264,   265,   266,   267,
     268,   305,   332,   280,   269,   270,   271,   272,   273,   274,
     275,   276,   334,   335,   277,   278,   279,   339,   280,   263,
     264,   265,   266,   267,   268,   347,   345,   281,   269,   270,
     271,   272,   273,   274,   275,   276,   353,   358,   277,   278,
     279,   361,   280,   364,   365,   370,   371,   395,   396,   263,
     264,   265,   266,   267,   268,   376,   383,   389,   269,   270,
     271,   272,   273,   274,   275,   276,   380,   385,   277,   278,
     279,   387,   280,   398,   399,   407,   400,   405,   406,   263,
     264,   265,   266,   267,   268,   408,   413,    42,   269,   270,
     271,   272,   273,   274,   275,   276,   172,   176,   277,   278,
     279,   330,   280,   179,   254,   285,   183,   306,   263,   264,
     265,   266,   267,   268,   299,     0,   336,   269,   270,   271,
     272,   273,   274,   275,   276,   238,     0,   277,   278,   279,
     158,   280,     0,     0,     0,     0,   412,   263,   264,   265,
     266,   267,   268,     0,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,     0,     0,   277,   278,   279,   341,
     280,   263,   264,   265,   266,   267,   268,   378,     0,     0,
     269,   270,   271,   272,   273,   274,   275,   276,     0,     0,
     277,   278,   279,     0,   280,   263,   264,   265,   266,   267,
     268,     0,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,     0,     0,   277,   278,   279,     0,   280,   263,
     264,   265,   266,   267,   268,   263,   264,   265,   266,   267,
     268,     0,     0,   274,   275,   276,     0,     0,   277,   278,
     279,     0,   280,     0,     0,   278,   279,     0,   280
};

static const yytype_int16 yycheck[] =
{
      31,    68,    33,   112,     1,   114,    41,     1,     6,   157,
      97,   186,   387,   242,    95,   187,    15,     6,     7,    14,
      15,    52,   251,     6,    55,   400,   194,    16,     6,     6,
       7,    14,   204,   408,    15,     6,    14,   205,   413,    16,
     188,   216,   217,   218,   219,   220,   221,   195,    55,    47,
      43,   118,    47,    34,    53,    32,    33,   166,     6,    43,
       6,   170,     4,    70,     6,   293,    97,     0,   177,    66,
     105,   239,    66,   160,    16,   304,    55,   249,    62,    63,
     111,    74,    64,    62,   252,    67,   121,    61,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   334,   282,   189,   338,
      66,   339,    14,    15,   107,   224,   284,   226,   290,   150,
      61,     6,    61,    47,   159,   353,    67,   356,    67,   160,
       6,    58,     6,   126,   302,    62,   364,    11,    12,    13,
      14,    57,   173,     6,   373,    61,     6,     6,     8,     9,
      10,    66,    11,    12,    13,    14,     8,   385,   345,    58,
     191,   228,    11,    12,    13,   337,   341,    15,   343,   162,
     398,   358,   281,    20,    21,   206,   344,     6,   365,    26,
      27,   349,    64,    65,   359,     6,    46,    47,    65,   376,
      50,    64,    57,    53,    54,   363,   383,     6,    65,    63,
     235,    61,     1,   378,    64,   380,     6,    62,     8,     9,
      10,    61,   399,   248,   389,   208,     5,     6,     7,   250,
     407,   396,    11,    12,    13,    14,    15,    16,    14,    18,
      19,   406,     6,    22,    23,    24,    25,    63,    62,    62,
      55,    30,    61,    32,    33,     6,    46,    47,     6,    67,
      50,    63,     7,    53,    54,    10,    11,    12,     6,    14,
       6,    61,     6,   372,    53,    20,   301,     8,    61,    65,
      55,    14,    15,    55,    68,    18,    19,    58,    67,    22,
      23,    24,    25,     0,    62,    15,    65,    50,     5,     8,
       7,    15,    47,    10,    11,    12,    14,    14,     0,     1,
     331,     3,     4,    20,    56,   336,    65,     6,    65,     6,
      64,    61,    65,    64,    16,    17,     6,    64,     6,   350,
      62,    44,    61,    68,    67,    65,    28,    64,    30,    67,
      47,     6,    68,    35,    69,    36,    37,    38,    39,    40,
      41,     6,     6,    59,    45,    46,    47,    48,    49,    50,
      51,    52,    61,    66,    55,    56,    57,    61,    59,    36,
      37,    38,    39,    40,    41,     6,    64,    68,    45,    46,
      47,    48,    49,    50,    51,    52,    61,    64,    55,    56,
      57,    63,    59,    61,    64,     6,     6,    64,    65,    36,
      37,    38,    39,    40,    41,    64,    64,    55,    45,    46,
      47,    48,    49,    50,    51,    52,    61,    61,    55,    56,
      57,    62,    59,    61,    64,    64,    62,    64,    65,    36,
      37,    38,    39,    40,    41,    62,    62,    16,    45,    46,
      47,    48,    49,    50,    51,    52,   115,   121,    55,    56,
      57,   286,    59,   126,   208,   228,   132,    64,    36,    37,
      38,    39,    40,    41,   245,    -1,   300,    45,    46,    47,
      48,    49,    50,    51,    52,   191,    -1,    55,    56,    57,
     103,    59,    -1,    -1,    -1,    -1,    64,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    56,    57,    -1,    59,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    55,    56,    57,    -1,    59,    36,
      37,    38,    39,    40,    41,    36,    37,    38,    39,    40,
      41,    -1,    -1,    50,    51,    52,    -1,    -1,    55,    56,
      57,    -1,    59,    -1,    -1,    56,    57,    -1,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    16,    17,    28,    30,    35,    72,
      74,    75,    76,    77,    80,    81,    82,    87,    88,    89,
      93,    94,    95,    96,    43,    62,    63,     6,     6,     6,
       4,     6,    16,    81,    72,     0,    72,    72,    72,    61,
      72,    66,    75,    58,    62,    90,    72,    73,    66,    55,
      62,   101,     6,    47,   114,     6,   114,     6,    78,     6,
       7,    16,    32,    33,    81,    83,    84,   109,   110,   111,
       6,    11,    12,    13,    14,    91,    92,   100,    66,    72,
       5,     6,    14,    15,    18,    19,    22,    23,    24,    25,
      30,    53,    67,   100,   102,   104,   105,   109,   117,   119,
     120,   121,   123,   126,   127,   128,     8,    58,    97,   114,
      15,   115,     6,   114,     6,    65,    79,    64,    57,     6,
      63,    62,    85,   114,   111,   100,    65,     6,    14,     1,
      61,    15,    53,    14,     6,   122,    20,    21,    26,    27,
     138,   139,   103,    63,   102,    62,    14,   106,   107,   114,
     128,    62,    61,    55,   118,    14,    15,    67,   127,   129,
     109,     6,    14,    98,    99,   100,     6,   114,    67,   108,
       6,   108,    78,   111,   112,   113,    83,     6,     6,    92,
       6,    63,     8,   122,    61,    55,    55,    68,    65,    58,
      62,    65,    50,   116,   114,    67,   134,   135,   136,   137,
       8,    15,    14,   138,   109,   114,   128,   100,    65,     6,
      14,   108,     6,     8,     9,    10,    46,    47,    50,    53,
      54,    61,   143,   144,   145,   108,   114,    56,    65,   108,
      64,    61,    64,     6,   143,   129,   138,   102,   106,   114,
       6,   130,   116,   138,    64,    65,    15,    34,   140,    68,
     129,   116,   114,     6,    99,     6,    44,   143,   143,   143,
     143,   143,   143,    36,    37,    38,    39,    40,    41,    45,
      46,    47,    48,    49,    50,    51,    52,    55,    56,    57,
      59,    68,    61,   108,   108,   112,    65,    86,    62,    64,
     109,   116,   108,    61,     6,   130,    68,    69,   131,   135,
     109,   129,   114,   130,   116,     6,    64,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   108,    64,   143,   146,   116,
      85,   129,     6,   134,    61,    66,   140,   109,   116,    61,
     130,    58,    64,    65,   114,    64,   134,     6,   132,   114,
     129,   130,   134,    61,   143,   143,   116,   115,    64,    55,
      70,    63,   116,   114,    61,    64,   134,   130,   115,   143,
       6,     6,   141,   116,   134,   115,    64,   124,    42,   133,
      61,   108,   130,    64,   115,    61,   143,    62,   143,    55,
     142,   125,   115,   134,   132,    64,    65,   143,    61,    64,
      62,   143,   134,   115,   132,    64,    65,    64,    62,   143,
     115,   132,    64,    62,   132
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
        case 3:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    { insideClass=false; othercodes.SetSize(0); startPos=-1;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {
  CleanStack();
}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    {
	printf("handle at Bison\n");
	othercodes.InsertAt(-1,"\n",strlen("\n"));
}
    break;

  case 12:

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

  case 13:

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
}
    break;

  case 14:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    {
  currentPack->SetEndLine(linenumber-1);

  currentPack=NULL;
  othercodes.SetSize(0);
  startPos=-1;
  
}
    break;

  case 16:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 227 "parser.y"
    {
  if (currentPack!=NULL)
    {
      currentPack->AddObject(GetToken((yyvsp[(1) - (2)])));
    }
}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 236 "parser.y"
    {
}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    {
}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    {
    CleanStack();
}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 259 "parser.y"
    {
  currentstruct=Pop();
  if (currentstruct!=NULL) currentstruct->SetTypeClass(false);
  (yyval)=(yyvsp[(1) - (4)]);
}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 265 "parser.y"
    {
  currentstruct=Pop();
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 25:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {
  TypeClassStruct *t=new TypeClassStruct(NULL,false);
  thisCodeFile->AddDataType(t);
  Push(t);
  (yyval)=-1;
}
    break;

  case 30:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 441 "parser.y"
    {
  if (seqclass!=NULL) seqclass->SetTypeClass(true);
}
    break;

  case 39:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 602 "parser.y"
    {
  currentClass->SetEndLine(linenumber);
  currentClass=NULL;
  insideClass=false;
}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 610 "parser.y"
    {
  accessmodifier=PUBLIC;
  if ((yyvsp[(2) - (3)])) currentClass->SetPureVirtual(true);

  thisCodeFile->AddCodeData(currentClass);
}
    break;

  case 51:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 718 "parser.y"
    {
	(yyval)=PRIVATE;
}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 722 "parser.y"
    {
	(yyval)=PUBLIC;
}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 726 "parser.y"
    {
	(yyval)=PROTECTED;
}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 733 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 737 "parser.y"
    {
  (yyval)= (paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])), "0")) ? 1 : 0;
}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 747 "parser.y"
    { accessmodifier=(AccessType)(yyvsp[(1) - (1)]); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 751 "parser.y"
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

  case 70:

/* Line 1455 of yacc.c  */
#line 767 "parser.y"
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

  case 71:

/* Line 1455 of yacc.c  */
#line 778 "parser.y"
    {
  //  Directive *t=new Directive(currentClass, GetToken($1));
  //  currentClass->AddMember(t);
}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 783 "parser.y"
    {
  currentClass->SetClassID(GetToken((yyvsp[(3) - (5)])));
}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 799 "parser.y"
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

  case 77:

/* Line 1455 of yacc.c  */
#line 830 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 834 "parser.y"
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

  case 79:

/* Line 1455 of yacc.c  */
#line 849 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 853 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 859 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 869 "parser.y"
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

  case 84:

/* Line 1455 of yacc.c  */
#line 884 "parser.y"
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

  case 85:

/* Line 1455 of yacc.c  */
#line 900 "parser.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 919 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 925 "parser.y"
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

  case 88:

/* Line 1455 of yacc.c  */
#line 938 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 945 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 954 "parser.y"
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

  case 91:

/* Line 1455 of yacc.c  */
#line 1026 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1031 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1039 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1043 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1049 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1053 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1071 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1077 "parser.y"
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

  case 103:

/* Line 1455 of yacc.c  */
#line 1093 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1102 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1111 "parser.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 1124 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1254 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1261 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1268 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1275 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1282 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1289 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1290 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1296 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1297 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1307 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1311 "parser.y"
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

  case 118:

/* Line 1455 of yacc.c  */
#line 1357 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1361 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1365 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1369 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1373 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1377 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1384 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1388 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1392 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1396 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1403 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1407 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1411 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1415 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1419 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1425 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1436 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1440 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1446 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1451 "parser.y"
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

  case 138:

/* Line 1455 of yacc.c  */
#line 1468 "parser.y"
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

  case 139:

/* Line 1455 of yacc.c  */
#line 1484 "parser.y"
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

  case 140:

/* Line 1455 of yacc.c  */
#line 1499 "parser.y"
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

  case 141:

/* Line 1455 of yacc.c  */
#line 1591 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1595 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1610 "parser.y"
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

  case 148:

/* Line 1455 of yacc.c  */
#line 1646 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1650 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1656 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1660 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1666 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1670 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1674 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1679 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1687 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1691 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1695 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1701 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1705 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1711 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1715 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1728 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1737 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1741 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1745 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1750 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1755 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1760 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1765 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1770 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1775 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1780 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1785 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1790 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1795 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1800 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1805 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1810 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1815 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1820 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1825 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1830 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1835 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1840 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1845 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1850 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1856 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1861 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1866 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1871 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1878 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1882 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1888 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1892 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1900 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1904 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;



/* Line 1455 of yacc.c  */
#line 4083 "parser.tab.c"
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
#line 1912 "parser.y"


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


