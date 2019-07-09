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
        function* fun_info;

    public:
        ASTFunctionNode() = default;
        ASTFunctionNode(std::string, data_type, ASTParamNode*, ASTBodyNode*, ASTReturnNode*);
        ~ASTFunctionNode();

        ASTNode* get_body();
        bool match(std::string, function*);

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTCallNode : public ASTSymbolTableNode
    {
    private:
        ASTArgumentNode* args;
        entry_data entry_d;

    public:
        ASTCallNode() = default;
        ASTCallNode(std::string, data_type, ASTArgumentNode *);
        ~ASTCallNode();

        ASTNode* get_args();
        entry_data get_entry_data();

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTIDNode : public ASTSymbolTableNode
    {
    public:
        ASTIDNode() = default;
        ASTIDNode(std::string, data_type);
        ASTIDNode(std::string, data_type, TableEntry*, TableEntry*, TableEntry*);
        ~ASTIDNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
