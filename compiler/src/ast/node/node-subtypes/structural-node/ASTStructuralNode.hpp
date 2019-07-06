#ifndef ASTSTRUCTURALNODE_HPP
#define ASTSTRUCTURALNODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../symbol-table/SymbolTablePack.hpp"

namespace wic
{
    class ASTIDNode;

    class ASTStructuralNode : public ASTNode
    {
    public:
        ASTStructuralNode();
        ASTStructuralNode(std::string, node_type, data_type);
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
        ~ASTBodyNode();

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
        ASTMainNode(ASTBodyNode*);
        ~ASTMainNode();

        void add_body(ASTBodyNode*);
        cpu_registers to_code(CodeGenerator*);
    };

    class ASTReturnNode : public ASTStructuralNode {
    private:
        void check_error(std::string) {};

    public:
        ASTNode* ret;

        ASTReturnNode();
        ASTReturnNode(ASTNode*);
        ~ASTReturnNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTArgumentNode : public ASTStructuralNode {
    private:
        ASTNode* args;
        unsigned int num_args;
        int memory;

        void check_error(std::string) {};
        void load_args(ASTNode*, CodeGenerator*);

    public:
        ASTArgumentNode();
        ASTArgumentNode(ASTNode*);
        ~ASTArgumentNode();

        void add_argument(ASTNode*);
        cpu_registers to_code(CodeGenerator*);
    };

    class ASTParamNode : public ASTStructuralNode {
    private:
        ASTIDNode* params;
        unsigned int num_params;
        int param_mem;

        void check_error(std::string) {};

    public:
        ASTParamNode();
        ASTParamNode(ASTIDNode*);
        ~ASTParamNode();

        unsigned int get_num_params();
        ASTIDNode* get_params();
        void add_params(ASTIDNode*);
        ASTIDNode* lookup(std::string);

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
