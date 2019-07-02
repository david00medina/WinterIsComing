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
        : ASTNode(name, node_t, data_t) {}

    ASTMainNode::ASTMainNode() : ASTStructuralNode("MAIN", MAIN, UNKNOWN) {}

    ASTMainNode::ASTMainNode(ASTNode* n) : ASTStructuralNode("MAIN",  MAIN, UNKNOWN, n) {}

    cpu_registers ASTMainNode::to_code(CodeGenerator *cg) {
        cg->init();

        ASTNode* node = body;
        while (node != nullptr)
        {
            reinterpret_cast<ASTSumNode *>(node)->to_code(cg);
            node = reinterpret_cast<ASTMainNode *>(node)->next;
        std::cout << "HOLA" << std::endl;
        }
        return NONE;
    }

    void ASTMainNode::add_body(wic::ASTNode *node)
    {
        if (body == nullptr) body = node;
        add_node(body, node);
    }

    ASTBodyNode::ASTBodyNode() : ASTStructuralNode("BODY", BODY, UNKNOWN) {}

    ASTBodyNode::ASTBodyNode(ASTNode* n) : ASTStructuralNode("BODY", BODY, UNKNOWN, n) {}

    cpu_registers ASTBodyNode::to_code(CodeGenerator *cg) {}

    ASTReturnNode::ASTReturnNode() : ASTStructuralNode("RETURN", RET, UNKNOWN) {}

    ASTReturnNode::ASTReturnNode(ASTNode* n) : ASTStructuralNode("RETURN", RET, UNKNOWN, n) {}

    cpu_registers ASTReturnNode::to_code(CodeGenerator *cg) {}

    ASTParamNode::ASTParamNode() : ASTStructuralNode("PARAM", PARAM, UNKNOWN) {}

    ASTParamNode::ASTParamNode(ASTNode* n) : ASTStructuralNode("PARAM", PARAM, UNKNOWN, n) {}

    cpu_registers ASTParamNode::to_code(CodeGenerator *cg) {}
}
