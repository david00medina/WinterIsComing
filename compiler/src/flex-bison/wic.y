%{

    /* Declaraciones */

    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "../symbol-table/SymbolTable.hpp"
    #include "../ast/AbstractSyntaxTree.hpp"

    int yylex(void);
    void yyerror(char const *);

    wic::GSymbolTable* gst;
    wic::AbstractSyntaxTree* ast;

    wic::data_type promote_to_float(wic::ASTNode*, wic::ASTNode*);
%}

/* Definición de tipo de valores */
%define api.value.type { void * }

/* Declaración de tokens */

/* Tokens para las palabras reservadas */
%token NEW CONTINUE BREAK RETURN FUN GLOBAL STATIC

/* Tokens de valores de datos */
%token INT_VAL REAL_VAL BOOL_VAL CHAR_VAL STRING_VAL


/* Tokens de tipo de dato */
%token INT_TYPE REAL_TYPE BOOL_TYPE CHAR_TYPE VOID

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
%token ID

/* Tipos de reglas  */

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
    | expr                                        {
                                                    printf("Instrucción EXPR\n");
                                                    ast->print();
                                                    $$ = ast->get_root();
                                                  }
    | fun_init                                    { printf("Instrucción FUN (declaration)\n"); }
    | fun_call                                    { printf("Instrucción FUN (call)\n"); }

comma_exp_init: comma_exp_init ELEM_SEPARATOR comma_exp_init     { printf("Expresión (,)\n"); }
    | data_type ID                                { printf("Expresión (,%s %s,)\n"); }
    | /* empty */

comma_exp: comma_exp ELEM_SEPARATOR comma_exp     { printf("Función llamada (,)\n"); }
    | factor                                      { printf("Función llamada (factor)\n"); }
    | data_value                                  { printf("Función llamada (valor)\n"); }
    | ID                                          { printf("Función llamada (variable)\n"); }
    | expr                                        { printf("Función llamada (término)\n"); $$ = $1; }

fun_init: FUN data_type ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
     {
        wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($3);
        printf("Función (nombre=%s)\n", node->get_id());
     }
    | FUN VOID ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      {
        wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($3);
        printf("Función (nombre=%s)\n", node->get_id());
      }
    | FUN data_type ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE END_OF_INSTR { printf("Función declaración void\n"); }
    | FUN VOID ID PARETHESES_OPEN comma_exp_init PARETHESES_CLOSE END_OF_INSTR { printf("Función declaración\n"); }

fun_call: ID PARETHESES_OPEN comma_exp PARETHESES_CLOSE         { printf("Función llamada PRINT\n"); }

while_instr: expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      while_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG

while_middle_block: while_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | /* empty */

for_instr: expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      for_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      ELSE_IF_FOR_WHILE_CLAUSE FOR_WHILE_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG

for_middle_block: for_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr FOR_WHILE_CLAUSE expr HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | /* empty */

if_instr: expr IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      if_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
      ELSE_IF_FOR_WHILE_CLAUSE IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | expr IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG

if_middle_block: if_middle_block
      ELSE_IF_FOR_WHILE_CLAUSE expr IF_CLAUSE HEADER_END END_OF_INSTR
      OPEN_CONTEXT_TAG input CLOSE_CONTEXT_TAG
    | /* empty */

array_access: SQUARE_BRACKET_OPEN INT_VAL SQUARE_BRACKET_CLOSE

