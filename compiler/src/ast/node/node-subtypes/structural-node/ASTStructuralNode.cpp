#include "ASTStructuralNode.hpp"
#include "../operator-node/ASTArithmeticNode.hpp"
#include "../../../../symbol-table/SymbolTable.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../symbol-table-node/ASTSymbolTableNode.hpp"
#include "../../../../error-manager/ErrorManager.hpp"
#include "../leaf-node/ASTLeafNode.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

extern int yylineno;
extern int level;

namespace wic
{
    ASTStructuralNode::ASTStructuralNode(std::string name, wic::node_type node_t, wic::data_type data_t)
        : ASTNode(name, node_t, data_t) {}

    ASTBodyNode::ASTBodyNode() : ASTStructuralNode("BODY", BODY, UNKNOWN)
    {
        instr_count = 0;
    }

    ASTBodyNode::ASTBodyNode(ASTNode* instr) : ASTStructuralNode("BODY", BODY, UNKNOWN)
    {
        instr_count = 0;
        add_instr(instr);
    }

    ASTBodyNode::~ASTBodyNode()
    {
        delete instr;
        delete next;
    }

    void ASTBodyNode::set_main(wic::ASTMainNode *main)
    {
        this->main = main;
    }

    void ASTBodyNode::add_instr(ASTNode *node)
    {
        add_node(instr, node);
        instr_count++;
    }

    unsigned int ASTBodyNode::get_instr_count()
    {
        return instr_count;
    }

    cpu_registers ASTBodyNode::to_code(section_enum section, CodeGenerator *cg) {
        ASTNode* curr = instr;

        cg->push_stack(section);

        while (curr != nullptr) {
            curr->to_code(section, cg);
            if (curr->get_node_type() == CALL) {
                ASTCallNode* call = reinterpret_cast<ASTCallNode *>(curr);

                function fun = call->get_entry_data().fun;
                if (!main->match_function(call->get_id(), &fun))
                    ErrorManager::send(NOT_DECLARED_FUN, call->get_id());
            }

            curr = curr->next;
        }

        lst->erase(level);
        level--;
        return NONE;
    }

    ASTMainNode::ASTMainNode() : ASTStructuralNode("MAIN", MAIN, UNKNOWN)
    {
        body_count = 1;
        func_count = 0;
        body = new wic::ASTBodyNode();
        fun_list = nullptr;
    }

    ASTMainNode::ASTMainNode(ASTBodyNode* n) : ASTStructuralNode("MAIN",  MAIN, UNKNOWN)
    {
        body_count = 0;
        func_count = 0;
        add_body(n);
        fun_list = nullptr;
    }

    ASTMainNode::~ASTMainNode()
    {
        delete body;
    }

    void ASTMainNode::add_body(wic::ASTBodyNode *node)
    {
        if (body == nullptr)
        {
            body = node;
            return;
        }

        ASTBodyNode* curr = body;
        while (curr != nullptr)
        {
            curr = curr->next;
        }
        curr = node;

        body_count++;
    }

    ASTBodyNode* ASTMainNode::get_body()
    {
        return body;
    }

    void ASTMainNode::add_function(wic::ASTFunctionNode *node)
    {
        if (fun_list == nullptr)
        {
            fun_list = node;
            return;
        }

        ASTFunctionNode* curr = fun_list;
        while (curr->next != nullptr)
        {
            curr = reinterpret_cast<ASTFunctionNode *>(curr->next);
        }
        curr->next = reinterpret_cast<ASTNode *>(node);

        func_count++;
    }

    ASTFunctionNode * ASTMainNode::lookup_function(std::string id)
    {
        if (fun_list == nullptr) return nullptr;

        ASTFunctionNode* curr = fun_list;
        while (curr != nullptr)
        {
            if (strcmp(curr->get_id(), id.c_str()) == 0) return curr;
            curr = reinterpret_cast<ASTFunctionNode *>(curr->next);
        }

        return nullptr;
    }

    ASTFunctionNode* ASTMainNode::get_last_function()
    {
        if (fun_list == nullptr) return nullptr;

        ASTFunctionNode* curr = fun_list;

        while (curr->next != nullptr)
        {
            curr = reinterpret_cast<ASTFunctionNode *>(curr->next);
        }

        return curr;
    }

