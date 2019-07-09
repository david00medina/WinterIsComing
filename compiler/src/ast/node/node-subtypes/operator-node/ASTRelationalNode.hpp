#ifndef ASTRELATIONALNODE_HPP
#define ASTRELATIONALNODE_HPP

#include "ASTOperatorNode.hpp"
#include "../../../AbstractSyntaxTreePack.hpp"

namespace wic {
    class ASTClauseNode;

    class ASTRelationalNode : public ASTOperatorNode
    {
    protected:
        cpu_registers compare(std::string, std::string, cpu_registers, cpu_registers, section_enum, CodeGenerator*, bool);
        cpu_registers do_and(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        cpu_registers do_or(cpu_registers, cpu_registers, section_enum, CodeGenerator*);

        virtual cpu_registers instr_reg2(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg2_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg3(cpu_registers, cpu_registers, section_enum, CodeGenerator*);
        virtual cpu_registers instr_reg3_float(cpu_registers, cpu_registers, section_enum, CodeGenerator*);

    public:
        ASTRelationalNode() = default;
        ASTRelationalNode(std::string, node_type, data_type, ASTNode*, ASTNode*);
        ASTRelationalNode(std::string, node_type, data_type, ASTNode*);
        ~ASTRelationalNode() = default;

        friend class ASTClauseNode;
    };

    class ASTGreaterEqualNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTGreaterNode : public ASTRelationalNode
    {
    public:
        ASTGreaterNode() = default;
        ASTGreaterNode(ASTNode*, ASTNode*);
        ~ASTGreaterNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTLessEqualNode : public ASTRelationalNode
    {
    public:
        ASTLessEqualNode() = default;
        ASTLessEqualNode(ASTNode*, ASTNode*);
        ~ASTLessEqualNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTLessNode : public ASTRelationalNode
    {
    public:
        ASTLessNode() = default;
        ASTLessNode(ASTNode*, ASTNode*);
        ~ASTLessNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTEqualNode : public ASTRelationalNode
    {
    public:
        ASTEqualNode() = default;
        ASTEqualNode(ASTNode*, ASTNode*);
        ~ASTEqualNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTNotEqualNode : public ASTRelationalNode
    {
    public:
        ASTNotEqualNode() = default;
        ASTNotEqualNode(ASTNode*, ASTNode*);
        ~ASTNotEqualNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTNotNode : public ASTRelationalNode
    {
    public:
        ASTNotNode() = default;
        ASTNotNode(ASTNode*);
        ~ASTNotNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTAndNode : public ASTRelationalNode
    {
    public:
        ASTAndNode() = default;
        ASTAndNode(ASTNode*, ASTNode*);
        ~ASTAndNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTOrNode : public ASTRelationalNode
    {
    public:
        ASTOrNode() = default;
        ASTOrNode(ASTNode*, ASTNode*);
        ~ASTOrNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
