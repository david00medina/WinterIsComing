#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "nodes/ASTNode.hpp"
#include "nodes/ASTLeafNode.hpp"
#include "nodes/ASTOperatorNode.hpp"
#include "nodes/ASTSymbolTableNode.hpp"

namespace wic
{
    class AbstractSyntaxTree
    {
    private:
        ASTNode* root;

    public:
        AbstractSyntaxTree();
        AbstractSyntaxTree(ASTNode* root) : root(root) {};
        ~AbstractSyntaxTree() { delete root; };

        ASTNode* tree_build(ASTNode*);
        ASTNode* get_root();
        void print();
        void toCode();
    };
}

#endif
