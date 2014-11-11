/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_UNCOOL_TAB_H_INCLUDED
# define YY_YY_UNCOOL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS_T = 258,
    INT_T = 259,
    BOOL_T = 260,
    STRING_T = 261,
    IN_T = 262,
    TEL_T = 263,
    INT_ARR_T = 264,
    VOID_T = 265,
    THEN_T = 266,
    ELSE_T = 267,
    FI_T = 268,
    LOOP_T = 269,
    POOL_T = 270,
    NEW_T = 271,
    ISVOID_T = 272,
    SELF_T = 273,
    LE = 274,
    LT = 275,
    GT = 276,
    GE = 277,
    NE = 278,
    EQ = 279,
    NOT_T = 280,
    OUT_STRING = 281,
    OUT_INT = 282,
    IN_INT = 283,
    TRUE_T = 284,
    FALSE_T = 285,
    INT_CONST = 286,
    LET_T = 287,
    IF_T = 288,
    WHILE_T = 289,
    STRING_CONST = 290,
    TYPE = 291,
    ID = 292,
    ASSIGN = 293,
    UC = 294,
    UM = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 56 "uncool.y" /* yacc.c:1909  */

    int type;
    char *str;

#line 100 "uncool.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_UNCOOL_TAB_H_INCLUDED  */
