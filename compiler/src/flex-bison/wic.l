/* Ajustes iniciales */

%x COMMENT_BLOCK
%x COMMENT_LINE
%x CHAR_STATE
%x STRING_STATE
%x CHECK_LVL

%option noyywrap

%{

    /* Declaraciones */

    #include <string.h>
    #include "wic.tab.h"
    int level = 0;
    int enter_special = 1;

    /* Declaraciones de funciones */
    int countTabs(char* pattern);
    int countSpaces(char* pattern);

%}

/* Definiciones regulares */

/* Expresiones regulares reutilizables */
letter                        [a-zA-Z]
digit                         [0-9]

/* Palabras reservadas */
new                           (new)
continue                      (continue)
break                         (break)
return                        (return)
void                          (void)
fun                           (fun)
global                        (global)
static                        (static)

/* Valores segun el tipo de dato */
int_val                       {digit}+
real_val                      ({digit}+\.){digit}*|\.{digit}+
bool_val                      (true|false)
char_val                      [^']?|(\\[nrtvb'"])
string_val                    [^"]*|(\\[nrtvb'"])

/* Tipos de dato */
int_type                      (int)
real_type                     (real)
bool_type                     (bool)
char_type                     (char)

/* Expresiones regulares para estructuras de control y bucles */
if                            (\?){1}
for_while                     (\?){2}
header_end                    :
else_if_for_while             (\.){1}

/* Expresiones regulares delimitadoras */

context_tag                   [ ]*
/* Identificador */
id                            {letter}({letter}|{digit})*

%%
  if (enter_special) {
    BEGIN(CHECK_LVL);
    printf("Inicio, %d", YY_START);
    enter_special = 0;
  }


   /* Reglas de traducción */

   /* Cambios de ámbito */

<CHECK_LVL>\n?{context_tag}    {
                                printf("Procesando... \n<%s>\n", yytext);
                                int level_change = countSpaces(yytext);
                                printf("%d\n", level_change);

                                if (level < level_change) {
                                  level++;
                                  if (level != level_change) yyless(0);
                                  printf("Level <OPEN_CONTEXT_TAG> : %d\n", level);
                                  return OPEN_CONTEXT_TAG;
                                } else if (level > level_change) {
                                   level--;
                                   if (level != level_change) yyless(0);
                                   printf("Level <CLOSE_CONTEXT_TAG> : %d\n", level);
                                   return CLOSE_CONTEXT_TAG;
                                }
                                printf("Level : %d\n", level);
                                BEGIN(INITIAL);
                              }
<CHECK_LVL><<EOF>>            {
                                if (level > 0) {
                                  level--;
                                  return CLOSE_CONTEXT_TAG;
                                } else return 0;
                              }
<CHECK_LVL>[^ \n]             {
                                printf("Vamos para atrás\n");
                                BEGIN(INITIAL);
                                yyless(0);
                              }
<<EOF>>                       {
                                BEGIN(CHECK_LVL);
                              }
"\n"                          {
                                BEGIN(CHECK_LVL);
                                yyless(0);
                                printf("Nueva línea\n");
                                return END_OF_INSTR;
                              }

   /* Reglas para las palabras reservadas */
{new}                         {
                                //printf("%s is a NEW\n", yytext);
                                return NEW;
                              }
{continue}                    {
                                //printf("%s is a CONTINUE\n", yytext);
                                return CONTINUE;
                              }
{break}                       {
                                //printf("%s is a BREAK\n", yytext);
                                return BREAK;
                              }
{return}                      {
                                //printf("%s is a RETURN\n", yytext);
                                return RETURN;
                              }
{void}                        {
                                //printf("%s is a VOID\n", yytext);
                                return VOID;
                              }
{fun}                         {
                                //printf("%s is a FUN\n", yytext);
                                return FUN;
                              }
{global}                      {
                                //printf("%s is a GLOBAL\n", yytext);
                                return GLOBAL;
                              }
{static}                         {
                                //printf("%s is a STATIC\n", yytext);
                                return STATIC;
                              }


   /* Reglas para los valores segun el tipo de dato */
{int_val}                     {
                                yylval.integer = atoi(yytext);
                                //printf("%d is a INT_VAL\n", yylval.integer);
                                return INT_VAL;
                              }

