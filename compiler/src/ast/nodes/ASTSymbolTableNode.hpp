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
        SSymbolTable *sst;
        LSymbolTable *lst;

    public:
        ASTSymbolTableNode() = default;
        ASTSymbolTableNode(std::string *, node_type, data_type);
        ASTSymbolTableNode(std::string *, node_type, data_type, SSymbolTable *, LSymbolTable *);
        virtual ~ASTSymbolTableNode();

        virtual const char* get_id();
        virtual void set_id(std::string *);
        virtual SSymbolTable* get_sst();
        virtual void set_sst(SSymbolTable*);
        virtual LSymbolTable* get_lst();
        virtual void set_lst(LSymbolTable*);
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
        ASTCallNode(std::string *, data_type, ASTNode *, SSymbolTable *, LSymbolTable *);
        ~ASTCallNode();

        ASTNode** get_args();
        void add_arg(ASTNode*);
    };

    class ASTIDNode : public ASTSymbolTableNode
    {
    public:
        ASTIDNode() = default;
        ASTIDNode(std::string *, data_type);
        ASTIDNode(std::string *, data_type, SSymbolTable *, LSymbolTable *);
        ~ASTIDNode() = default;
    };
}

#endif
