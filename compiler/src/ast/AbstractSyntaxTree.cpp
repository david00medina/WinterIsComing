#include <queue>
#include "AbstractSyntaxTree.hpp"

namespace wic
{
    ASTNode* AbstractSyntaxTree::tree_build(ASTNode *node)
    {
        root = node;
        return root;
    }

    ASTNode* AbstractSyntaxTree::get_root()
    {
        return root;
    }

    void AbstractSyntaxTree::print()
    {
        std::queue<ASTNode *> nodes;
        nodes.push(root);

        while (!nodes.empty())
        {
            // Pop & print
            ASTNode* curr = nodes.front();
            curr->print();
            nodes.pop();

            // Expand left --> continue
            // Save to queue
            if (curr->ptr1 != nullptr) nodes.push(curr->ptr1);
            // Expand middle --> continue
            // Save to queue
            for (int i = 0; curr->ptr2[i] != nullptr; i++) nodes.push(curr->ptr2[i]);
            // Expand right --> continue
            // Save to queue
            if (curr->ptr3 != nullptr) nodes.push(curr->ptr3);
        }
    }

    void AbstractSyntaxTree::toCode()
    {
        // TODO: Aquí generaremos todo el código en ensamblador a partir del AST
    }
}