%x COMMENT_LINE
%x CHECK_LVL
%{
  #include <string.h>
  int numlin = 1;
  int level = 0;
  int countSpaces(char* pattern);
  void error(char*, char);

  #define END_OF_INSTR 257
  #define RETURN 258
  #define BREAK 259
  #define INT_VAL 261
  #define REAL_VAL 262
  #define BOOL_VAL 263
  #define INT_TYPE 264
  #define REAL_TYPE 265
  #define BOOL_TYPE 266
  #define ASSIGN 267
  #define SUM 268
  #define SUBSTRACT 269
  #define PRODUCT 270
  #define DIVIDE 271
  #define AND 272
  #define OR 273
  #define NOT 274
  #define EQUALS 275
  #define NOT_EQUALS 276
  #define GREATER 277
  #define GREATER_EQUALS 278
  #define LESS 279
  #define LESS_EQUALS 280
  #define HEADER_END 281
  #define FOR_WHILE_CLAUSE 282
  #define SQUARE_BRACKET_OPEN 283
  #define SQUARE_BRACKET_CLOSE 284
  #define PARETHESES_OPEN 285
  #define PARETHESES_CLOSE 286
  #define ID 287
  #define OPEN_CONTEXT_TAG 288
  #define CLOSE_CONTEXT_TAG 289


%}

%option noyywrap

/* Definiciones regulares */

/* Expresiones regulares reutilizables */
letter                        [a-zA-Z]
digit                         [0-9]

/* Palabras reservadas */
new                           (new)
break                         (break)
return                        (return)

/* Valores segun el tipo de dato */
int_val                       {digit}+
real_val                      ({digit}+\.){digit}*|\.{digit}+
bool_val                      (true|false)

/* Tipos de dato */
int_type                      (int)
real_type                     (real)
bool_type                     (bool)

/* Expresiones regulares para estructuras de control y bucles */
for_while                     (\?){2}
header_end                    :

/* Expresiones regulares delimitadoras */

context_tag                   [ ]*
/* Identificador */
id                            {letter}({letter}|{digit})*


%%
<CHECK_LVL>\n?{context_tag}    {
                                //printf("Procesando... \n<%s>\n", yytext);
                                int level_change = countSpaces(yytext);
                                //printf("%d\n", level_change);

                                if (level < level_change) {
                                  level++;
                                  if (level != level_change) yyless(0);
                                  //printf("Level <OPEN_CONTEXT_TAG> : %d\n", level);
                                  return OPEN_CONTEXT_TAG;
                                } else if (level > level_change) {
                                   level--;
                                   if (level != level_change) yyless(0);
                                   //printf("Level <CLOSE_CONTEXT_TAG> : %d\n", level);
                                   return CLOSE_CONTEXT_TAG;
                                }
                                //printf("Level : %d\n", level);
                                BEGIN(INITIAL);
                              }
<CHECK_LVL><<EOF>>            {
                                if (level > 0) {
                                  level--;
                                  return CLOSE_CONTEXT_TAG;
                                } else return 0;
                              }
<CHECK_LVL>[^ \n]             {
                                //printf("Vamos para atrás\n");
                                BEGIN(INITIAL);
                                yyless(0);
                              }
<<EOF>>                       {
                                BEGIN(CHECK_LVL);
                              }



"\n"                          {
                                BEGIN(CHECK_LVL);
                                yyless(0);
                                //printf("%s is a END_OF_INSTR\n", yytext);
                                numlin++;
                                return END_OF_INSTR;
                              }
{break}                       {
                                //printf("%s is a BREAK\n", yytext);
                                return BREAK;
                              }
{return}                      {
                                //printf("%s is a RETURN\n", yytext);
                                return RETURN;
                              }
{int_val}                     {
                                //yylval.integer = atoi(yytext);
                                //printf("%d is a INT_VAL\n", yylval.integer);
                                //printf("%s is a INT_VAL\n", yytext);
                                return INT_VAL;
                              }

{real_val}                    {
                                //yylval.real = atof(yytext);
                                //printf("%f is a REAL_VAL\n", yylval.real);
                                //printf("%s is a REAL_VAL\n", yytext);
                                return REAL_VAL;
                              }
{bool_val}                    {
                                //if (strcmp("true", yytext) == 0) yylval.boolean = '\x01';
                                //else yylval.boolean = '\x00';
                                //printf("%d is a BOOL_VAL\n", yylval.boolean);
                                //printf("%s is a BOOL_VAL\n", yytext);
                                return BOOL_VAL;
                              }

{int_type}                    {
                                //printf("%s is a INT_TYPE\n", yytext);
                                //yylval.string = (char*)malloc(yyleng);
                                //strcpy(yylval.string, yytext);
                                return INT_TYPE;
                              }
{real_type}                   {
                                //printf("%s is a REAL_TYPE\n", yytext);
                                //yylval.string = (char*)malloc(yyleng);
                                //strcpy(yylval.string, yytext);
                                return REAL_TYPE;
                              }
{bool_type}                   {
                                //printf("%s is a BOOL_TYPE\n", yytext);
                                //yylval.string = (char*)malloc(yyleng);
                                //strcpy(yylval.string, yytext);
                                return BOOL_TYPE;
                              }


" "                           {
                              printf("");
                              }
"="                           {
                                //printf("%s is an ASSIGN\n", yytext);
                                return ASSIGN;
                              }

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

{header_end}                  {
                                //printf("%s is an HEADER_END\n", yytext);
                                return HEADER_END;
                              }
{for_while}                   {
                                //printf("%s is an FOR_WHILE_CLAUSE\n", yytext);
                                return FOR_WHILE_CLAUSE;
                              } 
"\["                          {
                                //printf("%s is an SQUARE_BRACKET_OPEN\n", yytext);
                                return SQUARE_BRACKET_OPEN;
                              }
"\]"                          {
                                //printf("%s is an SQUARE_BRACKET_CLOSE\n", yytext);
                                return SQUARE_BRACKET_CLOSE;
                              }   

"\("                          {
                                //printf("%s is an PARETHESES_OPEN\n", yytext);
                                return PARETHESES_OPEN;
                              }
"\)"                          {
                                //printf("%s is an PARETHESES_CLOSE\n", yytext);
                                return PARETHESES_CLOSE;
                              }  
{id}                          {
                                //printf("%s is a ID\n", yytext);
                                //yylval.string = (char*)malloc(yyleng);
                                //strcpy(yylval.string, yytext);
                                return ID;
                              }   
\.\.                          {
                                BEGIN(COMMENT_LINE);
                                //printf("COMMENT_LINE_START\n");
                              } 
<COMMENT_LINE>.+              {
                                //printf("THIS IS A COMMENT_LINE\n");
                              }
<COMMENT_LINE>\n              {
                                //printf("COMMENT_LINE_END\n");
                                //yylineno++;
                                BEGIN(INITIAL);
                                //confio en que no seas malvado y 
                                //se acabe el fichero inmediatamente 
                                //despues del comentario
                              }   
.                             {
                                error("caracter raro", yytext[0]);
                              }                          
%%

void error(char* mens, char character) {
  printf("Error lexico en linea %i: %s [%c]\n",numlin,mens, character);
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