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
%token END_OF_INSTR CONTEXT_TAG CHAR_QUOTE STRING_QUOTE

/* Token identificador */
%token ID

/* Asociatividad y precedencia de los operadores  */
%right ASSIGN
%left SUM SUBSTRACT
%left PRODUCT DIVIDE MODULUS
%left RADICAL
%right POWER

%start input

%%

/* Definición de gramáticas */

input: instrs END_OF_INSTR input                 { printf("1) Inicializo\n"); }
    |  /* empty */                               { printf("No encuentro nada\n"); }

instrs: instrs instr                             { printf("2) Instrucciones\n"); }
    | /* empty */

instr: ID ASSIGN expr                            { printf("3) Asignación\n"); }

expr: expr SUM term                              { printf("4) Suma: %d\n"); }
    | expr SUBSTRACT term                        { printf("4) Resta\n"); }
    | term                                       { printf("4) Solo un término\n"); }

term: term PRODUCT factor                        { printf("5) Producto\n"); }
    | term DIVIDE factor                         { printf("5) División\n"); }
    | factor                                     { printf("5) Factor\n"); return $1; }

factor: INT_VAL                                  { printf("6) Valor entero\n"); return $1; }
    | PARETHESES_OPEN expr PARETHESES_CLOSE      { printf("5) Expresión parentesis\n"); return $2; }

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
