#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "AbstractSyntaxTreePack.hpp"

namespace wic
{
    class CodeGenerator;

    class ASTNode;

    class AbstractSyntaxTree
    {
    private:
        ASTNode* root;

    public:
        AbstractSyntaxTree() = default;
        AbstractSyntaxTree(ASTNode* root) : root(root) {};
        ~AbstractSyntaxTree() = default;

        ASTNode* tree_build(ASTNode*);
        ASTNode* tree_build(void*, void*);
        ASTNode* get_root();
        void print();
        void to_code(CodeGenerator*);
    };
}

#endif
