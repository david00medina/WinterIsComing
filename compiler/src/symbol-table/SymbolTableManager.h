//TableManager
void insertVariableInSymbolTable(char *id);
void insertParameterInSymbolTable(char *id);
void insertFunctionSymbolTable(char *id);

bool _existSymbolInSymbolTable(struct Symbol* symbol);
void _linkSymbolToSymbolTable(struct Symbol* symbol);
void _incrementNumberOfLocalVariablesAndParameters();

int _getRelativeAddressFromSymbolTable();
int _getStaticAddressFromSymbolTable();

void _openScopeInSymbolTable();
void _closeScopeInSymbolTable();

struct Symbol
{
    char* id;
    int address; //absolute or relative
    char type;
    int depth;
    int label;
    int numberOfParameters;
    int numberOfLocalVariables;
    struct Symbol *previousSymbol;
    struct Symbol *nextSymbol;
};