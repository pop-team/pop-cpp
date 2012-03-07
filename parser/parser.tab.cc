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
#define YYLAST   643

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNRULES -- Number of states.  */
#define YYNSTATES  433

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
     246,   250,   253,   255,   259,   264,   265,   270,   273,   275,
     277,   279,   281,   283,   288,   290,   293,   295,   299,   304,
     305,   309,   310,   312,   313,   315,   317,   319,   322,   323,
     326,   332,   334,   339,   345,   347,   356,   366,   376,   387,
     399,   400,   415,   416,   432,   434,   437,   439,   441,   443,
     445,   447,   449,   451,   453,   456,   459,   460,   462,   464,
     467,   470,   472,   473,   478,   479,   492,   503,   512,   519,
     520,   523,   524,   526,   528,   532,   542,   543,   547,   549,
     553,   555,   557,   561,   565,   566,   568,   570,   571,   573,
     574,   577,   580,   582,   584,   588,   592,   596,   600,   604,
     608,   612,   616,   620,   624,   628,   632,   638,   642,   646,
     650,   654,   658,   661,   665,   669,   674,   677,   680,   683,
     686,   688,   690,   692,   696,   698
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
      -1,    -1,    87,    65,    86,    -1,   116,    88,    -1,   121,
       6,   115,    89,    -1,    -1,    68,    88,    -1,    17,     6,
     121,     6,   115,    -1,    17,    16,     6,   121,     6,   115,
      -1,    17,     4,     6,   121,     6,   115,    -1,    17,    84,
     121,     6,   115,    -1,    92,    93,    69,     1,    66,    -1,
      92,    65,    -1,     4,     6,    -1,    -1,    61,    94,    -1,
      95,    -1,    94,    68,    95,    -1,     6,    -1,   103,     6,
      -1,    14,   103,     6,    -1,   103,    14,     6,    -1,    99,
      65,    -1,    98,    69,   105,    66,    65,    -1,    99,   104,
     100,    -1,     3,     6,    -1,    -1,    61,   101,    -1,   102,
      -1,   101,    68,   102,    -1,     6,    -1,   103,     6,    -1,
      14,   103,     6,    -1,   103,    14,     6,    -1,    13,    -1,
      11,    -1,    12,    -1,    -1,    58,     8,    -1,    -1,   107,
     105,    -1,    -1,   103,   106,    61,   105,    -1,   108,    65,
      -1,   111,    65,    -1,   124,    65,    -1,   112,    65,    -1,
      30,    -1,     5,    64,     8,    67,    65,    -1,    45,     6,
      69,   109,    66,    -1,   110,    -1,   110,    68,   109,    -1,
       6,    -1,     6,    58,     8,    -1,    47,    69,    66,    -1,
     116,   113,    -1,   114,    -1,   114,    68,   113,    -1,   121,
     123,     6,   115,    -1,    -1,    70,   150,    71,   115,    -1,
     117,   118,    -1,   118,    -1,    32,    -1,    33,    -1,     6,
      -1,     7,    -1,     6,    60,   119,    59,    -1,    84,    -1,
      16,     6,    -1,   120,    -1,   120,    68,   119,    -1,   118,
     121,   115,   123,    -1,    -1,    50,   122,   121,    -1,    -1,
      15,    -1,    -1,    53,    -1,   126,    -1,   128,    -1,   130,
     125,    -1,    -1,    58,     8,    -1,   127,    64,   141,    67,
     138,    -1,     6,    -1,    56,   129,    64,    67,    -1,    14,
      56,   129,    64,    67,    -1,     6,    -1,   116,   121,   123,
     137,    64,   141,    67,   122,    -1,   135,   116,   121,   123,
     137,    64,   141,    67,   122,    -1,   116,   135,   121,   123,
     137,    64,   141,    67,   122,    -1,   135,   116,   135,   121,
     123,   137,    64,   141,    67,   122,    -1,   133,   136,   116,
     136,   121,   123,   137,    64,   141,    67,   122,    -1,    -1,
      70,   145,    71,   136,   116,   136,   121,   123,   137,   131,
      64,   141,    67,   122,    -1,    -1,   133,    70,   145,    71,
     136,   116,   136,   121,   123,   137,   132,    64,   141,    67,
     122,    -1,   134,    -1,   133,   134,    -1,    18,    -1,    19,
      -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,    14,
      -1,    15,    -1,    15,    14,    -1,    14,    15,    -1,    -1,
      14,    -1,    15,    -1,    15,    14,    -1,    14,    15,    -1,
       6,    -1,    -1,    72,    69,   139,    66,    -1,    -1,     6,
      73,     6,    64,   150,    68,   150,    68,   150,    67,    65,
     139,    -1,     6,    73,     6,    64,   150,    68,   150,    67,
      65,   139,    -1,     6,    73,     6,    64,   150,    67,    65,
     139,    -1,     6,    58,   150,   140,    65,   139,    -1,    -1,
      42,   150,    -1,    -1,   142,    -1,   143,    -1,   143,    68,
     142,    -1,   144,   147,   116,   147,   121,   123,   148,   115,
     149,    -1,    -1,    70,   145,    71,    -1,   146,    -1,   146,
      68,   145,    -1,    20,    -1,    21,    -1,    27,    58,   150,
      -1,    26,    58,     6,    -1,    -1,    15,    -1,    34,    -1,
      -1,     6,    -1,    -1,    58,   150,    -1,   152,   115,    -1,
     151,    -1,    10,    -1,   150,    48,   150,    -1,   150,    49,
     150,    -1,   150,    50,   150,    -1,   150,    51,   150,    -1,
     150,    52,   150,    -1,   150,    53,   150,    -1,   150,    54,
     150,    -1,   150,    55,   150,    -1,   150,    36,   150,    -1,
     150,    37,   150,    -1,   150,    38,   150,    -1,   150,    58,
     150,    -1,   150,    62,   150,    61,   150,    -1,   150,    39,
     150,    -1,   150,    59,   150,    -1,   150,    60,   150,    -1,
     150,    40,   150,    -1,   150,    41,   150,    -1,    49,   150,
      -1,    64,   150,    67,    -1,   152,    64,    67,    -1,   152,
      64,   153,    67,    -1,    50,   150,    -1,    53,   150,    -1,
      57,   150,    -1,    56,   150,    -1,     8,    -1,     9,    -1,
       6,    -1,     6,    44,     6,    -1,   150,    -1,   153,    68,
     150,    -1
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
     832,   838,   840,   841,   844,   876,   879,   894,   898,   904,
     908,   914,   929,   945,   964,   970,   983,   990,   999,  1072,
    1076,  1085,  1088,  1095,  1098,  1110,  1111,  1112,  1115,  1116,
    1122,  1138,  1147,  1156,  1169,  1299,  1306,  1313,  1320,  1327,
    1335,  1335,  1342,  1342,  1352,  1356,  1402,  1406,  1410,  1414,
    1418,  1422,  1429,  1433,  1437,  1441,  1449,  1452,  1456,  1460,
    1464,  1470,  1482,  1485,  1492,  1496,  1513,  1529,  1544,  1637,
    1640,  1648,  1649,  1651,  1652,  1655,  1692,  1695,  1701,  1705,
    1711,  1715,  1719,  1724,  1733,  1736,  1740,  1747,  1750,  1757,
    1760,  1773,  1782,  1786,  1790,  1795,  1800,  1805,  1810,  1815,
    1820,  1825,  1830,  1835,  1840,  1845,  1850,  1855,  1860,  1865,
    1870,  1875,  1880,  1885,  1890,  1895,  1901,  1906,  1911,  1916,
    1923,  1927,  1933,  1937,  1945,  1949
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
  "structure_declaration", "attribute_definition", "attribute_name_list",
  "attribute_name", "array_declarator", "decl_specifier",
  "storage_class_specifier", "type_specifier", "template_arguments",
  "template_arg", "pointer_specifier", "const_specifier", "ref_specifier",
  "function_definition", "pure_virtual_decl", "constructor_definition",
  "constructor_name", "destructor_definition", "destructor_name",
  "method_definition", "@3", "@4", "fct_specifier", "fct_spec",
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
     111,   112,   113,   113,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   118,   118,   118,   119,   119,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     126,   127,   128,   128,   129,   130,   130,   130,   130,   130,
     131,   130,   132,   130,   133,   133,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
     136,   137,   138,   138,   139,   139,   139,   139,   139,   140,
     140,   141,   141,   142,   142,   143,   144,   144,   145,   145,
     146,   146,   146,   146,   147,   147,   147,   148,   148,   149,
     149,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     151,   151,   152,   152,   153,   153
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
       3,     2,     1,     3,     4,     0,     4,     2,     1,     1,
       1,     1,     1,     4,     1,     2,     1,     3,     4,     0,
       3,     0,     1,     0,     1,     1,     1,     2,     0,     2,
       5,     1,     4,     5,     1,     8,     9,     9,    10,    11,
       0,    14,     0,    15,     1,     2,     1,     1,     1,     1,
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
       0,     0,     0,     0,    26,     0,    11,     0,    16,     0,
       0,     0,     0,     0,     0,    20,     0,    21,    22,    40,
       0,     4,     0,    63,    14,    12,    13,    51,    39,    25,
       0,    99,    26,    99,     7,     1,     2,    10,     8,     0,
       9,    27,    24,     0,    38,     0,     6,     0,    65,     0,
      48,    52,    99,   101,     0,    25,     0,    18,     0,    91,
      92,    26,    89,    90,    94,     0,     0,    99,     0,    88,
      44,    61,    62,    60,     0,    41,    42,     0,     0,     5,
       0,    91,   132,   133,   126,   127,   128,   129,   130,   131,
      73,     0,     0,     0,     0,    67,     0,    65,     0,     0,
       0,    99,     0,   105,     0,   106,   108,   136,   124,     0,
      64,     0,    50,     0,   102,    99,    85,     0,    85,     0,
      17,    15,     0,    95,    23,    27,    29,     0,    87,     0,
       0,    45,     0,     0,     0,   135,     0,   134,     0,     0,
     114,     0,   160,   161,     0,     0,     0,   158,     0,     0,
      66,    69,    70,    72,   132,    81,    82,   103,    99,    71,
     156,     0,   107,   137,   138,     0,   125,     0,    99,    56,
       0,    53,    54,     0,    85,   100,     0,    33,    85,    36,
      19,    99,     0,    96,    28,    85,    46,    43,    47,    37,
       0,     0,     0,    80,     0,     0,     0,   136,     0,    65,
      49,    99,   104,     0,   103,     0,     0,   152,   153,   164,
     109,   140,   139,     0,   136,   103,    99,     0,     0,    57,
       0,    35,   202,   200,   201,   173,     0,     0,     0,     0,
       0,     0,     0,   172,    85,    34,    85,    93,     0,    31,
       0,     0,    78,     0,    76,   112,   163,   162,     0,   159,
      68,    83,   103,    85,     0,     0,     0,   142,   156,   165,
     166,     0,   136,    99,     0,   103,    58,    55,    59,     0,
     192,   196,   197,   199,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,     0,   171,   103,    97,    99,
      30,    74,   113,     0,    75,     0,   136,     0,    84,   156,
     141,     0,   157,     0,   110,   154,   164,     0,   103,     0,
       0,   203,   193,   182,   183,   184,   187,   190,   191,   174,
     175,   176,   177,   178,   179,   180,   181,   185,   188,   189,
       0,    86,   194,   204,     0,    98,    32,    79,    77,    99,
      85,     0,   156,   144,    99,   136,     0,   156,     0,     0,
     195,     0,   103,   101,     0,     0,     0,   103,    99,     0,
       0,   156,   186,   205,     0,   115,   101,     0,     0,   143,
     167,   103,   156,   101,     0,   120,   117,   149,     0,   168,
      85,     0,     0,   116,   101,     0,     0,     0,     0,   169,
     122,   101,   118,   156,   150,   144,     0,     0,   155,     0,
     119,     0,   148,     0,     0,   170,   156,   101,   144,     0,
       0,   121,   147,     0,     0,   101,   144,     0,   123,   146,
       0,   144,   145
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    47,    10,    11,    12,    13,    58,   120,    14,
      64,    16,    65,    66,   126,   300,    17,    18,    19,    45,
      75,    76,    20,    21,    22,    23,   112,   171,   172,    95,
      51,    96,   148,    97,    98,   243,   244,    99,   100,   155,
     156,   308,   101,    68,    69,   182,   183,   127,   115,   203,
     102,   162,   103,   104,   105,   141,   106,   395,   409,   107,
     108,   109,   167,   254,   314,   366,   397,   206,   207,   208,
     209,   146,   147,   261,   390,   408,   232,   233,   234,   344
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -296
static const yytype_int16 yypact[] =
{
     369,    74,    30,    40,    45,   137,  -296,   369,  -296,    72,
     369,   369,   369,    10,   369,  -296,    11,  -296,  -296,    18,
     369,  -296,     8,   -35,  -296,  -296,  -296,  -296,  -296,  -296,
      80,    57,   110,    57,  -296,  -296,  -296,  -296,  -296,   115,
    -296,    31,  -296,   243,  -296,    61,  -296,   369,   228,   118,
    -296,    81,    57,   120,   127,     4,   138,    87,    93,   104,
    -296,   165,  -296,  -296,  -296,   111,   124,    57,   192,  -296,
    -296,  -296,  -296,  -296,   135,   112,  -296,    19,   193,  -296,
     132,    55,     0,   186,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,   198,   145,   200,   195,  -296,   141,   228,   147,   152,
     154,     3,   159,  -296,   161,  -296,   168,   143,  -296,    31,
    -296,   258,  -296,   223,  -296,    57,   160,   225,   160,   115,
    -296,  -296,   192,    13,  -296,    31,  -296,   230,  -296,   232,
     243,  -296,   239,   182,   251,  -296,   200,  -296,   199,   196,
    -296,   210,  -296,  -296,   218,   219,   209,   213,   221,   224,
    -296,  -296,  -296,  -296,   273,  -296,   222,   238,    57,  -296,
     -41,   284,  -296,   278,   280,   195,  -296,    31,     3,  -296,
     135,   227,  -296,    51,   160,  -296,   277,  -296,   160,  -296,
    -296,    57,   237,   229,  -296,   160,  -296,  -296,  -296,  -296,
     233,   235,   295,  -296,   236,   296,   277,   188,   195,   228,
    -296,    57,  -296,   298,   238,   195,   241,  -296,   244,     1,
    -296,  -296,  -296,   234,   188,   238,    57,   303,   258,  -296,
     305,  -296,   271,  -296,  -296,  -296,   277,   277,   277,   277,
     277,   277,   306,  -296,    -9,  -296,   160,  -296,   192,   248,
     252,   253,   261,   256,   260,  -296,  -296,   554,    31,  -296,
    -296,  -296,   238,    48,   265,   319,   264,   259,   262,  -296,
    -296,    31,   188,    57,   319,   238,  -296,  -296,  -296,   330,
    -296,   581,   343,   343,   343,   436,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   160,   257,  -296,   238,  -296,    57,
    -296,  -296,  -296,   331,  -296,   295,   188,   332,  -296,   -41,
    -296,   276,  -296,   279,  -296,  -296,     1,    31,   238,   285,
     319,  -296,  -296,   288,   288,   288,   288,   288,   288,   581,
     581,   581,   581,   581,   343,   343,   343,   343,   288,   288,
     500,  -296,  -296,   554,    84,  -296,  -296,  -296,  -296,    57,
     160,   286,   -41,   345,    57,   188,   319,   -41,   299,   277,
    -296,   277,   238,   120,   300,   -39,   308,   238,    57,   307,
     309,   -41,  -296,   554,   319,  -296,   120,   277,   346,  -296,
     356,   238,   -41,   120,   311,  -296,  -296,   527,   323,  -296,
     160,   319,   321,  -296,   120,   325,   277,   310,   277,   333,
    -296,   120,  -296,   -41,   554,   345,   370,   277,  -296,   326,
    -296,   327,  -296,   328,   277,   554,   -41,   120,   345,   403,
     329,  -296,  -296,   335,   277,   120,   345,   468,  -296,  -296,
     336,   345,  -296
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -296,    38,  -296,  -296,   376,  -296,  -296,   293,  -296,  -296,
     181,  -296,   270,  -296,    99,  -296,  -296,  -296,  -296,  -296,
    -296,   283,  -296,  -296,  -296,  -296,  -296,  -296,   197,   -42,
    -296,   -90,  -296,  -296,  -296,   109,  -296,  -296,  -296,   215,
    -296,  -112,   -38,  -296,   -63,   179,  -296,   -31,  -238,  -184,
    -296,  -296,  -296,  -296,  -296,   290,  -296,  -296,  -296,  -296,
     320,   -93,  -186,  -242,  -296,  -295,  -296,  -198,   173,  -296,
    -296,  -138,  -296,   117,  -296,  -296,  -187,  -296,  -296,  -296
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -152
static const yytype_int16 yytable[] =
{
      54,    77,    56,    67,   177,   128,   179,   150,   158,   247,
     -99,   248,     1,   311,   -25,   135,   259,   154,    83,   377,
     255,   113,   319,    49,   117,   131,  -151,   213,   263,   205,
      50,   264,   129,   132,   378,   260,    27,    59,    60,   270,
     271,   272,   273,   274,   275,    34,    28,    61,    36,    37,
      38,    29,    40,    53,    53,   295,   136,   219,    46,   181,
     249,   176,   221,    62,    63,   220,   235,   256,   307,   173,
     157,   168,    35,   239,    39,   216,   317,    48,   358,    43,
      41,   320,   -25,    44,   175,    79,    52,    67,    77,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,    53,   343,   250,
     412,   351,  -141,   345,   369,   122,    55,    24,   176,  -111,
     349,    57,   296,   422,   297,   375,   110,   204,   217,   214,
      78,   429,   385,   116,   356,   114,   432,   215,   386,    25,
      26,    30,   111,    31,   118,   393,    71,    72,    73,   400,
     236,   360,   361,    32,   364,   119,   402,   163,   164,   370,
     121,    84,    85,   410,   122,    86,    87,    88,    89,   368,
     252,   123,   372,   384,   373,   181,   173,   124,   374,   421,
     130,    15,   341,   380,   392,   265,    33,   428,    15,   125,
     387,    15,    15,    15,   133,    15,   134,   391,    59,    60,
     137,    15,   163,   164,   138,   411,   140,   149,    61,   404,
     306,   406,   151,   165,   139,   142,   143,   152,   420,   153,
     415,   144,   145,   316,   159,   160,   161,   419,    15,   174,
     176,   178,   318,    80,    81,    60,   185,   427,   186,    71,
      72,    73,    82,    83,    61,   188,    84,    85,   189,    70,
      86,    87,    88,    89,    71,    72,    73,    74,    90,   190,
      62,    63,   193,   222,   169,   223,   224,   225,   192,    71,
      72,    73,   170,    91,   194,    92,   195,   196,   399,   355,
     197,   198,   199,   222,    93,   223,   224,   225,   135,   200,
     201,   202,   210,   211,   212,   218,   237,   238,    94,   241,
     240,   242,   246,   245,   253,   262,   226,   227,   257,   266,
     228,   268,   258,   229,   230,   269,   299,   301,   362,   303,
     302,   231,   304,   367,   342,   310,   226,   227,   305,   309,
     228,   313,   205,   229,   230,   312,   321,   381,   350,   347,
     352,   231,   276,   277,   278,   279,   280,   281,   353,   357,
     293,   365,   388,   363,   282,   283,   284,   285,   286,   287,
     288,   289,   389,   371,   290,   291,   292,   376,   293,    -3,
       1,   382,     2,     3,   379,   405,   383,   294,   394,   276,
     277,   278,   279,   280,   281,     4,     5,   398,   401,   403,
     416,   407,    42,   418,   417,   184,   425,     6,   346,     7,
     426,   431,   291,   292,     8,   293,   276,   277,   278,   279,
     280,   281,   180,   187,   348,   267,   251,   298,   282,   283,
     284,   285,   286,   287,   288,   289,   191,   166,   290,   291,
     292,   315,   293,   354,     0,     0,     0,   413,   414,   276,
     277,   278,   279,   280,   281,     0,     0,     0,     0,     0,
       0,   282,   283,   284,   285,   286,   287,   288,   289,     0,
       0,   290,   291,   292,     0,   293,     0,     0,     0,     0,
     423,   424,   276,   277,   278,   279,   280,   281,     0,     0,
       0,     0,     0,     0,   282,   283,   284,   285,   286,   287,
     288,   289,     0,     0,   290,   291,   292,     0,   293,     0,
       0,     0,     0,   322,   276,   277,   278,   279,   280,   281,
       0,     0,     0,     0,     0,     0,   282,   283,   284,   285,
     286,   287,   288,   289,     0,     0,   290,   291,   292,     0,
     293,     0,     0,     0,     0,   430,   276,   277,   278,   279,
     280,   281,     0,     0,     0,     0,     0,     0,   282,   283,
     284,   285,   286,   287,   288,   289,     0,     0,   290,   291,
     292,   359,   293,   276,   277,   278,   279,   280,   281,   396,
       0,     0,     0,     0,     0,   282,   283,   284,   285,   286,
     287,   288,   289,     0,     0,   290,   291,   292,     0,   293,
     276,   277,   278,   279,   280,   281,     0,     0,     0,     0,
       0,     0,   282,   283,   284,   285,   286,   287,   288,   289,
       0,     0,   290,   291,   292,     0,   293,   276,   277,   278,
     279,   280,   281,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   287,   288,   289,     0,     0,   290,
     291,   292,     0,   293
};

static const yytype_int16 yycheck[] =
{
      31,    43,    33,    41,   116,    68,   118,    97,   101,   196,
       6,   197,     1,   255,     1,    15,    15,    14,    15,    58,
     204,    52,   264,    58,    55,     6,    67,   165,   214,    70,
      65,   215,    74,    14,    73,    34,     6,     6,     7,   226,
     227,   228,   229,   230,   231,     7,     6,    16,    10,    11,
      12,     6,    14,    50,    50,    64,    56,     6,    20,   122,
     198,    70,   174,    32,    33,    14,   178,   205,   252,   111,
     101,   109,     0,   185,    64,   168,   262,    69,   320,    61,
      69,   265,    69,    65,   115,    47,     6,   125,   130,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,    50,   295,   199,
     405,   309,    64,   297,   356,    60,     6,    43,    70,    64,
     306,     6,   234,   418,   236,   363,     8,   158,   170,   167,
      69,   426,   374,     6,   318,    15,   431,   168,   376,    65,
      66,     4,    61,     6,     6,   383,    11,    12,    13,   391,
     181,    67,    68,    16,   352,    68,   394,    14,    15,   357,
      67,    18,    19,   401,    60,    22,    23,    24,    25,   355,
     201,     6,   359,   371,   361,   238,   218,    66,   362,   417,
      68,     0,   294,   367,   382,   216,     5,   425,     7,    65,
     377,    10,    11,    12,     1,    14,    64,   381,     6,     7,
      14,    20,    14,    15,     6,   403,     6,    66,    16,   396,
     248,   398,    65,    70,    69,    20,    21,    65,   416,    65,
     407,    26,    27,   261,    65,    64,    58,   414,    47,     6,
      70,     6,   263,     5,     6,     7,     6,   424,     6,    11,
      12,    13,    14,    15,    16,     6,    18,    19,    66,     6,
      22,    23,    24,    25,    11,    12,    13,    14,    30,     8,
      32,    33,    66,     6,     6,     8,     9,    10,    69,    11,
      12,    13,    14,    45,    64,    47,    58,    58,   390,   317,
      71,    68,    61,     6,    56,     8,     9,    10,    15,    65,
      68,    53,     8,    15,    14,    68,    59,    68,    70,    64,
      67,     6,     6,    67,     6,    71,    49,    50,    67,     6,
      53,     6,    68,    56,    57,    44,    68,    65,   349,    58,
      67,    64,    66,   354,    67,     6,    49,    50,    68,    64,
      53,    72,    70,    56,    57,    71,     6,   368,     6,     8,
      64,    64,    36,    37,    38,    39,    40,    41,    69,    64,
      62,     6,     6,    67,    48,    49,    50,    51,    52,    53,
      54,    55,     6,    64,    58,    59,    60,    67,    62,     0,
       1,    64,     3,     4,    66,    65,    67,    71,    67,    36,
      37,    38,    39,    40,    41,    16,    17,    64,    67,    64,
      64,    58,    16,    65,    67,   125,    67,    28,   299,    30,
      65,    65,    59,    60,    35,    62,    36,    37,    38,    39,
      40,    41,   119,   130,   305,   218,   201,   238,    48,    49,
      50,    51,    52,    53,    54,    55,   136,   107,    58,    59,
      60,   258,    62,   316,    -1,    -1,    -1,    67,    68,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,
      67,    68,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,    67,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    58,    59,    60,    -1,
      62,    -1,    -1,    -1,    -1,    67,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    58,    59,
      60,    61,    62,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    58,    59,    60,    -1,    62,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    58,    59,    60,    -1,    62,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,    58,
      59,    60,    -1,    62
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
      65,   104,     6,    50,   121,     6,   121,     6,    81,     6,
       7,    16,    32,    33,    84,    86,    87,   116,   117,   118,
       6,    11,    12,    13,    14,    94,    95,   103,    69,    75,
       5,     6,    14,    15,    18,    19,    22,    23,    24,    25,
      30,    45,    47,    56,    70,   103,   105,   107,   108,   111,
     112,   116,   124,   126,   127,   128,   130,   133,   134,   135,
       8,    61,   100,   121,    15,   122,     6,   121,     6,    68,
      82,    67,    60,     6,    66,    65,    88,   121,   118,   103,
      68,     6,    14,     1,    64,    15,    56,    14,     6,    69,
       6,   129,    20,    21,    26,    27,   145,   146,   106,    66,
     105,    65,    65,    65,    14,   113,   114,   121,   135,    65,
      64,    58,   125,    14,    15,    70,   134,   136,   116,     6,
      14,   101,   102,   103,     6,   121,    70,   115,     6,   115,
      81,   118,   119,   120,    86,     6,     6,    95,     6,    66,
       8,   129,    69,    66,    64,    58,    58,    71,    68,    61,
      65,    68,    53,   123,   121,    70,   141,   142,   143,   144,
       8,    15,    14,   145,   116,   121,   135,   103,    68,     6,
      14,   115,     6,     8,     9,    10,    49,    50,    53,    56,
      57,    64,   150,   151,   152,   115,   121,    59,    68,   115,
      67,    64,     6,   109,   110,    67,     6,   150,   136,   145,
     105,   113,   121,     6,   137,   123,   145,    67,    68,    15,
      34,   147,    71,   136,   123,   121,     6,   102,     6,    44,
     150,   150,   150,   150,   150,   150,    36,    37,    38,    39,
      40,    41,    48,    49,    50,    51,    52,    53,    54,    55,
      58,    59,    60,    62,    71,    64,   115,   115,   119,    68,
      89,    65,    67,    58,    66,    68,   116,   123,   115,    64,
       6,   137,    71,    72,   138,   142,   116,   136,   121,   137,
     123,     6,    67,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   115,    67,   150,   153,   123,    88,     8,   109,   136,
       6,   141,    64,    69,   147,   116,   123,    64,   137,    61,
      67,    68,   121,    67,   141,     6,   139,   121,   136,   137,
     141,    64,   150,   150,   123,   122,    67,    58,    73,    66,
     123,   121,    64,    67,   141,   137,   122,   150,     6,     6,
     148,   123,   141,   122,    67,   131,    42,   140,    64,   115,
     137,    67,   122,    64,   150,    65,   150,    58,   149,   132,
     122,   141,   139,    67,    68,   150,    64,    67,    65,   150,
     141,   122,   139,    67,    68,    67,    65,   150,   122,   139,
      67,    65,   139
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

  case 84:
#line 845 "parser.y"
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

  case 85:
#line 876 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 86:
#line 880 "parser.y"
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

  case 87:
#line 895 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (2)]);
}
    break;

  case 88:
#line 899 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 89:
#line 905 "parser.y"
    {
  (yyval)=1;  
}
    break;

  case 90:
#line 909 "parser.y"
    {
  (yyval)=2;
}
    break;

  case 91:
#line 915 "parser.y"
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

  case 92:
#line 930 "parser.y"
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

  case 93:
#line 946 "parser.y"
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

  case 94:
#line 965 "parser.y"
    {
  assert(currenttype!=NULL);
  currenttype=currentstruct;
  (yyval)=(YYSTYPE)currenttype;
}
    break;

  case 95:
#line 971 "parser.y"
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

  case 96:
#line 984 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=new paroc_list<TemplateArgument *>();
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (1)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 97:
#line 991 "parser.y"
    {
  paroc_list<TemplateArgument *> *list=(paroc_list<TemplateArgument *> *)(yyvsp[(3) - (3)]);
  TemplateArgument *v=(TemplateArgument *)(yyvsp[(1) - (3)]);
  list->AddHead(v);
  (yyval)=(YYSTYPE)list;
}
    break;

  case 98:
#line 1000 "parser.y"
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

  case 99:
#line 1072 "parser.y"
    {
	(yyval)=0;
	constPointerPositions.clear();
}
    break;

  case 100:
#line 1077 "parser.y"
    {
	(yyval)=(yyvsp[(3) - (3)])+1; /* modivied by David (added const)*/
	constPointerPositions.push_back(((yyvsp[(2) - (3)]) == 1 ? true : false));
}
    break;

  case 101:
#line 1085 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 102:
#line 1089 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 103:
#line 1095 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 104:
#line 1099 "parser.y"
    {
  (yyval)=1;
}
    break;

  case 109:
#line 1117 "parser.y"
    {
  method->isPureVirtual=paroc_utils::isEqual(GetToken((yyvsp[(2) - (2)])),"0");
}
    break;

  case 110:
#line 1123 "parser.y"
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

  case 111:
#line 1139 "parser.y"
    {
  method=new Constructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);

  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 112:
#line 1148 "parser.y"
    {
  if (!paroc_utils::isEqual(method->name,currentClass->GetName()))
    {
      errormsg("Bad declaration of destructor\n");
      exit(1);
    }
	strcpy(method->name,currentClass->GetName());
}
    break;

  case 113:
#line 1157 "parser.y"
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

  case 114:
#line 1170 "parser.y"
    {
  method=new Destructor(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
}
    break;

  case 115:
#line 1300 "parser.y"
    {
	setReturnParam((yyvsp[(2) - (8)]),(yyvsp[(3) - (8)]), 0);
	
	method->isGlobalConst = ((yyvsp[(8) - (8)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 116:
#line 1307 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(1) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 117:
#line 1314 "parser.y"
    {
	setReturnParam((yyvsp[(3) - (9)]),(yyvsp[(4) - (9)]), (yyvsp[(2) - (9)]));
	
	method->isGlobalConst = ((yyvsp[(9) - (9)]) == 1 ? true : false); 
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 118:
#line 1321 "parser.y"
    {
	setReturnParam((yyvsp[(4) - (10)]),(yyvsp[(5) - (10)]), ((yyvsp[(1) - (10)]) | (yyvsp[(3) - (10)])));
	
	method->isGlobalConst = ((yyvsp[(10) - (10)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst); 
}
    break;

  case 119:
#line 1328 "parser.y"
    {
	setReturnParam((yyvsp[(5) - (11)]),(yyvsp[(6) - (11)]), ((yyvsp[(2) - (11)])|(yyvsp[(4) - (11)])));
	setPOPCMethodeModifier((yyvsp[(1) - (11)]));
	
	method->isGlobalConst = ((yyvsp[(11) - (11)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 120:
#line 1335 "parser.y"
    { UpdateMarshalParam((yyvsp[(2) - (9)]),&(method->returnparam) ); }
    break;

  case 121:
#line 1336 "parser.y"
    {
	setReturnParam((yyvsp[(7) - (14)]),(yyvsp[(8) - (14)]), ((yyvsp[(4) - (14)]) | (yyvsp[(6) - (14)])));
	
	method->isGlobalConst = ((yyvsp[(13) - (14)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 122:
#line 1342 "parser.y"
    { UpdateMarshalParam((yyvsp[(3) - (10)]),&(method->returnparam) ); }
    break;

  case 123:
#line 1343 "parser.y"
    {
	setReturnParam((yyvsp[(8) - (15)]),(yyvsp[(9) - (15)]), ((yyvsp[(5) - (15)]) & 7));
	setPOPCMethodeModifier((yyvsp[(1) - (15)]));
	
	method->isGlobalConst = ((yyvsp[(14) - (15)]) == 1 ? true : false);
	errorGlobalMehtode(method->isGlobalConst);
}
    break;

  case 124:
#line 1353 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 125:
#line 1357 "parser.y"
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

  case 126:
#line 1403 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 127:
#line 1407 "parser.y"
    {
	(yyval)=4;
}
    break;

  case 128:
#line 1411 "parser.y"
    {
	(yyval)=8;
}
    break;

  case 129:
#line 1415 "parser.y"
    {
	(yyval)=32;
}
    break;

  case 130:
#line 1419 "parser.y"
    {
  (yyval)=16;
}
    break;

  case 131:
#line 1423 "parser.y"
    {
  (yyval)=64;
}
    break;

  case 132:
#line 1430 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 133:
#line 1434 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 134:
#line 1438 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 135:
#line 1442 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 136:
#line 1449 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 137:
#line 1453 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 138:
#line 1457 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 139:
#line 1461 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 140:
#line 1465 "parser.y"
    {
	(yyval)=3;
}
    break;

  case 141:
#line 1471 "parser.y"
    {
  method=new Method(currentClass,accessmodifier);
  method->SetLineInfo(linenumber-1);
  currentClass->AddMember(method);
  strcpy(method->name,GetToken((yyvsp[(1) - (1)])));
  returntype=currenttype;
  currenttype=NULL;
}
    break;

  case 142:
#line 1482 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 143:
#line 1486 "parser.y"
    {
  (yyval)=(yyvsp[(3) - (4)]);
}
    break;

  case 144:
#line 1492 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 145:
#line 1497 "parser.y"
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

  case 146:
#line 1514 "parser.y"
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

  case 147:
#line 1530 "parser.y"
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

  case 148:
#line 1545 "parser.y"
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

  case 149:
#line 1637 "parser.y"
    {
    (yyval)=-1;
}
    break;

  case 150:
#line 1641 "parser.y"
    {
    (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 155:
#line 1656 "parser.y"
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

  case 156:
#line 1692 "parser.y"
    {
  (yyval)=0;
}
    break;

  case 157:
#line 1696 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (3)]);
}
    break;

  case 158:
#line 1702 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 159:
#line 1706 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (3)]) | (yyvsp[(3) - (3)]) ;
}
    break;

  case 160:
#line 1712 "parser.y"
    {
  (yyval)=PARAM_IN;
}
    break;

  case 161:
#line 1716 "parser.y"
    {
  (yyval)=PARAM_OUT;
}
    break;

  case 162:
#line 1720 "parser.y"
    {
  strcpy(tmpSize,GetToken((yyvsp[(3) - (3)])));
  (yyval)=PARAMSIZE;
}
    break;

  case 163:
#line 1725 "parser.y"
    {
  strcpy(tmpProc,GetToken((yyvsp[(3) - (3)])));
  (yyval)=USERPROC;
}
    break;

  case 164:
#line 1733 "parser.y"
    {
	(yyval)=0;
}
    break;

  case 165:
#line 1737 "parser.y"
    {
	(yyval)=1;
}
    break;

  case 166:
#line 1741 "parser.y"
    {
	(yyval)=2;
}
    break;

  case 167:
#line 1747 "parser.y"
    {
	(yyval)=-1;
}
    break;

  case 168:
#line 1751 "parser.y"
    {
	(yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 169:
#line 1757 "parser.y"
    {
  (yyval)=-1;
}
    break;

  case 170:
#line 1761 "parser.y"
    {
  (yyval)=(yyvsp[(2) - (2)]);
}
    break;

  case 171:
#line 1774 "parser.y"
    {
  if ((yyvsp[(2) - (2)])<0) (yyval)=(yyvsp[(1) - (2)]);
  else 
    {
      sprintf(tmp, "%s%s",GetToken((yyvsp[(1) - (2)])),GetToken((yyvsp[(2) - (2)])));
      (yyval)=PutToken(tmp);
    }
}
    break;

  case 172:
#line 1783 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 173:
#line 1787 "parser.y"
    {
    (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 174:
#line 1791 "parser.y"
    {
  sprintf(tmp,"%s + %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 175:
#line 1796 "parser.y"
    {
  sprintf(tmp,"%s - %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 176:
#line 1801 "parser.y"
    {
  sprintf(tmp,"%s * %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 177:
#line 1806 "parser.y"
    {
  sprintf(tmp,"%s / %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 178:
#line 1811 "parser.y"
    {
  sprintf(tmp,"%s %% %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 179:
#line 1816 "parser.y"
    {
  sprintf(tmp,"%s & %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 180:
#line 1821 "parser.y"
    {
  sprintf(tmp,"%s | %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 181:
#line 1826 "parser.y"
    {
  sprintf(tmp,"%s ^ %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 182:
#line 1831 "parser.y"
    {
  sprintf(tmp,"%s && %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 183:
#line 1836 "parser.y"
    {
  sprintf(tmp,"%s || %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 184:
#line 1841 "parser.y"
    {
  sprintf(tmp,"%s == %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 185:
#line 1846 "parser.y"
    {
  sprintf(tmp,"%s=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 186:
#line 1851 "parser.y"
    {
  sprintf(tmp,"%s ? %s : %s",GetToken((yyvsp[(1) - (5)])), GetToken((yyvsp[(3) - (5)])), GetToken((yyvsp[(5) - (5)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 187:
#line 1856 "parser.y"
    {
  sprintf(tmp,"%s != %s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 188:
#line 1861 "parser.y"
    {
  sprintf(tmp,"%s>%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 189:
#line 1866 "parser.y"
    {
  sprintf(tmp,"%s<%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 190:
#line 1871 "parser.y"
    {
  sprintf(tmp,"%s>=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 191:
#line 1876 "parser.y"
    {
  sprintf(tmp,"%s<=%s",GetToken((yyvsp[(1) - (3)])), GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 192:
#line 1881 "parser.y"
    {
  sprintf(tmp,"-%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 193:
#line 1886 "parser.y"
    {
  sprintf(tmp,"(%s)",GetToken((yyvsp[(2) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 194:
#line 1891 "parser.y"
    {
  sprintf(tmp,"%s()",GetToken((yyvsp[(1) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 195:
#line 1896 "parser.y"
    {
  sprintf(tmp,"%s(%s)",GetToken((yyvsp[(1) - (4)])),GetToken((yyvsp[(3) - (4)])));
  (yyval)=PutToken(tmp);
 
}
    break;

  case 196:
#line 1902 "parser.y"
    {
  sprintf(tmp,"*%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 197:
#line 1907 "parser.y"
    {
  sprintf(tmp,"&%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 198:
#line 1912 "parser.y"
    {
  sprintf(tmp,"!%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 199:
#line 1917 "parser.y"
    {
  sprintf(tmp,"~%s",GetToken((yyvsp[(2) - (2)])));
  (yyval)=PutToken(tmp);
}
    break;

  case 200:
#line 1924 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 201:
#line 1928 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 202:
#line 1934 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 203:
#line 1938 "parser.y"
    {
  sprintf(tmp,"%s::%s",GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);  
}
    break;

  case 204:
#line 1946 "parser.y"
    {
  (yyval)=(yyvsp[(1) - (1)]);
}
    break;

  case 205:
#line 1950 "parser.y"
    {
  sprintf(tmp,"%s, %s", GetToken((yyvsp[(1) - (3)])),GetToken((yyvsp[(3) - (3)])));
  (yyval)=PutToken(tmp);
}
    break;


/* Line 1267 of yacc.c.  */
#line 3831 "parser.tab.c"
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


#line 1958 "parser.y"


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


