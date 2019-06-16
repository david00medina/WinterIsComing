#ifndef ASTOPERATORNODE_HPP
#define ASTOPERATORNODE_HPP

#include "ASTNode.hpp"
#include "../AbstractSyntaxTreePack.hpp"

namespace wic {
    class ASTOperatorNode : public ASTNode
    {
    public:
        ASTOperatorNode() = default;
        ASTOperatorNode(node_type, data_type, ASTNode*, ASTNode*);
        ~ASTOperatorNode() = default;

        void set_operators(ASTNode*, ASTNode*);
    };

    class ASTSumNode : public ASTOperatorNode
    {
    public:
        ASTSumNode() = default;
        ASTSumNode(data_type, ASTNode*, ASTNode*);
        ~ASTSumNode() = default;
    };

    class ASTSubNode : public ASTOperatorNode
    {
    public:
        ASTSubNode() = default;
        ASTSubNode(data_type, ASTNode*, ASTNode*);
        ~ASTSubNode() = default;
    };

    class ASTProdNode : public ASTOperatorNode
    {
    public:
        ASTProdNode() = default;
        ASTProdNode(data_type, ASTNode*, ASTNode*);
        ~ASTProdNode() = default;
    };

    class ASTDivNode : public ASTOperatorNode
    {
    public:
        ASTDivNode() = default;
        ASTDivNode(data_type, ASTNode*, ASTNode*);
        ~ASTDivNode() = default;
    };

    class ASTPowerNode : public ASTOperatorNode
    {
    public:
        ASTPowerNode() = default;
        ASTPowerNode(data_type, ASTNode*, ASTNode*);
        ~ASTPowerNode() = default;
    };

    class ASTRadicalNode : public ASTOperatorNode
    {
    public:
        ASTRadicalNode() = default;
        ASTRadicalNode(data_type, ASTNode*, ASTNode*);
        ~ASTRadicalNode() = default;
    };

    class ASTModNode : public ASTOperatorNode
    {
    public:
        ASTModNode() = default;
        ASTModNode(data_type, ASTNode*, ASTNode*);
        ~ASTModNode() = default;
    };

    class ASTAssignNode : public ASTOperatorNode
    {
    public:
        ASTAssignNode() = default;
        ASTAssignNode(data_type, ASTNode*, ASTNode*);
        ~ASTAssignNode() = default;
    };
}

#endif
