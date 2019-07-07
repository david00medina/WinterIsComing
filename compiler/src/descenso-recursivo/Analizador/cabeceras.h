
FILE *yyin;



int getChar();

void while_instr();
void input();
void instr();
void expr();
void term();
void data_value();
void anid_while();
void match(int terminal);
void preanid_while();



  #define END_OF_INSTR 257
  #define RETURN 258
  #define BREAK 259
  #define INT_VAL 261
  #define REAL_VAL 262
  #define BOOL_VAL 263
  #define INT_TYPE 264
  #define REAL_TYPE 265
  #define BOOL_TYPE 266
  #define ASSIGN 267
  #define SUM 268
  #define SUBSTRACT 269
  #define PRODUCT 270
  #define DIVIDE 271
  #define AND 272
  #define OR 273
  #define NOT 274
  #define EQUALS 275
  #define NOT_EQUALS 276
  #define GREATER 277
  #define GREATER_EQUALS 278
  #define LESS 279
  #define LESS_EQUALS 280
  #define HEADER_END 281
  #define FOR_WHILE_CLAUSE 282
  #define SQUARE_BRACKET_OPEN 283
  #define SQUARE_BRACKET_CLOSE 284
  #define PARETHESES_OPEN 285
  #define PARETHESES_CLOSE 286
  #define ID 287
  #define OPEN_CONTEXT_TAG 288
  #define CLOSE_CONTEXT_TAG 289


