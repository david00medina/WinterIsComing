#ifndef ASTSTRUCTURALNODE_HPP
#define ASTSTRUCTURALNODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../symbol-table/SymbolTablePack.hpp"

namespace wic
{
    class ASTStructuralNode : public ASTNode
    {
    public:
        ASTStructuralNode();
        ASTStructuralNode(std::string, node_type, data_type);
        ASTStructuralNode(std::string, node_type, data_type, ASTNode*);
        ~ASTStructuralNode() = default;
    };

    class ASTMainNode : public ASTStructuralNode {
    private:
        ASTNode* body;

        void check_error(std::string) {};

    public:
        ASTMainNode();
        ASTMainNode(ASTNode*);
        ~ASTMainNode() = default;

        cpu_registers to_code(CodeGenerator*);
        void add_body(ASTNode*);
    };

    class ASTBodyNode : public ASTStructuralNode {
    private:
        ASTNode* instr;

        void check_error(std::string) {};

    public:
        ASTBodyNode();
        ASTBodyNode(ASTNode*);
        ~ASTBodyNode() = default;

        cpu_registers to_code(CodeGenerator*);
        void add_instr(ASTNode*);
    };

    class ASTReturnNode : public ASTStructuralNode {
    private:
        void check_error(std::string) {};

    public:
        ASTReturnNode();
        ASTReturnNode(ASTNode*);
        ~ASTReturnNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTParamNode : public ASTStructuralNode {
    private:
        void check_error(std::string) {};

    public:
        ASTParamNode();
        ASTParamNode(ASTNode*);
        ~ASTParamNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
