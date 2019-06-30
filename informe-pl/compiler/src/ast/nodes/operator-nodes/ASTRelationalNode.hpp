#ifndef ASTRELATIONALNODE_HPP
#define ASTRELATIONALNODE_HPP

#include "ASTOperatorNode.hpp"
#include "../../AbstractSyntaxTreePack.hpp"
#include "../../../code-generator/CodeGenerator.hpp"

namespace wic {
    class ASTRelationalNode : public ASTOperatorNode
    {
    protected:
        cpu_registers compare(std::string, cpu_registers, cpu_registers, CodeGenerator*);

        virtual cpu_registers intr_reg2(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg2_float(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg3(cpu_registers, cpu_registers, CodeGenerator*);
        virtual cpu_registers intr_reg3_float(cpu_registers, cpu_registers, CodeGenerator*);

    public:
        ASTRelationalNode() = default;
        ASTRelationalNode(node_type, data_type, ASTNode*, ASTNode*);
        ~ASTRelationalNode() = default;
    };

    class ASTGreaterEqualNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTGreaterNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTLessEqualNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTLessNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTEqualNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTNotEqualNode : public ASTRelationalNode
    {
    public:
        ASTGreaterEqualNode() = default;
        ASTGreaterEqualNode(ASTNode*, ASTNode*);
        ~ASTGreaterEqualNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
