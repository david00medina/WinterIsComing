#include "ASTLeafNode.hpp"
#include "../../../../code-generator/CodeGenerator.hpp"

namespace wic
{
    ASTLeafNode::ASTLeafNode(wic::data_type data_t, wic::data_value *data_v) : data_v(*data_v), ASTNode("LEAF", LEAF, data_t) {}

    data_value ASTLeafNode::get_data_value()
    {
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

    cpu_registers ASTLeafNode::to_code(CodeGenerator *cg)
    {
        switch (data_t)
        {
            case INT:
                {
                    cpu_registers r = cg->get_reg();
                    cg->write_code_section("movl", "$" + std::to_string(data_v.int_val), cg->translate_reg(r), "Move int to " + cg->translate_reg(r));
                    return r;
                }
            case REAL:
                {
                    std::string l = cg->get_label(LABEL_FLOAT);
                    std::string s1 = ".section\t.rodata";
                    std::string s2 = ".align 4";
                    cg->write_data_section(2, s1, s2);
                    cg->write_data_section(l, 1, ".float " + std::to_string(data_v.real_val));

                    cpu_registers r = cg->get_float_reg();
                    cg->write_code_section("movss", l, cg->translate_reg(r), "Move real to " + cg->translate_reg(r));
                    return r;
                }
            case CHAR:
                {
                    cpu_registers r = cg->get_reg();
                    cg->write_code_section("movl", "$" + std::to_string((int) data_v.char_val), cg->translate_reg(r), "Move char to " + cg->translate_reg(r));
                    return r;
                }
            case BOOL:
                {
                    cpu_registers r = cg->get_reg();
                    cg->write_code_section("movl", "$" + std::to_string((int) data_v.bool_val), cg->translate_reg(r), "Move bool to " + cg->translate_reg(r));
                    return r;
                }
            default:
                break;
        }

        return NONE;
    }

    void ASTLeafNode::print()
    {
        if (data_t == CHAR)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.char_val << ")";
        else if (data_t == STRING)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.str_val << ")";
        else if (data_t == INT)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.int_val << ")";
        else if (data_t == REAL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.real_val << ")";
        else if (data_t == BOOL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.bool_val << ")";
        else if (data_t == ARRAY_INT)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.int_array_val << ")";
        else if (data_t == ARRAY_REAL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.real_array_val << ")";
        else if (data_t == ARRAY_BOOL)
            std::cout << "(" << name << ", " << type_data_str[data_t] << ", " << data_v.bool_array_val << ")";
    }
}
