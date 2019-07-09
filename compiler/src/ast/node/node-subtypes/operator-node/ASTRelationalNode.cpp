#include "ASTRelationalNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    ASTRelationalNode::ASTRelationalNode(std::string name, wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(name, node_t, data_t, op1, op2) {}


    ASTRelationalNode::ASTRelationalNode(std::string name, wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op)
        : ASTOperatorNode(name, node_t, data_t, op) {}

    cpu_registers ASTRelationalNode::compare(std::string instr, std::string symbol, wic::cpu_registers r1, wic::cpu_registers r2,
                                             section_enum section, wic::CodeGenerator *cg, bool is_float)
    {
        if (is_float) {
            std::string msg;

            if (node_t == LT || node_t == LE) msg = cg->translate_reg(r2) + " " + symbol + " " + cg->translate_reg(r1);
            else msg = cg->translate_reg(r1) + " " + symbol + " " + cg->translate_reg(r2);

            cg->write(section, "c%s%s#s", "ucomiss", cg->translate_reg(r2), cg->translate_reg(r1), msg);

            cg->free_reg(r1);
            cg->free_reg(r2);
            r1 = cg->get_reg();

            cg->write(section, "s%s#s", "set" + instr, cg->translate_low_reg(r1),
                    "Save comparison result to " + cg->translate_low_reg(r1));

            return r1;
        } else {
            cg->write(section, "c%s%s#s", "cmpl", cg->translate_reg(r2), cg->translate_reg(r1),
                    "Compare " + cg->translate_reg(r1) + " : " + cg->translate_reg(r2));
            cg->write(section, "s%s#s", "set" + instr, cg->translate_low_reg(r2),
                    cg->translate_low_reg(r2) + " = " + cg->translate_reg(r1) + " " + symbol + " " + cg->translate_reg(r2));
            cg->write(section, "c%s%s#s", "movzbl", cg->translate_low_reg(r2), cg->translate_reg(r2),
                    "Save comparison result to " + cg->translate_reg(r2));
            cg->free_reg(r1);
            return r2;
        }
    }

    cpu_registers ASTRelationalNode::do_and(wic::cpu_registers r1, wic::cpu_registers r2, section_enum section, CodeGenerator* cg)
    {
        std::string l1 = cg->get_label(section);
        std::string l2 = cg->get_label(section);
        std::string l3 = cg->get_label(section);

        cpu_registers r_true = cg->get_reg();

        cg->write(section, "c%c%s#s", "movl", "$1", cg->translate_reg(r_true), "Load true registry (" + cg->translate_reg(r_true) + ")");

        cg->write(section, "c%s%s#c", "cmpl", cg->translate_reg(r1), cg->translate_reg(r_true), "Is first operand true?");
        cg->write(section, "c%s#c", "je", l1, "1st test passed?");
        cg->write(section, "c%c%s#c", "movl", "$0", cg->translate_reg(r1), "Failed test! (AND)");
        cg->write(section, "c%s#c", "jmp", l3, "Jump to the end of AND structure");
        cg->write_label(section, l1);
        cg->write(section, "c%s%s#c", "cmpl", cg->translate_reg(r2), cg->translate_reg(r_true), "Is second operand true?");
        cg->write(section, "c%s#c", "je", l2, "2nd test passed?");
        cg->write(section, "c%c%s#c", "movl", "$0", cg->translate_reg(r1), "Failed test! (AND)");
        cg->write(section, "c%s#c", "jmp", l3, "Jump to the end of the AND structure");
        cg->write_label(section, l2);
        cg->write(section, "c%c%s#c", "movl", "$1", cg->translate_reg(r1), "Successful test! (AND)");
        cg->write_label(section, l3);

        cg->free_reg(r_true);
        cg->free_reg(r2);

        return r1;
    }

    cpu_registers ASTRelationalNode::do_or(wic::cpu_registers r1, wic::cpu_registers r2, section_enum section, wic::CodeGenerator *cg)
    {
        std::string l1 = cg->get_label(section);
        std::string l2 = cg->get_label(section);

        cpu_registers r_true = cg->get_reg();

        cg->write(section, "c%c%s#s", "movl", "$1", cg->translate_reg(r_true), "Load true registry (" + cg->translate_reg(r_true) + ")");

        cg->write(section, "c%s%s#c", "cmpl", cg->translate_reg(r1), cg->translate_reg(r_true), "Is first operand true?");
        cg->write(section, "c%s#c", "je", l1, "1st chance passed?");
        cg->write(section, "c%s%s#c", "cmpl", cg->translate_reg(r2), cg->translate_reg(r_true), "Is second operand true?");
        cg->write(section, "c%s#c", "je", l1, "2nd chance passed?");
        cg->write(section, "c%c%s#c", "movl", "$0", cg->translate_reg(r1), "Failed test! (OR)");
        cg->write(section, "c%s#c", "jmp", l2, "Jump to the end of the OR structure");
        cg->write_label(section, l1);
        cg->write(section, "c%c%s#c", "movl", "$1", cg->translate_reg(r1), "Successful test! (OR)");
        cg->write_label(section, l2);

        cg->free_reg(r_true);
        cg->free_reg(r2);

        return r1;
    }

    cpu_registers ASTRelationalNode::instr_reg2(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg)
    {
        data_t = BOOL;
        switch (node_t) {
            case GE:
                return compare("ge", ">=", r1, r2, section, cg, false);
            case GT:
                return compare("g", ">", r1, r2, section, cg, false);
            case LE:
                return compare("le", "<=", r1, r2, section, cg, false);
            case LT:
                return compare("l", "<", r1, r2, section, cg, false);
            case EQ:
                return compare("e", "==", r1, r2, section, cg, false);
            case NEQ:
                return compare("ne", "!=", r1, r2, section, cg, false);
            case NOT:
                cg->write(section, "c%s#s", "notl", cg->translate_reg(r1), cg->translate_low_reg(r1) + " = !" + cg->translate_reg(r1));
                cg->write(section, "c%c%s#s", "andl", "$1", cg->translate_reg(r1), "Save logical result to " + cg->translate_reg(r1));
                return r1;
            case AND:
                return do_and(r1, r2, section, cg);
            case OR:
                return do_or(r1, r2, section, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg2_float(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg){
        data_t = BOOL;
        switch (node_t) {
            case GE:
                return compare("nb", ">=", r1, r2, section, cg, true);
            case GT:
                return compare("a", ">", r1, r2, section, cg, true);
            case LE:
                return compare("nb", "<=", r2, r1, section, cg, true);
            case LT:
                return compare("a", "<", r2, r1, section, cg, true);
            case EQ:
                return compare("e", "==", r1, r2, section, cg, true);
            case NEQ:
                return compare("ne", "!=", r1, r2, section, cg, true);
            case NOT:
                r2 = cg->get_reg();
                cg->write(section, "c%s%s#s", "movd", cg->translate_reg(r1), cg->translate_reg(r2), "Pass " + cg->translate_reg(r1) + " to " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return instr_reg2(r2, NONE, section, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg3(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg)
    {
        data_t = BOOL;
        switch (node_t)
        {
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::instr_reg3_float(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg){
        data_t = BOOL;
        switch (node_t)
        {
            default:
                return NONE;
        }
    }

    ASTGreaterEqualNode::ASTGreaterEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("GE", GE, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTGreaterEqualNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'>=\'");
        return operate(section, cg);
    }

    ASTGreaterNode::ASTGreaterNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTRelationalNode("GT", GT, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTGreaterNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'>\'");
        return operate(section, cg);
    }

    ASTLessEqualNode::ASTLessEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("LE", LE, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTLessEqualNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'<=\'");
        return operate(section, cg);
    }

    ASTLessNode::ASTLessNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("LT", LT, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTLessNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'<\'");
        return operate(section, cg);
    }

    ASTEqualNode::ASTEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("EQ", EQ, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTEqualNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'==\'");
        return operate(section, cg);
    }

    ASTNotEqualNode::ASTNotEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("NEQ", NEQ, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTNotEqualNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'!=\'");
        return operate(section, cg);
    }

    ASTNotNode::ASTNotNode(wic::ASTNode *op) : ASTRelationalNode("NOT", NOT, wic::UNKNOWN, op) {}

    cpu_registers ASTNotNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'!\'");
        return operate(section, cg);
    }

    ASTAndNode::ASTAndNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode("AND", AND, wic::BOOL, op1, op2) {}

    cpu_registers ASTAndNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'&&\'");
        return operate(section, cg);
    }

    ASTOrNode::ASTOrNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTRelationalNode("OR", OR, wic::BOOL, op1, op2) {}

    cpu_registers ASTOrNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        check_error("\'||\'");
        return operate(section, cg);
    }
}
