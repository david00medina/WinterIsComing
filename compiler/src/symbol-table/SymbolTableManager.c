#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "./headers.h"

struct Symbol* firstSymbol;
struct Symbol* lastSymbol;
struct Symbol* lastFunc;
int tableSize = 0;

int tablePointer = 12000 - 4; //12000 --> default Stackpointer R7
int currentDepth = 0;

void insertVariableInSymbolTable(char *id){
    struct Symbol* symbol = malloc(sizeof(struct Symbol));

    symbol->id = malloc(sizeof(char) * strlen(id));
    symbol->nextSymbol = NULL;
    symbol->label = NULL;
    symbol->numberOfLocalVariables = NULL;
    symbol->depth = currentDepth;
    symbol->type = currentDepth == 0 ? 'g' : 'l';
    symbol->address = symbol->type == 'g' ? _getStaticAddressFromSymbolTable() : _getRelativeAddressFromSymbolTable();

    strcpy(symbol->id, id);

    _existSymbolInSymbolTable(symbol) ? printf("Error") : _linkSymbolToSymbolTable(symbol);

}

void insertParameterInSymbolTable(char *id){
    struct Symbol* symbol = malloc(sizeof(struct Symbol));

    symbol->id = malloc(sizeof(char) * strlen(id));
    symbol->nextSymbol = NULL;
    symbol->label = NULL;
    symbol->numberOfLocalVariables = NULL;
    symbol->depth = currentDepth;
    symbol->type = 'p';
    symbol->address = _getRelativeAddressFromSymbolTable();

    strcpy(symbol->id, id);

    _existSymbolInSymbolTable(symbol) ? printf("Error") : _linkSymbolToSymbolTable(symbol);

}

void insertFunctionSymbolTable(char *id){
    struct Symbol* symbol = malloc(sizeof(struct Symbol));
    
    symbol->id = malloc(sizeof(char) * strlen(id));
    symbol->nextSymbol = NULL;
    symbol->label = getLabel();
    symbol->numberOfLocalVariables = 0;
    symbol->type = 'f';
    symbol->address = NULL;
    symbol->depth = 0;

    strcpy(symbol->id, id);

    _existSymbolInSymbolTable(symbol) ? printf("Error") : _linkSymbolToSymbolTable(symbol);
    
}

int getLabel(){
    return 0;
}

void _linkSymbolToSymbolTable(struct Symbol* symbol){
    _incrementNumberOfLocalVariablesAndParameters();
    if(tableSize == 0) firstSymbol = symbol;
    else {
        lastSymbol->nextSymbol = symbol;
        symbol->previousSymbol = lastSymbol;
    }
    
    if(symbol->type == "f") lastFunc = symbol;
    tableSize ++;
    lastSymbol = symbol; 
}

void _incrementNumberOfLocalVariablesAndParameters(){
    if(lastFunc->type == 'p') lastFunc->numberOfParameters++;
    else if(lastFunc->type == 'l') lastFunc->numberOfLocalVariables++;
}

int _getRelativeAddressFromSymbolTable(){
    return (lastFunc->numberOfLocalVariables * 4) + 4;
}

int _getStaticAddressFromSymbolTable() {
    tablePointer = tablePointer - 4;
    return tablePointer;
}

bool _existSymbolInSymbolTable(struct Symbol* symbol){
    struct Symbol* currentSymbol = lastSymbol;
    for(int i = tableSize; i > 0; i--){
        if(currentSymbol->type == symbol->type && currentSymbol->depth == symbol->depth && (strcmp(currentSymbol->id, symbol->id) == 0)){
            return true;
        }
    }
    return false;
}

void _openScopeInSymbolTable(){
    currentDepth++;
}

void _closeScopeInSymbolTable(){
    currentDepth--;
}