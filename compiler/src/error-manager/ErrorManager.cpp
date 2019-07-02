#include "ErrorManager.hpp"
#include "ErrorManagerPack.hpp"
#include "../utils/termcolor.hpp"

namespace wic
{
    ErrorManager::ErrorManager() { }

    void ErrorManager::send(error_flag flag)
    {
        std::string out;

        switch (flag)
        {
            case WRONG_ASSIGN:
                out = "Wrong assignation";
                break;
            default:
                return;
        }

        std::cout << termcolor::red << termcolor::bold << error_header << termcolor::reset << out << std::endl;
        exit(-1);
    }

    void ErrorManager::send(error_flag flag, std::string msg)
    {
        std::string out;
        switch (flag)
        {
            case NOT_DECLARED_VAR:
                out = "\'" + msg + "\' was not declared in this scope";
                break;
            case REDECLARATION_VAR:
                out = "Redeclaration of \'" + msg + "\'";
                break;
            case INCOMPATIBLE_OPERANDS:
                out = "Incompatible operand type for the " + msg + " operation";
                break;
            case INCOMPATIBLE_ASSIGN:
                out = "Cannot assign a different value type to the variable \'" + msg + "\'";
                break;
            case WRONG_RELATIONAL_OPERANDS:
                out = "Boolean data type is required to perform a " + msg + " operation";
                break;
            case NOT_CLAUSE_BOOL_EXPR:
                out = "The " + msg + " clause expected a boolean expression";
                break;
            default:
                return;
        }

        std::cout << termcolor::red << termcolor::bold << error_header << termcolor::reset << out << std::endl;
        exit(-1);
    }
}
