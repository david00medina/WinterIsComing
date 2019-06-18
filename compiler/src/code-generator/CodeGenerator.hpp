#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <cstdarg>
#include <iostream>
#include <fstream>
#include <string>
#include "CodeGeneratorPack.hpp"
#include "../ast/AbstractSyntaxTree.hpp"

#define TOTAL_REG 8

namespace wic {
    class CodeGenerator {
    private:
        bool register_use[TOTAL_REG];
        std::string path;
        std::fstream fout, fcode, fdata;
        fstream_p file_p;
        label_c label;

        const std::string initial_spacing = "        ";
        const std::string instr_spacing = "\t\t";
        const std::string code_label = "C";
        const std::string data_label = "D";

        std::string get_label(section_enum);

    public:
        CodeGenerator();
        CodeGenerator(const std::string);
        ~CodeGenerator() = default;

        void set_path(const std::string);

        int get_reg();
        void lock_reg(int);
        void free_reg(int);

        void init();
        void print(std::string, unsigned int, ...);
        void exit();
        void end();
    };
}

#endif
