#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "AbstractSyntaxTreePack.hpp"

namespace wic
{
    class CodeGenerator;
    class ASTNode;
    class ASTMainNode;

    class AbstractSyntaxTree
    {
    private:
        ASTMainNode* root;

    public:
        AbstractSyntaxTree();
        AbstractSyntaxTree(ASTMainNode* root);
        ~AbstractSyntaxTree() = default;

        ASTNode* tree_build(ASTNode*);
        ASTNode* get_root();
        void print();
        void to_code(CodeGenerator*);
    };
}

#endif
