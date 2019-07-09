#include <regex>
#include <cstdio>
#include <sstream>
#include <stdlib.h>

#include "CodeGenerator.hpp"
#include "../utils/termcolor.hpp"
#include "../ast/node/node-subtypes/leaf-node/ASTLeafNode.hpp"

namespace wic
{
    CodeGenerator::CodeGenerator() : fout(nullptr)
    {
        fdata.open("data.s", std::ios::in | std::ios::out | std::ios::app);
        fcode.open("code.s", std::ios::in | std::ios::out | std::ios::app);
        ffunc.open("func.s", std::ios::in | std::ios::out | std::ios::app);

        file_p.data_p = 0;
        file_p.code_p = 0;

        label.code_l = 0;
        label.data_l = 0;

        general_spill_count = 0;
        float_spill_count = 8;

        for (int i = 0; i < TOTAL_REG; ++i) {
            reg_use[i] = !(i != ESP && i != EBP);
        }
    }

    CodeGenerator::CodeGenerator(const std::string path) : path(path)
    {
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
        fdata.open("data.s", std::ios::in | std::ios::out | std::ios::app);
        fcode.open("code.s", std::ios::in | std::ios::out | std::ios::app);
        ffunc.open("func.s", std::ios::in | std::ios::out | std::ios::app);

        file_p.data_p = 0;
        file_p.code_p = 0;

        label.code_l = 0;
        label.data_l = 0;

        general_spill_count = 0;
        float_spill_count = 8;

        for (int i = 0; i < TOTAL_REG; ++i) {
            reg_use[i] = !(i != ESP && i != EBP);
        }
    }

