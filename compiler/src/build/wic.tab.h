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
    FUN = 262,
    GLOBAL = 263,
    STATIC = 264,
    INT_VAL = 265,
    REAL_VAL = 266,
    BOOL_VAL = 267,
    CHAR_VAL = 268,
    STRING_VAL = 269,
    INT_TYPE = 270,
    REAL_TYPE = 271,
    BOOL_TYPE = 272,
    CHAR_TYPE = 273,
    VOID = 274,
    ASSIGN = 275,
    SUM = 276,
    SUBSTRACT = 277,
    PRODUCT = 278,
    DIVIDE = 279,
    MODULUS = 280,
    POWER = 281,
    RADICAL = 282,
    INCREMENT = 283,
    DECREMENT = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    EQUALS = 288,
    NOT_EQUALS = 289,
    GREATER = 290,
    GREATER_EQUALS = 291,
    LESS = 292,
    LESS_EQUALS = 293,
    AND_BIT = 294,
    OR_BIT = 295,
    XOR_BIT = 296,
    LEFT_SHIFT = 297,
    RIGHT_SHIFT = 298,
    UNION = 299,
    DIFFERENCE = 300,
    INTERSECTION = 301,
    IF_CLAUSE = 302,
    FOR_WHILE_CLAUSE = 303,
    HEADER_END = 304,
    ELSE_IF_FOR_WHILE_CLAUSE = 305,
    SQUARE_BRACKET_OPEN = 306,
    SQUARE_BRACKET_CLOSE = 307,
    CURLY_BRACKET_OPEN = 308,
    CURLY_BRACKET_CLOSE = 309,
    ELEM_SEPARATOR = 310,
    PARETHESES_OPEN = 311,
    PARETHESES_CLOSE = 312,
    END_OF_INSTR = 313,
    OPEN_CONTEXT_TAG = 314,
    CLOSE_CONTEXT_TAG = 315,
    CHAR_QUOTE = 316,
    STRING_QUOTE = 317,
    ID = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  void *  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WIC_TAB_H_INCLUDED  */
