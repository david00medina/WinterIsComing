#ifndef ASTARITHMETICNODE_HPP
#define ASTARITHMETICNODE_HPP

#include "ASTOperatorNode.hpp"

namespace wic
{
    class ASTArithmeticNode : public ASTOperatorNode
    {
    protected:
        typedef enum {
            QUOTIENT,
            REMAINDER
        } div_selector;

        virtual cpu_registers div_mod(cpu_registers, cpu_registers, div_selector, section_enum, CodeGenerator*);
        virtual cpu_registers division(div_selector, section_enum, CodeGenerator*);

        virtual cpu_registers instr_reg2(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg2_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg3(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg3_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*);

    public:
        ASTArithmeticNode() = default;
        ASTArithmeticNode(std::string, node_type, data_type, ASTNode*, ASTNode*);
        ~ASTArithmeticNode() = default;
    };

    class ASTSumNode : public ASTArithmeticNode
    {
    public:
        ASTSumNode() = default;
        ASTSumNode(ASTNode*, ASTNode*);
        ~ASTSumNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTSubNode : public ASTArithmeticNode
    {
    public:
        ASTSubNode() = default;
        ASTSubNode(ASTNode*, ASTNode*);
        ~ASTSubNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTProdNode : public ASTArithmeticNode
    {
    public:
        ASTProdNode() = default;
        ASTProdNode(ASTNode*, ASTNode*);
        ~ASTProdNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTDivNode : public ASTArithmeticNode
    {
    public:
        ASTDivNode() = default;
        ASTDivNode(ASTNode*, ASTNode*);
        ~ASTDivNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTPowerNode : public ASTArithmeticNode
    {
    public:
        ASTPowerNode() = default;
        ASTPowerNode(ASTNode*, ASTNode*);
        ~ASTPowerNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTRadicalNode : public ASTArithmeticNode
    {
    public:
        ASTRadicalNode() = default;
        ASTRadicalNode(ASTNode*, ASTNode*);
        ~ASTRadicalNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTModNode : public ASTArithmeticNode
    {
    public:
        ASTModNode() = default;
        ASTModNode(ASTNode*, ASTNode*);
        ~ASTModNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTAssignNode : public ASTArithmeticNode
    {
    public:
        ASTAssignNode() = default;
        ASTAssignNode(data_type, ASTNode*, ASTNode*);
        ~ASTAssignNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
