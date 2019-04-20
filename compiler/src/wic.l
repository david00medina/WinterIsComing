/* Ajustes iniciales */

%option yylineno
%x COMMENT_BLOCK
%x COMMENT_LINE


%{

    /* Declaraciones */

    #include <stdio.h>
    #include "wic.tab.h"

%}

    /* Definiciones regulares */

    /* Expresiones regulares genéricas */
    letter                        [a-z]|[A-Z]
    digit                         [0-9]
    end_of_instr                  ([\r\n])
    separator                     [ ]{1,3}
    context_tag                   [\t]|[ ]{4}
    id                            ({letter}|{digit})+

    /* Tipos de dato */
    int_val                       {digit}+
    real_val                      {digit}+(\.{digit}+)?
    bool_val                      (true|false)
    char_val                      (['][\W|\w]?['])
    string_val                    (["][\W|\w]*["])
    int_type                      (int)
    real_type                     (real)
    bool_type                     (bool)
    char_type                     (char)

    /* Array */
    array_declare                 {int_type|real_type|bool_type|char_type}[\[][\]]{separator}{id}
    array_declare_size            {int_type|real_type|bool_type|char_type}[\[]{int_val}[\]]{separator}{id}

    /* Palabras reservadas */
    new                           (new)
    continue                      (continue)
    break                         (break)
    return                        (return)
    void                          (void)
    fun                           (fun)

    /* Operadores aritméticos */
    preincrement                  [\+]{2}({id}|{int_val})
    postincrement                 ({id}|{int_val})[\+]{2}
    predecrement                  [-]{2}({id}|{int_val})
    postdecrement                 ({id}|{int_val})[-]{2}

%%

    /* Reglas de traducción */

    /* Reglas genéricas */
    {letter}                      { printf("%s is a LETTER\n", yytext); }
    {digit}                       { printf("%s is a DIGIT\n", yytext); }
    {end_of_instr}                {
                                    printf("%s is a END_OF_INSTR\n", yytext);
                                    yylineno++;
                                  }
    {separator}                   { printf("%s is a SEPARATOR\n", yytext); }
    {context_tag}                 { printf("%s is a CONTEXT_TAG\n", yytext); }
    {ID}                          { printf("%s is a ID\n", yytext); }


    /* Reglas para los tipos de dato */
    {int_val}                     { printf("%s is a INT_VAL\n", yytext); }
    {real_val}                    { printf("%s is a REAL_VAL\n", yytext); }
    {bool_val}                    { printf("%s is a BOOL_VAL\n", yytext); }
    {char_val}                    { printf("%s is a CHAR_VAL\n", yytext); }
    {string_val}                  { printf("%s is a STRING_VAL\n", yytext); }
    {int_type}                    { printf("%s is a INT_TYPE\n", yytext); }
    {real_type}                   { printf("%s is a REAL_TYPE\n", yytext); }
    {bool_type}                   { printf("%s is a BOOL_TYPE\n", yytext); }
    {char_type}                   { printf("%s is a CHAR_TYPE\n", yytext); }

    /* Reglas para los arrays */
    {array_declare}               { printf("%s is a ARRAY_DECLARE\n", yytext); }
    {array_declare_size}          { printf("%s is a ARRAY_DECLARE_SIZE\n", yytext); }

    /* Reglas para las palabras reservadas */
    {new}                         { printf("%s is a NEW\n", yytext); }
    {continue}                    { printf("%s is a CONTINUE\n", yytext); }
    {break}                       { printf("%s is a BREAK\n", yytext); }
    {return}                      { printf("%s is a RETURN\n", yytext); }
    {void}                        { printf("%s is a VOID\n", yytext); }
    {fun}                         { printf("%s is a FUN\n", yytext); }

    /* Reglas para los operadores aritméticos */
    {preincrement}                { printf("%s is a PREINCREMENT\n", yytext); }
    {postincrement}               { printf("%s is a POSTINCREMENT\n", yytext); }
    {predecrement}                { printf("%s is a PREDECREMENT\n", yytext); }
    {postdecrement}               { printf("%s is a POSTDECREMENT\n", yytext); }

    /* Reglas para los comentarios */
    ",\."                         { BEGIN(COMMENT_BLOCK); }
    <COMMENT_BLOCK>"\.,"          { BEGIN(INITIAL); }
    <COMMENT_BLOCK>([^\.]|\n)+|.
    <COMMENT_BLOCK><<EOF>>        /* Do something */
    <COMMENT_LINE>"\.\."          { BEGIN(COMMENT_LINE); }
    <COMMENT_LINE>(\n)            { BEGIN(INITIAL); }
    <COMMENT_LINE>([^\n]|.)+
    <COMMENT_LINE><<EOF>>         /* Do something */

    /* Unknowns */
    .                             { printf("%s is an unknown\n", yytext); }

%%

    /* Funciones auxiliares */

    int yywrap(){}
