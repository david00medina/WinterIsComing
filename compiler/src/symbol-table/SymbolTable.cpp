#include "SymbolTable.hpp"
#include "../error-manager/ErrorManager.hpp"

namespace wic
{
    const char* TableEntry::get_id()
    {
        return id;
    }

    entry_data TableEntry::get_data()
    {
        return entry_d;
    }

    unsigned int TableEntry::get_line()
    {
        return line;
    }

    unsigned int TableEntry::get_scope()
    {
        return scope;
    }

    SymbolTable::SymbolTable()
    {
        for (int i = 0; i < MAX_ENTRIES; ++i) head[i] = nullptr;
        addr = 0;
    }

    SymbolTable::~SymbolTable()
    {
        delete *head;
    }

    int SymbolTable::hash(const char* id)
    {
        int hash = 0;

        for (int i = 0; id[i] != '\0'; ++i) {
            if (id[i+1] == '\0') hash += id[i] ^ id[0];
            else hash += id[i] ^ id[i+1];
        }

        return hash % MAX_ENTRIES;
    }

    bool SymbolTable::insert(const char* id, entry_data entry_d, unsigned int line, unsigned int scope)
    {
        printf("\n-----------------linea-%d-----------valor-%d-------\n", line, entry_d);
        int i = hash(id);

        TableEntry* existing_entry = lookup(id);

        if (existing_entry != nullptr && existing_entry->scope == scope)
        {
            ErrorManager::send(REDECLARATION_VAR, id);
        }

        addr -= entry_d.var.size;
        entry_d.var.offset = addr;

        TableEntry* tEntry = new TableEntry(id, entry_d, line, scope);

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
        TableEntry* prev = nullptr;

        TableEntry* curr = head[i];
        if (curr == nullptr) return false;

        TableEntry* next = curr->next;

        while (curr != nullptr)
        {
            if (strcmp(curr->id, id) == 0 && prev == nullptr)
            {
                head[i] = next;
                addr += curr->entry_d.var.size;
                delete curr;
                return true;
            } else if (strcmp(curr->id, id) == 0)
            {
                prev->next = next;
                addr += curr->entry_d.var.size;
                delete curr;
                return true;
            }

            prev = curr;
            curr = next;
            next = next->next;
        }

        return false;
    }

    int SymbolTable::erase(int scope)
    {
        int erased = 0;

        for (int i = 0; i < MAX_ENTRIES; i++)
        {
            TableEntry* prev = nullptr;
            TableEntry* curr = head[i];
            TableEntry* next = nullptr;

            if (curr != nullptr && curr->next != nullptr) next = curr->next;

            while (curr != nullptr)
            {
                if (curr->scope == scope)
                {
                    erased++;
                    delete curr;
                    prev = next;
                    if (next != nullptr) curr = next->next;
                    else curr = nullptr;
                    if (curr != nullptr) next = curr->next;
                } else
                {
                    prev = curr;
                    curr = next;
                    if (next != nullptr) next = next->next;
                }
            }
        }

        return erased;
    }


    bool SymbolTable::modify(const char* id, entry_data entry_d, unsigned int line, unsigned int scope)
    {
        int i = hash(id);
        TableEntry* start = head[i];

        if (start == nullptr) return false;

        while (start != nullptr)
        {
            if (strcmp(start->id, id) == 0)
            {
                start->entry_d = entry_d;
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
            if (strcmp(start->id, id) == 0) return start;
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