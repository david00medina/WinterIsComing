#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <cstdarg>
#include <iostream>
#include <fstream>
#include <string>

#include "CodeGeneratorPack.hpp"

#define TOTAL_REG 4
#define ALL_REG 12

namespace wic {
    class CodeGenerator {
    private:
        bool reg_use[ALL_REG];
        unsigned int general_spill_count;
        unsigned int float_spill_count;
        std::string path;
        std::fstream fout, fcode, fdata;
        fstream_p file_p;
        label_c label;

        const std::string initial_spacing = "\t\t";
        const std::string instr_spacing = "\t";
        const std::string comment_spacing = "\t\t\t";
        const std::string code_label = ".C";
        const std::string data_label = ".D";
        const std::string float_label = ".F";
        const std::string reg[ALL_REG] = { "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%esp", "%ebp", "%xmm0", "%xmm1", "%xmm2", "%xmm3" };
        const std::string low_reg[ALL_REG] = { "%al", "%bl", "%cl", "%el", "%sil", "%dil", "spl", "bpl" };

    public:
        CodeGenerator();
        CodeGenerator(const std::string);
        ~CodeGenerator() = default;

        void set_path(const std::string);
        void write_data_section(unsigned int, ...);
        void write_data_section(const std::string, unsigned int, ...);
        void write_code_section(const std::string, const std::string);
        void write_code_section(const std::string, const std::string, const std::string);
        void write_code_section(const std::string, const std::string, const std::string, const std::string);

        std::string get_label(section_enum);

        const std::string translate_reg(cpu_registers);
        const std::string translate_low_reg(cpu_registers);
        cpu_registers get_reg();
        cpu_registers get_float_reg();
        void lock_reg(cpu_registers);
        void free_reg(cpu_registers);
        bool is_used(cpu_registers);

        void init();
        void print(std::string, unsigned int, ...);
        void exit();
        void end();

        void print_reg_use();
    };
}

#endif