    std::string CodeGenerator::get_label(section_enum selector)
    {
        switch (selector)
        {
            case DATA:
                return data_label + std::to_string(label.data_l++);
            case FUNCTION_CODE:
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
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
    }

    void CodeGenerator::push_stack(){
        write(CODE, "c%s#c", "pushl", reg[EBP], "Save previous scope");
        write(CODE, "c%s%s#c", "movl", reg[ESP], reg[EBP], "Set new scope");
    }

    void CodeGenerator::pop_stack()
    {
        write(CODE, "c%s#c", "popl", reg[EBP], "Save previous scope");
        write(CODE, "c%s%s#c", "movl", reg[EBP], reg[ESP], "Set new scope");
    }

    void CodeGenerator::push_scope()
    {
        for (int i = 0; i < TOTAL_REG; i++)
        {
            push_reg(static_cast<cpu_registers>(EAX+i), "Push scope (" + reg[EAX+i] + ")");
            push_float_reg(static_cast<cpu_registers>(XMM0+i), "Push scope (" + reg[XMM0+i] + ")");

            free_reg(static_cast<cpu_registers>(EAX+i));
            free_reg(static_cast<cpu_registers>(XMM0+i));
        }
    }

    void CodeGenerator::pop_scope()
    {
        for (int i = 0; i < TOTAL_REG; i++)
        {
            pop_reg(static_cast<cpu_registers>(EAX+i), "Pop scope (" + reg[EAX+i] + ")");
            pop_float_reg(static_cast<cpu_registers>(XMM0+i), "Pop scope (" + reg[XMM0+i] + ")");

            lock_reg(static_cast<cpu_registers>(EAX+i));
            lock_reg(static_cast<cpu_registers>(XMM0+i));
        }
    }

    void CodeGenerator::push_reg(cpu_registers r, std::string msg)
    {
        write(CODE, "c%s#s", "pushl", reg[r], msg);
        free_reg(r);
    }

    void CodeGenerator::pop_reg(cpu_registers r, std::string msg)
    {
        write(CODE, "c%s#s", "popl", reg[r], msg);
        lock_reg(r);

    }

    void CodeGenerator::push_float_reg(cpu_registers r, std::string msg)
    {
        cpu_registers r2 = get_reg();
        write(CODE, "c%s%s#s", "movd", reg[r], reg[r2], "Save float value temporarily in a general register (" + reg[r2] + ")");
        free_reg(r);
        write(CODE, "c%s#s", "pushl", reg[r2], msg);
        free_reg(r2);
    }

    void CodeGenerator::pop_float_reg(cpu_registers r, std::string msg)
    {
        write(CODE, "c%s%s%s", "movss", reg[ESP], reg[r], msg);
        write(CODE, "c%c%s#c", "add", "$4", reg[ESP], "Restore stack pointer");
        lock_reg(r);
    }

    void CodeGenerator::push_mem(int offset, std::string msg)
    {
        write(CODE, "c%s#s", "pushl", get_mem_var(offset), msg);
    }

    void CodeGenerator::write_to_file(std::fstream &f, va_list argv, const char *fmt)
    {
        bool comment = false;
        bool op = false;

        std::string s;
        const char* c;

        for (const char* p = fmt; *p != '\0'; p++)
        {
            switch (*p)
            {
                case 's':
                {
                    s = *va_arg(argv, std::string *);

                    ++p;

                    if (op && *p == '%') f << s << ", ";
                    else if (op && *p != '%') f << s;
                    else if (comment) f << initial_spacing << comment_spacing + "# " + s;
                    else f << initial_spacing + s + instr_spacing;

                    --p;
                    comment = false;
                    op = false;
                }
                    break;
                case 'c':
                {
                    c = va_arg(argv, const char*);
                    s = c;

                    ++p;

                    if (op && *p == '%') f << s << ", ";
                    else if (op && *p != '%') f << s;
                    else if (comment) f << initial_spacing << comment_spacing + "# " + s;
                    else f << initial_spacing + s + instr_spacing;

                    --p;
                    comment = false;
                    op = false;
                }
                    break;
                case '#':
                {
                    comment = true;
                }
                    break;
                case '%':
                {
                    op = true;
                }
                    break;
                default:
                    break;
            }
        }

        f << std::endl;
    }

    void CodeGenerator::write(section_enum select, const char* fmt, ...)
    {
        va_list argv;
        va_start(argv, fmt);


        switch (select)
        {
            case CODE:
                write_to_file(fcode, argv, fmt);
                break;
            case DATA:
                write_to_file(fdata, argv, fmt);
                break;
            case FUNCTION_CODE:
                write_to_file(ffunc, argv, fmt);
                break;
            default:
                break;
        }

        va_end(argv);
    }

    void CodeGenerator::write_label(section_enum select, const std::string label)
    {
        switch (select)
        {
            case CODE:
                fcode << label << ":" << std::endl;
                break;

            case DATA:
                fdata << label << ":" << std::endl;
                break;
            case FUNCTION_CODE:
                ffunc << "_" + label << ":" << std::endl;
                break;
            default:
                break;
        }
    }

    const std::string CodeGenerator::translate_reg(cpu_registers r)
    {
        return reg[r];
    }

    const std::string CodeGenerator::translate_low_reg(cpu_registers r)
    {
        return low_reg[r];
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
        write(CODE, "c%s#s", "pushl", translate_reg(r), "General register spilling (" + translate_reg(r) + ")");
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
        write(CODE, "c%s#s", "pushl", translate_reg(r), "General register spilling (" + translate_reg(r) + ")");
        return r;
    }

    std::string CodeGenerator::get_mem_var(int offset)
    {
        return std::to_string(offset) + "(" + reg[EBP] + ")";
    }

    void CodeGenerator::free_reg(cpu_registers r)
    {
        reg_use[r] = false;
    }

    void CodeGenerator::lock_reg(cpu_registers r)
    {
        reg_use[r] = true;
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
        write(CODE, "c#c", "leave", "Leave the main program");
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

        ffunc.seekg(0);
        ffunc.seekp(0);
        while(!ffunc.eof())
        {
            ffunc.get(ch);
            fout << ch;
        }
        ffunc.close();

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
        std::remove("func.s");
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