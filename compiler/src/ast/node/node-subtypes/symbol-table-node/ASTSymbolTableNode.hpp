#ifndef ASTSYMBOLTABLENODE_HPP
#define ASTSYMBOLTABLENODE_HPP

#include "../../ASTNode.hpp"
#include "../../../../symbol-table/SymbolTablePack.hpp"
#include "../../../../code-generator/CodeGeneratorPack.hpp"

namespace wic {
    class TableEntry;
    class CodeGenerator;

    class ASTSymbolTableNode : public ASTNode
    {
    protected:
        std::string id;
        TableEntry* global_te;
        TableEntry* static_te;
        TableEntry* local_te;

        void check_error(std::string) {};

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
        virtual cpu_registers to_code(CodeGenerator*) = 0;
        virtual void print();
    };

    class ASTCallNode : public ASTSymbolTableNode
    {
    private:
        ASTNode* args;
        ASTNode* body;

    public:
        ASTCallNode() = default;
        ASTCallNode(std::string, data_type, ASTNode *, ASTNode *);
        ASTCallNode(std::string, data_type, ASTNode *, ASTNode *, TableEntry*);
        ~ASTCallNode();

        ASTNode* get_args();
        ASTNode* get_body();

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTIDNode : public ASTSymbolTableNode
    {
    public:
        ASTIDNode() = default;
        ASTIDNode(std::string, data_type);
        ASTIDNode(std::string, data_type, TableEntry*, TableEntry*, TableEntry*);
        ~ASTIDNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
