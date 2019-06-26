#include "ASTOperatorNode.hpp"
#include "ASTSymbolTableNode.hpp"
#include "ASTLeafNode.hpp"
#include "../../error-manager/ErrorManager.hpp"

namespace wic
{
    ASTOperatorNode::ASTOperatorNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *ptr1, wic::ASTNode *ptr3)
    {
        this->node_t = node_t;
        this->data_t = data_t;
        this->ptr1 = ptr1;
        this->ptr3 = ptr3;
    }

    void ASTOperatorNode::set_operators(wic::ASTNode *op1, wic::ASTNode *op2)
    {
        ptr1 = op1;
        ptr3 = op2;
    }

    void ASTOperatorNode::check_error(std::string op)
    {
        data_type type1 = get_node_data_type(ptr1);
        data_type type2 = get_node_data_type(ptr3);

        if (get_node_type() == ASSIGN && ptr1->get_node_type() != ID) ErrorManager::send(WRONG_ASSIGN);
        else if (get_node_type() == ASSIGN && type1 != type2) ErrorManager::send(INCOMPATIBLE_ASSIGN, reinterpret_cast<ASTIDNode *>(ptr1)->get_entry()->get_id());
        if (type1 == UNKNOWN || type2 == UNKNOWN) ErrorManager::send(INCOMPATIBLE_OPERANDS, op);
    }

    void ASTOperatorNode::set_operator_type()
    {
        data_type type1 = get_node_data_type(ptr1);
        data_type type2 = get_node_data_type(ptr3);
        if (type1 == type2) data_t = type1;
        else
        {
            if (type1 == REAL) data_t = type1;
            else data_t = type2;
        }
    }

    data_type ASTOperatorNode::get_node_data_type(ASTNode* ptr)
    {
        switch (ptr->get_node_type())
        {
            case ID:
                return reinterpret_cast<ASTIDNode *>(ptr)->get_entry()->get_data().var.type;
            case CALL:
                return reinterpret_cast<ASTCallNode *>(ptr)->get_entry()->get_data().var.type;
            case LEAF:
                return reinterpret_cast<ASTLeafNode *>(ptr)->get_data_type();
            default:
                return UNKNOWN;
        }
    }

    cpu_registers ASTOperatorNode::int_to_float(cpu_registers r, CodeGenerator *cg)
    {
        cpu_registers fr = cg->get_float_reg();
        cg->write_code_section("cvtsi2ss", cg->translate_reg(r), cg->translate_reg(fr), "Convert int to real (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        return fr;
    }

    cpu_registers ASTOperatorNode::float_to_int(cpu_registers r, CodeGenerator *cg)
    {
        cpu_registers ir = cg->get_reg();
        cg->write_code_section("cvttss2sil", cg->translate_reg(r), cg->translate_reg(ir), "Convert real to int (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        std::cout << cg->is_used(ir) << std::endl;
        return ir;
    }

    cpu_registers ASTOperatorNode::operand_type_conversion(cpu_registers r1, cpu_registers r2, CodeGenerator* cg)
    {
        data_type type1 = get_node_data_type(ptr1);
        data_type type2 = get_node_data_type(ptr3);
        if (type1 == type2) return NONE;
        else if (type1 != REAL && type2 == REAL) return int_to_float(r1, cg);
        else if (type1 == REAL && type2 != REAL) return int_to_float(r2, cg);
    }

    cpu_registers ASTOperatorNode::operate(CodeGenerator *cg)
    {
        set_operator_type();
        cpu_registers arithmetic = arithmetic_operation(cg);
        return arithmetic;
    }

    cpu_registers ASTOperatorNode::arithmetic_operation(CodeGenerator *cg)
    {
        cpu_registers r1 = ptr1->to_code(cg);
        cpu_registers r2 = ptr3->to_code(cg);
        cpu_registers r = operand_type_conversion(r1, r2, cg);

        data_type type1 = get_node_data_type(ptr1);
        data_type type2 = get_node_data_type(ptr3);

        switch (r)
        {
            case NONE:
                if (type1 == INT)
                {
                    cpu_registers o1 = intr_reg2(r1, r2, cg);
                    cpu_registers o2 = intr_reg3(r1, r2, cg);

                    if (o1 != NONE) return o1;
                    else if (o2 != NONE) return o2;
                }
                else if (type1 == REAL)
                {
                    cpu_registers o1 = intr_reg2_float(r1, r2, cg);
                    cpu_registers o2 = intr_reg3_float(r1, r2, cg);

                    if (o1 != NONE) return o1;
                    else if (o2 != NONE) return o2;
                }

            default:
                if (type1 != REAL)
                {
                    cpu_registers o1 = intr_reg2_float(r, r2, cg);
                    cpu_registers o2 = intr_reg3_float(r, r2, cg);

                    if (o1 != NONE) return o1;
                    else if (o2 != NONE) return o2;
                }
                else if (type2 != REAL)
                {
                    cpu_registers o1 = intr_reg2_float(r1, r, cg);
                    cpu_registers o2 = intr_reg3_float(r1, r, cg);

                    if (o1 != NONE) return o1;
                    else if (o2 != NONE) return o2;
                }
        }
    }

    cpu_registers ASTOperatorNode::intr_reg2(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
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

    cpu_registers ASTOperatorNode::intr_reg2_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
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

    cpu_registers ASTOperatorNode::intr_reg3(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
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

    cpu_registers ASTOperatorNode::intr_reg3_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t)
        {
            case MOD:
                return div_mod(float_to_int(r1, cg), float_to_int(r2, cg), REMAINDER, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTOperatorNode::div_mod(cpu_registers r1, cpu_registers r2, div_selector selector, CodeGenerator *cg)
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

    cpu_registers ASTOperatorNode::division(div_selector selector, CodeGenerator *cg)
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

    ASTSumNode::ASTSumNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::SUM, data_t, op1, op2) { name = "SUM"; }

    cpu_registers ASTSumNode::to_code(CodeGenerator *cg)
    {
        check_error("sum");
        return operate(cg);
    }

    ASTSubNode::ASTSubNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::SUB, data_t, op1, op2) { name = "SUBTRACT"; }

    cpu_registers ASTSubNode::to_code(CodeGenerator *cg)
    {
        check_error("subtract");
        return operate(cg);
    }

    ASTProdNode::ASTProdNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::PROD, data_t, op1, op2) { name = "PRODUCT"; }

    cpu_registers ASTProdNode::to_code(CodeGenerator *cg)
    {
        check_error("multiply");
        return operate(cg);
    }

    ASTDivNode::ASTDivNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::DIV, data_t, op1, op2) { name = "DIVISION"; }

    cpu_registers ASTDivNode::to_code(CodeGenerator *cg)
    {
        check_error("divide");
        return operate(cg);
    }

    ASTPowerNode::ASTPowerNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::POWER, data_t, op1, op2) { name = "POWER"; }

    cpu_registers ASTPowerNode::to_code(CodeGenerator *cg) {}

    ASTRadicalNode::ASTRadicalNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::RADICAL, data_t, op1, op2) { name = "RADICAL"; }

    cpu_registers ASTRadicalNode::to_code(CodeGenerator *cg) {}

    ASTModNode::ASTModNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::MOD, data_t, op1, op2) { name = "MODULUS"; }

    cpu_registers ASTModNode::to_code(CodeGenerator *cg)
    {
        check_error("mod");
        return operate(cg);
    }

    ASTAssignNode::ASTAssignNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::ASSIGN, data_t, op1, op2) { name = "ASSIGN"; }

    cpu_registers ASTAssignNode::to_code(CodeGenerator *cg)
    {
        check_error("assign");
        return operate(cg);
    }
}