expr: ID ASSIGN term                              { printf("Expresión (=)\n"); }
    | expr SUM term                               {
                                                    std::cout << "Expresión (Suma)" << std::endl;

                                                    wic::ASTNode* expr = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(expr, term);

                                                    wic::ASTNode* sum = new wic::ASTNode(nullptr, wic::SUM, data_t, nullptr, expr, term, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(sum);
                                                  }
    | expr SUBSTRACT term                         {
                                                    std::cout << "Expresión (Resta)" << std::endl;

                                                    wic::ASTNode* expr = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(expr, term);

                                                    wic::ASTNode* sub = new wic::ASTNode(nullptr, wic::SUB, data_t, nullptr, expr, term, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(sub);
                                                  }
    | INCREMENT ID                                {
                                                    std::cout << "Expresión (++ID)" << std::endl;
                                                  }
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
    | term                                        { printf("Expresión\n"); $$ = $1; }
    | data_vector                                 { printf("Expresión (vector)\n"); }

term: term PRODUCT power                          {
                                                    std::cout << "Expresión (Producto)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(term, power);

                                                    wic::ASTNode* prod = new wic::ASTNode(nullptr, wic::PROD, data_t, nullptr, term, power, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(prod);
                                                  }
    | term DIVIDE power                           {
                                                    std::cout << "Expresión (División)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(term, power);

                                                    wic::ASTNode* div = new wic::ASTNode(nullptr, wic::DIV, data_t, nullptr, term, power, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(div);
                                                  }
    | term MODULUS power                          {
                                                    std::cout << "Expresión (Módulo)" << std::endl;

                                                    wic::ASTNode* term = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(term, power);

                                                    wic::ASTNode* mod = new wic::ASTNode(nullptr, wic::MOD, data_t, nullptr, term, power, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(mod);
                                                  }
    | power                                       { printf("Término\n"); $$ = $1; }
    | ID array_access                             { printf("Término (VectorVal)");}

power: power RADICAL factor                       {
                                                    std::cout << "Expresión (Radical)" << std::endl;

                                                    wic::ASTNode* power = reinterpret_cast<wic::ASTNode *>($1);
                                                    wic::ASTNode* factor = reinterpret_cast<wic::ASTNode *>($3);

                                                    wic::data_type data_t = promote_to_float(power, factor);

                                                    wic::ASTNode* radical = new wic::ASTNode(nullptr, wic::RADICAL, data_t, nullptr, power, factor, nullptr, nullptr, nullptr, nullptr);

                                                    $$ = ast->tree_build(radical);
                                                  }
    | power POWER factor                          { printf("Potencia/Raiz (Potencia)"); $$ = $1; }
    | factor                                      { $$ = reinterpret_cast<void *>($1); }

factor: PARETHESES_OPEN expr PARETHESES_CLOSE     { printf("Factor (Expresión parentesis)\n"); $$ = $2; }
    | data_value                                  { printf("Factor (DATA_VALUE)\n"); $$ = $1; }
    | ID                                          {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($1);
                                                    std::cout << "Factor : ID (name=" << node->get_id() << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }

data_value: INT_VAL                               {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($1);
                                                    std::cout << "Factor : INT(value=" << node->get_data_value().int_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | SUBSTRACT INT_VAL                           {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($2);
                                                    int val = -node->get_data_value().int_val;
                                                    node->set_data_value((void*)&val);
                                                    std::cout << "Factor: NEG_INT(value=" << node->get_data_value().int_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | REAL_VAL                                    {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($1);
                                                    std::cout << "Factor : REAL(value=" << node->get_data_value().real_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | SUBSTRACT REAL_VAL                          {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($2);
                                                    float val = -node->get_data_value().real_val;
                                                    node->set_data_value((void*)&val);
                                                    std::cout << "Factor: NEG_REAL(value=" << node->get_data_value().real_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | BOOL_VAL                                    {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($1);
                                                    std::cout << "Factor : BOOL(value=" << node->get_data_value().bool_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | CHAR_QUOTE CHAR_VAL CHAR_QUOTE              {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($2);
                                                    std::cout << "Factor : CHAR(value=" << node->get_data_value().char_val << ",ascii="
                                                    << (int)node->get_data_value().char_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }
    | STRING_QUOTE STRING_VAL STRING_QUOTE        {
                                                    wic::ASTNode* node = reinterpret_cast<wic::ASTNode *>($2);
                                                    std::cout << "Factor : STRING(value=" << node->get_data_value().str_val << ")" << std::endl;
                                                    $$ = reinterpret_cast<void *>(node);
                                                  }

data_vector: CURLY_BRACKET_OPEN comma_exp CURLY_BRACKET_CLOSE        { printf("Factor (VECTOR)\n"); }

%%

wic::data_type promote_to_float(wic::ASTNode* elem1, wic::ASTNode* elem2)
{
    if (elem1->get_data_type() == wic::REAL && elem2->get_data_type() == wic::REAL) return wic::REAL;
    else if (elem1->get_data_type() == wic::INT && elem2->get_data_type() == wic::INT) return wic::INT;
    else if (elem1->get_data_type() == wic::INT && elem2->get_data_type() == wic::REAL)
    {
       float val = static_cast<float>(elem1->get_data_value().int_val);
       elem1->set_data_type(wic::REAL);
       elem1->set_data_value((void*)&val);
    }
    else if (elem1->get_data_type() == wic::REAL && elem2->get_data_type() == wic::INT)
    {
       float val = static_cast<float>(elem2->get_data_value().int_val);
       elem2->set_data_type(wic::REAL);
       elem2->set_data_value((void*)&val);
    }
    return wic::REAL;
}