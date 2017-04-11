#include "../include/lexer.hpp"

//To test the log output version
int main() {
  std::ofstream a("test1.log"); //out put log to test1.log
  if (a.is_open()){
     std::ifstream b("test1.asm");
     std::stringstream ss;
     ss<<b.rdbuf();
     for(auto x:libc8Lexer(ss.str(),a))
	std::cout<<x<<" ";
     std::cout<<std::endl;
     a.close();
}
  return 0;
}
