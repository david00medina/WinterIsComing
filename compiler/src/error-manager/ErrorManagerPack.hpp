#ifndef ERRORMANAGERPACK_HPP
#define ERRORMANAGERPACK_HPP

#include <string>

typedef enum
{
    NOT_DECLARED_VAR,
    REDECLARATION_VAR,
    INCOMPATIBLE_OPERANDS,
    INCOMPATIBLE_ASSIGN,
    WRONG_ASSIGN,
    WRONG_RELATIONAL_OPERANDS
} error_flag;

const std::string error_header = "[!] Error : ";

#endif
