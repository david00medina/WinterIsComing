#ifndef WIC_TABLE_HPP
#define WIC_TABLE_HPP

#include <string.h>

#include "SymbolTablePack.hpp"
#include "../utils/termcolor.hpp"

#define MAX_ENTRIES 128
#define TYPE_NUM 11

namespace wic
{
    class TableEntry
    {
    private:
        const char* id;
        entry_data entry_d;
        unsigned int line;
        unsigned int scope;
        TableEntry* next;

        const char* type_data_str[TYPE_NUM] =
        {
            "int",
            "real",
            "bool",
            "char",
            "void",
            "string",
            "array_int",
            "array_real",
            "array_bool",
            "function",
            "unknown"
        };

    public:
        TableEntry() { next = nullptr; }
        TableEntry(const char* id, entry_data entry_d, unsigned int line, unsigned int scope)
            : id(id), entry_d(entry_d), line(line), scope(scope) {}

        ~TableEntry(){};

        const char* get_id();
        entry_data get_data();
        unsigned int get_line();
        unsigned int get_scope();

        void print()
        {
            if (sizeof(entry_d) == sizeof(variable)) std::cout << "(" << id << ", " << type_data_str[entry_d.var.type] << ", " << line << ", " << scope << ")";
            else if (sizeof(entry_d) == sizeof(function)) std::cout << "(" << id << ", " << type_data_str[entry_d.fun.return_type] << ", " << line << ", " << scope << ")";
        }

        friend class SymbolTable;
    };


    class SymbolTable
    {
    protected:
        TableEntry* head[MAX_ENTRIES];
        int addr;

        virtual int hash(const char*);

    public:
        SymbolTable();
        virtual ~SymbolTable();

        virtual bool insert(const char*, entry_data, unsigned int, unsigned int);
        virtual bool erase(const char*);
        virtual int erase(int);
        virtual bool modify(const char*, entry_data, unsigned int, unsigned int);
        virtual TableEntry* lookup(const char*);
        virtual void show(const char*);
        virtual void show(int);
    };


    class LSymbolTable : public SymbolTable
    {
    public:
        LSymbolTable() = default;
        ~LSymbolTable() = default;
    };


    class GSymbolTable : public SymbolTable
    {
    public:
        GSymbolTable() = default;
        ~GSymbolTable() = default;
    };


    class SSymbolTable : public SymbolTable
    {
    public:
        SSymbolTable() = default;
        ~SSymbolTable() = default;
    };
}

#endif
