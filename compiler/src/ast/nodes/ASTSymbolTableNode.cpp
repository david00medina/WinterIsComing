#include "ASTSymbolTableNode.hpp"

namespace wic
{
    ASTSymbolTableNode::ASTSymbolTableNode(std::string *id, wic::node_type node_t, wic::data_type data_t)
    {
        if (id != nullptr) this->id = *id;
        this->node_t = node_t;
        this->data_t = data_t;
    }

    ASTSymbolTableNode::ASTSymbolTableNode(std::string *id, wic::node_type node_t, wic::data_type data_t,
                                           wic::SSymbolTable *sst, wic::LSymbolTable *lst)
    {
        if (id != nullptr) this->id = *id;
        this->node_t = node_t;
        this->data_t = data_t;

        this->sst = sst;
        this->lst = lst;
    }

    ASTSymbolTableNode::~ASTSymbolTableNode()
    {
        delete sst;
        delete lst;
    }

    const char* ASTSymbolTableNode::get_id()
    {
        return id.c_str();
    }

    void ASTSymbolTableNode::set_id(std::string *id)
    {
        if (id != nullptr) this->id = *id;
    }

    SSymbolTable* ASTSymbolTableNode::get_sst()
    {
        return sst;
    }

    void ASTSymbolTableNode::set_sst(wic::SSymbolTable *sst)
    {
        this->sst = sst;
    }

    LSymbolTable* ASTSymbolTableNode::get_lst()
    {
        return lst;
    }

    void ASTSymbolTableNode::set_lst(wic::LSymbolTable *lst)
    {
        this->lst = lst;
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

    ASTCallNode::ASTCallNode(std::string *id, wic::data_type data_t, wic::ASTNode *arg, wic::SSymbolTable *sst, wic::LSymbolTable *lst)
    {
        args_i = 0;
        if (id != nullptr) this->id = *id;
        this->node_t = wic::CALL;
        this->data_t = data_t;
        add_arg(arg);
        this->sst = sst;
        this->lst = lst;
        name = "CALL";
    }

    ASTCallNode::~ASTCallNode()
    {
        delete ptr1;
        delete *ptr2;
        delete ptr3;
        delete *args;
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

    ASTIDNode::ASTIDNode(std::string *id, wic::data_type data_t, wic::SSymbolTable *sst, wic::LSymbolTable *lst)
        : ASTSymbolTableNode(id, wic::ID, data_t, sst, lst) { name = "ID"; }
}