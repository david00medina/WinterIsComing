#include "utils/termcolor.hpp"
#include "symbol-table/SymbolTable.hpp"
#include "ast/AbstractSyntaxTree.hpp"
#include "code-generator/CodeGenerator.hpp"
#include "ast/node/ASTNode.hpp"
#include "ast/node/node-subtypes/leaf-node/ASTLeafNode.hpp"
#include "ast/node/node-subtypes/clause-node/ASTClauseNode.hpp"
#include "ast/node/node-subtypes/operator-node/ASTOperatorNode.hpp"
#include "ast/node/node-subtypes/operator-node/ASTRelationalNode.hpp"
#include "ast/node/node-subtypes/operator-node/ASTArithmeticNode.hpp"
#include "ast/node/node-subtypes/structural-node/ASTStructuralNode.hpp"
#include "ast/node/node-subtypes/symbol-table-node/ASTSymbolTableNode.hpp"


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
    }

    if (cg == nullptr) cg = new wic::CodeGenerator();

    int result = yyparse();


    //int result = 1;
    //while(1) { /* TODO: Quitar este bucle cuando entreguemos el trabajo */
        /*int result = yyparse();

        if (result == 0) {
            std::cout << "[OK] The input is valid." << std::endl;
        } else {
            std::cout << "[FAIL] The input is invalid." << std::endl;
        }
    }*/
    delete cg;
    return result;
}


/* Funciones auxiliares */
void yyerror(char const *x) {
    printf("[!] Error :  %s\n", x);
}
