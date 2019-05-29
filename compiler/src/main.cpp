#include <iostream>


extern int yylex();
extern int yyparse(void);
extern void yyerror(const char *);
extern FILE *yyin;
extern int yylineno;

int main(int argc, char const **argv) {
  if (argc > 1) {
    if (!(yyin = fopen(argv[1], "r"))) {
      perror(argv[1]);
      return(1);
    }
  }

  int result = 1;
  while(1) { /* TODO: Quitar este bucle cuando entreguemos el trabajo */
    int result = yyparse();

    if (result == 0) {
      std::cout << "[OK] The input is valid." << std::endl;
    } else {
      std::cout << "[FAIL] The input is invalid." << std::endl;
    }
  }
  return result;
}


/* Funciones auxiliares */
void yyerror(char const *x) {
  printf("[!] Error %s\n", x);
}
