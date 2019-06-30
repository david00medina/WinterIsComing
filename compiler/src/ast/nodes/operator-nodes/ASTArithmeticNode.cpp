#include "ASTArithmeticNode.hpp"
#include "../ASTSymbolTableNode.hpp"
#include "../ASTLeafNode.hpp"


namespace wic
{
    ASTArithmeticNode::ASTArithmeticNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *ptr1, wic::ASTNode *ptr3)
        : ASTOperatorNode(node_t, data_t, ptr1, ptr3) {}

    cpu_registers ASTArithmeticNode::div_mod(cpu_registers r1, cpu_registers r2, div_selector selector, CodeGenerator *cg)
    {
        if (cg->is_used(EAX) && r1 != EAX && r2 != EAX) cg->write_code_section("pushl", cg->translate_reg(EAX), "Push used register to stack (" + cg->translate_reg(EAX) + ")");
        if (cg->is_used(EBX) && r1 != EBX && r2 != EBX) cg->write_code_section("pushl", cg->translate_reg(EBX), "Push used register to stack (" + cg->translate_reg(EBX) + ")");
        if (cg->is_used(ECX) && r1 != ECX && r2 != ECX) cg->write_code_section("pushl", cg->translate_reg(ECX), "Push used register to stack (" + cg->translate_reg(ECX) + ")");
        if (cg->is_used(EDX) && r1 != EDX && r2 != EDX) cg->write_code_section("pushl", cg->translate_reg(EDX), "Push used register to stack (" + cg->translate_reg(EDX) + ")");

        bool mess = false;
        if (r1 != EAX)
        {
            if (r2 == EAX) {
                if (r1 != EBX) cg->write_code_section("movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                else {
                    mess = true;
                    cg->write_code_section("movl", cg->translate_reg(r1), cg->translate_reg(EDX), "");
                    cg->write_code_section("movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                    cg->write_code_section("movl", cg->translate_reg(EDX), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                }
            }
            if (!mess) cg->write_code_section("movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
        }

        mess = false;
        if (r2 != EBX)
        {
            if (r1 == EBX) {
                if (r2 != EAX) cg->write_code_section("movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                else {
                    mess = true;
                    cg->write_code_section("movl", cg->translate_reg(r2), cg->translate_reg(EDX), "");
                    cg->write_code_section("movl", cg->translate_reg(r1), cg->translate_reg(EAX), "Prepare dividend (" + cg->translate_reg(r1) + ")");
                    cg->write_code_section("movl", cg->translate_reg(EDX), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
                }
            }
            if (!mess) cg->write_code_section("movl", cg->translate_reg(r2), cg->translate_reg(EBX), "Prepare divisor (" + cg->translate_reg(r2) + ")");
        }

        cpu_registers res = division(selector, cg);
        cg->write_code_section("movl", cg->translate_reg(res), cg->translate_reg(r2), "Save quotient to " + cg->translate_reg(r2));

        if (cg->is_used(EDX) && r2 != EDX && r1 != EDX) cg->write_code_section("popl", cg->translate_reg(EDX), "Pop used register from stack (" + cg->translate_reg(EDX) + ")");
        if (cg->is_used(ECX) && r2 != ECX && r1 != ECX) cg->write_code_section("popl", cg->translate_reg(ECX), "Pop used register from stack (" + cg->translate_reg(ECX) + ")");
        if (cg->is_used(EBX) && r2 != EBX && r1 != EBX) cg->write_code_section("popl", cg->translate_reg(EBX), "Pop used register from stack (" + cg->translate_reg(EBX) + ")");
        if (cg->is_used(EAX) && r1 != EAX && r2 != EAX) cg->write_code_section("popl", cg->translate_reg(EAX), "Pop used register from stack (" + cg->translate_reg(EAX) + ")");
        cg->free_reg(r1);

        return r2;
    }

    cpu_registers ASTArithmeticNode::division(div_selector selector, CodeGenerator *cg)
    {
        cg->write_code_section("movl", "$0", cg->translate_reg(EDX), cg->translate_reg(EDX) + " = 0");
        cg->write_code_section("cltd", cg->translate_reg(EDX) + ":" + cg->translate_reg(EAX));

        std::string comment;
        switch (selector)
        {
            case QUOTIENT:
                comment = cg->translate_reg(EBX) + " = " + cg->translate_reg(EAX) + " / " + cg->translate_reg(EBX);
                break;
            case REMAINDER:
                comment = cg->translate_reg(EBX) + " = " + cg->translate_reg(EAX) + " % " + cg->translate_reg(EBX);
        }

        cg->write_code_section("idivl", cg->translate_reg(EBX), comment);

        if (selector == QUOTIENT) return EAX;
        else if (selector == REMAINDER) return EDX;
    }

    cpu_registers ASTArithmeticNode::instr_reg2(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t) {
            case SUM:
                cg->write_code_section("addl", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " + " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case SUB:
                cg->write_code_section("subl", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " - " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case PROD:
                cg->write_code_section("imul", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " * " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case ASSIGN:
            {
                TableEntry* entry = reinterpret_cast<ASTIDNode *>(ptr1)->get_entry();
                int offset = entry->get_data().var.offset;
                std::string op = std::to_string(offset) + "(" + cg->translate_reg(EBX) + ")";
                std::string id = entry->get_id();

                cg->write_code_section("movl", cg->translate_reg(r1), op, "Save variable \'" + id + "\'");
                cg->free_reg(r1);
                return r2;
            }
            case POWER:
                return NONE;
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg2_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t) {
            case SUM:
                cg->write_code_section("addss", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " + " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case SUB:
                cg->write_code_section("subss", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " - " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case PROD:
                cg->write_code_section("mulss", cg->translate_reg(r1), cg->translate_reg(r2),
                                       cg->translate_reg(r2) + " = " + cg->translate_reg(r1) + " * " + cg->translate_reg(r2));
                cg->free_reg(r1);
                return r2;
            case DIV:
                cg->write_code_section("divss", cg->translate_reg(r2), cg->translate_reg(r1),
                                       cg->translate_reg(r1) + " = " + cg->translate_reg(r1) + " / " + cg->translate_reg(r2));
                cg->free_reg(r2);
                return r1;
            case POWER:
                return NONE;
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg3(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
    {
        switch (node_t)
        {
            case DIV:
                return div_mod(r1, r2, QUOTIENT, cg);
            case MOD:
                return div_mod(r1, r2, REMAINDER, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTArithmeticNode::instr_reg3_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t)
        {
            case MOD:
                return div_mod(float_to_int(r1, cg), float_to_int(r2, cg), REMAINDER, cg);
            default:
                return NONE;
        }
    }

    ASTSumNode::ASTSumNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::SUM, wic::UNKNOWN, op1, op2) { name = "SUM"; }

    cpu_registers ASTSumNode::to_code(CodeGenerator *cg)
    {
        check_error("sum");
        return operate(cg);
    }

    ASTSubNode::ASTSubNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::SUB, wic::UNKNOWN, op1, op2) { name = "SUBTRACT"; }

    cpu_registers ASTSubNode::to_code(CodeGenerator *cg)
    {
        check_error("subtract");
        return operate(cg);
    }

    ASTProdNode::ASTProdNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::PROD, wic::UNKNOWN, op1, op2) { name = "PRODUCT"; }

    cpu_registers ASTProdNode::to_code(CodeGenerator *cg)
    {
        check_error("multiply");
        return operate(cg);
    }

    ASTDivNode::ASTDivNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::DIV, wic::UNKNOWN, op1, op2) { name = "DIVISION"; }

    cpu_registers ASTDivNode::to_code(CodeGenerator *cg)
    {
        check_error("divide");
        return operate(cg);
    }

    ASTPowerNode::ASTPowerNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::POWER, wic::UNKNOWN, op1, op2) { name = "POWER"; }

    cpu_registers ASTPowerNode::to_code(CodeGenerator *cg) {}

    ASTRadicalNode::ASTRadicalNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::RADICAL, wic::UNKNOWN, op1, op2) { name = "RADICAL"; }

    cpu_registers ASTRadicalNode::to_code(CodeGenerator *cg) {}

    ASTModNode::ASTModNode(wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::MOD, wic::UNKNOWN, op1, op2) { name = "MODULUS"; }

    cpu_registers ASTModNode::to_code(CodeGenerator *cg)
    {
        check_error("mod");
        return operate(cg);
    }

    ASTAssignNode::ASTAssignNode(data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
            : ASTArithmeticNode(wic::ASSIGN, data_t, op1, op2) { name = "ASSIGN"; }

    cpu_registers ASTAssignNode::to_code(CodeGenerator *cg)
    {
        check_error("assign");
        return operate(cg);
    }
}
