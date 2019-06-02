#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace wic {
    class CodeGenerator {
    private:
        std::fstream fout;
        unsigned int num_label;

        const std::string initial_spacing = "        ";
        const std::string instr_spacing = "     ";

    public:
        CodeGenerator() : fout(nullptr), num_label(0) {};
        CodeGenerator(const std::string);
        ~CodeGenerator() = default;

        void set_path(const std::string);

        void init();
        void print(std::string, void**);
        void end();
    };
}

#endif
