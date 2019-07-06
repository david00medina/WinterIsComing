#include <stdio.h>
#include "cabeceras.h"

int l;

int yylex();
int fails = 0;
char terminals [][20] = {"END_OF_INSTR","RETURN","BREAK","VARIABLE","INT_VAL","REAL_VAL","BOOL_VAL","INT_TYPE","REAL_TYPE","BOOL_TYPE","ASSIGN","SUM","SUBSTRACT","PRODUCT","DIVIDE","AND","OR","NOT","EQUALS","NOT_EQUALS","GREATER","GREATER_EQUALS","LESS","LESS_EQUALS","HEADER_END","FOR_WHILE_CLAUSE","SQUARE_BRACKET_OPEN","SQUARE_BRACKET_CLOSE","PARETHESES_OPEN","PARETHESES_CLOSE","ID","OPEN_CONTEXT_TAG","CLOSE_CONTEXT_TAG"};

int main(int argc, char** argv) {
    //yyin = fopen("./tests/DRTest7.wic", "r");
	printf("\n--------[%s]--------\n",argv[1]);
	//char ss []= "./tests/DRTest";
	//strcat(ss, argv[1]);
	//strcat(ss,".wic");
	yyin = fopen(argv[1], "r");
    l = getChar();
    while_instr();
    if(fails==0){
        printf("NO HAY ERRORES\n");
    } else {
        printf(" %d ERRORES DETECTADOS\n",fails);
    }
    return 1;
}

int getChar() {
    return yylex();
}



void while_instr () {
	expr();
    while(l == AND || l == OR){
        match(l);
        expr();
    }
	match(FOR_WHILE_CLAUSE);
	match(HEADER_END);
	match(END_OF_INSTR);
	match(OPEN_CONTEXT_TAG);
	input();
	match(CLOSE_CONTEXT_TAG);
}

void input () {
	if (l == ID || l == INT_TYPE || l == BOOL_TYPE || l == REAL_TYPE || l == INT_VAL || l == REAL_VAL || l == BOOL_VAL || l == BREAK) {
		instr();
		input();
	}else if (l != CLOSE_CONTEXT_TAG) {
		printf("ERROR en input\n");
	}
}

void instr () {
    if(l == BREAK){
        match(l);
        match(END_OF_INSTR);
    }else if (l == ID) {
		match(ID);
        if(l == LESS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS || l == LESS_EQUALS){
            match(l);
            if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL){
                match(l);
            } else if (l == ID){
                match(ID);
            }
            anid_while();
        } else {
            match(ASSIGN);
            term();
            match(END_OF_INSTR);
        }
	}else if(l == INT_TYPE || l == BOOL_TYPE || l == REAL_TYPE){
        match(l);
		match(ID);
        match(ASSIGN);
		term();
		match(END_OF_INSTR);
    } else if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL){
        match(l);
        if(l == LESS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS || l == LESS_EQUALS){
            match(l);
            if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL){
                match(l);
            } else if (l == ID){
                match(l);
            } else {
                printf("ERROR[instr]: Expresión de while no correcta.\n");
            }
        }
		anid_while(); 
	} else {
        printf("ERROR[instr]: Algo va mal con la inicialización de una instrucción.\n");
    }
}

void anid_while(){
    match(FOR_WHILE_CLAUSE);
	match(HEADER_END);
	match(END_OF_INSTR);
	match(OPEN_CONTEXT_TAG);
	input();
	match(CLOSE_CONTEXT_TAG);
}

void expr () {
	term();
	if (l == LESS) {
		match(LESS);
		term();
	} else if (l == GREATER) {
		match(GREATER);
		term();
	} else if (l == EQUALS) {
		match(EQUALS);
		term();
    } else if (l == GREATER_EQUALS) {
		match(GREATER_EQUALS);
		term();
	} else if (l == NOT_EQUALS) {
		match(NOT_EQUALS);
		term();
	}else if (l == LESS_EQUALS) {
		match(LESS_EQUALS);
		term();
	}else if (l != FOR_WHILE_CLAUSE) {
		printf("ERROR en expr\n");
	}
}

void term () {
	if (l == INT_VAL || l == REAL_VAL || l == BOOL_VAL) {
		data_value();
	} else {
		match(ID);
	}
	if (l == SUM) {
		match(SUM);
		term();
	} else if (l == SUBSTRACT) {
		match(SUBSTRACT);
		term();
	} else if (l == PRODUCT) {
		match(PRODUCT);
		term();
	} else if (l == DIVIDE) {
		match(DIVIDE);
		term();
	} //else if (l != END_OF_INSTR && l != FOR_WHILE_CLAUSE) {
		//printf("WARNING[term]: Es posible que se haya introducido un operando no reconocible. -> [%s]\n", terminals[l-257]);
	//}
}

void data_value () {
	if (l == INT_VAL) {
		match(INT_VAL);
	} else if (l == REAL_VAL) {
		match(REAL_VAL);
	} else if (l == BOOL_VAL){
		match(BOOL_VAL);
	} else {
        printf("ERROR[data_value]:Valor de dato no reconocible.\n");
    }
}

void match(int terminal) {
    if(l == terminal) {
        printf("Simbolo %s\n",terminals[l-257]);
        l = getChar();
    } else {
        printf("Error: Expected character %s != Actual character %s\n", terminals[terminal-257], terminals[l-257]);
        fails++;
    }
}


