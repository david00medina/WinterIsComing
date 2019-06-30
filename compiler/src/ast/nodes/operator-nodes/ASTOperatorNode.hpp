#ifndef ASTOPERATORNODE_HPP
#define ASTOPERATORNODE_HPP

#include "../ASTNode.hpp"
#include "../../AbstractSyntaxTreePack.hpp"
#include "../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    class ASTOperatorNode : public ASTNode
    {
    private:
        cpu_registers execute(cpu_registers, cpu_registers, CodeGenerator*);
        cpu_registers execute_float(cpu_registers, cpu_registers, CodeGenerator*);

    protected:
        virtual void check_error(std::string);
        virtual void set_operator_type();

        virtual cpu_registers int_to_float(cpu_registers, CodeGenerator*);
        virtual cpu_registers float_to_int(cpu_registers, CodeGenerator*);
        virtual cpu_registers operand_type_conversion(cpu_registers, cpu_registers, CodeGenerator*);
        virtual data_type get_node_data_type(ASTNode*);

        virtual cpu_registers instr_reg2(cpu_registers, cpu_registers, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg2_float(cpu_registers, cpu_registers, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg3(cpu_registers, cpu_registers, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg3_float(cpu_registers, cpu_registers, CodeGenerator*) = 0;

        virtual cpu_registers operate(CodeGenerator*);

    public:
        ASTOperatorNode() = default;
        ASTOperatorNode(node_type, data_type, ASTNode*, ASTNode*);
        ~ASTOperatorNode() = default;

        void set_operators(ASTNode*, ASTNode*);
        virtual cpu_registers to_code(CodeGenerator*) = 0;
    };
}

#endif
