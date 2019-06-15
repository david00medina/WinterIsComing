#include <iostream>
#include "ASTNode.hpp"

namespace wic {
    ASTNode::ASTNode()
    {
        node_t = wic::LEAF;
        data_t = wic::UNKNOWN;
        ptr2_i = 0;
    }

    ASTNode::ASTNode(wic::node_type node_t, wic::data_type data_t, wic::ASTNode *ptr1, wic::ASTNode *ptr2, wic::ASTNode *ptr3)
    {
        ptr2_i = 0;

        this->node_t = node_t;
        this->data_t = data_t;

        this->ptr1 = ptr1;
        add_ptr2(ptr2);
        this->ptr3 = ptr3;
    }

    ASTNode::~ASTNode() {
        delete ptr1;
        delete *ptr2;
        delete ptr3;
    }

    node_type ASTNode::get_node_type() {
        return node_t;
    }

    void ASTNode::set_node_type(node_type node_t) {
        this->node_t = node_t;
    }

    data_type ASTNode::get_data_type() {
        return data_t;
    }

    void ASTNode::set_data_type(data_type data_t) {
        this->data_t = data_t;
    }

    ASTNode* ASTNode::get_ptr1() {
        return ptr1;
    }

    void ASTNode::set_ptr1(wic::ASTNode *ptr1)
    {
        this->ptr1 = ptr1;
    }

    ASTNode** ASTNode::get_ptr2() {
        return ptr2;
    }

    void ASTNode::add_ptr2(ASTNode *ptr2) {
        if (ptr2 != nullptr) this->ptr2[ptr2_i++] = ptr2;
    }

    ASTNode* ASTNode::get_ptr3() {
        return ptr3;
    }

    void ASTNode::set_ptr3(wic::ASTNode *ptr3)
    {
        this->ptr3 = ptr3;
    }

    void ASTNode::print()
    {
        std::cout << "(" << name << ", " << type_data_str[data_t] << ")";
    }
}
