#include "ASTStructuralNode.hpp"
#include "../operator-node/ASTArithmeticNode.hpp"
#include "../../../../symbol-table/SymbolTable.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"
#include "../symbol-table-node/ASTSymbolTableNode.hpp"

extern wic::GSymbolTable* gst;
extern wic::SSymbolTable* sst;
extern wic::LSymbolTable* lst;

extern int yylineno;
extern int level;

namespace wic
{
    ASTStructuralNode::ASTStructuralNode(std::string name, wic::node_type node_t, wic::data_type data_t)
        : ASTNode(name, node_t, data_t) {}

    ASTBodyNode::ASTBodyNode() : ASTStructuralNode("BODY", BODY, UNKNOWN) {}

    ASTBodyNode::ASTBodyNode(ASTNode* instr) : ASTStructuralNode("BODY", BODY, UNKNOWN)
    {
        add_instr(instr);
    }

    ASTBodyNode::~ASTBodyNode()
    {
        delete instr;
        delete next;
    }

    void ASTBodyNode::add_instr(ASTNode *node)
    {
        add_node(instr, node);
    }

    cpu_registers ASTBodyNode::to_code(CodeGenerator *cg) {
        ASTNode *curr = instr;
        while (curr != nullptr) {
            cpu_registers ret = curr->to_code(cg);
            curr = curr->next;
        }

        lst->erase(level);
        return NONE;
    }

    ASTMainNode::ASTMainNode() : ASTStructuralNode("MAIN", MAIN, UNKNOWN) {}

    ASTMainNode::ASTMainNode(ASTBodyNode* n) : ASTStructuralNode("MAIN",  MAIN, UNKNOWN)
    {
        add_body(n);
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

    cpu_registers ASTMainNode::to_code(CodeGenerator *cg) {
        cg->init();
        cg->push_stack();

        ASTBodyNode* node = body;

        while (node != nullptr)
        {
            node->to_code(cg);
            node = node->next;
        }
        cg->exit();
        cg->end();

        return NONE;
    }

    ASTArgumentNode::ASTArgumentNode() : ASTStructuralNode("ARGUMENT", ARG, UNKNOWN)
    {
        num_args = 0;
    }

    ASTArgumentNode::ASTArgumentNode(wic::ASTNode *arg) : ASTStructuralNode("ARGUMENT", ARG, UNKNOWN)
    {
        num_args = 1;
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

    void ASTArgumentNode::load_args(wic::ASTNode *node, wic::CodeGenerator *cg)
    {
        cpu_registers r = node->to_code(cg);

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
                            cg->write(CODE, "c%s%s#s", "movl", "." + id, cg->get_mem_var(offset),
                                 "Loading variable \'" + id + "\' at "
                                 + cg->get_mem_var(offset) + " as function arguments");
                        }
                        else
                        {
                            cg->write(CODE, "c%s%s#s", "movs", "." + id, cg->get_mem_var(offset),
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

    cpu_registers ASTArgumentNode::to_code(wic::CodeGenerator *cg)
    {
        ASTNode* curr = args;
        while (curr != nullptr)
        {
            load_args(curr, cg);

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

    cpu_registers ASTParamNode::to_code(CodeGenerator *cg)
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

    cpu_registers ASTReturnNode::to_code(CodeGenerator *cg)
    {
        cpu_registers r = ret->to_code(cg);
        cg->free_reg(EAX);
        cg->write(CODE, "c%s%s#s", "movl", cg->translate_reg(r), cg->translate_reg(EAX), "Return value saved in " + cg->translate_reg(EAX) + " register");
    }
}
