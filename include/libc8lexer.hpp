#include <exception>
#include <sstream>
#include <string>
#include <vector>

#ifndef LIBC8_LEXER_H
#define LIBC8_LEXER_H
static const char AlphaTable[] = "0123456789ABCDEFGHIJKLMNOPRSTUVWXYZ,@!/\n\t ";
// The empty

enum C8TokenType { INS, BIT8REG, VAR, ADDREG, TIMER, COMMA };

// Chip-8 assembly token types
std::string C8TokenTypeTable[] = {"Instruction", "8 Bit Register",
                                  "Var",         "Address Register",
                                  "Timer",       "Comma"};

// Chip-8 Token Type class
class C8Token {
 public:
  C8Token();
  ~C8Token();
  inline std::string Type();
  inline std::string Token();
  template <typename T>
  C8Token(C8TokenType TypeID, std::string Token, unsigned int Pos_Start,
          unsigned int Pos_End = NULL);

 private:
  C8TokenType TypeID;
  std::string TokenStr;
  unsigned int Pos_Start;
  unsigned int Pos_End;
};

class C8Lexer {
 public:
  C8Lexer();
  C8Lexer(std::string SourceProg);
  ~C8Lexer();
  bool Scan();  // scan source and constructs token lists
  std::vector<C8Token>& GetList();
  // Generates lexer output string
  std::string Output(std::vector<C8Token> TokenList);
  std::string Output();

 private:
  std::string SourceProg;
  bool Scanned = false;
  std::vector<C8Token> TokenList;
}

std::vector<C8Token>
libc8Lexer(std::string SourceProg);

std::string libc8LexerOutput(std::vector<C8Token> TokenList);

#endif