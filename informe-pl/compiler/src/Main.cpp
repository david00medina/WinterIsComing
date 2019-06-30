#include "utils/termcolor.hpp"
#include "ast/AbstractSyntaxTree.hpp"
#include "ast/nodes/ASTNode.hpp"
#include "ast/nodes/operator-nodes/ASTOperatorNode.hpp"
#include "ast/nodes/operator-nodes/ASTArithmeticNode.hpp"
#include "ast/nodes/operator-nodes/ASTRelationalNode.hpp"
#include "ast/nodes/ASTSymbolTableNode.hpp"
#include "ast/nodes/ASTLeafNode.hpp"
#include "symbol-table/SymbolTable.hpp"
#include "code-generator/CodeGenerator.hpp"


extern int yylex();
extern int yyparse(void);
extern void yyerror(const char*);
extern FILE *yyin;
extern int yylineno;
extern int yydebug;

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

extern wic::AbstractSyntaxTree* ast;

extern wic::CodeGenerator* cg;

int main(int argc, char const **argv) {
    // Turn debug mode ON (yydebug = 1)
    yydebug = 0;

    ast = new wic::AbstractSyntaxTree();
    gst = new wic::GSymbolTable();
    sst = new wic::SSymbolTable();
    lst = new wic::LSymbolTable();
    wic::entry_data entry_d;
    /*entry_d.var.type = wic::ARRAY_INT;
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

    lst.show(0);*/

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return(1);
        }

        const char* arg;
        if (argc == 3) arg = argv[2];
        else arg = argv[0];

        const std::string mid_code_path(arg);

        cg = new wic::CodeGenerator(mid_code_path);

        /*cg.init();
        wic::data_value d1;
        d1.str_val = (char*)"rojo";
        wic::ASTLeafNode node1(wic::STRING, &d1);

        wic::data_value d2;
        d2.int_val = 45;
        wic::ASTLeafNode node2(wic::INT, &d2);

        wic::data_value d3;
        d3.char_val = '\n';
        wic::ASTLeafNode node3(wic::STRING, &d3);

        wic::data_value d4;
        d4.real_val = 5.457f;
        wic::ASTLeafNode node4(wic::STRING, &d4);

        wic::data_value d5;
        d5.bool_val = true;
        wic::ASTLeafNode node5(wic::STRING, &d5);

        cg.print("caballo loco %s loquisimo, %d, %c, %r, %b", 4, node1, node2, node3, node4, node5);
        cg.exit();
        cg.end();*/
        wic::ASTMainNode* main = new wic::ASTMainNode();
        wic::data_value data_v;
        data_v.int_val = 12;
        wic::ASTLeafNode* int_node = new wic::ASTLeafNode(wic::INT, &data_v);
        data_v.int_val = -52;
        wic::ASTLeafNode* int_node2 = new wic::ASTLeafNode(wic::INT, &data_v);
        data_v.real_val = 500.18263f;
        wic::ASTLeafNode* float_node = new wic::ASTLeafNode(wic::REAL, &data_v);
        data_v.real_val = -453.4646f;
        wic::ASTLeafNode* float_node2 = new wic::ASTLeafNode(wic::REAL, &data_v);
        data_v.char_val = 'a';
        wic::ASTLeafNode* char_node = new wic::ASTLeafNode(wic::CHAR, &data_v);
        data_v.bool_val = false;
        wic::ASTLeafNode* bool_node = new wic::ASTLeafNode(wic::BOOL, &data_v);
        wic::ASTSumNode* sum = new wic::ASTSumNode(char_node, float_node);
        wic::ASTSubNode* sub = new wic::ASTSubNode(int_node, float_node);
        wic::ASTProdNode* prod = new wic::ASTProdNode(int_node, int_node);
        wic::ASTDivNode* div = new wic::ASTDivNode(int_node, int_node);
        wic::ASTModNode* mod = new wic::ASTModNode(float_node, int_node);
        wic::ASTGreaterEqualNode* ge = new wic::ASTGreaterEqualNode(int_node2, int_node);

        entry_d.var.type = wic::INT;
        entry_d.var.offset = -4;
        entry_d.var.size = 4;
        lst->insert("hola", entry_d, yylineno, 0);
        lst->insert("ohla", entry_d, yylineno, 0);
        lst->insert("hoal", entry_d, yylineno, 0);
        lst->insert("alho", entry_d, yylineno, 0);
        lst->show("ohla");
        lst->erase("ohla");
        lst->show("ohla");
        wic::TableEntry* entry = lst->lookup("hola");
        wic::ASTIDNode* id = new wic::ASTIDNode("hola", wic::INT, nullptr, nullptr, entry);
        wic::ASTAssignNode* assign = new wic::ASTAssignNode(wic::INT, id, int_node);


        main->to_code(cg);
        //int_node->to_code(cg);
        //float_node->to_code(cg);
        //char_node->to_code(cg);
        //bool_node->to_code(cg);
//        sum->to_code(cg);
        //sub->to_code(cg);
        //prod->to_code(cg);
        //div->to_code(cg);
        //mod->to_code(cg);
//        assign->to_code(cg);
        ge->to_code(cg);
    }

    if (cg == nullptr) cg == new wic::CodeGenerator();

    int result = yyparse();

    cg->exit();
    cg->end();

    delete cg;

    //int result = 1;
    //while(1) { /* TODO: Quitar este bucle cuando entreguemos el trabajo */
        /*int result = yyparse();

        if (result == 0) {
            std::cout << "[OK] The input is valid." << std::endl;
        } else {
            std::cout << "[FAIL] The input is invalid." << std::endl;
        }
    }*/
    return result;
}


/* Funciones auxiliares */
void yyerror(char const *x) {
    printf("[!] Error :  %s\n", x);
}
