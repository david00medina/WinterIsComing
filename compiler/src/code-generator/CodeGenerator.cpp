#include "CodeGenerator.hpp"

namespace wic
{
    CodeGenerator::CodeGenerator(const std::string path) : num_label(0)
    {
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
    }

    void CodeGenerator::set_path(const std::string path)
    {
        fout.open(path + ".s", std::ios::in | std::ios::out | std::ios::trunc);
    }

    void CodeGenerator::init()
    {
        fout << ".global _start" << char(10) << char(10);
        fout << initial_spacing <<".text" << char(10);
        fout << "_start:" << char(10);
    }

    void CodeGenerator::print(std::string msg, void** args)
    {
        unsigned int i = 0, k = 0;
        std::size_t j = msg.find("%s", k);

        while (j != std::string::npos)
        {
            std::string* arg = static_cast<std::string*>(args[i]);
            msg.replace(j, 2, *arg);
            i++;
            j = msg.find("%s", k);
            k = j + 2;
        }
    }

    void CodeGenerator::end()
    {
        fout << char(10);
        fout.close();
    }
}