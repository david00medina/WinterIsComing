#ifndef ASTPACK_HPP
#define ASTPACK_HPP

#include "../symbol-table/SymbolTable.hpp"
#include "../symbol-table/SymbolTablePack.hpp"

namespace wic
{
    typedef enum
    {
        LEAF,
        ID,
        SUM,
        SUB,
        PROD,
        DIV,
        POWER,
        RADICAL,
        MOD,
        GT,
        GE,
        EQ,
        NEQ,
        LE,
        LT,
        NOT,
        AND,
        OR,
        IF,
        WHILE,
        FOR,
        SCAN,
        PRINT,
        ASSIGN,
        FUNCTION,
        BODY,
        RET,
        CALL,
        PARAM,
        ARG,
        MAIN
    } node_type;

    typedef union data_value
    {
        int int_val;
        float real_val;
        bool bool_val;
        char char_val;
        char* str_val;
        int* int_array_val;
        float* real_array_val;
        bool* bool_array_val;
    } data_value;
}

#endif
