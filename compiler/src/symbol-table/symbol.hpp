typedef enum {
  INT, REAL, BOOL, CHAR, STRING, ARRAY_INT, ARRAY_REAL, ARRAY_BOOL
} data_type;

typedef struct {
  char* name;
  data_type data_type;
  uint32_t offset;
  uint32_t addr;
  bool isGlobal;
  bool isStatic;
  uint32_t scope;
} variable;

typedef struct {
  variable var;
  uint32_t next;
} variable_list;

typede struct {
  char* label;
  data_type return_type;
  variable_list local_vars;
  variable_list static_vars;
  uint32_t init_addr;
  uint32_t return_addr;
  uint32_t scope;
} function;
