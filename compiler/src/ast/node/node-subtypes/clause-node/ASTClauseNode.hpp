#ifndef ASTCLAUSENODE_HPP
#define ASTCLAUSENODE_HPP

#include "../../ASTNode.hpp"

namespace wic
{
    class AbstractSyntaxTree;
    class ASTRelationalNode;
    class CodeGenerator;

    class ASTClauseNode : public ASTNode
    {
    protected:
        ASTRelationalNode* cond;
        ASTNode* body;
        ASTNode* else_body;
        ASTClauseNode* next;

        std::string else_l;
        std::string exit_l;

        void check_error(std::string);

        virtual void write_condition(ASTRelationalNode*, section_enum, CodeGenerator*) = 0;
        virtual void write_body(section_enum, CodeGenerator*) = 0;
        virtual void write_else_body(section_enum, CodeGenerator*) = 0;

    public:
        ASTClauseNode(const ASTClauseNode&);
        ASTClauseNode() = default;
        ASTClauseNode(std::string, node_type, ASTRelationalNode*, ASTNode*);
        ASTClauseNode(std::string, node_type, ASTRelationalNode*, ASTNode*, ASTNode*);
        ~ASTClauseNode();

        void add_mid_block(ASTClauseNode*);

        ASTRelationalNode* get_cond();
        ASTNode* get_body();
        ASTNode* get_else_body();

        void set_cond(ASTNode*);
        void set_body(ASTNode*);
        void set_else_body(ASTNode*);
    };

    class ASTIfNode : public ASTClauseNode
    {
    private:
        void write_condition(ASTRelationalNode*, section_enum, CodeGenerator*);
        void write_body(section_enum, CodeGenerator*);
        void write_else_body(section_enum, CodeGenerator*);

    public:
        ASTIfNode(const ASTIfNode&);
        ASTIfNode() = default;
        ASTIfNode(ASTRelationalNode*,ASTNode*);
        ASTIfNode(ASTRelationalNode*,ASTNode*, ASTNode*);
        ~ASTIfNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTWhileNode : public ASTClauseNode
    {
    private:
        void write_condition(ASTRelationalNode*, section_enum, CodeGenerator*);
        void write_body(section_enum, CodeGenerator*);
        void write_else_body(section_enum, CodeGenerator*);

    public:
        ASTWhileNode() = default;
        ASTWhileNode(ASTRelationalNode*,ASTNode*);
        ASTWhileNode(ASTRelationalNode*,ASTNode*, ASTNode*);
        ~ASTWhileNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };

    class ASTForNode : public ASTClauseNode
    {
    private:
        void write_condition(ASTRelationalNode*, section_enum, CodeGenerator*);
        void write_body(section_enum, CodeGenerator*);
        void write_else_body(section_enum, CodeGenerator*);

    public:
        ASTForNode() = default;
        ASTForNode(ASTRelationalNode*,ASTNode*);
        ASTForNode(ASTRelationalNode*,ASTNode*, ASTNode*);
        ~ASTForNode() = default;

        cpu_registers to_code(section_enum, CodeGenerator*);
    };
}

#endif
