#ifndef ASTOPERATORNODE_HPP
#define ASTOPERATORNODE_HPP

#include "ASTNode.hpp"
#include "AbstractSyntaxTreePack.hpp"

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
    private:
        const char *name = "SUM";

    public:
        ASTSumNode() = default;
        ASTSumNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTSumNode() = default;
    };

    class ASTSubNode : public ASTOperatorNode
    {
    private:
        const char *name = "SUBTRACT";

    public:
        ASTSubNode() = default;
        ASTSubNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTSubNode() = default;
    };

    class ASTProdNode : public ASTOperatorNode
    {
    private:
        const char *name = "PRODUCT";

    public:
        ASTProdNode() = default;
        ASTProdNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTProdNode() = default;
    };

    class ASTDivNode : public ASTOperatorNode
    {
    private:
        const char *name = "DIVISION";

    public:
        ASTDivNode() = default;
        ASTDivNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTDivNode() = default;
    };

    class ASTPowerNode : public ASTOperatorNode
    {
    private:
        const char *name = "POWER";

    public:
        ASTPowerNode() = default;
        ASTPowerNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTPowerNode() = default;
    };

    class ASTRadicalNode : public ASTOperatorNode
    {
    private:
        const char *name = "RADICAL";

    public:
        ASTRadicalNode() = default;
        ASTRadicalNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTRadicalNode() = default;
    };

    class ASTProdNode : public ASTOperatorNode
    {
    private:
        const char *name = "PRODUCT";

    public:
        ASTProdNode() = default;
        ASTProdNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTProdNode() = default;
    };

    class ASTModNode : public ASTOperatorNode
    {
    private:
        const char *name = "MODULUS";

    public:
        ASTModNode() = default;
        ASTModNode(node_type, data_type, ASTNode*, ASTNode*) = default;
        ~ASTModNode() = default;
    };

    class ASTAssignNode : public ASTOperatorNode
    {
    private:
        const char *name = "ASSIGN";

    public:
        ASTAssignNode() = default;
        ASTAssignNode(node_type, data_type, ASTNode*, ASTNode*);
        ~ASTAssignNode() = default;
    };
}

#endif
