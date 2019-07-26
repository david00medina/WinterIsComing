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
        ASTStructuralNode() = default;
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

        unsigned int body_count;
        unsigned int func_count;

        void check_error(std::string) {};

    public:
        ASTMainNode();
        ASTMainNode(ASTBodyNode*);
        ~ASTMainNode();

        void add_body(ASTBodyNode*);
        ASTBodyNode* get_body();
        void add_function(ASTFunctionNode*);
        ASTFunctionNode* lookup_function(std::string);
        ASTFunctionNode* get_last_function();
        bool match_function(std::string, function*);
        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTReturnNode : public ASTStructuralNode {
    private:
        void check_error(std::string) {};

    public:
        ASTNode* ret;

        ASTReturnNode(data_type);
        ASTReturnNode(ASTNode*, data_type);
        ~ASTReturnNode() = default;

        void set_return(ASTNode*);
        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
