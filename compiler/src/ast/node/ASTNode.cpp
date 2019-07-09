#include "ASTNode.hpp"

namespace wic {
    ASTNode::ASTNode() : name(""), node_t(MAIN), data_t(UNKNOWN), next(nullptr) {}

    ASTNode::ASTNode(std::string name, wic::node_type node_t, wic::data_type data_t)
        : name(name), node_t(node_t), data_t(data_t), next(nullptr) {}

    ASTNode::~ASTNode()
    {
        delete next;
    }

    void ASTNode::add_node(ASTNode* &head, ASTNode* node)
    {
        if (head == nullptr)
        {
            head = node;
            return;
        }

        ASTNode* curr = head;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr->next = node;
    }

    ASTNode * ASTNode::find(unsigned int count, wic::node_type node_t, ASTNode* head)
    {
        ASTNode* curr = head;
        for (int i = 0; i < count; ++i)
        {
            if(curr->next != nullptr) curr = curr->next;
        }

        while (curr->next != nullptr && curr->node_t != node_t)
        {
            curr = curr->next;
        }

        return curr;
    }

    node_type ASTNode::get_node_type() {
        return node_t;
    }

    void ASTNode::set_node_type(node_type node_t)
    {
        this->node_t = node_t;
    }

    data_type ASTNode::get_data_type() {
        return data_t;
    }

    void ASTNode::set_data_type(data_type data_t) {
        this->data_t = data_t;
    }

    std::string ASTNode::get_node_name()
    {
        return name;
    }

    void ASTNode::check_error(std::string) {}

    cpu_registers ASTNode::to_code(section_enum section, wic::CodeGenerator *cg) { return NONE; }

    void ASTNode::print()
    {
        std::cout << "(" << name << ", " << type_data_str[data_t] << ")";
    }
}
