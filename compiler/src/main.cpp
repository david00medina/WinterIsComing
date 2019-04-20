#include <iostream>

extern int yyparse();

int int main(int argc, char const *argv[]) {
  int result = yyparse();
  if (result) {
    std::out << "The input is valid." << std::endl;
  } else {
    std::out << "The input is invalid." << std::endl;
  }
  return result;
}
