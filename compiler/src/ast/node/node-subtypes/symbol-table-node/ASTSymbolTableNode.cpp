#include "ASTSymbolTableNode.hpp"
#include "../structural-node/ASTStructuralNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../../../../error-manager/ErrorManager.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

extern int yylineno;
extern int level;
extern int call_level;

namespace wic
{
    ASTSymbolTableNode::ASTSymbolTableNode(std::string name, std::string id, wic::node_type node_t, wic::data_type data_t)
        : ASTNode(name, node_t, data_t)
    {
        this->id = id.c_str();
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
                if (local_te != nullptr && static_te != nullptr && local_te->get_scope() == static_te->get_scope()) ErrorManager::send(REDECLARATION_VAR, msg);
                if (local_te == nullptr && static_te == nullptr && global_te == nullptr) ErrorManager::send(NOT_DECLARED_VAR, msg);
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

    ASTFunctionNode::ASTFunctionNode(std::string id, entry_data entry_d)
        : ASTSymbolTableNode("FUNCTION", id, FUNCTION, entry_d.fun.return_type)
    {
        params = nullptr;
        body = new ASTBodyNode();
        ret = new ASTReturnNode(data_t);

        if (gst->lookup(get_id()) == nullptr) gst->insert(get_id(), entry_d, yylineno, 0);
        global_te = gst->lookup(get_id());
    }

    ASTFunctionNode::ASTFunctionNode(std::string id, entry_data entry_d, ASTParamNode *param, ASTBodyNode *body, ASTReturnNode* ret)
        : ASTSymbolTableNode("FUNCTION", id, FUNCTION, entry_d.fun.return_type)
    {
        this->params = param;
        this->body = body;
        this->ret = ret;

        if (gst->lookup(get_id()) == nullptr) gst->insert(id.c_str(), entry_d, yylineno, 0);
        global_te = gst->lookup(get_id());
    }

    ASTFunctionNode::~ASTFunctionNode()
    {
        delete params;
        delete body;
    }

    unsigned int ASTFunctionNode::get_num_params()
    {
        return global_te->get_data().fun.params_no;
    }

    ASTParamNode* ASTFunctionNode::get_params()
    {
        return params;
    }

    void ASTFunctionNode::add_param(ASTParamNode* node)
    {
        if (params == nullptr) params = node;
        else
        {
            ASTParamNode* curr = params;
            while (curr->next != nullptr)
            {
                curr = reinterpret_cast<ASTParamNode *>(curr->next);
            }
            curr->next = node;
        }

        entry_data entry_d = global_te->get_data();
        entry_d.fun.params_no = ++num_params;
        int param_mem = 2 * 4 + entry_d.fun.params_no * 4;

        if (entry_d.fun.params_no == 1)
        {
            entry_d.fun.params.id = (char *) node->get_id();
            entry_d.fun.params.type = node->get_data_type();
            entry_d.fun.params.offset = param_mem;
        }
        else
        {
            param_list* param = &(entry_d.fun.params);

            while (param->next != nullptr) param = param->next;
            param->next = new param_list;
            param->next->id = (char *) node->get_id();
            param->next->type = node->get_data_type();
            param->next->offset = param_mem;
        }

        gst->modify(get_id(), entry_d, yylineno, 0);
        global_te = gst->lookup(get_id());
    }

    ASTBodyNode* ASTFunctionNode::get_body()
    {
        return body;
    }

    ASTReturnNode* ASTFunctionNode::get_return()
    {
        return ret;
    }

    void ASTFunctionNode::set_return(ASTNode* node)
    {
        ret->set_return(node);
    }

    bool ASTFunctionNode::match(std::string id, wic::function* call)
    {
        if (id.compare(id) != 0 || global_te->get_data().fun.params_no != call->params_no
            || global_te->get_data().fun.return_type != call->return_type) return false;

        function func_info = global_te->get_data().fun;
        param_list* curr = &(func_info.params);
        param_list* curr_call = &(call->params);

        while (curr != nullptr && curr_call != nullptr)
        {
            if (curr->type != curr_call->type) return false;
            curr = curr->next;
            curr_call = curr_call->next;
        }

        return true;
    }

    cpu_registers ASTFunctionNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        cg->write(FUNCTION_CODE, "c", ".text");
        cg->write(FUNCTION_CODE, "c%s", ".globl", "_" + id);
        cg->write(FUNCTION_CODE, "c%s%c", ".type", "_" + id, "@function");
        cg->write_label(FUNCTION_CODE, id);

        if (params != nullptr) params->to_code(FUNCTION_CODE, cg);
        body->to_code(FUNCTION_CODE, cg);

        return ret->to_code(FUNCTION_CODE, cg);
    }

