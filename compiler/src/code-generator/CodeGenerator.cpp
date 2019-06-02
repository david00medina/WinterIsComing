#include <regex>
#include <cstdio>
#include <sstream>
#include "CodeGenerator.hpp"

namespace wic
{
    CodeGenerator::CodeGenerator() : fout(nullptr)
    {
//        fdata.open("data.s", fstream::in | fstream::out | fstream::app);
//        fcode.open("code.s", fstream::in | fstream::out | fstream::app);
        file_p.data_p = 0;
        file_p.code_p = 0;
        label.code_l = 0;
        label.data_l = 0;
    }

    CodeGenerator::CodeGenerator(const std::string &path) : path(path)
    {
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
//        fdata.open("data.s", fstream::in | fstream::out | fstream::app);
//        fcode.open("code.s", fstream::in | fstream::out | fstream::app);
        file_p.data_p = 0;
        file_p.code_p = 0;
        label.code_l = 0;
        label.data_l = 0;
    }

    void CodeGenerator::save_fstream_p(section_enum selector)
    {
        switch (selector)
        {
            case DATA:
                file_p.data_p = fout.tellp();
                std::cout << "DATA SAVE: " << file_p.data_p << std::endl;
                break;
            case CODE:
                file_p.code_p = fout.tellp();
                std::cout << "CODE SAVE: " << file_p.code_p << std::endl;
                break;
        }
    }

    void CodeGenerator::load_fstream_p(section_enum selector)
    {
        switch (selector)
        {
            case DATA:
                std::cout << "DATA LOAD: " << file_p.data_p << std::endl;
                fout.seekp(file_p.data_p);
                fout.seekg(file_p.data_p);
                break;
            case CODE:
                std::cout << "CODE LOAD: " << file_p.code_p << std::endl;
                fout.seekp(file_p.code_p);
                fout.seekg(file_p.code_p);
                break;
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
        }
    }

    void CodeGenerator::set_path(const std::string path)
    {
        this->path = path;
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
    }

    void CodeGenerator::init()
    {
        /*fcode << initial_spacing <<".text" << std::endl;
        fcode << initial_spacing << ".global main" << std::endl << std::endl;
        fcode << "main:" << std::endl;*/
        save_fstream_p(DATA);

        fout << std::endl;

        fout << initial_spacing <<".text" << std::endl;
        fout << initial_spacing << ".global main" << std::endl << std::endl;
        fout << "main:" << std::endl;

        save_fstream_p(CODE);
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

                else if (m.str(0) == "%c") ss << node->data_v.char_val;

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

        /*fdata << label <<":\n";
        fdata << initial_spacing << ".asciiz " << "\"" << msg << "\"" << char(10);

        fcode << initial_spacing << "mov" << instr_spacing << "$" + label << ", %edi" << char(10);
        fcode << initial_spacing << "call" << instr_spacing << "puts" << char(10) << char(10);*/

        load_fstream_p(DATA);
        fout << label <<":" << std::endl;
        fout << initial_spacing << ".asciiz " << "\"" << msg << "\"" << std::endl;
        save_fstream_p(DATA);

        load_fstream_p(CODE);
        fout << initial_spacing << "mov" << instr_spacing << "$" + label << ", %edi" << std::endl;
        fout << initial_spacing << "call" << instr_spacing << "puts" << std::endl << std::endl;
        save_fstream_p(CODE);

        va_end(argv);


    }

    void CodeGenerator::end()
    {

//        fout << fdata.rdbuf();
//        fout << fcode.rdbuf();

//        fdata.close();
//        fcode.close();
        fout.close();

//        std::remove("data.s");
//        std::remove("code.s");
    }
}