#include "ASTOperatorNode.hpp"
#include "../ASTSymbolTableNode.hpp"
#include "../ASTLeafNode.hpp"
#include "../../../error-manager/ErrorManager.hpp"

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

    cpu_registers ASTOperatorNode::int_to_float(cpu_registers r, CodeGenerator *cg)
    {
        cpu_registers fr = cg->get_float_reg();
        cg->write_code_section("cvtsi2ss", cg->translate_reg(r), cg->translate_reg(fr),
                               "Convert int to real (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        return fr;
    }

    cpu_registers ASTOperatorNode::float_to_int(cpu_registers r, CodeGenerator *cg)
    {
        cpu_registers ir = cg->get_reg();
        cg->write_code_section("cvttss2sil", cg->translate_reg(r), cg->translate_reg(ir),
                               "Convert real to int (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        std::cout << cg->is_used(ir) << std::endl;
        return ir;
    }

    cpu_registers ASTOperatorNode::operand_type_conversion(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
    {
        data_type type1 = get_node_data_type(ptr1);
        data_type type2 = get_node_data_type(ptr3);
        if (type1 == type2) return NONE;
        else if (type1 != REAL && type2 == REAL) return int_to_float(r1, cg);
        else if (type1 == REAL && type2 != REAL) return int_to_float(r2, cg);
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

    cpu_registers ASTOperatorNode::operate(wic::CodeGenerator *cg)
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
}