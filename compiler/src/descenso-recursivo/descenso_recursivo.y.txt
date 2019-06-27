#include "wic.tab.h"

Token token;

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
	} else if (token.tipo != Token.CLOSE_CONTEXT_TAG) {
		err();
	}
}

public final void instr () {
	match(Token.ID);
	match(Token.ASSIGN);
	term();
	match(Token.END_OF_INSTR);
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

public final void match (Token tokEsperado) {
	if (tokEsperado != token.tipo) {
		err();
	} else {
		
	}
}

public void main () {

}
