#include <queue>

#include "AbstractSyntaxTree.hpp"
#include "node/node-subtypes/clause-node/ASTClauseNode.hpp"
#include "node/node-subtypes/operator-node/ASTOperatorNode.hpp"
#include "node/node-subtypes/operator-node/ASTRelationalNode.hpp"
#include "node/node-subtypes/structural-node/ASTStructuralNode.hpp"
#include "node/node-subtypes/symbol-table-node/ASTSymbolTableNode.hpp"
#include "../code-generator/CodeGenerator.hpp"

extern int yylineno;
extern int level;
extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

namespace wic
{
    ASTNode* AbstractSyntaxTree::tree_build(ASTNode *node)
    {
        std::cout << "TREE BUILD" << std::endl;
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

            switch (curr->get_node_type())
            {
                case CALL:
                    break;
                case MAIN:
                    while (curr != nullptr)
                    {
                        nodes.push(curr->next);
                        curr = curr->next;
                    }
                    break;
                case SUM:
                case SUB:
                case PROD:
                case DIV:
                case MOD:
                case POWER:
                case RADICAL:
                case ASSIGN:
                case GE:
                case GT:
                case EQ:
                case NEQ:
                case LE:
                case LT:
                case AND:
                case OR:
                    nodes.push(reinterpret_cast<ASTOperatorNode *>(curr)->op1);
                    nodes.push(reinterpret_cast<ASTOperatorNode *>(curr)->op2);
                    break;
                case NOT:
                    nodes.push(reinterpret_cast<ASTOperatorNode *>(curr)->op1);
                    break;
                case IF:
                    {
                        ASTRelationalNode* cond = reinterpret_cast<ASTClauseNode *>(curr)->get_cond();
                        ASTNode* body = reinterpret_cast<ASTClauseNode *>(curr)->get_body();

                        while (curr != nullptr) {
                            nodes.push(reinterpret_cast<ASTNode *>(cond));
                            nodes.push(body);
                            curr = curr->next;
                        }
                        nodes.push(reinterpret_cast<ASTClauseNode *>(curr)->get_else_body());
                    }
                    break;
                case WHILE:
                case FOR:
                default:
                    break;
            }
        }
    }

    void AbstractSyntaxTree::to_code(CodeGenerator* cg)
    {
        root->to_code(CODE, cg);
    }
}