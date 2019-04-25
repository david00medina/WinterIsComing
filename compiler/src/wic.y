%{

    /* Declaraciones */

    #include <stdio.h>
    #include <stdlib.h>

    extern int yyparse(void);
    extern int yylex(void);
    extern FILE* yyin;
    extern int yylineno;

    void yyerror(const char* s);
%}

/* Definición de tipo de valores */
%union
{
  int integer;
  float real;
  char bool;
  char character[2];
  char string[512];
};

/* Declaración de tokens */

/* Tokens para las palabras reservadas */
%token NEW CONTINUE BREAK RETURN VOID FUN GLOBAL STATIC

/* Tokens de valores según el tipo de dato */
%token <integer> INT_VAL
%token <real> REAL_VAL
%token <bool> BOOL_VAL
%token <character> CHAR_VAL
%token <string> STRING_VAL

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

/* Tokens de los operadores de arrays */
%token UNION DIFFERENCE INTERSECTION

/* Tokens para estructuras de control y bucles */
%token IF_CLAUSE FOR_WHILE_CLAUSE HEADER_END ELSE_IF_FOR_WHILE_CLAUSE

/* Tokens delimitadores */
%token SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE
%token ELEM_SEPARATOR PARETHESES_OPEN PARETHESES_CLOSE
%token END_OF_INSTR BLANK_SPACE CONTEXT_TAG CHAR_QUOTE STRING_QUOTE

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
    printf("Numero de linea : %d\n", yylineno);
  }

  //yylex_destroy();
  return 0;
}
