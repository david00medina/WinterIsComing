#include "ASTOperatorNode.hpp"

namespace wic
{
    ASTOperatorNode::ASTOperatorNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *ptr1, wic::ASTNode *ptr3)
    {
        this->node_t = node_t;
        this->data_t = data_t;
        this->ptr1 = ptr1;
        this->ptr3 = ptr3;
    }

    void ASTOperatorNode::set_operators(wic::ASTNode *op1, wic::ASTNode *op2)
    {
        ptr1 = op1;
        ptr3 = op2;
    }

    ASTSumNode::ASTSumNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::SUM, data_t, op1, op2) { name = "SUM"; }

    ASTSubNode::ASTSubNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::SUB, data_t, op1, op2) { name = "SUBTRACT"; }

    ASTProdNode::ASTProdNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::PROD, data_t, op1, op2) { name = "PRODUCT"; }

    ASTDivNode::ASTDivNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::DIV, data_t, op1, op2) { name = "DIVISION"; }

    ASTPowerNode::ASTPowerNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::POWER, data_t, op1, op2) { name = "POWER"; }

    ASTRadicalNode::ASTRadicalNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::RADICAL, data_t, op1, op2) { name = "RADICAL"; }

    ASTModNode::ASTModNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::MOD, data_t, op1, op2) { name = "MODULUS"; }

    ASTAssignNode::ASTAssignNode(wic::data_type data_t, wic::ASTNode *op1, wic::ASTNode *op2)
        : ASTOperatorNode(wic::ASSIGN, data_t, op1, op2) { name = "ASSIGN"; }
}