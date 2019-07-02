#include "ASTClauseNode.hpp"
#include "../operator-node/ASTRelationalNode.hpp"
#include "../structural-node/ASTStructuralNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../../../../error-manager/ErrorManager.hpp"

namespace wic
{
    ASTClauseNode::ASTClauseNode(std::string name, node_type node_t, ASTRelationalNode *n1, ASTStructuralNode *n2)
        : ASTNode(name, node_t, UNKNOWN)
    {
        middle_block_depth = 0;
        cond = n1;
        body = n2;
    }

    ASTClauseNode::ASTClauseNode(std::string name, node_type node_t,
            ASTRelationalNode *n1, wic::ASTStructuralNode *n2, ASTStructuralNode *n3) : ASTNode(name, node_t, UNKNOWN)
    {
        middle_block_depth = 0;
        cond = n1;
        body = n2;
        else_body = n3;
    }

    ASTClauseNode::~ASTClauseNode()
    {
        delete cond;
        delete body;
        delete else_body;
    }

    void ASTClauseNode::check_error(std::string op)
    {
        /*ASTRelationalNode* curr = cond;

        if (curr == nullptr) ErrorManager::send(NOT_CLAUSE_BOOL_EXPR, op);

        while (curr != nullptr) {
            if (curr->get_data_type() != BOOL) ErrorManager::send(NOT_CLAUSE_BOOL_EXPR, op);
            curr = reinterpret_cast<ASTClauseNode *>(curr->next);
        }*/
    }

    void ASTClauseNode::add_middle_block(wic::ASTNode *node)
    {
        if (node == nullptr) return;

        bool if_locked = false;
        if (node->get_node_type() == IF)
        {
            middle_block_depth++;
            if_locked = true;
        }

        if (if_locked && node->get_node_type() != IF) int dummy = 0;// TODO: Send an error message (just else if allowed)

        add_node(reinterpret_cast<ASTNode *>(body), node);
    }

    ASTRelationalNode* ASTClauseNode::get_cond()
    {
        return cond;
    }

    ASTStructuralNode* ASTClauseNode::get_body()
    {
        return body;
    }

    ASTStructuralNode* ASTClauseNode::get_else_body()
    {
        return else_body;
    }

    ASTIfNode::ASTIfNode(ASTRelationalNode *n1, ASTStructuralNode *n2) : ASTClauseNode("IF", IF, n1, n2) {}

    ASTIfNode::ASTIfNode(ASTRelationalNode *n1, ASTStructuralNode *n2, ASTStructuralNode *n3) : ASTClauseNode("IF", IF, n1, n2, n3) {}

    cpu_registers ASTIfNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'IF\'");

        /*std::string middle_label = cg->get_label(CODE);
        std::string else_label = cg->get_label(CODE);
        std::string exit = cg->get_label(CODE);

        cg->push_scope();

        first_block(middle_label, exit, cg);
        if (body != nullptr && ptr2[0]->get_node_type() == IF) middle_block(middle_label, else_label, exit, cg);
        if (else_body != nullptr) last_block();

        cg->write_code_label(exit);

        cg->pop_scope(cg);*/
    }

    void ASTIfNode::first_block(std::string label, std::string exit, CodeGenerator *cg)
    {
        cpu_registers r1 = cond->to_code(cg);

        cpu_registers r_true = cg->get_reg();
        cg->write_code_section("movl", "$1", cg->translate_reg(r_true), "Set true register to 1");
        cg->write_code_section("cmpl", cg->translate_reg(r_true), cg->translate_reg(r1), "1st \'IF\' condition accomplished?");

        cg->free_reg(r_true);

        cg->write_code_section("jne", label);

        body->to_code(cg);

        cg->write_code_section("jmp", exit, "\'IF\' clause got to an end");
    }

    void ASTIfNode::middle_block(std::string label1, std::string else_label, std::string exit, CodeGenerator *cg)
    {
        /*ASTNode* curr_cond = cond;
        ASTNode* curr_body = body;

        bool first_time = true;
        std::string label2;

        while (curr_cond->next == nullptr && curr_body->next == nullptr)
        {
            curr_cond = curr_cond->next;
            curr_body = curr_body->next;

            if (!first_time)
            {
                label1 = label2;
            }

            cg->write_code_label(label1);

            cpu_registers r1 = curr_cond->to_code(cg);

            cpu_registers r_true = cg->get_reg();
            cg->write_code_section("movl", "$1", cg->translate_reg(r_true), "Set true register to 1");
            cg->write_code_section("cmpl", cg->translate_reg(r_true), cg->translate_reg(r1), "1st \'IF\' condition accomplished?");

            cg->free_reg(r_true);

            label2 = cg->get_label(CODE);

            cg->write_code_section("jne", label2);

            curr_body->to_code(cg);

            cg->write_code_section("jmp", exit, "\'IF\' clause got to an end");

            first_time = false;
        }

        cg->write_code_label(else_label);*/
    }

    void ASTIfNode::last_block(std::string label, std::string exit, CodeGenerator *cg)
    {
        cg->write_code_label(label);

        else_body->to_code(cg);
    }
}
