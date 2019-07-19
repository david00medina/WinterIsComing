#include "ASTArithmeticNode.hpp"
#include "../symbol-table-node/ASTSymbolTableNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    ASTArithmeticNode::ASTArithmeticNode(std::string name, wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(name, node_t, data_t, op1, op2) {}

    void ASTArithmeticNode::set_initialization(bool is_initialization)
    {
        this->is_initialization = is_initialization;
    }

    cpu_registers ASTArithmeticNode::assign(bool is_float, cpu_registers r1, cpu_registers r2,
                                               section_enum section, CodeGenerator *cg)
    {
        ASTIDNode *id = reinterpret_cast<ASTIDNode *>(op1);

        int offset = id->get_entry()->get_data().var.offset;
        std::string op = std::to_string(offset) + "(" + cg->translate_reg(EBP) + ")";
        std::string id_ = id->get_entry()->get_id();

        variable var_data = id->get_entry()->get_data().var;

        if (is_initialization)
        {
            if (var_data.global || var_data.stat) {
                cg->write(DATA, "c%s", ".globl", id_);
                cg->write(DATA, "c", ".bss");
                cg->write(DATA, "c%s", ".align", std::to_string(var_data.size));
                cg->write(DATA, "c%s%c", ".type", id_, "@object");
                cg->write(DATA, "c%s%s", ".size", id_, std::to_string(var_data.size));
                cg->write_label(DATA, id_);

                if (var_data.array_length == 0) cg->write(DATA, "c%s", ".zero", std::to_string(var_data.size));

                if (!is_float)
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r1), id_,
                              "Save global/static variable \'" + id_ + "\'");
                else
                    cg->write(section, "c%s%s#s", "movss", cg->translate_reg(r1), id_,
                              "Save global/static variable \'" + id_ + "\'");

            } else if (var_data.local)
            {
                if (!is_float) cg->write(CODE, "c%s#s", "pushl", cg->translate_reg(r1), "Save local variable \'" + id_ + "\'");
                else
                {
                    cpu_registers r = cg->get_reg();
                    cg->write(CODE, "c%s%s#s", "movd", cg->translate_reg(r1), cg->translate_reg(r), "Move " +  cg->translate_reg(r1) + " to " + cg->translate_reg(r) + "register");
                    cg->write(CODE, "c%s#s", "pushl", cg->translate_reg(r), "Save local variable \'" + id_  + "\'");
                    cg->free_reg(r);
                }
            }
        } else
        {
            if (var_data.local) {
                if (!is_float)
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r1), op,
                              "Save local variable \'" + id_ + "\'");
                else
                    cg->write(section, "c%s%s#s", "movss", cg->translate_reg(r1), op,
                              "Save local variable \'" + id_ + "\'");

            } else if (var_data.global || var_data.stat) {
                if (!is_float)
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r1), id_,
                              "Save global/static variable \'" + id_ + "\'");
                else
                    cg->write(section, "c%s%s#s", "movss", cg->translate_reg(r1), id_,
                              "Save global/static variable \'" + id_ + "\'");
            }
        }
        cg->free_reg(r1);
        cg->free_reg(r2);
        return NONE;
    }

    cpu_registers ASTArithmeticNode::div_mod(cpu_registers r1, cpu_registers r2, div_selector selector, section_enum section, CodeGenerator *cg)
    {
        if (cg->is_used(EAX) && r1 != EAX && r2 != EAX) cg->write(section, "c%s#s", "pushl", cg->translate_reg(EAX), "Push used register to stack (" + cg->translate_reg(EAX) + ")");
        if (cg->is_used(EBX) && r1 != EBX && r2 != EBX) cg->write(section, "c%s#s", "pushl", cg->translate_reg(EBX), "Push used register to stack (" + cg->translate_reg(EBX) + ")");
        if (cg->is_used(ECX) && r1 != ECX && r2 != ECX) cg->write(section, "c%s#s", "pushl", cg->translate_reg(ECX), "Push used register to stack (" + cg->translate_reg(ECX) + ")");
        if (cg->is_used(EDX) && r1 != EDX && r2 != EDX) cg->write(section, "c%s#s", "pushl", cg->translate_reg(EDX), "Push used register to stack (" + cg->translate_reg(EDX) + ")");

        bool mess = false;
        if (r1 != EAX)
        {
            if (r2 == EAX) {
                if (r1 != EBX) cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                else {
                    mess = true;
                    cg->write(section, "c%s%s", "movl", cg->translate_reg(r1), cg->translate_reg(EDX));
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(EDX), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                }
            }
            if (!mess) cg->write(CODE, "c%s%s#s", "movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
        }

        mess = false;
        if (r2 != EBX)
        {
            if (r1 == EBX) {
                if (r2 != EAX) cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                else {
                    mess = true;
                    cg->write(section, "c%s%s", "movl", cg->translate_reg(r2), cg->translate_reg(EDX));
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                    cg->write(section, "c%s%s#s", "movl", cg->translate_reg(EDX), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                }
            }
            if (!mess) cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
        }

        cpu_registers res = division(selector, section, cg);
        cg->write(section, "c%s%s#s", "movl", cg->translate_reg(res), cg->translate_reg(r2), "Save quotient to " + cg->translate_reg(r2));

        if (cg->is_used(EDX) && r2 != EDX && r1 != EDX) cg->write(section, "c%s#s", "popl", cg->translate_reg(EDX), "Pop used register from stack (" + cg->translate_reg(EDX) + ")");
        if (cg->is_used(ECX) && r2 != ECX && r1 != ECX) cg->write(section, "c%s#s", "popl", cg->translate_reg(ECX), "Pop used register from stack (" + cg->translate_reg(ECX) + ")");
        if (cg->is_used(EBX) && r2 != EBX && r1 != EBX) cg->write(section, "c%s#s", "popl", cg->translate_reg(EBX), "Pop used register from stack (" + cg->translate_reg(EBX) + ")");
        if (cg->is_used(EAX) && r1 != EAX && r2 != EAX) cg->write(section, "c%s#s", "popl", cg->translate_reg(EAX), "Pop used register from stack (" + cg->translate_reg(EAX) + ")");
        cg->free_reg(r1);

        return r2;
    }

    cpu_registers ASTArithmeticNode::division(div_selector selector, section_enum section, CodeGenerator *cg)
    {
        cg->write(section, "c%c%s#s", "movl", "$0", cg->translate_reg(EDX), cg->translate_reg(EDX) + " = 0");
        cg->write(section, "c#s", "cltd", cg->translate_reg(EDX) + ":" + cg->translate_reg(EAX));

        std::string comment;
        switch (selector)
        {
            case QUOTIENT:
                comment = cg->translate_reg(EBX) + " = " + cg->translate_reg(EAX) + " / " + cg->translate_reg(EBX);
                break;
            case REMAINDER:
                comment = cg->translate_reg(EBX) + " = " + cg->translate_reg(EAX) + " % " + cg->translate_reg(EBX);
        }

        cg->write(section, "c%s#s", "idivl", cg->translate_reg(EBX), comment);

        if (selector == QUOTIENT) return EAX;
        else if (selector == REMAINDER) return EDX;
    }

    cpu_registers ASTArithmeticNode::instr_reg2(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg){
        switch (node_t) {
            case SUM:
                cg->write(section, "c%s%s#s", "addl", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " + " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case SUB:
                cg->write(section, "c%s%s#s", "subl", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " - " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case PROD:
                cg->write(section, "c%s%s#s", "imul", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " * " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case ASSIGN:
                return assign(false, r1, r2, section, cg);
            case POWER:
                return NONE;
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg2_float(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg){
        switch (node_t) {
            case SUM:
                cg->write(section, "c%s%s#s", "addss", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " + " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case SUB:
                cg->write(section, "c%s%s#s", "subss", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " - " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case PROD:
                cg->write(section, "c%s%s#s", "mulss", cg->translate_reg(r1), cg->translate_reg(r2),
                cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " * " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case DIV:
                cg->write(section, "c%s%s#s", "divss", cg->translate_reg(r2), cg->translate_reg(r1),
                cg->translate_reg(r1) + " = " + cg->translate_reg(r1) + " / " + cg->translate_reg(r2));
                cg->free_reg(r2);
                return r1;
            case ASSIGN:
                return assign(true, r1, r2, section, cg);
            case POWER:
                return NONE;
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg3(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg)
    {
        switch (node_t)
        {
            case DIV:
                return div_mod(r1, r2, QUOTIENT, section, cg);
            case MOD:
                return div_mod(r1, r2, REMAINDER, section, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg3_float(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg){
        switch (node_t)
        {
            case MOD:
                return div_mod(float_to_int(r1, section, cg), float_to_int(r2, section, cg), REMAINDER, section, cg);
            default:
                return NONE;
        }
    }

    ASTSumNode::ASTSumNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("SUM", wic::SUM, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTSumNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error("sum");
        return operate(section, cg);
    }

    ASTSubNode::ASTSubNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("SUBTRACT", wic::SUB, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTSubNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error("subtract");
        return operate(section, cg);
    }

    ASTProdNode::ASTProdNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("PRODUCT", wic::PROD, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTProdNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error("multiply");
        return operate(section, cg);
    }

    ASTDivNode::ASTDivNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("DIVISION", wic::DIV, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTDivNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error("divide");
        return operate(section, cg);
    }

    ASTPowerNode::ASTPowerNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("POWER", wic::POWER, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTPowerNode::to_code(section_enum section, CodeGenerator *cg) {}

    ASTRadicalNode::ASTRadicalNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("RADICAL", wic::RADICAL, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTRadicalNode::to_code(section_enum section, CodeGenerator *cg) {}

    ASTModNode::ASTModNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("MODULUS", wic::MOD, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTModNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error("mod");
        return operate(section, cg);
    }

    ASTAssignNode::ASTAssignNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode("ASSIGN", wic::ASSIGN, op1->get_data_type(), op1, op2) {}


    cpu_registers ASTAssignNode::to_code(section_enum section, CodeGenerator *cg)
    {
        cpu_registers r = operate(section, cg);
        check_error("assign");
        return r;
    }
}
