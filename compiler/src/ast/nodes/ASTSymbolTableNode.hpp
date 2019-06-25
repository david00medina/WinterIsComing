#ifndef ASTSYMBOLTABLENODE_HPP
#define ASTSYMBOLTABLENODE_HPP

#include "ASTNode.hpp"
#include "../AbstractSyntaxTreePack.hpp"

#define MAX_ARGS 512

namespace wic {
    class ASTSymbolTableNode : public ASTNode
    {
    protected:
        std::string id;
        TableEntry *global_te;
        TableEntry *static_te;
        TableEntry *local_te;

    public:
        ASTSymbolTableNode() = default;
        ASTSymbolTableNode(std::string *, node_type, data_type);
        ASTSymbolTableNode(std::string *, node_type, data_type, TableEntry*, TableEntry*, TableEntry*);
        virtual ~ASTSymbolTableNode();

        virtual const char* get_id();
        virtual void set_id(std::string *);
        virtual TableEntry* get_global_entry();
        virtual void set_global_entry(TableEntry*);
        virtual TableEntry* get_static_entry();
        virtual void set_static_entry(TableEntry*);
        virtual TableEntry* get_local_entry();
        virtual void set_local_entry(TableEntry*);
        virtual bool is_registered();
        virtual cpu_registers to_code(CodeGenerator*) = 0;
        virtual void print();
    };

    class ASTCallNode : public ASTSymbolTableNode
    {
    private:
        ASTNode *args[MAX_ARGS];
        int args_i;

    public:
        ASTCallNode() = default;
        ASTCallNode(std::string *, data_type, ASTNode *);
        ASTCallNode(std::string *, data_type, ASTNode *, TableEntry*, TableEntry*, TableEntry*);
        ~ASTCallNode();

        ASTNode** get_args();
        void add_arg(ASTNode*);

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTIDNode : public ASTSymbolTableNode
    {
    public:
        ASTIDNode() = default;
        ASTIDNode(std::string *, data_type);
        ASTIDNode(std::string *, data_type, TableEntry*, TableEntry*, TableEntry*);
        ~ASTIDNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
