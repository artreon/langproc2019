/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_SIMPLEPARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_SIMPLEPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/simpleparser.y" /* yacc.c:1909  */

	#include <fstream>
	#include <string>
	#include <iostream>
	#include <cassert>

	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;


	#include "ast/program.hpp"
	extern ASTProgram* program;

	void yyerror(const char *s);

#line 61 "src/simpleparser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    CHAR = 259,
    VOID = 260,
    CHAR_WORD = 261,
    COMMA = 262,
    IF = 263,
    ELSE = 264,
    AMPERSAND = 265,
    WHILE = 266,
    IDENTIFIER = 267,
    RETURN = 268,
    NUMBER = 269,
    WORD = 270,
    L_BRACE = 271,
    R_BRACE = 272,
    L_BRACKET = 273,
    R_BRACKET = 274,
    SEMI_COLON = 275,
    T_EQUALS = 276,
    T_PLUS = 277,
    T_DIVIDE = 278,
    T_MOD = 279,
    T_MULT = 280,
    T_MINUS = 281,
    T_EQUALSTO = 282,
    T_LESSTHAN = 283,
    T_MORETHAN = 284,
    T_LESSOREQUAL = 285,
    T_MOREOREQUAL = 286,
    T_NOT_EQUAL = 287,
    T_ANDCOND = 288,
    T_ORCOND = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "src/simpleparser.y" /* yacc.c:1909  */

	std::string* literal;
	ASTGlobalDeclarations* global_decls;
	ASTDeclaration* declaration;
	ASTBlock* block;
	ASTStatementList* stmt_list;
	ASTNode* node;
	ASTExpression* expr;
	ASTArgumentsList* args_list;
	ASTArgumentsFormal* args_formal;
	ASTType* type;

#line 121 "src/simpleparser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_SIMPLEPARSER_TAB_HPP_INCLUDED  */
