#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include <string>

#include "ErrorManagerPack.hpp"

namespace wic
{
    class ErrorManager
    {
    private:
        ErrorManager();

    public:
        static void send(error_flag);
        static void send(error_flag, std::string);
    };
}

#endif
