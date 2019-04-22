/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_WIC_TAB_H_INCLUDED
# define YY_YY_WIC_TAB_H_INCLUDED
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
    NEW = 258,
    CONTINUE = 259,
    BREAK = 260,
    RETURN = 261,
    VOID = 262,
    FUN = 263,
    INT_VAL = 264,
    REAL_VAL = 265,
    BOOL_VAL = 266,
    CHAR_VAL = 267,
    STRING_VAL = 268,
    INT_TYPE = 269,
    REAL_TYPE = 270,
    BOOL_TYPE = 271,
    CHAR_TYPE = 272,
    ASSIGN = 273,
    SUM = 274,
    SUBSTRACT = 275,
    PRODUCT = 276,
    DIVIDE = 277,
    MODULUS = 278,
    POWER = 279,
    RADICAL = 280,
    INCREMENT = 281,
    DECREMENT = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    EQUALS = 286,
    NOT_EQUALS = 287,
    GREATER = 288,
    GREATER_EQUALS = 289,
    LESS = 290,
    LESS_EQUALS = 291,
    AND_BIT = 292,
    OR_BIT = 293,
    XOR_BIT = 294,
    LEFT_SHIFT = 295,
    RIGHT_SHIFT = 296,
    IF_CLAUSE = 297,
    FOR_WHILE_CLAUSE = 298,
    HEADER_END = 299,
    ELSE_IF_FOR_WHILE_CLAUSE = 300,
    ARRAY_OPEN = 301,
    ARRAY_CLOSE = 302,
    ARRAY_ELEM_OPEN = 303,
    ARRAY_ELEM_CLOSE = 304,
    ELEM_SEPARATOR = 305,
    FUN_PARAM_OPEN = 306,
    FUN_PARAM_CLOSE = 307,
    END_OF_INSTR = 308,
    BLANK_SPACE = 309,
    CONTEXT_TAG = 310,
    ID = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WIC_TAB_H_INCLUDED  */
