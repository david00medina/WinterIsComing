#ifndef ASTOPERATORNODE_HPP
#define ASTOPERATORNODE_HPP

#include "ASTNode.hpp"
#include "../AbstractSyntaxTreePack.hpp"

namespace wic {
    class ASTOperatorNode : public ASTNode
    {
    protected:
        typedef enum {
            QUOTIENT,
            REMAINDER
        } div_selector;

        virtual void check_error(std::string);
        virtual void set_operator_type();

        virtual data_type get_node_data_type(ASTNode*);
        virtual cpu_registers int_to_float(cpu_registers, CodeGenerator*);
        virtual cpu_registers float_to_int(cpu_registers, CodeGenerator*);
        virtual cpu_registers operand_type_conversion(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers operate(CodeGenerator*);
        virtual cpu_registers arithmetic_operation(CodeGenerator*);

        virtual cpu_registers div_mod(cpu_registers, cpu_registers, div_selector, CodeGenerator*);
        virtual cpu_registers division(div_selector, CodeGenerator*);

        virtual cpu_registers intr_reg2(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg2_float(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg3(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg3_float(cpu_registers, cpu_registers, CodeGenerator*);

    public:
        ASTOperatorNode() = default;
        ASTOperatorNode(node_type, data_type, ASTNode*, ASTNode*);
        ~ASTOperatorNode() = default;

        void set_operators(ASTNode*, ASTNode*);
        virtual cpu_registers to_code(CodeGenerator*) = 0;
    };

    class ASTSumNode : public ASTOperatorNode
    {
    public:
        ASTSumNode() = default;
        ASTSumNode(data_type, ASTNode*, ASTNode*);
        ~ASTSumNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTSubNode : public ASTOperatorNode
    {
    public:
        ASTSubNode() = default;
        ASTSubNode(data_type, ASTNode*, ASTNode*);
        ~ASTSubNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTProdNode : public ASTOperatorNode
    {
    public:
        ASTProdNode() = default;
        ASTProdNode(data_type, ASTNode*, ASTNode*);
        ~ASTProdNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTDivNode : public ASTOperatorNode
    {
    public:
        ASTDivNode() = default;
        ASTDivNode(data_type, ASTNode*, ASTNode*);
        ~ASTDivNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTPowerNode : public ASTOperatorNode
    {
    public:
        ASTPowerNode() = default;
        ASTPowerNode(data_type, ASTNode*, ASTNode*);
        ~ASTPowerNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTRadicalNode : public ASTOperatorNode
    {
    public:
        ASTRadicalNode() = default;
        ASTRadicalNode(data_type, ASTNode*, ASTNode*);
        ~ASTRadicalNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTModNode : public ASTOperatorNode
    {
    public:
        ASTModNode() = default;
        ASTModNode(data_type, ASTNode*, ASTNode*);
        ~ASTModNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTAssignNode : public ASTOperatorNode
    {
    public:
        ASTAssignNode() = default;
        ASTAssignNode(data_type, ASTNode*, ASTNode*);
        ~ASTAssignNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
