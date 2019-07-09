#ifndef ASTOPERATORNODE_HPP
#define ASTOPERATORNODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../code-generator/CodeGeneratorPack.hpp"

namespace wic
{
    class ASTOperatorNode : public ASTNode
    {
    private:
        cpu_registers execute(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        cpu_registers execute_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*);

    protected:
        ASTNode* op1;
        ASTNode* op2;

        void check_error(std::string);
        void set_operator_type();

        cpu_registers int_to_float(cpu_registers, section_enum, CodeGenerator*);
        cpu_registers float_to_int(cpu_registers, section_enum, CodeGenerator*);
        cpu_registers operand_type_conversion(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        data_type get_node_data_type(ASTNode*);

        virtual cpu_registers instr_reg2(cpu_registers, cpu_registers, section_enum, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg2_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg3(cpu_registers, cpu_registers, section_enum, CodeGenerator*) = 0;
        virtual cpu_registers instr_reg3_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*) = 0;

        cpu_registers operate(section_enum, CodeGenerator*);

    public:
        ASTOperatorNode() = default;
        ASTOperatorNode(std::string, node_type, data_type, ASTNode*);
        ASTOperatorNode(std::string, node_type, data_type, ASTNode*, ASTNode*);
        ~ASTOperatorNode();

        void set_operators(ASTNode*, ASTNode*);

        friend class AbstractSyntaxTree;
    };
}

#endif
