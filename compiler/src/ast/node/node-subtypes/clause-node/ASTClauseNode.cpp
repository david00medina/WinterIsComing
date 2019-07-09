#include "ASTClauseNode.hpp"
#include "../operator-node/ASTRelationalNode.hpp"
#include "../structural-node/ASTStructuralNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../../../../error-manager/ErrorManager.hpp"

namespace wic
{
    ASTClauseNode::ASTClauseNode(const wic::ASTClauseNode &n)
    {
        set_cond(n.cond);
        body = n.body;
        else_body = n.else_body;
        else_l = n.else_l;
        exit_l = n.exit_l;
        next = n.next;
    }

    ASTClauseNode::ASTClauseNode(std::string name, node_type node_t, ASTRelationalNode *n1, ASTNode *n2)
        : ASTNode(name, node_t, UNKNOWN)
    {
        set_cond(n1);
        body = n2;
    }

    ASTClauseNode::ASTClauseNode(std::string name, node_type node_t,
            ASTRelationalNode *n1, wic::ASTNode *n2, ASTNode *n3) : ASTNode(name, node_t, UNKNOWN)
    {
        set_cond(n1);
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
        ASTRelationalNode* curr = cond;

        if (curr == nullptr) ErrorManager::send(MISSING_CLAUSE_BOOL_EXPR,op);

        while (curr != nullptr) {
            if (curr->get_data_type() != BOOL) ErrorManager::send(MISSING_CLAUSE_BOOL_EXPR, op);
            curr = reinterpret_cast<ASTRelationalNode *>(curr->next);
        }
    }

    void ASTClauseNode::add_mid_block(wic::ASTClauseNode *block)
    {
        std::string op;
        switch (get_node_type())
        {
            case IF:
                op = "\'IF\'";
                break;
            case WHILE:
                op = "\'WHILE\'";
                break;
            case FOR:
                op = "\'FOR\'";
                break;
            default:
                break;
        }

        if (else_body != nullptr && block->else_body != nullptr) ErrorManager::send(MULTIPLE_ELSE, op);

        if (next == nullptr)
        {
            next = block;
            return;
        }

        ASTIfNode* curr = reinterpret_cast<ASTIfNode *>(next);
        while (curr != nullptr)
        {
            curr = reinterpret_cast<ASTIfNode *>(curr->next);
        }
    }

    void ASTClauseNode::set_cond(wic::ASTNode *cond)
    {
        std::string op;
        switch (get_node_type())
        {
            case IF:
                op = "\'IF\'";
                break;
            case WHILE:
                op = "\'WHILE\'";
                break;
            case FOR:
                op = "\'FOR\'";
                break;
            default:
                break;
        }

        if (cond == nullptr || cond->get_data_type() != BOOL) ErrorManager::send(MISSING_CLAUSE_BOOL_EXPR, op);

        this->cond = reinterpret_cast<ASTRelationalNode *>(cond);
    }

    void ASTClauseNode::set_body(wic::ASTNode *instr)
    {
        body = instr;
    }

    void ASTClauseNode::set_else_body(wic::ASTNode *instr)
    {
        else_body = instr;
    }

    ASTIfNode::ASTIfNode(const wic::ASTIfNode &n) : ASTClauseNode(n) {}

    ASTIfNode::ASTIfNode(ASTRelationalNode *n1, ASTNode *n2) : ASTClauseNode("IF", IF, n1, n2) {}

    ASTIfNode::ASTIfNode(ASTRelationalNode *n1, ASTNode *n2, ASTNode *n3) : ASTClauseNode("IF", IF, n1, n2, n3) {}

    cpu_registers ASTIfNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'IF\'");

        else_l = cg->get_label(section);
        exit_l = cg->get_label(section);

        write_condition(cond, section, cg);
        write_body(section, cg);

        if (else_body != nullptr) write_else_body(section, cg);

        cg->write_label(section, exit_l);
    }

    ASTRelationalNode* ASTClauseNode::get_cond()
    {
        return cond;
    }

    ASTNode* ASTClauseNode::get_body()
    {
        return body;
    }

    ASTNode* ASTClauseNode::get_else_body()
    {
        return else_body;
    }

    void ASTIfNode::write_condition(ASTRelationalNode* cond, section_enum section, CodeGenerator *cg)
    {
        cpu_registers r1 = cond->to_code(section, cg);

        cpu_registers r_true = cg->get_reg();
        cg->write(section, "c%c%s#c", "movl", "$1", cg->translate_reg(r_true), "Set true register to 1");
        cg->write(section, "c%s%s#c", "cmpl", cg->translate_reg(r_true), cg->translate_reg(r1), "\'IF\' condition accomplished?");

        cg->free_reg(r_true);
        cg->free_reg(r1);
    }

    void ASTIfNode::write_body(section_enum section, CodeGenerator *cg)
    {
        ASTIfNode* curr = new ASTIfNode(*this);
        std::string if_l;

        while (curr != nullptr) {
            if_l = cg->get_label(section);

            if (curr->next != nullptr) cg->write(section, "c%s#s", "jne", if_l, "Jump to next \'IF\' condition at " + if_l);
            else cg->write(section, "c%s#s", "jne", else_l, "Jump to \'ELSE\' at " + else_l);

            curr->body->to_code(section, cg);

            cg->write(section, "c%s#c", "jmp", exit_l, "\'IF\' clause got to an end");

            if (curr->next != nullptr) cg->write_label(section, if_l);

            curr = reinterpret_cast<ASTIfNode *>(curr->next);
            if (curr != nullptr) write_condition(curr->cond, section, cg);
        }
    }

    void ASTIfNode::write_else_body(section_enum section, CodeGenerator *cg)
    {
        cg->write_label(section, else_l);

        else_body->to_code(section, cg);
    }
}
