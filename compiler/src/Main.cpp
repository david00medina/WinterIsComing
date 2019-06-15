#include <iostream>
#include "ast/AbstractSyntaxTree.hpp"
#include "symbol-table/SymbolTable.hpp"
#include "code-generator/CodeGenerator.hpp"


extern int yylex();
extern int yyparse(void);
extern void yyerror(const char*);
extern FILE *yyin;
extern int yylineno;

extern wic::SSymbolTable* gst;
extern wic::AbstractSyntaxTree* ast;

int main(int argc, char const **argv) {
    ast = new wic::AbstractSyntaxTree(new wic::ASTNode());
    wic::entry_data entry_d;
    entry_d.var.type = wic::ARRAY_INT;
    entry_d.var.offset = 0;
    entry_d.var.size = 4;

    wic::TableEntry te("hola", entry_d, 2, 0);
    te.print();
    std::cout << std::endl;

    wic::LSymbolTable lst;
    lst.insert("test", entry_d, 1, 0);
    entry_d.var.type = wic::INT;
    lst.insert("test", entry_d, 2, 1);
    lst.show("test");
    entry_d.var.type = wic::REAL;
    lst.insert("test", entry_d, 3, 3);
    lst.show("test");

    lst.erase("test");
    lst.show("test");

    lst.modify("test", entry_d, 0, 0);
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
        std::string n1 = "node1";
        wic::data_value d1;
        d1.str_val = (char*)"rojo";
        wic::ASTNode node1(&n1, wic::LEAF, wic::STRING, &d1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

        std::string n2 = "node2";
        wic::data_value d2;
        d2.int_val = 45;
        wic::ASTNode node2(&n2, wic::LEAF, wic::INT, &d2, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

        std::string n3 = "node3";
        wic::data_value d3;
        d3.char_val = '\n';
        wic::ASTNode node3(&n3, wic::LEAF, wic::STRING, &d3, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

        std::string n4 = "node4";
        wic::data_value d4;
        d4.real_val = 5.457f;
        wic::ASTNode node4(&n4, wic::LEAF, wic::STRING, &d4, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

        std::string n5 = "node5";
        wic::data_value d5;
        d5.bool_val = true;
        wic::ASTNode node5(&n5, wic::LEAF, wic::STRING, &d5, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

        cg.print("caballo loco %s loquisimo, %d, %c, %r, %b", 4, node1, node2, node3, node4, node5);
        cg.exit();
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