{real_val}                    {
                                yylval.real = atof(yytext);
                                //printf("%f is a REAL_VAL\n", yylval.real);
                                return REAL_VAL;
                              }
{bool_val}                    {
                                if (strcmp("true", yytext) == 0) yylval.bool = '\x01';
                                else yylval.bool = '\x00';
                                //printf("%d is a BOOL_VAL\n", yylval.bool);
                                return BOOL_VAL;
                              }


   /* Reglas segun el tipo de dato */
{int_type}                    {
                                //printf("%s is a INT_TYPE\n", yytext);
                                return INT_TYPE;
                              }
{real_type}                   {
                                //printf("%s is a REAL_TYPE\n", yytext);
                                return REAL_TYPE;
                              }
{bool_type}                   {
                                //printf("%s is a BOOL_TYPE\n", yytext);
                                return BOOL_TYPE;
                              }
{char_type}                   {
                                //printf("%s is a CHAR_TYPE\n", yytext);
                                return CHAR_TYPE;
                              }


   /* Regla de asignación */
"="                           {
                                //printf("%s is an ASSIGN\n", yytext);
                                return ASSIGN;
                              }


   /* Reglas para los operadores aritméticos */
"\+"                          {
                                //printf("%s is a SUM\n", yytext);
                                return SUM;
                              }
"-"                           {
                                //printf("%s is a SUBSTRACT\n", yytext);
                                return SUBSTRACT;
                              }
"\*"                          {
                                //printf("%s is a PRODUCT\n", yytext);
                                return PRODUCT;
                              }
"/"                           {
                                //printf("%s is a DIVIDE\n", yytext);
                                return DIVIDE;
                              }
"%"                           {
                                //printf("%s is a MODULUS\n", yytext);
                                return MODULUS;
                              }
"\*\*"                        {
                                //printf("%s is a POWER\n", yytext);
                                return POWER;
                              }
"#"                           {
                                //printf("%s is a RADICAL\n", yytext);
                                return RADICAL;
                              }
"++"                          {
                                //printf("%s is a INCREMENT\n", yytext);
                                return INCREMENT;
                              }
"--"                          {
                                //printf("%s is a DECREMENT\n", yytext);
                                return DECREMENT;
                              }


  /* Reglas para los operadores bit a bit */
"&"                           {
                                //printf("%s is a AND_BIT\n", yytext);
                                return AND_BIT;
                              }
"|"                           {
                                //printf("%s is a OR_BIT\n", yytext);
                                return OR_BIT;
                              }
"^"                           {
                                //printf("%s is a XOR_BIT\n", yytext);
                                return XOR_BIT;
                              }
"<<"                          {
                                //printf("%s is a LEFT_SHIFT\n", yytext);
                                return LEFT_SHIFT;
                              }
">>"                          {
                                //printf("%s is a RIGHT_SHIFT\n", yytext);
                                return RIGHT_SHIFT;
                              }


   /* Reglas para los operadores lógicos */
"&&"                          {
                                //printf("%s is a AND\n", yytext);
                                return AND;
                              }
"||"                          {
                                //printf("%s is a OR\n", yytext);
                                return OR;
                              }
"!"                           {
                                //printf("%s is a NOT\n", yytext);
                                return NOT;
                              }
"=="                          {
                                //printf("%s is a EQUALS\n", yytext);
                                return EQUALS;
                              }
"!="                          {
                                //printf("%s is a NOT_EQUALS\n", yytext);
                                return NOT_EQUALS;
                              }
">"                           {
                                //printf("%s is a GREATER\n", yytext);
                                return GREATER;
                              }
">="                          {
                                //printf("%s is a GREATER_EQUALS\n", yytext);
                                return GREATER_EQUALS;
                              }
"<"                           {
                                //printf("%s is a LESS\n", yytext);
                                return LESS;
                              }
"<="                          {
                                //printf("%s is a LESS_EQUALS\n", yytext);
                                return LESS_EQUALS;
                              }


   /* Reglas para los operadores de array */
"U"                           {
                                //printf("%s is an UNION\n", yytext);
                                return UNION;
                              }
"D"                           {
                                //printf("%s is a DIFFERENCE\n", yytext);
                                return DIFFERENCE;
                              }
"I"                           {
                                //printf("%s is an INTERSECTION\n", yytext);
                                return INTERSECTION;
                              }


   /* Expresiones regulares para estructuras de control y bucles */
{if}                          {
                                //printf("%s is an IF_CLAUSE\n", yytext);
                                return IF_CLAUSE;
                              }
{header_end}                  {
                                //printf("%s is an HEADER_END\n", yytext);
                                return HEADER_END;
                              }
{for_while}                   {
                                //printf("%s is an FOR_WHILE_CLAUSE\n", yytext);
                                return FOR_WHILE_CLAUSE;
                              }
{else_if_for_while}           {
                                //printf("%s is an ELSE_IF_FOR_WHILE_CLAUSE\n", yytext);
                                return ELSE_IF_FOR_WHILE_CLAUSE;
                              }



   /* Expresiones regulares delimitadoras */
