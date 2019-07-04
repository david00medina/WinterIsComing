#include "ASTStructuralNode.hpp"
#include "../operator-node/ASTArithmeticNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    ASTStructuralNode::ASTStructuralNode(std::string name, wic::node_type node_t, wic::data_type data_t, ASTNode *n)
        : ASTNode(name, node_t, data_t)
    {
        next = n;
    }

    ASTStructuralNode::ASTStructuralNode(std::string name, node_type node_t, data_type data_t)
        : ASTNode(name, node_t, data_t)
    {
        next = nullptr;
    }

    ASTBodyNode::ASTBodyNode() : ASTStructuralNode("BODY", BODY, UNKNOWN) {}

    ASTBodyNode::ASTBodyNode(ASTNode* n) : ASTStructuralNode("BODY", BODY, UNKNOWN, n) {}

    void ASTBodyNode::add_instr(wic::ASTNode *node)
    {
        // TODO: No añade los nodos de instrucción
        if (instr == nullptr) {
            instr = node;
            return;
        }

        ASTNode* curr = instr;
        while (curr != nullptr)
        {
            curr = curr->next;
        }

        curr = node;
    }

    cpu_registers ASTBodyNode::to_code(CodeGenerator *cg)
    {
        ASTNode* curr = instr;
        while (curr != nullptr)
        {
            curr->to_code(cg);
            curr = curr->next;
        }

        return NONE;
    }

    ASTMainNode::ASTMainNode() : ASTStructuralNode("MAIN", MAIN, UNKNOWN) {}

    ASTMainNode::ASTMainNode(ASTNode* n) : ASTStructuralNode("MAIN",  MAIN, UNKNOWN, n) {}

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

    ASTReturnNode::ASTReturnNode() : ASTStructuralNode("RETURN", RET, UNKNOWN) {}

    ASTReturnNode::ASTReturnNode(ASTNode* n) : ASTStructuralNode("RETURN", RET, UNKNOWN, n) {}

    cpu_registers ASTReturnNode::to_code(CodeGenerator *cg) {}

    ASTParamNode::ASTParamNode() : ASTStructuralNode("PARAM", PARAM, UNKNOWN) {}

    ASTParamNode::ASTParamNode(ASTNode* n) : ASTStructuralNode("PARAM", PARAM, UNKNOWN, n) {}

    cpu_registers ASTParamNode::to_code(CodeGenerator *cg) {}
}
