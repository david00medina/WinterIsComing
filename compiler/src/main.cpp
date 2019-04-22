#include <iostream>

extern "C"
  int yylineno;
  int yyparse();
  void yyerror(const char*);
  int yylex();
}

int main(int argc, char const *argv[]) {
  int result = yyparse();
  if (result) {
    std::out << "The input is valid." << std::endl;
  } else {
    std::out << "The input is invalid." << std::endl;
  }
  return result;
}
