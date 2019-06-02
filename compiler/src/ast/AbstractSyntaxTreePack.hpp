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
        MUL,
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
        ASSGN,
        BODY,
        RET,
        CALL,
        PARAM,
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

    typedef struct ASTNode
    {
        std::string id;
        node_type node_t;
        data_type data_t;
        data_value data_v;
        ASTNode* ptr1;
        ASTNode** ptr2;
        ASTNode* ptr3;
        ASTNode** args;
        GSymbolTable* gst;
        SSymbolTable* sst;
        LSymbolTable* lst;
    } ASTNode;
}

#endif
