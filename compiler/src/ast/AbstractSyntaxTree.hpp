#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "nodes/ASTNode.hpp"
#include "nodes/ASTLeafNode.hpp"
#include "nodes/operator-nodes/ASTOperatorNode.hpp"
#include "nodes/ASTSymbolTableNode.hpp"

namespace wic
{
    class AbstractSyntaxTree
    {
    private:
        ASTNode* root;

    public:
        AbstractSyntaxTree() = default;
        AbstractSyntaxTree(ASTNode* root) : root(root) {};
        ~AbstractSyntaxTree() { delete root; };

        ASTNode* tree_build(ASTNode*);
        ASTNode* tree_build(void*, void*);
        ASTNode* get_root();
        void print();
        void toCode();
    };
}

#endif
