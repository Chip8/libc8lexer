#include <fstream>
#include <iostream>
#include "../include/libc8lexer.hpp"

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    std::cout << argc - 1 << " File read. ";
    std::ifstream infile(argv[i]);
    std::stringstream ss;
    ss << infile.rdbuf();
    std::cout << argv[i] << " :" << std::endl << ss.str();
    libc8Lexer lexer(ss);
    std::string OutFile = argv[i];
    OutFile += ".log";
    std::ofstream ofile(OutFile);
    lexer.Scan();
    ofile << lexer.Output();
    std::cout << "Lexer output: " << std::endl;
    std::cout << lexer.Output();
    std::cout << "Writing log to " << OutFile << "...";
    if (ofile.good())
      std::cout << "Succeed!" << std::endl;
    else
      std::cout << "Failed." << std::endl;
    ofile.close();
  }
}