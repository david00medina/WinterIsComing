#include <regex>
#include <cstdio>
#include <sstream>
#include <stdlib.h>
#include "CodeGenerator.hpp"
#include "../utils/termcolor.hpp"

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

        for (int i = 0; i < TOTAL_REG; ++i) reg_use[i] = false;
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
        std::cout << "HOLA" << std::endl;
    }

    int CodeGenerator::get_reg()
    {
        for (int i = 0; i < TOTAL_REG; i++)
        {
            if (!reg_use[i]) return static_cast<cpu_registers>(i);
        }
        return -1;
    }

    void CodeGenerator::free_reg(cpu_registers reg)
    {
        reg_use[reg] = false;
    }

    void CodeGenerator::lock_reg(cpu_registers reg)
    {
        reg_use[reg] = true;
    }

    void CodeGenerator::init()
    {
        fcode << initial_spacing <<".text" << std::endl;
        fcode << initial_spacing << ".global main" << std::endl << std::endl;
        fcode << "main:" << std::endl;

        instr("pushl", EBP);
        instr("movl", ESP, EBP);
    }

    void CodeGenerator::save_value(void* val, unsigned int addr, bool is_imm)
    {
        fcode << initial_spacing << "pushl" << instr_spacing;
        if (is_imm) fcode << "$" << *static_cast<int*>(val);
        else fcode << reg[*static_cast<cpu_registers*>(val)];
        fcode << ", " << "-" << addr << "(" << reg[EBP] << ")" << std::endl;
    }

    cpu_registers CodeGenerator::get_value(unsigned int addr)
    {
        cpu_registers r = static_cast<cpu_registers>(get_reg());
        if (r == -1) {
            std::cout << termcolor::red << termcolor::bold << "[!] Error: " << termcolor::reset
            << "There are no free registers" << std::endl;
            std::exit(-1);
        }
        fcode << initial_spacing << "-" << addr << "(" << reg[EBP] << ")" << ", " << reg[r] << std::endl;
        lock_reg(r);
        return r;
    }

    void CodeGenerator::instr(const std::string instr, wic::cpu_registers r)
    {
        fcode << initial_spacing << instr << instr_spacing << reg[r] << std::endl;
    }

    void CodeGenerator::instr(const std::string instr, unsigned int addr)
    {
        fcode << initial_spacing << instr << instr_spacing << reg[get_value(addr)] << std::endl;
    }

    void CodeGenerator::instr(const std::string instr, wic::cpu_registers r1, wic::cpu_registers r2)
    {
        fcode << initial_spacing << instr << instr_spacing << reg[r1] << ", " << reg[r2] << std::endl;
    }

    void CodeGenerator::instr(const std::string instr, unsigned int addr, wic::cpu_registers r)
    {
        fcode << initial_spacing << instr << instr_spacing << reg[r] /*<< ", " << reg[r2]*/ << std::endl;
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