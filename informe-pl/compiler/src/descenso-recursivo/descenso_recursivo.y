%{

    /* Declaraciones */

    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "../utils/termcolor.hpp"
    #include "../symbol-table/SymbolTable.hpp"
    #include "../ast/AbstractSyntaxTree.hpp"
    #include "../ast/nodes/operator-nodes/ASTArithmeticNode.hpp"
    #include "../code-generator/CodeGenerator.hpp"
	#include "wic.tab.h"

    int yylex(void);
    void yyerror(char const *);

    extern int level;
    extern int yylineno;

    wic::GSymbolTable* gst;
    wic::SSymbolTable* sst;
    wic::LSymbolTable* lst;

    wic::AbstractSyntaxTree* ast;
    wic::CodeGenerator* cg;

%}

%token FOR_WHILE_CLAUSE
%token HEADER_END
%token END_OF_INSTR
%token OPEN_CONTEXT_TAG
%token CLOSE_CONTEXT_TAG
%token ID
%token ASSIGN
%token LESS
%token GREATER
%token EQUALS
%token SUM
%token SUBSTRACT
%token PRODUCT
%token DIVIDE
%token INT_VAL
%token REAL_VAL
%token BOOL_VAL
%token INT_TYPE
%token REAL_TYPE
%token BOOL_TYPE

/* Asociatividad y precedencia de los operadores  */
%right ASSIGN
%left LESS GREATER EQUALS
%left SUM SUBSTRACT
%left PRODUCT DIVIDE

%start while_instr

public final void while_instr () {
	expr();
	match(Token.FOR_WHILE_CLAUSE);
	match(Token.HEADER_END);
	match(Token.END_OF_INSTR);
	match(Token.OPEN_CONTEXT_TAG);
	input();
	match(Token.CLOSE_CONTEXT_TAG);
}

public final void input () {
	if (token.tipo == Token.ID) {
		instr();
		input();
	} else if (token.tipo != Token.CLOSE_CONTEXT_TAG) {
		err();
	}
}

public final void instr () {
	if (token.tipo == Token.ID) {
		match(Token.ID);
		match(Token.ASSIGN);
		term();
		match(Token.END_OF_INSTR);
	} else {
		data_type();
		match(Token.ID);
		if (token.tipo == Token.END_OF_INSTR) {
			match(Token.END_OF_INSTR);
		} else {
			match(Token.ASSIGN);
			term();
			match(Token.END_OF_INSTR);
		}
	}
}

public final void expr () {
	term();
	if (token.tipo == Token.LESS) {
		match(Token.LESS);
		term();
	} else if (token.tipo == Token.GREATER) {
		match(Token.GREATER);
		term();
	} else if (token.tipo == Token.EQUALS) {
		match(Token.EQUALS);
		term();
	} else if (token.tipo != Token.FOR_WHILE_CLAUSE) {
		err();
	}
}

public final void term () {
	if (token.tipo == Token.INT_VAL || token.tipo == Token.REAL_VAL || token.tipo == Token.BOOL_VAL) {
		data_value();
	} else {
		match(Token.ID);
	}
	if (token.tipo == Token.SUM) {
		match(Token.SUM);
		term();
	} elseif (token.tipo == Token.SUBSTRACT) {
		match(Token.SUBSTRACT);
		term();
	} else if (token.tipo == Token.PRODUCT) {
		match(Token.PRODUCT);
		term();
	} else if (token.tipo == Token.DIVIDE) {
		match(Token.DIVIDE);
		term();
	} else if (token.tipo != Token.END_OF_INSTR && token.tipo != token.FOR_WHILE_CLAUSE) {
		err();
	}
}

public final void data_value () {
	if (token.tipo == Token.INT_VAL) {
		match(Token.INT_VAL);
	} else if (token.tipo == Token.REAL_VAL) {
		match(Token.REAL_VAL);
	} else {
		match(Token.BOOL_VAL);
	}
}

public final void data_type () {
	if (token.tipo == Token.INT_TYPE) {
		match(Token.INT_TYPE);
	} else if (token.tipo == Token.REAL_TYPE) {
		match(Token.REAL_TYPE);
	} else {
		match(Token.BOOL_TYPE);
	}
}

public final void match (Token tokEsperado) {
	if (tokEsperado == token.tipo) {
		yyparse();
	} else {
		err();
	}
}

public void main () {
	
	while_instr();
}
