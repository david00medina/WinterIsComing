#include "AbstractSyntaxTree.hpp"

namespace wic
{
    ASTNode * AbstractSyntaxTree::tree_create(std::string id, node_type node_t, data_type data_t, data_value data_v,
                                              ASTNode* ptr1, ASTNode** ptr2, ASTNode* ptr3, ASTNode** args,
                                              GSymbolTable* gst, SSymbolTable* sst, LSymbolTable* lst)

    {
        node->id = id;
        node->node_t = node_t;
        node->data_t = data_t;
        node->data_v = data_v;
        node->ptr1 = ptr1;
        node->ptr2 = ptr2;
        node->ptr3 = ptr3;
        node->args = args;
        node->gst = gst;
        node->sst = sst;
        node->lst = lst;

        return node;
    }


    void AbstractSyntaxTree::connect(ASTNode* ptr1, ASTNode** ptr2, ASTNode* ptr3)
    {
        node->ptr1 = ptr1;
        node->ptr2 = ptr2;
        node->ptr3 = ptr3;
    }

    void AbstractSyntaxTree::add_args(ASTNode** args)
    {
        node->args = args;
    }

    void AbstractSyntaxTree::toCode()
    {
        // TODO: Aquí generaremos todo el código en ensamblador a partir del AST
    }
}