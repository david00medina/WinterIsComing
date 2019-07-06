#include "ASTSymbolTableNode.hpp"
#include "../structural-node/ASTStructuralNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../../../../error-manager/ErrorManager.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

extern int yylineno;
extern int level;

namespace wic
{
    ASTSymbolTableNode::ASTSymbolTableNode(std::string name, std::string id, wic::node_type node_t, wic::data_type data_t)
        : ASTNode(name, node_t, data_t)
    {
        this->id = id;
    }

    ASTSymbolTableNode::ASTSymbolTableNode(std::string name, std::string id, wic::node_type node_t, wic::data_type data_t,
                                           wic::TableEntry* global_te, wic::TableEntry* static_te, wic::TableEntry* local_te)
        : ASTNode(name, node_t, data_t)
    {
        this->id = id;
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

    void ASTSymbolTableNode::check_error(std::string msg)
    {
        switch (get_node_type())
        {
            case ID:
                if (local_te->get_scope() == static_te->get_scope()) ErrorManager::send(REDECLARATION_VAR, msg);
                else if (local_te == nullptr && static_te == nullptr && global_te == nullptr) ErrorManager::send(NOT_DECLARED_VAR, msg);
                break;
            case CALL:
                if (global_te == nullptr) ErrorManager::send(NOT_DECLARED_FUN, msg);
                break;
            default:
                break;
        }
    }

    const char* ASTSymbolTableNode::get_id()
    {
        return id.c_str();
    }

    void ASTSymbolTableNode::set_id(std::string *id)
    {
        if (id != nullptr) this->id = *id;
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
        return !(global_te == nullptr && static_te == nullptr && local_te == nullptr);
    }

    void ASTSymbolTableNode::print()
    {
        std::cout << "(" << name << ", " << id << ", " << type_data_str[data_t] << ")";
    }

    ASTFunctionNode::ASTFunctionNode(std::string id, wic::data_type data_t, wic::ASTParamNode *param, wic::ASTBodyNode *body, wic::ASTReturnNode* ret)
        : ASTSymbolTableNode("FUNCTION", id, FUNCTION, data_t)
    {
        this->params = param;
        this->body = body;
        this->ret = ret;

        entry_data entry_d;

        fun_info->params_no = param->get_num_params();
        fun_info->return_type = data_t;


        ASTIDNode* curr = params->get_params();

        param_list* curr_params = nullptr;

        while (curr != nullptr)
        {
            if (curr_params == nullptr) curr_params = &fun_info->params;

            curr_params->id = (char*)curr->get_id();
            curr_params->type = curr->get_data_type();

            curr = reinterpret_cast<ASTIDNode *>(curr->next);

            param_list* new_param = new param_list;
            curr_params->next = new_param;
        }

        entry_d.fun = *fun_info;

        gst->insert(id.c_str(), entry_d, yylineno, level);
        global_te = gst->lookup(id.c_str());
    }

    ASTFunctionNode::~ASTFunctionNode()
    {
        delete params;
        delete body;
    }

    ASTNode* ASTFunctionNode::get_body()
    {
        return body;
    }

    cpu_registers ASTFunctionNode::to_code(wic::CodeGenerator *cg)
    {
        params->to_code(cg);
        body->to_code(cg);
        return ret->to_code(cg);
    }

    ASTCallNode::ASTCallNode(std::string id, wic::data_type data_t, wic::ASTArgumentNode *arg)
        : ASTSymbolTableNode("CALL", id, CALL, data_t)
    {
        if (arg->get_node_type() == ARG) this->args = arg;
        global_te = gst->lookup(id.c_str());
    }

    ASTCallNode::~ASTCallNode()
    {
        delete args;
    }

    ASTNode* ASTCallNode::get_args()
    {
        return args;
    }

    cpu_registers ASTCallNode::to_code(CodeGenerator *cg)
    {
        check_error(id);

        if (args != nullptr) args->to_code(cg);
        cg->write(CODE, "c%s#s", "call", "_" + id, "Call the function \'" + id + "\'");

        // TODO: Si el registro EAX no está libre pasar el contenido a otro registro diferente.
        if (cg->is_used(EAX)) cg->lock_reg(EAX);

        return EAX;
    }

    ASTIDNode::ASTIDNode(std::string id, wic::data_type data_t) : ASTSymbolTableNode("ID", id, wic::ID, data_t)
    {
        local_te = lst->lookup(id.c_str());
        static_te = sst->lookup(id.c_str());
        global_te = gst->lookup(id.c_str());

        if (local_te != nullptr && static_te != nullptr
            && local_te->get_scope() <= level && static_te->get_scope() <= level)
        {

            global_te = nullptr;

            if (local_te->get_line() < static_te->get_line())
            {
                static_te = nullptr;
            }
            else local_te = nullptr;

        }
    }

    ASTIDNode::ASTIDNode(std::string id, wic::data_type data_t, wic::TableEntry *global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
        : ASTSymbolTableNode("ID", id, wic::ID, data_t, global_te, static_te, local_te) {}

    cpu_registers ASTIDNode::to_code(CodeGenerator *cg)
    {
        check_error(id);
        cpu_registers r = cg->get_reg();

        entry_data entry_d;
        if (static_te != nullptr) entry_d = static_te->get_data();
        else if (local_te != nullptr) entry_d = local_te->get_data();
        else if (global_te != nullptr) global_te->get_data();

        int offset = entry_d.var.offset - entry_d.var.array_selection;
        cg->write(CODE, "c%s%s#s", "movl", std::to_string(offset) + cg->translate_reg(EBP), cg->translate_reg(r), "Get value from \'" + id + "\' variable");

        return r;
    }
}