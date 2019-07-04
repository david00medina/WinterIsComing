#include "ASTSymbolTableNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

namespace wic
{
    ASTSymbolTableNode::ASTSymbolTableNode(std::string name, std::string id, wic::node_type node_t, wic::data_type data_t)
        : ASTNode(name, node_t, data_t)
    {
        if (&id != nullptr) this->id = id;
    }

    ASTSymbolTableNode::ASTSymbolTableNode(std::string name, std::string id, wic::node_type node_t, wic::data_type data_t,
                                           wic::TableEntry* global_te, wic::TableEntry* static_te, wic::TableEntry* local_te)
        : ASTNode(name, node_t, data_t)
    {
        if (&id != nullptr) this->id = id;

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
        if (&id != nullptr) this->id = *id;
    }

    TableEntry* ASTSymbolTableNode::get_entry()
    {
        if (global_te != nullptr) return global_te;
        else if (static_te != nullptr) return static_te;
        else return local_te;
    }

    void ASTSymbolTableNode::set_global_entry(wic::TableEntry *global_te)
    {
        this->global_te = global_te;
    }

    void ASTSymbolTableNode::set_static_entry(wic::TableEntry *static_te)
    {
        this->static_te = static_te;
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

    ASTCallNode::ASTCallNode(std::string id, wic::data_type data_t, wic::ASTNode *args, wic::ASTNode *body)
        : ASTSymbolTableNode("CALL", id, CALL, data_t)
    {
        if (&id != nullptr) this->id = id;
        this->args = args;
        this->body = body;
    }

    ASTCallNode::ASTCallNode(std::string id, wic::data_type data_t, wic::ASTNode *args, wic::ASTNode *body, wic::TableEntry *global_te)
        : ASTSymbolTableNode("CALL", id, CALL, data_t, global_te, nullptr, nullptr)
    {
        if (&id != nullptr) this->id = id;
        this->args = args;
        this->body = body;
    }

    ASTCallNode::~ASTCallNode()
    {
        delete body;
        delete args;
    }

    ASTNode* ASTCallNode::get_args()
    {
        return args;
    }

    ASTNode* ASTCallNode::get_body()
    {
        return body;
    }

    cpu_registers ASTCallNode::to_code(CodeGenerator *cg) {}

    ASTIDNode::ASTIDNode(std::string id, wic::data_type data_t) : ASTSymbolTableNode("ID", id, wic::ID, data_t) {}

    ASTIDNode::ASTIDNode(std::string id, wic::data_type data_t, wic::TableEntry *global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
        : ASTSymbolTableNode("ID", id, wic::ID, data_t, global_te, static_te, local_te) {}

    cpu_registers ASTIDNode::to_code(CodeGenerator *cg)
    {
        return cg->get_reg();
    }
}