#include "SymbolTable.hpp"

namespace wic
{
    int SymbolTable::hash(const char* id)
    {
        int hash = 0;

        for (int i = 0; id[i] != '\0'; ++i) {
            if (id[i+1] == '\0') hash += id[i] ^ id[0];
            else hash += id[i] ^ id[i+1];
        }

        return hash % MAX_ENTRIES;
    }

    bool SymbolTable::insert(const char* id, variable* var, function* fun, unsigned int line, unsigned int scope)
    {
        int i = hash(id);
        TableEntry* tEntry = new TableEntry(id, var, fun, line, scope);

        if (head[i] == nullptr) head[i] = tEntry;
        else
        {
            TableEntry* start = head[i];
            head[i] = tEntry;
            tEntry->next = start;
        }

        return true;
    }


    bool SymbolTable::erase(const char* id)
    {
        int i = hash(id);
        TableEntry* curr = head[i];
        TableEntry* prev = nullptr;

        if (curr == nullptr) return false;

        while (curr->next != nullptr)
        {
            TableEntry* next = curr->next;

            if (curr->id == id && prev == nullptr)
            {
                head[i] = next;
                return true;
            }
            else if (curr->id == id)
            {
                prev->next = next;
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }


    bool SymbolTable::modify(const char* id, variable* var, function* fun, unsigned int line, unsigned int scope)
    {
        int i = hash(id);
        TableEntry* start = head[i];

        if (start == nullptr) return false;

        while (start != nullptr)
        {
            if (start->id == id)
            {
                start->var = var;
                start->fun = fun;
                start->line = line;
                start->scope = scope;
                return true;
            }
            start = start->next;
        }
        return false;
    }

    TableEntry* SymbolTable::lookup(const char* id)
    {
        int i = hash(id);
        TableEntry* start = head[i];

        if (start == nullptr) return nullptr;

        while (start != nullptr)
        {
            if (start->id == id) return start;
            start = start->next;
        }

        return nullptr;
    }

    void SymbolTable::show(const char* id)
    {
        int i = hash(id);

        if (head[i] == nullptr) std::cout << i << ": ";

        else
        {
            TableEntry* tEntry = head[i];
            std::cout << i << ": ";
            tEntry->print();

            while (tEntry->next != nullptr)
            {
                tEntry = tEntry->next;
                std::cout << "--->";
                tEntry->print();
            }
        }

        std::cout << std::endl;
    }

    void SymbolTable::show(int num_entries)
    {
        if (num_entries == 0) num_entries = MAX_ENTRIES;

        std::cout << std::endl << std::endl << "####################################################" << std::endl;
        std::cout << "#                   SYMBOL TABLE                   #" << std::endl;
        std::cout << "####################################################" << std::endl << std::endl;

        for (int i = 0; i < num_entries; ++i) {
            if (head[i] == nullptr) std::cout << i << ": ";

            else
            {
                TableEntry* tEntry = head[i];
                std::cout << i << ": ";
                tEntry->print();

                while (tEntry->next != nullptr)
                {
                    tEntry = tEntry->next;
                    std::cout << "--->";
                    tEntry->print();
                }
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}