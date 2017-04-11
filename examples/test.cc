#include <fstream>
#include <iostream>
#include "../include/libc8lexer.hpp"
// To test the log output version
int main() {
  std::ofstream a("a.log");  // out put log to test1.log
  if (a.is_open()) {
    std::ifstream b("ex.asm");
    std::stringstream ss;
    ss << b.rdbuf();
    libc8Lexer lexer(ss.str());
    lexer.Scan();
    ss.str("");
    ss.clear();
    std::cout << ss.str() << std::endl;
    std::cout << lexer.Output();
    ss << lexer.Output();
    a << ss.str();
    a.close();
  }
  return 0;
}
