%{

    /* Declaraciones */

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string>

    int yylex(void);
    void yyerror(char const *);
%}

/* Definición de tipo de valores */
%union
{
  int integer;
  float real;
  char boolean;
  char character[2];
  char* string;
};

/* Declaración de tokens */

/* Tokens para las palabras reservadas */
%token NEW CONTINUE BREAK RETURN FUN GLOBAL STATIC

/* Tokens de valores de datos */
%token <integer> INT_VAL
%token <real> REAL_VAL
%token <boolean> BOOL_VAL
%token <character> CHAR_VAL
%token <string> STRING_VAL


/* Tokens de tipo de dato */
%token <string> INT_TYPE REAL_TYPE BOOL_TYPE CHAR_TYPE VOID

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
%token END_OF_INSTR OPEN_CONTEXT_TAG CLOSE_CONTEXT_TAG CHAR_QUOTE STRING_QUOTE

/* Token identificador */
%token <string> ID

/* Tipos de reglas  */
%type <string> data_type
%type <integer> expr term factor power data_value

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
    | END_OF_INSTR input
    | OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG input
    | /* empty */

data_init: GLOBAL data_type
    | STATIC data_type
    | data_type
    | array_init

array_init: data_type SQUARE_BRACKET_OPEN INT_VAL SQUARE_BRACKET_CLOSE
    | data_type SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE

data_type: INT_TYPE
    | REAL_TYPE
    | BOOL_TYPE
    | CHAR_TYPE                                   { printf("Tipo (CHAR)\n"); }

instr: data_init ID                               { printf("Instrucción (DECLARE VAR)\n"); }
    | data_init ID ASSIGN expr                    { printf("Instrucción (=)\n"); }
    | ID array_access ASSIGN expr                 { printf("Instrucción acceso array\n"); }
    | if_instr                                    { printf("Instrucción (IF-IFELSE-ELSE)\n"); }
    | for_instr                                   { printf("Instrucción (FOR-FORELSE-ELSE)\n"); }
    | while_instr                                 { printf("Instrucción (WHILE-WHILEELSE-ELSE)\n"); }
    | expr                                        { printf("Instrucción EXPR: %d\n", $1); }
    | fun_init                                    { printf("Instrucción FUN (declaration)\n"); }
    | fun_call                                    { printf("Instrucción FUN (call)\n"); }

comma_exp_init: comma_exp_init ELEM_SEPARATOR comma_exp_init     { printf("Expresión (,)\n"); }
    | data_type ID                                { printf("Expresión (,%s %s,)\n", $1); }
    | /* empty */

comma_exp: comma_exp ELEM_SEPARATOR comma_exp     { printf("Función llamada (,)\n"); }
    | factor                                      { printf("Función llamada (factor)\n"); }
    | data_value                                  { printf("Función llamada (valor)\n"); }
    | ID                                          { printf("Función llamada (variable)\n"); }
    | expr                                        { printf("Función llamada (término)\n"); }

fun_init: FUN data_type ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE HEADER_END END_OF_INSTR
      fun_body                                    { printf("Función (tipo=%s,nombre=%s)\n", $2, $3); }
    | FUN VOID ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE HEADER_END END_OF_INSTR
      fun_body                                    { printf("Función (tipo=%s,nombre=%s)\n", $2, $3); }
    | FUN data_type ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE END_OF_INSTR { printf("Función (tipo=%s,nombre=%s)\n", $2, $3); }
    | FUN VOID ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE END_OF_INSTR { printf("Función (tipo=%s,nombre=%s)\n", $2, $3); }

fun_body: OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | /* empty */

fun_call: ID PARETHESES_OPEN comma_exp PARETHESES_CLOSE         { printf("Función llamada (nombre=%s)\n", $1); }

while_instr: expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
      while_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input

while_middle_block: while_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
    | /* empty */

for_instr: expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      input
      for_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      input
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      input

for_middle_block: for_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      input
    | /* empty */

if_instr: expr IF_CLAUSE HEADER_END END_OF_INSTR
      input
      if_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE IF_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr IF_CLAUSE HEADER_END END_OF_INSTR
      input
      ELSE_IF_FOR_WHILE_CLAUSE IF_CLAUSE HEADER_END END_OF_INSTR
      input
    | expr IF_CLAUSE HEADER_END END_OF_INSTR
      input

