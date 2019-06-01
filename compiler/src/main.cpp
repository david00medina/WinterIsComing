#include <iostream>
#include "symbol-table/symbol.hpp"
#include "symbol-table/wic.table.hpp"


extern int yylex();
extern int yyparse(void);
extern void yyerror(const char *);
extern FILE *yyin;
extern int yylineno;

int main(int argc, char const **argv) {
    variable var;
    var.type = ARRAY_INT;
    var.offset = 4;
    var.addr = 1;

    wic::TableEntry te("hola", &var, nullptr, 2, 0);
    te.print();
    std::cout << std::endl;

    wic::LSymbolTable lst;
    lst.insert("test", &var, nullptr, 1, 0);
    lst.insert("test", &var, nullptr, 2, 1);
    lst.show("test");
    lst.insert("test", &var, nullptr, 3, 3);
    lst.show("test");

    lst.erase("test");
    lst.show("test");

    lst.modify("test", &var, nullptr, 0, 0);
    lst.show("test");

    wic::TableEntry* hey = lst.lookup("test");
    hey->print();

    lst.show(0);

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return(1);
        }
    }

    int result = 1;
    while(1) { /* TODO: Quitar este bucle cuando entreguemos el trabajo */
        int result = yyparse();

        if (result == 0) {
            std::cout << "[OK] The input is valid." << std::endl;
        } else {
            std::cout << "[FAIL] The input is invalid." << std::endl;
        }
    }
    return result;
}


/* Funciones auxiliares */
void yyerror(char const *x) {
    printf("[!] Error %s\n", x);
}
