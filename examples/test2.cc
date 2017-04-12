#include "../include/libc8lexer"

#include <iostream>

int main(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    std::ifstream infile(argv[i]);
    std::stringstream ss << infile.rdbuf();
    libc8Lexer lexer(ss.str());
  }
}