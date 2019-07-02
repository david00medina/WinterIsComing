#ifndef ASTCLAUSENODE_HPP
#define ASTCLAUSENODE_HPP

#include "../../ASTNode.hpp"

namespace wic
{
    class ASTStructuralNode;
    class ASTRelationalNode;
    class CodeGenerator;

    class ASTClauseNode : public ASTNode
    {
    protected:
        ASTRelationalNode* cond;
        ASTStructuralNode* body;
        ASTStructuralNode* else_body;

        unsigned int middle_block_depth;

        void check_error(std::string);
        void add_middle_block(ASTNode*);

        virtual void first_block(std::string, std::string, CodeGenerator*) = 0;
        virtual void middle_block(std::string, std::string, std::string, CodeGenerator*) = 0;
        virtual void last_block(std::string, std::string, CodeGenerator*) = 0;

    public:
        ASTClauseNode() = default;
        ASTClauseNode(std::string, node_type, ASTRelationalNode*,ASTStructuralNode*);
        ASTClauseNode(std::string, node_type, ASTRelationalNode*,ASTStructuralNode*, ASTStructuralNode*);
        ~ASTClauseNode();

        ASTRelationalNode* get_cond();
        ASTStructuralNode* get_body();
        ASTStructuralNode* get_else_body();
    };

    class ASTIfNode : public ASTClauseNode
    {
    private:
        void first_block(std::string, std::string, CodeGenerator*);
        void middle_block(std::string, std::string, std::string, CodeGenerator*);
        void last_block(std::string, std::string, CodeGenerator*);

    public:
        ASTIfNode() = default;
        ASTIfNode(ASTRelationalNode*,ASTStructuralNode*);
        ASTIfNode(ASTRelationalNode*,ASTStructuralNode*, ASTStructuralNode*);
        ~ASTIfNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTWhileNode : public ASTClauseNode
    {
    private:
        void first_block(std::string, std::string, CodeGenerator*);
        void middle_block(std::string, std::string, std::string, CodeGenerator*);
        void last_block(std::string, std::string, CodeGenerator*);

    public:
        ASTWhileNode() = default;
        ASTWhileNode(ASTRelationalNode*,ASTStructuralNode*);
        ASTWhileNode(ASTRelationalNode*,ASTStructuralNode*, ASTStructuralNode*);
        ~ASTWhileNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };

    class ASTForNode : public ASTClauseNode
    {
    private:
        void first_block(std::string, std::string, CodeGenerator*);
        void middle_block(std::string, std::string, std::string, CodeGenerator*);
        void last_block(std::string, std::string, CodeGenerator*);

    public:
        ASTForNode() = default;
        ASTForNode(ASTRelationalNode*,ASTStructuralNode*);
        ASTForNode(ASTRelationalNode*,ASTStructuralNode*, ASTStructuralNode*);
        ~ASTForNode() = default;

        cpu_registers to_code(CodeGenerator*);
    };
}

#endif
