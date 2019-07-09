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
        level++;
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
        body = nullptr;
        fun_list = nullptr;
    }

    ASTMainNode::ASTMainNode(ASTBodyNode* n) : ASTStructuralNode("MAIN",  MAIN, UNKNOWN)
    {
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
    }

    void ASTMainNode::add_function(wic::ASTFunctionNode *node)
    {
        if (fun_list == nullptr)
        {
            fun_list = node;
            return;
        }

        ASTFunctionNode* curr = fun_list;
        while (curr != nullptr)
        {
            curr = reinterpret_cast<ASTFunctionNode *>(curr->next);
        }
        curr = node;
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
        cg->push_stack();
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

    void ASTArgumentNode::add_argument(wic::ASTNode *arg)
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
                        cg->push_mem(entry_d.var.offset,
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
                if (node->get_data_type() != REAL) cg->push_reg(r, "Loading values as function argument (" + cg->translate_reg(r) + ")");
                else cg->push_float_reg(r, "Loading function argument (" + cg->translate_reg(r) + ")");
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

    ASTParamNode::ASTParamNode() : ASTStructuralNode("PARAM", PARAM, UNKNOWN)
    {
        num_params = 0;
        param_mem = 2 * 4; // Make room for the return address and previous EBP
    }

    ASTParamNode::ASTParamNode(ASTIDNode* param) : ASTStructuralNode("PARAM", PARAM, UNKNOWN)
    {
        num_params = 1;
        param_mem = 2 * 4; // Make room for the return address and previous EBP
        add_params(param);
    }

    ASTParamNode::~ASTParamNode()
    {
        delete params;
    }

    unsigned int ASTParamNode::get_num_params()
    {
        return num_params;
    }

    ASTIDNode* ASTParamNode::get_params()
    {
        return params;
    }

    void ASTParamNode::add_params(wic::ASTIDNode *param)
    {
        if (params == nullptr)
        {
            params = param;
            return;
        }

        ASTIDNode* curr = params;
        while (curr != nullptr)
        {
            curr = reinterpret_cast<ASTIDNode *>(curr->next);
        }
        curr = param;

        num_params++;
    }

    ASTIDNode* ASTParamNode::lookup(std::string id)
    {
        ASTIDNode* curr = params;

        while (curr->next != nullptr)
        {
            std::string node_id = curr->get_id();
            if (node_id.compare(id) == 0) return curr;
            curr = reinterpret_cast<ASTIDNode *>(curr->next);
        }

        return nullptr;
    }

    cpu_registers ASTParamNode::to_code(section_enum section, CodeGenerator *cg)
    {
        ASTIDNode* curr = params;
        int count = num_params;

        while (curr->next != nullptr)
        {
            entry_data entry_d;
            entry_d.var.global = false;
            entry_d.var.stat = false;
            entry_d.var.local = true;
            entry_d.var.type = curr->get_data_type();

            switch (get_data_type())
            {
                case BOOL:
                case ARRAY_BOOL:
                case CHAR:
                case STRING:
                    entry_d.var.size = 1;
                    break;
                default:
                    entry_d.var.size = 4;
                    break;
            }

            entry_d.var.array_selection = 0;
            entry_d.var.offset = (4 * count) + (entry_d.var.array_length / 4) + param_mem;

            lst->insert(curr->get_id(), entry_d, yylineno, level+1);

            curr = reinterpret_cast<ASTIDNode *>(curr->next);

            count--;
        }
    }

    ASTReturnNode::ASTReturnNode() : ASTStructuralNode("RETURN", RET, UNKNOWN) {}

    ASTReturnNode::ASTReturnNode(ASTNode* ret) : ASTStructuralNode("RETURN", RET, ret->get_data_type())
    {
        this->ret = ret;
    }

    cpu_registers ASTReturnNode::to_code(section_enum section, CodeGenerator *cg)
    {
        cpu_registers r = ret->to_code(section, cg);
        cg->free_reg(EAX);
        cg->write(section, "c%s%s#s", "movl", cg->translate_reg(r), cg->translate_reg(EAX), "Return value saved in " + cg->translate_reg(EAX) + " register");
    }
}