if_middle_block: if_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr IF_CLAUSE HEADER_END END_OF_INSTR
      input
    | /* empty */

array_access: SQUARE_BRACKET_OPEN INT_VAL SQUARE_BRACKET_CLOSE

expr: ID ASSIGN term                              { printf("Expresión (=)\n"); }
    | expr SUM term                               { printf("Expresión (Suma): %d\n", $1 + $3); $$ = $1 + $3;}
    | expr SUBSTRACT term                         { printf("Expresión (Resta): %d\n", $1 - $3); $$ = $1 - $3;}
    | INCREMENT ID                                { printf("Expresión (++ID)\n"); }
    | ID INCREMENT                                { printf("Expresión (ID++)\n"); }
    | DECREMENT ID                                { printf("Expresión (--ID)\n"); }
    | ID DECREMENT                                { printf("Expresión (ID--)\n"); }
    | expr LESS term                              { printf("Expresión (<)\n"); }
    | expr LESS_EQUALS term                       { printf("Expresión (<=)\n"); }
    | expr GREATER term                           { printf("Expresión (>)\n"); }
    | expr GREATER_EQUALS term                    { printf("Expresión (>=)\n"); }
    | expr EQUALS term                            { printf("Expresión (==)\n"); }
    | expr NOT_EQUALS term                        { printf("Expresión (!=)\n"); }
    | expr AND term                               { printf("Expresión (&&)\n"); }
    | expr OR term                                { printf("Expresión (||)\n"); }
    | NOT term                                    { printf("Expresión (!)\n"); }
    | expr AND_BIT term                           { printf("Expresión (&)\n"); }
    | expr OR_BIT term                            { printf("Expresión (|)\n"); }
    | expr XOR_BIT term                           { printf("Expresión (^)\n"); }
    | expr LEFT_SHIFT term                        { printf("Expresión (<<)\n"); }
    | expr RIGHT_SHIFT term                       { printf("Expresión (>>)\n"); }
    | expr UNION term                             { printf("Expresión (U)\n"); }
    | expr DIFFERENCE term                        { printf("Expresión (D)\n"); }
    | expr INTERSECTION term                      { printf("Expresión (I)\n"); }
    | term                                        { printf("Expresión: %d\n", $1); $$ = $1;}
    | data_vector                                 { printf("Expresión (vector)\n"); }

term: term PRODUCT power                          { printf("Término (Producto): %d\n", $1 * $3); $$ = $1 * $3;}
    | term DIVIDE power                           { printf("Término (División): %d\n", $1 / $3); $$ = $1 / $3;}
    | term MODULUS power                          { printf("Término (Módulo): %d\n", $1 % $3); $$ = $1 % $3;}
    | power                                       { printf("Término: %d\n", $1); $$ = $1;}
    | ID array_access                             { printf("Término (VectorVal)");}

power: power RADICAL factor                       { printf("Potencia/Raiz (Raíz): %f\n", pow((float)$3, 1/$1)); $$ = pow($3, (float)1/$1);}
    | power POWER factor                          { printf("Potencia/Raiz (Potencia): %f\n", pow((float)$1, $3)); $$ = pow($1, (float)$3);}
    | factor

factor: PARETHESES_OPEN expr PARETHESES_CLOSE     { printf("Factor (Expresión parentesis): %d\n", $2); $$ = $2; }
    | SUBSTRACT factor                            { printf("Factor (Numero negativo): %d\n", -$2); $$ = -$2; }
    | data_value                                  { printf("Factor (DATA_VALUE): %d\n", $1); }
    | ID                                          { printf("Factor (ID): %d\n", $1); }

data_value: INT_VAL                               { printf("Factor (Numero): %d\n", $1); $$ = $1; }
    | REAL_VAL                                    { printf("Factor (REAL): %d\n", $1); }
    | BOOL_VAL                                    { printf("Factor (BOOLEAN): %d\n", $1); }
    | CHAR_QUOTE CHAR_VAL CHAR_QUOTE              { printf("Factor (CARACTER): %d\n", $2); }
    | STRING_QUOTE STRING_VAL STRING_QUOTE        { printf("Factor (STRING): %d\n", $2); }

data_vector: CURLY_BRACKET_OPEN comma_exp CURLY_BRACKET_CLOSE        { printf("Factor (VECTOR): %d\n"); }

%%
