#ifndef WIC_TABLE_HPP
#define WIC_TABLE_HPP

#include <iostream>
#include "SymbolTablePack.hpp"

#define MAX_ENTRIES 128
#define TYPE_NUM 10

namespace wic
{
    class TableEntry
    {
    private:
        const char* id;
        variable* var;
        function* fun;
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
                    "function"
            };

    public:
        TableEntry() { next = nullptr; }
        TableEntry(const char* id, variable* var, function* fun, unsigned int line, unsigned int scope)
            : id(id), var(var), fun(fun), line(line), scope(scope) {}

        ~TableEntry()
        {
            delete id;
            delete var;
            delete fun;
            delete next;
        }


        void print()
        {
            if (var != nullptr) std::cout << "(" << id << ", " << type_data_str[var->type] << ", " << line << ", " << scope << ")";
            else if (fun != nullptr) std::cout << "(" << id << ", " << type_data_str[fun->return_type] << ", " << line << ", " << scope << ")";
        }

        friend class SymbolTable;
    };


    class SymbolTable
    {
    protected:
        TableEntry* head[MAX_ENTRIES];

        virtual int hash(const char*);

    public:
        SymbolTable() { for (int i = 0; i < MAX_ENTRIES; ++i) head[i] = nullptr; }
        ~SymbolTable() { for (int i = 0; i < MAX_ENTRIES; ++i) head[i] = nullptr; }

        virtual bool insert(const char*, variable*, function*, unsigned int, unsigned int);
        virtual bool erase(const char*);
        virtual bool modify(const char*, variable*, function*, unsigned int, unsigned int);
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
