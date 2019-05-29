enum Type {
  INT, REAL, BOOL, CHAR, STRING
}

struct Entry {
  char* name;
  Type type;
  byte value;
  int scope_lvl;
  struct Entry *hash_link;
}


bool lookup(char*);

bool insert(char*, Type, byte);

bool delete(char*);

bool modify(char*, byte);
