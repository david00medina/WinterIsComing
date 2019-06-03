#include <iostream>
#include "symbol-table/SymbolTable.hpp"
#include "symbol-table/SymbolTablePack.hpp"
#include "code-generator/CodeGenerator.hpp"


extern int yylex();
extern int yyparse(void);
extern void yyerror(const char *);
extern FILE *yyin;
extern int yylineno;

int main(int argc, char const **argv) {
    wic::variable var;
    var.type = wic::ARRAY_INT;
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

    wic::CodeGenerator cg;

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return(1);
        }

        const char* arg;
        if (argc == 3) arg = argv[2];
        else arg = argv[0];

        const std::string mid_code_path(arg);
        cg.set_path(mid_code_path);

        cg.init();


        wic::ASTNode node1;
        std::string n1("node1");
        node1.id = n1;
        node1.data_v.str_val = (char*)"rojo";

        wic::ASTNode node2;
        std::string n2("node2");
        node2.id = n2;
        node2.data_v.int_val = 45;

        wic::ASTNode node3;
        std::string n3("node3");
        node3.id = n3;
        node3.data_v.char_val = '\n';

        wic::ASTNode node4;
        std::string n4("node4");
        node4.id = n4;
        node4.data_v.real_val = 5.457f;

        wic::ASTNode node5;
        std::string n5("node5");
        node5.id = n5;
        node5.data_v.bool_val = true;

        cg.print("caballo loco %s loquisimo, %d, %c, %r, %b", 4, node1, node2, node3, node4, node5);
        cg.end();
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
    printf("[!] Error :  %s\n", x);
}
