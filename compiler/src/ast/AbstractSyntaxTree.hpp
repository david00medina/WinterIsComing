#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "AbstractSyntaxTreePack.hpp"

namespace wic
{
    class CodeGenerator;
    class ASTNode;
    class ASTMainNode;
    class ASTFunctionNode;

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
        void function_build(std::string, entry_data);
        ASTFunctionNode* lookup_function(std::string);
        ASTFunctionNode* get_last_function();
        void print();
        void to_code(CodeGenerator*);
    };
}

#endif
