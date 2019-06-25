#include <regex>
#include <cstdio>
#include <sstream>
#include <stdlib.h>

#include "CodeGenerator.hpp"
#include "../utils/termcolor.hpp"
#include "../ast/nodes/ASTLeafNode.hpp"

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

        general_spill_count = 0;
        float_spill_count = 8;

        for (int i = 0; i < TOTAL_REG; ++i) {
            if (i != ESP && i != EBP) reg_use[i] = false;
            else reg_use[i] = true;
        }
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

        general_spill_count = 0;
        float_spill_count = 8;

        for (int i = 0; i < TOTAL_REG; ++i) {
            if (i != ESP && i != EBP) reg_use[i] = false;
            else reg_use[i] = true;
        }
    }

    std::string CodeGenerator::get_label(section_enum selector)
    {
        switch (selector)
        {
            case DATA:
                return data_label + std::to_string(label.data_l++);
            case CODE:
                return code_label + std::to_string(label.code_l++);
            case LABEL_FLOAT:
                return float_label + std::to_string(label.float_l++);
        }
        return nullptr;
    }

    void CodeGenerator::set_path(const std::string path)
    {
        std::cout << this->path << std::endl;
        this->path = path;
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::app);
    }

    void CodeGenerator::write_data_section(unsigned int argc, ...)
    {
        va_list argv;
        va_start(argv, argc);

        for (unsigned int i = 0; i < argc; ++i) {
            fdata << initial_spacing << *static_cast<const std::string *>(va_arg(argv, void*)) << std::endl;
        }

        va_end(argv);
    }

    void CodeGenerator::write_data_section(const std::string label, unsigned int argc, ...)
    {
        va_list argv;
        va_start(argv, argc);

        fdata << label << ":" << std::endl;

        for (unsigned int i = 0; i < argc; ++i) {
            fdata << initial_spacing << *static_cast<const std::string *>(va_arg(argv, void*)) << std::endl;
        }

        va_end(argv);
    }

    void CodeGenerator::write_code_section(const std::string instr, const std::string comment)
    {
        fcode << initial_spacing << instr << instr_spacing << instr_spacing << comment_spacing << "# " << comment << std::endl;
    }

    void CodeGenerator::write_code_section(const std::string instr, const std::string op, const std::string comment)
    {
        fcode << initial_spacing << instr << instr_spacing << op << "\t" << comment_spacing << "# " << comment << std::endl;
    }

    void CodeGenerator::write_code_section(const std::string instr, const std::string op1, const std::string op2, const std::string comment)
    {
        fcode << initial_spacing << instr << instr_spacing << op1 << ", " << op2 << comment_spacing << "# " << comment << std::endl;
    }

    const std::string CodeGenerator::translate_reg(cpu_registers r)
    {
        return reg[r];
    }

    cpu_registers CodeGenerator::get_reg()
    {
        for (int i = EAX; i < ESI; i++)
        {
            if (!reg_use[i])
            {
                lock_reg(static_cast<cpu_registers>(i));
                return static_cast<cpu_registers>(i);
            }
        }

        cpu_registers r = static_cast<cpu_registers>(general_spill_count);
        general_spill_count = (general_spill_count + 1) % TOTAL_REG;
        write_code_section("pushl", translate_reg(r), "General register spilling (" + translate_reg(r) + ")");
        return r;
    }

    cpu_registers CodeGenerator::get_float_reg()
    {
        for (int i = XMM0; i < NONE; i++)
        {
            if (!reg_use[i])
            {
                lock_reg(static_cast<cpu_registers>(i));
                return static_cast<cpu_registers>(i);
            }
        }

        cpu_registers r = static_cast<cpu_registers>(float_spill_count);
        float_spill_count = (float_spill_count + 1) % TOTAL_REG + 8;
        write_code_section("pushl", translate_reg(r), "General register spilling (" + translate_reg(r) + ")");
        return r;
    }

    void CodeGenerator::free_reg(cpu_registers reg)
    {
        reg_use[reg] = false;
    }

    void CodeGenerator::lock_reg(cpu_registers reg)
    {
        reg_use[reg] = true;
    }

    bool CodeGenerator::is_used(cpu_registers r)
    {
        return reg_use[r];
    }

    void CodeGenerator::init()
    {
        fcode << initial_spacing <<".section\t.text" << std::endl;
        fcode << initial_spacing << ".globl main" << std::endl;
        fcode << "main:" << std::endl;

        fcode << initial_spacing << "pushl" << instr_spacing << reg[EBP] << "\t" << comment_spacing << "# Save previous scope" << std::endl;
        fcode << initial_spacing << "movl" << instr_spacing << reg[ESP] << ", " << reg[EBP] << comment_spacing << "# Set new scope up" << std::endl;
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
        write_code_section("leave", "Leave the main program");
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

    void CodeGenerator::print_reg_use()
    {
        std::cout << "[ ";
        for (int i = 0; i < ALL_REG; ++i) {
            if (reg_use[i]) std::cout << "TRUE ";
            else std::cout << "FALSE ";
        }
        std::cout << std::endl;
    }
}