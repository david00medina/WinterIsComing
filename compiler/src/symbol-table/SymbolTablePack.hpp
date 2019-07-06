#ifndef SYMBOL_HPP
#define SYMBOL_HPP

namespace wic
{
    typedef enum {
        INT,
        REAL,
        BOOL,
        CHAR,
        VOID,
        STRING,
        ARRAY_INT,
        ARRAY_REAL,
        ARRAY_BOOL,
        UNKNOWN
    } data_type;

    typedef struct variable {
        data_type type;
        int offset;
        unsigned int size;
        unsigned int array_length;
        unsigned int array_selection;
        bool global;
        bool stat;
        bool local;
    } variable;

    typedef struct param_list {
        char* id;
        data_type type;
        struct param_list *next;
    } param_list;

    typedef struct function {
        data_type return_type;
        unsigned int params_no;
        param_list params;
    } function;

    typedef union entry_data {
        variable var;
        function fun;
    } entry_data;
}

#endif
