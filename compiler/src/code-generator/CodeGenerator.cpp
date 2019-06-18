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

        for (int i = 0; i < TOTAL_REG; ++i) register_use[i] = false;
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

    int CodeGenerator::get_reg()
    {
        int i = 0;
        while (register_use[i] == false) i++;
        return i;
    }

    void CodeGenerator::free_reg(int i)
    {
        register_use[i] = false;
    }

    void CodeGenerator::lock_reg(int i)
    {
        register_use[i] = true;
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
                ASTLeafNode* node = reinterpret_cast<ASTLeafNode*>(va_arg(argv, void*));
                data_value data_v = node->get_data_value();


                if (m.str(0) == "%s") ss << data_v.str_val;

                else if (m.str(0) == "%c")
                {
                    if (data_v.char_val == '\n') ss << "\\n";
                    else if (data_v.char_val == '\r') ss << "\\r";
                    else if (data_v.char_val == '\b') ss << "\\b";
                    else if (data_v.char_val == '\t') ss << "\\t";
                    else if (data_v.char_val == '\a') ss << "\\a";
                    else if (data_v.char_val == '\v') ss << "\\v";
                    else if (data_v.char_val == '\f') ss << "\\f";
                    else if (data_v.char_val == '\0') ss << "\\0";
                    else if (data_v.char_val == '\'') ss << "\\\'";
                    else if (data_v.char_val == '\"') ss << "\\\"";
                    else if (data_v.char_val == '\\') ss << "\\\\";
                    else ss << data_v.char_val;
                }

                else if (m.str(0) == "%d") ss << data_v.int_val;

                else if (m.str(0) == "%r") ss << data_v.real_val;

                else if (m.str(0) == "%b")
                {
                    if (data_v.bool_val) ss << "True";
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

    void CodeGenerator::exit()
    {
        fcode << initial_spacing << "mov" << instr_spacing << "$60" << ", %eax" << std::endl;
        fcode << initial_spacing << "xor" << instr_spacing << "%edi" << ", %edi" << std::endl;
        fcode << initial_spacing << "syscall" << std::endl;
    }

    void CodeGenerator::end()
    {
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