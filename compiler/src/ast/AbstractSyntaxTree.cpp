#include <queue>

#include "AbstractSyntaxTree.hpp"
#include "nodes/ASTNode.hpp"
#include "nodes/ASTOperatorNode.hpp"
#include "nodes/ASTSymbolTableNode.hpp"
#include "nodes/ASTLeafNode.hpp"

extern int yylineno;
extern int level;
extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;
namespace wic
{
    ASTNode* AbstractSyntaxTree::tree_build(ASTNode *node)
    {
        root = node;
        return root;
    }

    ASTNode* AbstractSyntaxTree::tree_build(void* elem1, void* elem2){
        entry_data* entry_d = reinterpret_cast<entry_data *>(elem1);
        ASTIDNode* node = reinterpret_cast<ASTIDNode *>(elem2);
        node->set_data_type(entry_d->var.type);

        if (entry_d->var.global)
        {
            gst->insert(node->get_id(), *entry_d, yylineno, level);
            node->set_global_entry(gst->lookup(node->get_id()));
        }
        else if (entry_d->var.local)
        {
            lst->insert(node->get_id(), *entry_d, yylineno, level);
            node->set_local_entry(lst->lookup(node->get_id()));
        }
        else if (entry_d->var.stat)
        {
            sst->insert(node->get_id(), *entry_d, yylineno, level);
            node->set_static_entry(sst->lookup(node->get_id()));
        }

        return tree_build(reinterpret_cast<ASTNode*>(node));
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