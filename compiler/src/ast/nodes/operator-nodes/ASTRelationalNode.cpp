#include "ASTRelationalNode.hpp"

namespace wic
{
    ASTRelationalNode::ASTRelationalNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(node_t, data_t, op1, op2) {}


    ASTRelationalNode::ASTRelationalNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op)
        : ASTOperatorNode(node_t, data_t, op, nullptr) {}

    cpu_registers ASTRelationalNode::compare(std::string instr, std::string symbol, wic::cpu_registers r1, wic::cpu_registers r2,
                                             wic::CodeGenerator *cg, bool is_float)
    {
        if (is_float) {
            std::string msg;

            if (node_t == LT || node_t == LE) msg = cg->translate_reg(r2) + " " + symbol + " " + cg->translate_reg(r1);
            else msg = cg->translate_reg(r1) + " " + symbol + " " + cg->translate_reg(r2);

            cg->write_code_section("ucomiss", cg->translate_reg(r2), cg->translate_reg(r1), msg);

            cg->free_reg(r1);
            cg->free_reg(r2);
            r1 = cg->get_reg();

            cg->write_code_section("set" + instr, cg->translate_low_reg(r1),
                    "Save comparison result to " + cg->translate_low_reg(r1));

            return r1;
        } else {
            cg->write_code_section("cmpl", cg->translate_reg(r2), cg->translate_reg(r1),
                    "Compare " + cg->translate_reg(r1) + " : " + cg->translate_reg(r2));
            cg->write_code_section("set" + instr, cg->translate_low_reg(r2),
                    cg->translate_low_reg(r2) + " = " + cg->translate_reg(r1) + " " + symbol + " " + cg->translate_reg(r2));
            cg->write_code_section("movzbl", cg->translate_low_reg(r2), cg->translate_reg(r2),
                    "Save comparison result to " + cg->translate_reg(r2));
            cg->free_reg(r1);
            return r2;
        }
    }

    cpu_registers ASTAndNode::do_and(wic::cpu_registers r2, wic::cpu_registers r1, CodeGenerator* cg)
    {
        std::string l1 = cg->get_label(CODE);
        std::string l2 = cg->get_label(CODE);
        std::string l3 = cg->get_label(CODE);

        cpu_registers r_true = cg->get_reg();

        cg->write_code_section("movl", "$1", cg->translate_reg(r_true), "Load true registry (" + cg->translate_reg(r_true) + ")");

        cg->write_code_section("cmpl", cg->translate_reg(r1), cg->translate_reg(r_true), "Is first operand true?");
        cg->write_code_section("je", l1, "Test passed!");
        cg->write_code_section("movl", "$0", cg->translate_reg(r1), "Failed test! (AND)");
        cg->write_code_section("jmp", l3, "Jump to the end of AND structure");
        cg->write_code_section(l1 + ":");
        cg->write_code_section("cmpl", cg->translate_reg(r2), cg->translate_reg(r_true), "Is second operand true?");
        cg->write_code_section("je", l2, "Test passed!");
        cg->write_code_section("movl", "$0", cg->translate_reg(r1), "Mark the it as failure");
        cg->write_code_section("jmp", l3, "Jump to the end of AND structure");
        cg->write_code_section(l2 + ":");
        cg->write_code_section("movl", "$1", cg->translate_reg(r1), "Successful test! (AND)");
        cg->write_code_section(l3 + ":");

        cg->free_reg(r_true);
        cg->free_reg(r2);

        return r1;
    }

    cpu_registers ASTRelationalNode::instr_reg2(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
    {
        data_t = BOOL;
        switch (node_t) {
            case GE:
                return compare("ge", ">=", r1, r2, cg, false);
            case GT:
                return compare("g", ">", r1, r2, cg, false);
            case LE:
                return compare("le", "<=", r1, r2, cg, false);
            case LT:
                return compare("l", "<", r1, r2, cg, false);
            case EQ:
                return compare("e", "==", r1, r2, cg, false);
            case NEQ:
                return compare("ne", "!=", r1, r2, cg, false);
            case NOT:
                cg->write_code_section("notl", cg->translate_reg(r1), cg->translate_low_reg(r1) + " = !" + cg->translate_reg(r1));
                cg->write_code_section("andl", "$1", cg->translate_reg(r1), "Save logical result to " + cg->translate_reg(r1));
                return r1;
            case AND:
                return do_and(r1, r2, cg);
            case OR:
                // TODO: Pendiente de terminar
                return NONE;
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg2_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        data_t = BOOL;
        switch (node_t) {
            case GE:
                return compare("nb", ">=", r1, r2, cg, true);
            case GT:
                return compare("a", ">", r1, r2, cg, true);
            case LE:
                return compare("nb", "<=", r2, r1, cg, true);
            case LT:
                return compare("a", "<", r2, r1, cg, true);
            case EQ:
                return compare("e", "==", r1, r2, cg, true);
            case NEQ:
                return compare("ne", "!=", r1, r2, cg, true);
            case NOT:
                r2 = cg->get_reg();
                cg->write_code_section("movd", cg->translate_reg(r1), cg->translate_reg(r2), "Pass " + cg->translate_reg(r1) + " to " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return instr_reg2(r2, NONE, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg3(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
    {
        data_t = BOOL;
        switch (node_t)
        {
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg3_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        data_t = BOOL;
        switch (node_t)
        {
            default:
                return NONE;
        }
    }

    ASTGreaterEqualNode::ASTGreaterEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(GE, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTGreaterEqualNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'>=\'");
        return operate(cg);
    }

    ASTGreaterNode::ASTGreaterNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTRelationalNode(GT, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTGreaterNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'>\'");
        return operate(cg);
    }

    ASTLessEqualNode::ASTLessEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(LE, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTLessEqualNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'<=\'");
        return operate(cg);
    }

    ASTLessNode::ASTLessNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(LT, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTLessNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'<\'");
        return operate(cg);
    }

    ASTEqualNode::ASTEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(EQ, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTEqualNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'==\'");
        return operate(cg);
    }

    ASTNotEqualNode::ASTNotEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(NEQ, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTNotEqualNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'!=\'");
        return operate(cg);
    }

    ASTNotNode::ASTNotNode(wic::ASTNode *op) : ASTRelationalNode(NOT, wic::UNKNOWN, op) {}

    cpu_registers ASTNotNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'!\'");
        return operate(cg);
    }

    ASTAndNode::ASTAndNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(AND, wic::BOOL, op1, op2) {}

    cpu_registers ASTAndNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'&&\'");
        return operate(cg);
    }
}