    bool ASTMainNode::match_function(std::string id, function* call)
    {
        if(gst->lookup(id.c_str()) == nullptr) return false;

        ASTFunctionNode* curr = fun_list;

        while (curr != nullptr)
        {
            if (curr->match(id, call)) return true;
            curr = reinterpret_cast<ASTFunctionNode *>(curr->next);
        }

        return false;
    }

    cpu_registers ASTMainNode::to_code(section_enum section, CodeGenerator *cg) {
        cg->init();

        body->set_main(this);
        ASTBodyNode* node = body;
        while (node != nullptr)
        {
            node->to_code(section, cg);
            node = node->next;
        }
        cg->exit();

        ASTFunctionNode* fun = fun_list;
        while (fun != nullptr)
        {
            fun->to_code(section, cg);
            fun = reinterpret_cast<ASTFunctionNode *>(fun->next);
        }

        cg->end();

        return NONE;
    }

    ASTArgumentNode::ASTArgumentNode() : ASTStructuralNode("ARGUMENT", ARG, UNKNOWN)
    {
        num_args = 0;
    }

    ASTArgumentNode::ASTArgumentNode(wic::ASTNode *arg) : ASTStructuralNode("ARGUMENT", ARG, UNKNOWN)
    {
        num_args = 0;
        memory += 4;
        add_argument(arg);
    }

    ASTArgumentNode::~ASTArgumentNode()
    {
        delete args;
    }

    void ASTArgumentNode::add_argument(ASTNode *arg)
    {
        add_node(args, arg);
        num_args++;
        memory += 4;
    }

    void ASTArgumentNode::load_args(wic::ASTNode *node, section_enum section, wic::CodeGenerator *cg)
    {
        cpu_registers r = node->to_code(section, cg);

        switch (node->get_node_type())
        {
            case ID:
                {
                    ASTIDNode* id_node = reinterpret_cast<ASTIDNode *>(node);
                    entry_data entry_d = id_node->get_entry()->get_data();
                    int offset = id_node->get_entry()->get_data().var.offset;
                    std::string id = id_node->get_id();

                    if (!entry_d.var.global || !entry_d.var.stat)
                    {
                        cg->push_mem(section, entry_d.var.offset,
                                "Loading variable \'" + id + "\' as function arguments (" + cg->get_mem_var(offset) + ")");
                    } else
                    {
                        if (id_node->get_data_type() != REAL)
                        {
                            cg->write(section, "c%s%s#s", "movl", "." + id, cg->get_mem_var(offset),
                                 "Loading variable \'" + id + "\' at "
                                 + cg->get_mem_var(offset) + " as function arguments");
                        }
                        else
                        {
                            cg->write(section, "c%s%s#s", "movs", "." + id, cg->get_mem_var(offset),
                                                   "Loading variable \'" + id + "\' at "
                                                   + cg->get_mem_var(offset) + " as function arguments");
                        }
                    }
                }
                break;
            default:
                if (node->get_data_type() != REAL) cg->push_reg(section, r, "Loading values as function argument (" + cg->translate_reg(r) + ")");
                else cg->push_float_reg(section, r, "Loading function argument (" + cg->translate_reg(r) + ")");
                break;
        }

        cg->free_reg(r);
    }

    int ASTArgumentNode::get_num_args()
    {
        return num_args;
    }

    cpu_registers ASTArgumentNode::to_code(section_enum section, wic::CodeGenerator *cg)
    {
        ASTNode* curr = args;
        curr = curr->next;

        while (curr != nullptr)
        {
            load_args(curr, section, cg);
            curr = curr->next;
        }
    }

    ASTReturnNode::ASTReturnNode(data_type data_t) : ASTStructuralNode("RETURN", RET, data_t) {}

    ASTReturnNode::ASTReturnNode(ASTNode* ret, data_type data_t) : ASTStructuralNode("RETURN", RET, data_t)
    {
        // TODO: Devolver error si data_t != ret->get_data_type()
        this->ret = ret;
    }

    void ASTReturnNode::set_return(wic::ASTNode *ret)
    {
        this->ret = ret;
    }

    cpu_registers ASTReturnNode::to_code(section_enum section, CodeGenerator *cg)
    {
        if (ret != nullptr) {
            cpu_registers r = ret->to_code(section, cg);

            cg->free_reg(EAX);
            cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r), cg->translate_reg(EAX),
                      "Return value saved in " + cg->translate_reg(EAX) + " register");
        }

        cg->write(section, "c#c", "ret", "Return from function");
    }
}
