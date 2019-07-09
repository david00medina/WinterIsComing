#ifndef ERRORMANAGERPACK_HPP
#define ERRORMANAGERPACK_HPP

#include <string>

typedef enum
{
    NOT_DECLARED_VAR,
    NOT_DECLARED_FUN,
    REDECLARATION_VAR,
    INCOMPATIBLE_OPERANDS,
    INCOMPATIBLE_ASSIGN,
    WRONG_ASSIGN,
    WRONG_RELATIONAL_OPERANDS,
    MISSING_CLAUSE_BOOL_EXPR,
    MULTIPLE_ELSE
} error_flag;

const std::string error_header = "[!] Error : ";

#endif
