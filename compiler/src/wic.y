%{

    /* Declaraciones */

    #include <stdio.h>

%}

    /* Declaración de tokens */

    /* Tokens genéricos */
    %token LETTER DIGIT END_OF_INSTR SEPARATOR CONTEXT_TAG ID

    /* Tokens de valores según el tipo de dato */
    %token INT_VAL REAL_VAL BOOL_VAL CHAR_VAL STRING_VAL

    /* Tokens de tipo de dato */
    %token INT_TYPE REAL_TYPE BOOL_TYPE CHAR_TYPE

    /* Tokens de arrays */
    %token ARRAY_DECLARE ARRAY_DECLARE_SIZE

    /* Tokens para las palabras reservadas */
    %token NEW CONTINUE BREAK RETURN VOID FUN

    /* Tokens para los operadores aritméticos */
    %token PREINCREMENT POSTINCREMENT PREDECREMENT POSTDECREMENT

%%

    /* Definición de gramáticas */

    . : ;

%%

    /* Funciones auxiliares */
    int int main() {
      yylineno = 1;
      yylex();
      printf("\nNumber of lines : %d\n", line);
      return 0;
    }
