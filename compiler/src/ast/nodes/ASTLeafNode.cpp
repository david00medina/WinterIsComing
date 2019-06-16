#include <iostream>
#include "ASTLeafNode.hpp"

namespace wic
{
    ASTLeafNode::ASTLeafNode(wic::data_type data_t, wic::data_value *data_v)
    {
        this->node_t = wic::LEAF;
        this->data_t = data_t;
        if (data_v != nullptr) this->data_v = *data_v;
        name = "LEAF";
    }

    data_value ASTLeafNode::get_data_value() {
        return data_v;
    }

    void ASTLeafNode::set_data_value(void *val) {
        if (data_t == wic::CHAR) this->data_v.char_val = *(char *) val;
        else if (data_t == wic::STRING) this->data_v.str_val = (char *) val;
        else if (data_t == wic::INT) this->data_v.int_val = *(int *) val;
        else if (data_t == wic::REAL) this->data_v.real_val = *(float *) val;
        else if (data_t == wic::BOOL) this->data_v.bool_val = *(bool *) val;
        else if (data_t == wic::ARRAY_INT) this->data_v.int_array_val = (int *) val;
        else if (data_t == wic::ARRAY_REAL) this->data_v.real_array_val = (float *) val;
        else if (data_t == wic::ARRAY_BOOL) this->data_v.bool_array_val = (bool *) val;
    }

    void ASTLeafNode::print()
    {
        if (data_t == wic::CHAR)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.char_val << ")";
        else if (data_t == wic::STRING)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.str_val << ")";
        else if (data_t == wic::INT)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.int_val << ")";
        else if (data_t == wic::REAL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.real_val << ")";
        else if (data_t == wic::BOOL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.bool_val << ")";
        else if (data_t == wic::ARRAY_INT)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.int_array_val << ")";
        else if (data_t == wic::ARRAY_REAL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.real_array_val << ")";
        else if (data_t == wic::ARRAY_BOOL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.bool_array_val << ")";
    }
}
