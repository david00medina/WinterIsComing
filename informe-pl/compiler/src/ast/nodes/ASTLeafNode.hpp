#ifndef ASTLEAFNODE_HPP
#define ASTLEAFNODE_HPP

#include "ASTNode.hpp"
#include "../AbstractSyntaxTreePack.hpp"

namespace wic {
    class ASTLeafNode : public ASTNode
    {
    private:
        data_value data_v;

    public:
        ASTLeafNode() = default;
        ASTLeafNode(data_type, data_value *);
        ~ASTLeafNode() = default;

        data_value get_data_value();
        void set_data_value(void *);
        cpu_registers to_code(CodeGenerator*);
        void print();
    };
}

#endif
