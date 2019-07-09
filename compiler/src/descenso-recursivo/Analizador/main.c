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
	int n = 0;
	/* 
	while(n<20){
		
		printf("-----%s----\n",terminals[l-257]);
		l = getChar();
		n++;
	}
	*/
	/*
	while(l != 0){
		printf("l -> %d\n", l);
		l = getChar();
	}
	 */
	if(l != 0){
		
		printf("error");
	}
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
	while(1){
		expr();
		if(l == FOR_WHILE_CLAUSE) break;
		if(l==AND){
			match(AND);
		} else{
			match(OR);
		}
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
	//el else if de arriba se puede borrar?
}

void instr () {
    if(l == ID){
		if(l == ASSIGN){
			term();
			match(END_OF_INSTR);
		} else if(l == LESS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS || l == LESS_EQUALS){
			match(l);
			if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL || l == ID){
				match(l);
				anid_while();
			} else {
				//ERROR
				match(1000);
			}
		}
	}else if(l == BREAK){
		match(l);
		match(END_OF_INSTR);
	}else if(l==INT_VAL || l == REAL_VAL || l == BOOL_VAL){
		match(l);
		if(l == LESS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS || l == LESS_EQUALS){
			match(l);
			if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL || l == ID){
				match(l);
				anid_while();
			} else {
				//ERROR
				match(1000);
			}
		} else {
			match(1000);
		}
	}else if(l == INT_TYPE || l == BOOL_TYPE || l == REAL_TYPE){
		match(l);
		match(ID);
		match(ASSIGN);
		term();
		match(END_OF_INSTR);
	}
}
/*
void instr () {
    if(l == BREAK){
        match(l);
        match(END_OF_INSTR);
    }else if (l == ID) {
		match(ID);
        if(l == LESS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS || l == LESS_EQUALS){
            preanid_while();
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
            preanid_while();
        }
		anid_while(); 
	} else {
        printf("ERROR[instr]: Algo va mal con la inicialización de una instrucción.\n");
    }
}
 
void preanid_while(){
	match(l);
	if(l == INT_VAL || l == REAL_VAL || l == BOOL_VAL){
		match(l);
	} else if (l == ID){
		match(ID);
	} else {
		printf("ERROR[instr]: Expresión de while no correcta.\n");
	}
}
*/
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
	if(l == LESS_EQUALS || l == LESS || l == EQUALS || l == GREATER || l == GREATER_EQUALS || l == NOT_EQUALS){
		match(l);
		term();
	} else {
		//NOTHING TODO
	}
}

void term () {
	if (l == INT_VAL || l == REAL_VAL || l == BOOL_VAL) {
		data_value();
	} else if(l == ID){
		match(ID);
		printf("\n        [%s]       \n",terminals[l-257]);
	} else {
		match(1000);
	}
	if(l == SUM || l == SUBSTRACT || l == PRODUCT || l == DIVIDE){
		match(l);
		term();
	}else{
		//NOTHING TODO
	}
}

void data_value () {
	if (l == INT_VAL) {
		match(INT_VAL);
	} else if (l == REAL_VAL) {
		match(REAL_VAL);
	} else{
		match(BOOL_VAL);
	}
}

void match(int terminal) {
    if(l == terminal) {
        printf("Simbolo %s\n",terminals[l-257]);
		printf("\n--SE-confirma-> %s\n",terminals[l-257]);
        l = getChar();
		printf("----SIGUIENTE----%s-------\n",terminals[l-257]);
		
    } else {
        printf("Error: Expected character %s != Actual character %s\n", terminals[terminal-257], terminals[l-257]);
        fails++;
    }
}


