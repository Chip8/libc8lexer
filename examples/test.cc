#include "../include/libc8lexer.hpp"

// To test the log output version
int main() {
  std::ofstream a("test.log");  // out put log to test1.log
  if (a.is_open()) {
    std::ifstream b("test.asm");
    std::stringstream ss;
    ss << b.rdbuf();
    for (auto x : libc8Lexer(ss.str())) a << x << " ";
    a.close();
  }
  return 0;
}