"\["                          {
                                //printf("%s is an SQUARE_BRACKET_OPEN\n", yytext);
                                return SQUARE_BRACKET_OPEN;
                              }
"\]"                          {
                                //printf("%s is an SQUARE_BRACKET_CLOSE\n", yytext);
                                return SQUARE_BRACKET_CLOSE;

                              }
"\{"                          {
                                //printf("%s is an CURLY_BRACKET_OPEN\n", yytext);
                                return CURLY_BRACKET_OPEN;
                              }
"\}"                          {
                                //printf("%s is an CURLY_BRACKET_CLOSE\n", yytext);
                                return CURLY_BRACKET_CLOSE;
                              }
","                           {
                                //printf("%s is an ELEM_SEPARATOR\n", yytext);
                                return ELEM_SEPARATOR;
                              }
"\("                          {
                                //printf("%s is an PARETHESES_OPEN\n", yytext);
                                return PARETHESES_OPEN;
                              }
"\)"                          {
                                //printf("%s is an PARETHESES_CLOSE\n", yytext);
                                return PARETHESES_CLOSE;
                              }


  /* Identificador */
{id}                          {
                                //printf("%s is a ID\n", yytext);
                                return ID;
                              }


  /* Reglas para los caracteres */
\'                            {
                                 BEGIN(CHAR_STATE);
                                 //printf("CHAR_STATE_START\n");
                                 //printf("%s is a CHAR_QUOTE\n", yytext);
                                 return CHAR_QUOTE;
                              }
<CHAR_STATE>{char_val}        {
                                memcpy(yylval.character, yytext, sizeof(yytext));
                                //printf("%s is a CHAR_VAL\n", yylval.character);
                                return CHAR_VAL;
                              }
<CHAR_STATE>\'                 {
                                //printf("%s is a CHAR_QUOTE\n", yytext);
                                //printf("CHAR_STATE_END\n");
                                BEGIN(INITIAL);
                                return CHAR_QUOTE;
                              }

  /* Reglas para los strings */
\"                            {
                                BEGIN(STRING_STATE);
                                //printf("STRING_STATE_START\n");
                                //printf("%s is a STRING_QUOTE\n", yytext);
                                return STRING_QUOTE;
                              }
<STRING_STATE>{string_val}    {
                                memcpy(yylval.string, yytext, sizeof(yytext));
                                //printf("%s is a STRING_VAL\n", yylval.string);
                                return STRING_VAL;
                              }
<STRING_STATE>\"              {
                                //printf("%s is a STRING_QUOTE\n", yytext);
                                //printf("STRING_STATE_END\n");
                                BEGIN(INITIAL);
                                return STRING_QUOTE;
                              }


  /* Reglas para los comentarios */
\.\.                          {
                                BEGIN(COMMENT_LINE);
                                //printf("COMMENT_LINE_START\n");
                              }
<COMMENT_LINE>.+              {
                                //printf("THIS IS A COMMENT_LINE\n");
                              }
<COMMENT_LINE>\n              {
                                //printf("COMMENT_LINE_END\n");
                                yylineno++;
                                BEGIN(INITIAL);
                              }
<COMMENT_LINE><<EOF>>         /* Do error */


",\."                         {
                                BEGIN(COMMENT_BLOCK);
                                //printf("COMMENT_BLOCK_START\n");
                              }
<COMMENT_BLOCK>"\.,"          {
                                //printf("COMMENT_BLOCK_END\n");
                                BEGIN(INITIAL);
                              }
<COMMENT_BLOCK>[^\n]
<COMMENT_BLOCK>\n             {
                                yylineno++;
                              }
<COMMENT_BLOCK><<EOF>>        /* Do error */


"\t"+                          {
                                printf("Esto es un tabulado\n");
                              }

   /* Unknowns & errors */
.                             {
                                printf("<%s> is an unknown\n", yytext);
                              }

%%

/* Funciones y declaraciones auxiliares */

/*void countContextLevel(char* pattern) {
  level += countTabs(pattern);
  level += countSpaces(pattern);
}*/

int countTabs(char* pattern) {
  int i = 0;
  int total = 0;
  while (pattern[i] != '\0') {
    if (pattern[i] == '\t') total++;
    i++;
  }
  return total;
}

int countSpaces(char* pattern) {
  int i = 0;
  int numSpaces = 0;
  int total = 0;
  while (pattern[i] != '\0') {
    if (pattern[i] == ' ') numSpaces++;
    if ((numSpaces % 4) == 0 && numSpaces > 0) total++;
    i++;
  }
  return total;
}
