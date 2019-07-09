#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>

#include "../AbstractSyntaxTreePack.hpp"
#include "../../code-generator/CodeGeneratorPack.hpp"

#define DATA_TYPE_NUM 11
#define NODE_TYPE_NUM 5

namespace wic
{
    class AbstractSyntaxTree;
    class ASTMainNode;
    class ASTBodyNode;
    class ASTArgumentNode;
    class ASTParamNode;
    class ASTFunctionNode;
    class ASTCallNode;
    class CodeGenerator;

    class ASTNode
    {
    protected:
        std::string name;
        node_type node_t;
        data_type data_t;
        ASTNode* next;

        void add_node(ASTNode*&, ASTNode*);

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
                        "while",
                        "for",
                        "scan",
                        "print"
                };

    public:
        ASTNode();
        ASTNode(std::string, node_type, data_type);
        virtual ~ASTNode();

        std::string get_node_name();
        node_type get_node_type();
        void set_node_type(node_type);
        data_type get_data_type();
        void set_data_type(data_type);

        ASTNode* find(unsigned int, node_type, ASTNode*);

        virtual void check_error(std::string);
        virtual cpu_registers to_code(section_enum, CodeGenerator*);

        virtual void print();

        friend class AbstractSyntaxTree;
        friend class ASTMainNode;
        friend class ASTBodyNode;
        friend class ASTArgumentNode;
        friend class ASTParamNode;
        friend class ASTFunctionNode;
        friend class ASTCallNode;
    };
}

#endif
