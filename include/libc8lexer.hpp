#include <exception>
#include <sstream>
#include <string>
#include <vector>

#ifndef LIBC8_LEXER_H
#define LIBC8_LEXER_H
static const char AlphaTable[] =
    "0123456789ABCDEFGHIJKLMNOPRSTUVWXYZ,@!:/\n\t ";
// The empty

enum libc8TokenType { INS, BIT8REG, VAR, ADDREG, TIMER, COMMA };

static const std::string C8InsTable[] = {
    "CLS", "RET", "SYS", "JP",  "CALL", "SE",  "SNE", "LD",  "ADD", "OR",
    "AND", "XOR", "SUB", "SHR", "SUBN", "SHL", "RND", "DRW", "SKP", "SKNP"};
// Chip-8 assembly token types
static const std::string libc8TokenTypeTable[] = {
    "Instruction",      "8 Bit Register", "Var",
    "Address Register", "Timer",          "Comma"};

// Chip-8 Token Type class
class libc8Token {
 public:
  inline std::string Type();
  inline std::string TokenStr();
  std::string Pos();
  libc8Token(libc8TokenType TypeID, std::string Token, unsigned int Pos_Start,
             unsigned int Pos_End = 0);

 private:
  libc8TokenType TypeID;
  std::string Token;
  unsigned int Pos_Start;
  unsigned int Pos_End;
};

class libc8Lexer {
 public:
  libc8Lexer(std::string SourceProg);
  bool Scan();  // scan source and constructs token lists
  std::vector<libc8Token>& GetList();
  // Generates lexer output string
  std::string Output(std::vector<libc8Token> TokenList);
  std::string Output();

 private:
  std::string SourceProg;
  bool Scanned = false;
  std::vector<libc8Token> TokenList;
};
#endif