    void ASTFunctionNode::print()
    {
        function func = global_te->get_data().fun;

        param_list* curr = &(func.params);

        while (curr != nullptr)
        {
            std::cout << "(id=" << curr->id << ", data_type=" << curr->type
                << ", offset=" << curr->offset << ")" << std::endl;
            curr = curr->next;
        }
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

    entry_data ASTCallNode::get_entry_data()
    {
        return entry_d;
    }

    cpu_registers ASTCallNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error(id);
        entry_d.fun.params_no = args->get_num_args();
        entry_d.fun.return_type = data_t;

        ASTArgumentNode* curr = args;
        param_list* curr_param = new param_list;

        while (curr != nullptr)
        {
            curr_param->type = curr->get_data_type();
            curr_param->next = new param_list;
            curr_param = curr_param->next;
            curr = reinterpret_cast<ASTArgumentNode *>(curr->next);
        }

        if (args != nullptr) args->to_code(section, cg);
        cg->write(section, "c%s#s", "call", "_" + id, "Call the function \'" + id + "\'");

        // TODO: Si el registro EAX no está libre pasar el contenido a otro registro diferente.
        if (cg->is_used(EAX)) cg->lock_reg(EAX);

        return EAX;
    }

    ASTIDNode::ASTIDNode(void *entry_data, void *id)
    {
        name = "ID";
        node_t = wic::ID;
        register_id(entry_data, id);
    }

    ASTIDNode::ASTIDNode(std::string id)
    {
        this->name = "ID";
        this->id = id;
        node_t = ID;

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

        data_t = get_entry()->get_data().var.type;
    }

    ASTIDNode::ASTIDNode(std::string id, wic::data_type data_t, wic::TableEntry *global_te, wic::TableEntry *static_te, wic::TableEntry *local_te)
        : ASTSymbolTableNode("ID", id, wic::ID, data_t, global_te, static_te, local_te) {}

    void ASTIDNode::register_id(void* elem1, void* elem2)
    {
        entry_data* entry_d = static_cast<entry_data *>(elem1);
        id = static_cast<char *>(elem2);
        data_t = entry_d->var.type;

        if (entry_d->var.global)
        {
            gst->insert(id.c_str(), *entry_d, yylineno, level);
            global_te = gst->lookup(id.c_str());
        }
        else if (entry_d->var.local)
        {
            lst->insert(id.c_str(), *entry_d, yylineno, level);
            local_te = lst->lookup(id.c_str());
        }
        else if (entry_d->var.stat)
        {
            sst->insert(id.c_str(), *entry_d, yylineno, level);
            static_te = sst->lookup(id.c_str());
        }
    }

    cpu_registers ASTIDNode::get_var(section_enum section, CodeGenerator *cg)
    {
        cpu_registers r = cg->get_reg();

        entry_data entry_d;
        if (sst->lookup(id.c_str()) != nullptr) entry_d = static_te->get_data();
        else if (lst->lookup(id.c_str()) != nullptr) entry_d = local_te->get_data();
        else if (gst->lookup(id.c_str()) != nullptr) entry_d = global_te->get_data();

        if (is_initialization)
        {
            if (entry_d.var.stat)
            {
                // TODO: Faltan static
            } else if (entry_d.var.local)
            {
                cg->write(section, "c%c%s#s", "subl", "$4", cg->translate_reg(ESP), "Initialization of variable \'" + id + "\'");
            } else if (entry_d.var.global)
            {
                cg->write(DATA, "c%s", ".globl", id);
                cg->write(DATA, "c", ".bss");
                cg->write(DATA, "c%s", ".align", std::to_string(entry_d.var.size));
                cg->write(DATA, "c%s%c", ".type", id, "@object");
                cg->write(DATA, "c%s%s", ".size", id, std::to_string(entry_d.var.size));
                cg->write_label(DATA, id);
                cg->write(DATA, "c%s", ".zero", std::to_string(entry_d.var.size));
            }

        } else {
            if (entry_d.var.stat) {
                std::cout << "STAT" << std::endl;
                cg->write(section, "c%s%s#s", "movl", id, cg->translate_reg(r), "Load static variable \'" + id + "\'");
            } else if (entry_d.var.local) {
                std::cout << "LOCAL" << std::endl;
                int offset = entry_d.var.offset - entry_d.var.array_selection;
                cg->write(section, "c%s%s#s", "movl", std::to_string(offset) + "(" + cg->translate_reg(EBP) + ")",
                          cg->translate_reg(r), "Load local variable \'" + id + "\'");
            } else if (entry_d.var.global) {
                std::cout << "GLOBAL" << std::endl;
                cg->write(section, "c%s%s#s", "movl", id, cg->translate_reg(r), "Load global variable \'" + id + "\'");
            }
            return r;
        }

        return NONE;
    }

    void ASTIDNode::set_initialization(bool is_initialization)
    {
        this->is_initialization = is_initialization;
    }

    cpu_registers ASTIDNode::to_code(section_enum section, CodeGenerator *cg)
    {
        check_error(id);
        return get_var(section, cg);
    }

    ASTParamNode::ASTParamNode(std::string id, entry_data entry_d) : ASTSymbolTableNode("PARAM", id, PARAM, entry_d.var.type) {}

    ASTParamNode::~ASTParamNode()
    {
        delete params;
    }

    cpu_registers ASTParamNode::to_code(section_enum section, CodeGenerator *cg) {}
}