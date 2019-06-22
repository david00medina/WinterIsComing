#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <cstdarg>
#include <iostream>
#include <fstream>
#include <string>
#include "CodeGeneratorPack.hpp"
#include "../ast/AbstractSyntaxTree.hpp"

#define TOTAL_REG 4
#define ALL_REG 8

namespace wic {
    class CodeGenerator {
    private:
        bool reg_use[TOTAL_REG];
        std::string path;
        std::fstream fout, fcode, fdata;
        fstream_p file_p;
        label_c label;

        const std::string initial_spacing = "        ";
        const std::string instr_spacing = "\t\t";
        const std::string code_label = "C";
        const std::string data_label = "D";
        const char* reg[ALL_REG] = { "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%esp", "%ebp" };

        std::string get_label(section_enum);

    public:
        CodeGenerator();
        CodeGenerator(const std::string);
        ~CodeGenerator() = default;

        void set_path(const std::string);

        int get_reg();
        void lock_reg(cpu_registers);
        void free_reg(cpu_registers);

        void init();
        /*void push_scope();
        void pop_scope();*/
        void save_value(void*, unsigned int, bool);
        cpu_registers get_value(unsigned int);
        void instr(const std::string, cpu_registers);
        void instr(const std::string, unsigned int);
        void instr(const std::string, cpu_registers, cpu_registers);
        void instr(const std::string, unsigned int, unsigned int);
        void instr(const std::string, unsigned int, cpu_registers);
        void instr(const std::string, cpu_registers, unsigned int);
        void print(std::string, unsigned int, ...);
        void exit();
        void end();
    };
}

#endif
