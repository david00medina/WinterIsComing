%{

    /* Declaraciones */

    #include <stdio.h>
    #include <stdlib.h>

    extern int yyparse(void);
    extern int yylex(void);
    extern FILE* yyin;

    void yyerror(const char* s);
%}

/* Declaración de tokens */

/* Tokens para las palabras reservadas */
%token NEW CONTINUE BREAK RETURN VOID FUN

/* Tokens de valores según el tipo de dato */
%token INT_VAL REAL_VAL BOOL_VAL CHAR_VAL STRING_VAL

/* Tokens de tipo de dato */
%token INT_TYPE REAL_TYPE BOOL_TYPE CHAR_TYPE

/* Token de asignación */
%token ASSIGN

/* Tokens de los operadores aritméticos */
%token SUM SUBSTRACT PRODUCT DIVIDE MODULUS POWER RADICAL INCREMENT DECREMENT

/* Tokens de los operadores lógicos */
%token AND OR NOT EQUALS NOT_EQUALS GREATER GREATER_EQUALS LESS LESS_EQUALS

/* Tokens de los operadores bit a bit */
%token AND_BIT OR_BIT XOR_BIT LEFT_SHIFT RIGHT_SHIFT

/* Tokens delimitadores */
%token ARRAY_OPEN ARRAY_CLOSE ARRAY_ELEM_OPEN ARRAY_ELEM_CLOSE
%token ELEM_SEPARATOR FUN_PARAM_OPEN FUN_PARAM_CLOSE
%token END_OF_INSTR BLANK_SPACE CONTEXT_TAG

/* Token identificador */
%token ID

%start input

%%

/* Definición de gramáticas */

input :

%%

/* Funciones auxiliares */

void yyerror(char const* x) {
  printf("Error : %s\n", x);
  exit(1);
}

int main(int argc, char const *argv[]) {
  while (1) {
    yylex();
  }

  //yylex_destroy();
  return 0;
}
