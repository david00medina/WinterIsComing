#include <regex>
#include <cstdio>
#include <sstream>
#include "CodeGenerator.hpp"

namespace wic
{
    CodeGenerator::CodeGenerator() : fout(nullptr)
    {
        fdata.open("data.s", std::ios::in | std::ios::out | std::ios::app);
        fcode.open("code.s", std::ios::in | std::ios::out | std::ios::app);

        file_p.data_p = 0;
        file_p.code_p = 0;

        label.code_l = 0;
        label.data_l = 0;
    }

    CodeGenerator::CodeGenerator(const std::string path) : path(path)
    {
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::app);
        fdata.open("data.s", std::ios::in | std::ios::out | std::ios::app);
        fcode.open("code.s", std::ios::in | std::ios::out | std::ios::app);

        file_p.data_p = 0;
        file_p.code_p = 0;

        label.code_l = 0;
        label.data_l = 0;
    }

    std::string CodeGenerator::get_label(section_enum selector)
    {
        switch (selector)
        {
            case DATA:
                return data_label + std::to_string(label.data_l++);
            case CODE:
                return code_label + std::to_string(label.code_l++);
        }
        return nullptr;
    }

    void CodeGenerator::set_path(const std::string path)
    {
        this->path = path;
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::app);
    }

    void CodeGenerator::init()
    {
        fcode << initial_spacing <<".text" << std::endl;
        fcode << initial_spacing << ".global main" << std::endl << std::endl;
        fcode << "main:" << std::endl;
    }

    void CodeGenerator::print(std::string msg, unsigned int argc, ...)
    {
        va_list argv;
        va_start(argv, argc);

        std::smatch m;
        std::regex e("(%[scbrd])");

        while (std::regex_search(msg, m, e))
        {
            if (msg.at(m.position(0) - 1) != '\\')
            {
                std::string val;
                std::stringstream ss;
                ASTNode* node = static_cast<ASTNode*>(va_arg(argv, void*));


                if (m.str(0) == "%s") ss << node->data_v.str_val;

                else if (m.str(0) == "%c")
                {
                    if (node->data_v.char_val == '\n') ss << "\\n";
                    if (node->data_v.char_val == '\r') ss << "\\r";
                    if (node->data_v.char_val == '\b') ss << "\\b";
                    if (node->data_v.char_val == '\t') ss << "\\t";
                    if (node->data_v.char_val == '\a') ss << "\\a";
                    if (node->data_v.char_val == '\v') ss << "\\v";
                    if (node->data_v.char_val == '\f') ss << "\\f";
                    if (node->data_v.char_val == '\0') ss << "\\0";
                    else ss << node->data_v.char_val;
                }

                else if (m.str(0) == "%d") ss << node->data_v.int_val;

                else if (m.str(0) == "%r") ss << node->data_v.real_val;

                else if (m.str(0) == "%b")
                {
                    if (node->data_v.bool_val) ss << "True";
                    else ss << "False";
                }

                ss >> val;

                msg.replace(m.position(0), 2, val);
            }
        }

        std::string label = get_label(DATA);

        fdata << label <<":" << std::endl;
        fdata << initial_spacing << ".asciz " << "\"" << msg << "\"" << std::endl << std::endl;

        fcode << initial_spacing << "mov" << instr_spacing << "$" + label << ", %edi" << std::endl;
        fcode << initial_spacing << "call" << instr_spacing << "puts" << std::endl << std::endl;

        va_end(argv);
    }

    void CodeGenerator::end()
    {
        fcode << initial_spacing << "mov" << instr_spacing << "$60" << ", %eax" << std::endl;
        fcode << initial_spacing << "xor" << instr_spacing << "%edi" << ", %edi" << std::endl;
        fcode << initial_spacing << "syscall" << std::endl;

        char ch;

        fdata.seekg(0);
        fdata.seekp(0);
        while(!fdata.eof())
        {
            fdata.get(ch);
            fout << ch;
        }
        fdata.close();

        fcode.seekg(0);
        fcode.seekp(0);
        while(!fcode.eof())
        {
            fcode.get(ch);
            fout << ch;
        }
        fcode.close();

        fout.close();

        std::remove("data.s");
        std::remove("code.s");
    }
}