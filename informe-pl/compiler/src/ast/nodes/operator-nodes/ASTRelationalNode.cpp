#include "ASTRelationalNode.hpp"

namespace wic
{
    ASTRelationalNode::ASTRelationalNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(node_t, data_t, op1, op2) {}

    cpu_registers ASTRelationalNode::compare(std::string instr, wic::cpu_registers r1, wic::cpu_registers r2,
                                             wic::CodeGenerator *cg)
        {
            cg->write_code_section("cmpl", cg->translate_reg(r2), cg->translate_reg(r1), "Compare " + cg->translate_reg(r1) + " with " + cg->translate_reg(r2));
            cg->write_code_section("set" + instr, cg->translate_low_reg(r2), cg->translate_low_reg(r2) + " = " + cg->translate_reg(r1) + " >= " + cg->translate_reg(r2));
            cg->write_code_section("movzbl", cg->translate_low_reg(r2), cg->translate_reg(r2), "Save comparison result to " + cg->translate_reg(r2));
            cg->free_reg(r1);
        }

    cpu_registers ASTRelationalNode::intr_reg2(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t) {
            case GE:
                compare("ge", r1, r2, cg);
            case GT:
                compare("g", r1, r2, cg);
            case LE:
                compare("le", r1, r2, cg);
            case LT:
                compare("l", r1, r2, cg);
            case EQ:
                compare("e", r1, r2, cg);
            case NEQ:
                compare("ne", r1, r2, cg);
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::intr_reg2_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
        switch (node_t) {
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::intr_reg3(cpu_registers r1, cpu_registers r2, CodeGenerator *cg)
    {
        switch (node_t)
        {
            default:
                return NONE;
        }
    }

    cpu_registers ASTRelationalNode::intr_reg3_float(cpu_registers r1, cpu_registers r2, CodeGenerator *cg){
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

    ASTLessEqualNode::ASTLessNode(wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTRelationalNode(LT, wic::UNKNOWN, op1, op2) {}

    cpu_registers ASTLessNode::to_code(wic::CodeGenerator *cg)
    {
        check_error("\'<\'");
        return operate(cg);
    }

    ASTLessEqualNode::ASTEqualNode(wic::ASTNode *op1, wic::ASTNode *op2)
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
}
