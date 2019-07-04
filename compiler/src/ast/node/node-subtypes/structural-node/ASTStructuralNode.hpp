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

    class ASTBodyNode : public ASTStructuralNode {
    private:
        ASTNode* instr;
        ASTBodyNode* next;
        void check_error(std::string) {};

    public:
        ASTBodyNode();
        ASTBodyNode(ASTNode*);
        ~ASTBodyNode() = default;

        void add_instr(ASTNode*);
        cpu_registers to_code(CodeGenerator*);

        friend class ASTMainNode;
    };

    class ASTMainNode : public ASTStructuralNode {
    private:
        ASTBodyNode* body;
        void check_error(std::string) {};

    public:
        ASTMainNode();
        ASTMainNode(ASTNode*);
        ~ASTMainNode() = default;

        void add_body(ASTBodyNode*);
        cpu_registers to_code(CodeGenerator*);
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
