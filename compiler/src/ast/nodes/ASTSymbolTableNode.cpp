#include "ASTSymbolTableNode.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

namespace wic
{
    ASTSymbolTableNode::ASTSymbolTableNode(std::string *id, wic::node_type node_t, wic::data_type data_t)
    {
        if (id != nullptr) this->id = *id;
        this->node_t = node_t;
        this->data_t = data_t;
    }

    ASTSymbolTableNode::ASTSymbolTableNode(std::string *id, wic::node_type node_t, wic::data_type data_t,
                                           wic::TableEntry* global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
    {
        if (id != nullptr) this->id = *id;
        this->node_t = node_t;
        this->data_t = data_t;

        this->global_te = global_te;
        this->static_te = static_te;
        this->local_te = local_te;
    }

    ASTSymbolTableNode::~ASTSymbolTableNode()
    {
        delete global_te;
        delete static_te;
        delete local_te;
    }

    const char* ASTSymbolTableNode::get_id()
    {
        return id.c_str();
    }

    void ASTSymbolTableNode::set_id(std::string *id)
    {
        if (id != nullptr) this->id = *id;
    }

    TableEntry* ASTSymbolTableNode::get_global_entry()
    {
        return global_te;
    }

    void ASTSymbolTableNode::set_global_entry(wic::TableEntry *global_te)
    {
        this->global_te = global_te;
    }

    TableEntry* ASTSymbolTableNode::get_static_entry()
    {
        return static_te;
    }

    void ASTSymbolTableNode::set_static_entry(wic::TableEntry *static_te)
    {
        this->static_te = static_te;
    }

    TableEntry* ASTSymbolTableNode::get_local_entry()
    {
        return local_te;
    }

    void ASTSymbolTableNode::set_local_entry(wic::TableEntry *local_te)
    {
        this->local_te = local_te;
    }

    bool ASTSymbolTableNode::is_registered()
    {
        global_te = gst->lookup(id.c_str());
        static_te = sst->lookup(id.c_str());
        local_te = lst->lookup(id.c_str());
        if (global_te == nullptr && static_te == nullptr && local_te == nullptr) return false;

        return true;
    }

    void ASTSymbolTableNode::print()
    {
        std::cout << "(" << name << ", " << id << ", " << type_data_str[data_t] << ")";
    }

    ASTCallNode::ASTCallNode(std::string *id, wic::data_type data_t, wic::ASTNode *arg)
    {
        args_i = 0;
        if (id != nullptr) this->id = *id;
        this->node_t = wic::CALL;
        this->data_t = data_t;
        add_arg(arg);
        name = "CALL";
    }

    ASTCallNode::ASTCallNode(std::string *id, wic::data_type data_t, wic::ASTNode *arg,
            wic::TableEntry *global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
    {
        args_i = 0;
        if (id != nullptr) this->id = *id;
        this->node_t = wic::CALL;
        this->data_t = data_t;
        add_arg(arg);
        this->global_te = global_te;
        this->static_te = static_te;
        this->local_te = local_te;
        name = "CALL";
    }

    ASTCallNode::~ASTCallNode()
    {
        delete ptr1;
        delete *ptr2;
        delete ptr3;
        delete *args;
        delete global_te;
        delete static_te;
        delete local_te;
    }

    ASTNode** ASTCallNode::get_args()
    {
        return args;
    }

    void ASTCallNode::add_arg(wic::ASTNode *arg)
    {
        if (arg != nullptr) this->args[args_i++] = arg;
    }

    ASTIDNode::ASTIDNode(std::string *id, wic::data_type data_t) : ASTSymbolTableNode(id, wic::ID, data_t) { name = "ID"; }

    ASTIDNode::ASTIDNode(std::string *id, wic::data_type data_t, wic::TableEntry *global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
        : ASTSymbolTableNode(id, wic::ID, data_t, global_te, static_te, local_te) { name = "ID"; }
}