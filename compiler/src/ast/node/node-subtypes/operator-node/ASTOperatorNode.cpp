#include "ASTOperatorNode.hpp"
#include "../leaf-node/ASTLeafNode.hpp"
#include "../../../../error-manager/ErrorManager.hpp"
#include "../symbol-table-node/ASTSymbolTableNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    ASTOperatorNode::ASTOperatorNode(std::string name, wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op)
        : ASTNode(name, node_t, data_t)
    {
        op1 = op;
        op2 = nullptr;
    }

    ASTOperatorNode::ASTOperatorNode(std::string name, wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTNode(name, node_t, data_t)
    {
        this->op1 = op1;
        this->op2 = op2;
    }

    ASTOperatorNode::~ASTOperatorNode()
    {
        delete op1;
        delete op2;
    }

    void ASTOperatorNode::set_operators(wic::ASTNode *op1, wic::ASTNode *op2)
    {
        this->op1 = op1;
        this->op2 = op2;
    }

    cpu_registers ASTOperatorNode::execute(wic::cpu_registers r1, wic::cpu_registers r2, section_enum section, wic::CodeGenerator *cg)
    {
        cpu_registers o1 = instr_reg2(r1, r2, section, cg);
        cpu_registers o2 = instr_reg3(r1, r2, section, cg);

        if (o1 != NONE) return o1;
        else if (o2 != NONE) return o2;
    }

    cpu_registers ASTOperatorNode::execute_float(wic::cpu_registers r1, wic::cpu_registers r2, section_enum section, wic::CodeGenerator *cg)
    {
        cpu_registers o1 = instr_reg2_float(r1, r2, section, cg);
        cpu_registers o2 = instr_reg3_float(r1, r2, section, cg);

        if (o1 != NONE) return o1;
        else if (o2 != NONE) return o2;
    }

    void ASTOperatorNode::check_error(std::string op)
    {
        data_type type1 = get_node_data_type(op1);

        if (op2 == nullptr) return;

        data_type type2 = get_node_data_type(op2);

        switch (get_node_type())
        {
            case ASSIGN:
                if (op1->get_node_type() != ID) ErrorManager::send(WRONG_ASSIGN);
                else if (type1 != type2) ErrorManager::send(INCOMPATIBLE_ASSIGN, reinterpret_cast<ASTIDNode *>(op1)->get_entry()->get_id());
                break;
            case AND:
                if (type1 != BOOL || type2 != BOOL) ErrorManager::send(WRONG_RELATIONAL_OPERANDS, op);
                break;
            case OR:
                if (type1 != BOOL || type2 != BOOL) ErrorManager::send(WRONG_RELATIONAL_OPERANDS, op);
                break;
            default:
                std::cout << "HOLA: " << get_node_data_type(op1);
                std::cout << "HOLA: " << op2->get_node_type();

                if (type1 == UNKNOWN || type2 == UNKNOWN) ErrorManager::send(INCOMPATIBLE_OPERANDS, op);
                break;
        }

    }

    void ASTOperatorNode::set_operator_type()
    {
        data_type type1 = get_node_data_type(op1);
        data_type type2 = get_node_data_type(op2);
        if (type1 == type2) data_t = type1;
        else
        {
            if (type1 == REAL) data_t = type1;
            else data_t = type2;
        }
    }

    cpu_registers ASTOperatorNode::int_to_float(cpu_registers r, section_enum section, CodeGenerator *cg)
    {
        cpu_registers fr = cg->get_float_reg();
        cg->write(section, "c%s%s#s", "cvtsi2ss", cg->translate_reg(r), cg->translate_reg(fr),
                               "Convert int to real (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        return fr;
    }

    cpu_registers ASTOperatorNode::float_to_int(cpu_registers r, section_enum section, CodeGenerator *cg)
    {
        cpu_registers ir = cg->get_reg();
        cg->write(section, "c%s%s#s", "cvttss2sil", cg->translate_reg(r), cg->translate_reg(ir),
                               "Convert real to int (" + cg->translate_reg(r) + ")");
        cg->free_reg(r);
        return ir;
    }

    cpu_registers ASTOperatorNode::operand_type_conversion(cpu_registers r1, cpu_registers r2, section_enum section, CodeGenerator *cg)
    {
        data_type type1 = get_node_data_type(op1);
        data_type type2 = type1;

        if (op2 != nullptr) type2 = get_node_data_type(op2);

        if (type1 == type2)
        {
            data_t = type1;
            return NONE;
        }
        else if (type1 != REAL && type2 == REAL)
        {
            data_t = REAL;
            return int_to_float(r1, section, cg);
        }
        else if (type1 == REAL && type2 != REAL)
        {
            data_t = REAL;
            return int_to_float(r2, section, cg);
        }
    }

    data_type ASTOperatorNode::get_node_data_type(ASTNode* op)
    {
        switch (op->get_node_type())
        {
            case ID:
                return reinterpret_cast<ASTIDNode *>(op)->get_entry()->get_data().var.type;
            case CALL:
                return reinterpret_cast<ASTCallNode *>(op)->get_entry()->get_data().var.type;
            case LEAF:
                return reinterpret_cast<ASTLeafNode *>(op)->get_data_type();
            default:
                return UNKNOWN;
        }
    }

    cpu_registers ASTOperatorNode::operate(section_enum section, wic::CodeGenerator *cg)
    {
        cpu_registers r1 = op1->to_code(section, cg);

        cpu_registers r2;
        if (op2 != nullptr) r2 = op2->to_code(section, cg);
        cpu_registers r = operand_type_conversion(r1, r2, section, cg);

        data_type type1 = get_node_data_type(op1);
        data_type type2;
        if (op2 != nullptr) type2 = get_node_data_type(op2);

        switch (r)
        {
            case NONE:
                if (type1 == INT || type1 == BOOL)
                {
                    return execute(r1, r2, section, cg);
                }
                else if (type1 == REAL)
                {
                    return execute_float(r1, r2, section, cg);
                }
                break;

            default:
                if (type1 != REAL)
                {
                    return execute_float(r, r2, section, cg);
                }
                else if (type2 != REAL)
                {
                    return execute_float(r1, r, section, cg);
                }
                break;
        }
    }
}