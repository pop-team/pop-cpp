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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



