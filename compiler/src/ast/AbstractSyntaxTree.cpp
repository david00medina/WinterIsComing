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
    AbstractSyntaxTree::AbstractSyntaxTree()
    {
        root = new ASTMainNode();
    }

    AbstractSyntaxTree::AbstractSyntaxTree(wic::ASTMainNode *root)
    {
        root = root;
    }

    ASTNode* AbstractSyntaxTree::tree_build(ASTNode *node)
    {
        root->get_body()->add_instr(node);
        return node;
    }

    ASTNode* AbstractSyntaxTree::get_root()
    {
        return root;
    }

    void AbstractSyntaxTree::function_build(std::string id, entry_data entry_d)
    {
        ASTFunctionNode* func = new ASTFunctionNode(id, entry_d);
        root->add_function(func);
    }

    ASTFunctionNode * AbstractSyntaxTree::lookup_function(std::string id)
    {
        return root->lookup_function(id);
    }

    ASTFunctionNode* AbstractSyntaxTree::get_last_function()
    {
        return root->get_last_function();
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