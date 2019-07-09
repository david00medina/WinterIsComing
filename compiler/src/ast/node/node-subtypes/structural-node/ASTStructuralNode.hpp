#ifndef ASTSTRUCTURALNODE_HPP
#define ASTSTRUCTURALNODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../symbol-table/SymbolTablePack.hpp"

namespace wic
{
    class ASTIDNode;
    class ASTFunctionNode;

    class ASTStructuralNode : public ASTNode
    {
    public:
        ASTStructuralNode();
        ASTStructuralNode(std::string, node_type, data_type);
        ~ASTStructuralNode() = default;
    };

    class ASTBodyNode : public ASTStructuralNode {
    private:
        ASTMainNode* main;
        ASTNode* instr;
        ASTBodyNode* next;
        unsigned int instr_count;

        void check_error(std::string) {};

    public:
        ASTBodyNode();
        ASTBodyNode(ASTNode*);
        ~ASTBodyNode();

        void set_main(ASTMainNode*);
        void add_instr(ASTNode*);
        unsigned int get_instr_count();
        cpu_registers to_code(section_enum, CodeGenerator*);

        friend class ASTMainNode;
    };

    class ASTMainNode : public ASTStructuralNode {
    private:
        ASTBodyNode* body;
        ASTFunctionNode* fun_list;

        void check_error(std::string) {};

    public:
        ASTMainNode();
        ASTMainNode(ASTBodyNode*);
        ~ASTMainNode();

        void add_body(ASTBodyNode*);
        void add_function(ASTFunctionNode*);
        bool match_function(std::string, function*);
        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTReturnNode : public ASTStructuralNode {
    private:
        void check_error(std::string) {};

    public:
        ASTNode* ret;

        ASTReturnNode();
        ASTReturnNode(ASTNode*);
        ~ASTReturnNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTArgumentNode : public ASTStructuralNode {
    private:
        ASTNode* args;
        unsigned int num_args;
        int memory;

        void check_error(std::string) {};
        void load_args(ASTNode*, section_enum, CodeGenerator*);

    public:
        ASTArgumentNode();
        ASTArgumentNode(ASTNode*);
        ~ASTArgumentNode();

        void add_argument(ASTNode*);
        int get_num_args();
        cpu_registers to_code(section_enum, CodeGenerator*);
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

        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
