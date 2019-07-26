#ifndef ASTSYMBOLTABLENODE_HPP
#define ASTSYMBOLTABLENODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../symbol-table/SymbolTablePack.hpp"
#include "../../../../code-generator/CodeGeneratorPack.hpp"
#include "../structural-node/ASTStructuralNode.hpp"

namespace wic {
    class TableEntry;
    class CodeGenerator;
    class ASTParamNode;
    class ASTArgumentNode;
    class ASTBodyNode;

    class ASTSymbolTableNode : public ASTNode
    {
    protected:
        std::string id;
        TableEntry* global_te;
        TableEntry* static_te;
        TableEntry* local_te;

        void check_error(std::string);

    public:
        ASTSymbolTableNode() = default;
        ASTSymbolTableNode(std::string, std::string, node_type, data_type);
        ASTSymbolTableNode(std::string, std::string, node_type, data_type, TableEntry*, TableEntry*, TableEntry*);
        virtual ~ASTSymbolTableNode();

        virtual const char* get_id();
        virtual void set_id(std::string *);
        virtual TableEntry* get_entry();
        virtual void set_global_entry(TableEntry*);
        virtual void set_static_entry(TableEntry*);
        virtual void set_local_entry(TableEntry*);
        virtual bool is_registered();
        virtual cpu_registers to_code(section_enum, CodeGenerator*) = 0;
        virtual void print();
    };

    class ASTFunctionNode : public ASTSymbolTableNode
    {
    private:
        ASTParamNode* params;
        ASTBodyNode* body;
        ASTReturnNode* ret;

        int num_params = 0;

    public:
        ASTFunctionNode() = default;
        ASTFunctionNode(std::string, entry_data, ASTParamNode*, ASTBodyNode*, ASTReturnNode*);
        ASTFunctionNode(std::string, entry_data);
        ~ASTFunctionNode();

        unsigned int get_num_params();
        ASTParamNode* get_params();
        void add_param(ASTParamNode*);
        ASTBodyNode* get_body();
        ASTReturnNode* get_return();
        void set_return(ASTNode*);
        bool match(std::string, function*);

        cpu_registers to_code(section_enum, CodeGenerator*);

        void print();
    };

    class ASTCallNode : public ASTSymbolTableNode
    {
    private:
        ASTArgumentNode* args;
        entry_data entry_d;
        unsigned int num_args;

        void initialize();

    public:
        ASTCallNode() = default;
        ASTCallNode(std::string, ASTArgumentNode*);
        ~ASTCallNode();

        void add_arg(ASTArgumentNode*);
        ASTArgumentNode* get_args();
        entry_data get_entry_data();

        cpu_registers to_code(section_enum, CodeGenerator*);
        void print();
    };

    class ASTIDNode : public ASTSymbolTableNode
    {
    private:
        bool is_initialization = false;

        void register_id(void*, void*);
        cpu_registers get_var(section_enum, CodeGenerator*);

    public:
        ASTIDNode() = default;
        ASTIDNode(void*, void*);
        ASTIDNode(std::string);
        ASTIDNode(std::string, data_type, TableEntry*, TableEntry*, TableEntry*);
        ~ASTIDNode() = default;

        void set_initialization(bool);
        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTParamNode : public ASTSymbolTableNode {
    private:
        ASTIDNode* params;

        void check_error(std::string) {};

    public:
        ASTParamNode(std::string, entry_data);
        ~ASTParamNode();

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTArgumentNode : public ASTSymbolTableNode {
    private:
        ASTNode* arg;
        int offset;

        void check_error(std::string) {};
        void load_args(ASTNode*, section_enum, CodeGenerator*);

    public:
        ASTArgumentNode(ASTNode*);
        ~ASTArgumentNode() = default;

        void set_offset(int);
        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
