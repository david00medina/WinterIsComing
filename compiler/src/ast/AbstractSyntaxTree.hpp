#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include <iostream>
#include <string>
#include "ASTPack.hpp"

namespace wic
{
    class AbstractSyntaxTree
    {
    private:
        ASTNode* node;

    public:
        AbstractSyntaxTree() : node(nullptr) {};
        AbstractSyntaxTree(ASTNode* node) : node(node) {};
        ~AbstractSyntaxTree() { delete node; };

        ASTNode* tree_create(std::string, node_type, data_type, data_value, ASTNode*, ASTNode**, ASTNode*, ASTNode**,
                GSymbolTable*, SSymbolTable*, LSymbolTable*);
        void connect(ASTNode*, ASTNode**, ASTNode*);
        void add_args(ASTNode**);
        void toCode();
    };
}

#endif
