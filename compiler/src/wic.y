%{

    /* Declaraciones */

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

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

%type<integer> expr term factor power

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
%token END_OF_INSTR CONTEXT_TAG CHAR_QUOTE STRING_QUOTE

/* Token identificador */
%token ID

/* Asociatividad y precedencia de los operadores  */
%right ASSIGN NOT
%left UNION DIFFERENCE INTERSECTION
%left LESS LESS_EQUALS GREATER GREATER_EQUALS EQUALS NOT_EQUALS AND OR
%left AND_BIT OR_BIT XOR_BIT LEFT_SHIFT RIGHT_SHIFT
%left SUM SUBSTRACT
%left PRODUCT DIVIDE MODULUS
%left RADICAL
%right POWER
%nonassoc INCREMENT DECREMENT

%start input

%%

/* Definición de gramáticas */

input: instr END_OF_INSTR input                 /*{ printf("1) Inicializo\n"); }*/
    |  /* empty */                               /*{ printf("No encuentro nada\n"); }*/

instr: ID ASSIGN expr                            /*{ printf("3) Asignación\n"); }*/
    | expr                                       { printf("Instrucción: %d\n", $1); }
    | /* empty */

expr: expr SUM term                              { printf("Expresión (Suma): %d\n", $1 + $3); $$ = $1 + $3;}
    | expr SUBSTRACT term                        { printf("Expresión (Resta): %d\n", $1 - $3); $$ = $1 - $3;}
    | expr LESS term
    | INCREMENT ID
    | ID INCREMENT
    | DECREMENT ID
    | ID DECREMENT
    | expr LESS_EQUALS term
    | expr GREATER term
    | expr GREATER_EQUALS term
    | expr EQUALS term
    | expr NOT_EQUALS term
    | expr AND term
    | expr OR term
    | NOT term
    | expr AND_BIT term
    | expr OR_BIT term
    | expr XOR_BIT term
    | expr LEFT_SHIFT term
    | expr RIGHT_SHIFT term
    | expr UNION term
    | expr DIFFERENCE term
    | expr INTERSECTION term
    | term                                       { printf("Expresión: %d\n", $1); $$ = $1;}

term: term PRODUCT power                        { printf("Término (Producto): %d\n", $1 * $3); $$ = $1 * $3;}
    | term DIVIDE power                         { printf("Término (División): %d\n", $1 / $3); $$ = $1 / $3;}
    | term MODULUS power                        { printf("Término (Módulo): %d\n", $1 % $3); $$ = $1 % $3;}
    | power                                     { printf("Término: %d\n", $1); $$ = $1;}

power: power RADICAL factor                       { printf("Potencia/Raiz (Raíz): %f\n", pow((float)$3, 1/$1)); $$ = pow($3, (float)1/$1);}
    | power POWER factor                          { printf("Potencia/Raiz (Potencia): %f\n", pow((float)$3, $1)); $$ = pow($3, (float)$1);}
    | factor

factor: PARETHESES_OPEN expr PARETHESES_CLOSE    { printf("Factor (Expresión parentesis): %d\n", $2); $$ = $2; }
    | SUBSTRACT factor                           { printf("Factor (Numero negativo): %d\n", -$2); $$ = -$2; }
    | INT_VAL                                    { printf("Factor (Numero): %d\n", $1); $$ = $1; }
    | REAL_VAL
    | ID

/*list: expr SUM term list                       { printf("La suma es igual a %d\n", $1 + $3); }
    |*/ /* empty */

%%

/* Funciones auxiliares */

void yyerror(char const* x) {
  printf("Error : %s\n", x);
  exit(1);
}

int main(int argc, char const *argv[]) {
  while (1) {
    yyparse();
    printf("Numero de linea : %d\n", yylineno);
  }

  //yylex_destroy();
  return 0;
}
