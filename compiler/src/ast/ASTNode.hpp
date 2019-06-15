#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>
#include "AbstractSyntaxTreePack.hpp"

#define DATA_TYPE_NUM 11
#define NODE_TYPE_NUM 29
#define MAX_PTR2 512

namespace wic {
    class ASTNode {
    protected:
        const char* name;
        node_type node_t;
        data_type data_t;
        ASTNode *ptr1;
        ASTNode *ptr2[MAX_PTR2];
        ASTNode *ptr3;
        int ptr2_i;

        const char *type_data_str[DATA_TYPE_NUM] =
                {
                        "int",
                        "real",
                        "bool",
                        "char",
                        "void",
                        "string",
                        "array_int",
                        "array_real",
                        "array_bool",
                        "function",
                        "unknown"
                };

        const char *type_node_str[NODE_TYPE_NUM] =
                {
                        "gt",
                        "ge",
                        "eq",
                        "neq",
                        "le",
                        "lt",
                        "not",
                        "and",
                        "or",
                        "if",
                        "while",
                        "for",
                        "scan",
                        "print"
                };

    public:
        ASTNode();
        ASTNode(node_type, data_type, ASTNode *, ASTNode *, ASTNode *);
        ~ASTNode();

        virtual node_type get_node_type();
        virtual void set_node_type(node_type);
        virtual data_type get_data_type();
        virtual void set_data_type(data_type);

        virtual ASTNode* get_ptr1();
        virtual void set_ptr1(ASTNode *);
        virtual ASTNode** get_ptr2();
        virtual void add_ptr2(ASTNode *);
        virtual ASTNode* get_ptr3();
        virtual void set_ptr3(ASTNode *);

        virtual void print();

        friend class AbstractSyntaxTree;
    };

    class ASTMainNode : public ASTNode {
    private:
        const char *name = "MAIN";

    public:
        ASTMainNode() = default;
        ASTMainNode(node_type, data_type, ASTNode *, ASTNode *, ASTNode *) = default;
        ~ASTMainNode() = default;
    };

    class ASTBodyNode : public ASTNode {
    private:
        const char *name = "BODY";

    public:
        ASTBodyNode() = default;
        ASTBodyNode(node_type, data_type, ASTNode *, ASTNode *, ASTNode *) = default;
        ~ASTBodyNode() = default;
    };

    class ASTReturnNode : public ASTNode {
    private:
        const char *name = "RETURN";

    public:
        ASTReturnNode() = default;
        ASTReturnNode(node_type, data_type, ASTNode *) = default;
        ~ASTReturnNode() = default;
    };

    class ASTParamNode : public ASTNode {
    private:
        const char *name = "PARAMETER";

    public:
        ASTParamNode() = default;
        ASTParamNode(node_type, data_type, ASTNode *, ASTNode *, ASTNode *) = default;
        ~ASTParamNode() = default;
    };
}

#endif
