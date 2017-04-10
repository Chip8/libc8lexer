#include "lexer.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
static std::string C8InsTable[] = {"ADD", "SUB",  "SUBN", "AND", "OR", "XOR",
                                   "SE",  "SNE",  "SYS",  "JP",  "LD", "DRW",
                                   "SKP", "CALL", "CLS",  "RET"};
static const std::string C88BitReg[] = {"V1", "V2", "V3", "V4", "V5",
                                        "V6", "V7", "V8", "V9", "VA",
                                        "VB", "VC", "VD", "VE", "VF"};
static const std::string AlphaTable = "0123456789ABCDEF@!";
std::string TokenTypeTable[] = {"Instruction",      "8 Bit Register",
                                "Address Register", "Var",
                                "Delay Timer",      "Sound Timer"};
enum TokenTypeIndex { INS, REG8BIT, REGADDR, VAR, DT, ST };
class LexEmptyExc : public std::runtime_error {
 public:
  LexEmptyExc() : runtime_error("Empty Line."){};
  virtual const char* what() const throw() { return runtime_error::what(); }
} LexEE;
class LexErrorVar : public std::runtime_error {
 public:
  LexErrorVar()
      : runtime_error("Error var type.Out of range or not a valid var."){};
  virtual const char* what() const throw() { return runtime_error::what(); }
} LexEV;

class LexErrorToken : public std::runtime_error {
 public:
  LexErrorToken() : runtime_error("Error Token."){};
  virtual const char* what() const throw() { return runtime_error::what(); }
} LexET;
bool LexerLogWriter(std::string LogLine, std::ofstream& LexerLogFile) {
  if (!LexerLogFile.good())
    return false;
  else {
    LexerLogFile << LogLine;
    return true;
  }
}

std::vector<std::string> lexer(std::string ProgLine,
                               std::ofstream& LexerLogFile) {
  try {
    if (ProgLine.length() == 0) throw LexEE;
    std::transform(ProgLine.begin(), ProgLine.end(), ProgLine.begin(),
                   std::toupper) if (ProgLine.back() != ';') ProgLine += ";";
    std::stringstream LogStream;
    std::string Token("");
    std::string Var("");
    std::vector<std::string> TokenList;
    std::string param("");
    for (auto x : ProgLine) {
      std::string TokenType;
      if (x == ' ' || x == ',' || x == ';') {
        if (&x == &ProgLine.back()) {
          Token += x;
          std::cout << "aaa";
        }
        if (find(std::begin(C8InsTable), std::end(C8InsTable), Token) !=
            std::end(C8InsTable)) {
          TokenType = TokenTypeTable[INS];
        } else if (Token[0] == 'V' &&
                   (find(std::begin(C88BitReg), std::end(C88BitReg), Token) !=
                    std::end(C88BitReg))) {
          TokenType = TokenTypeTable[REG8BIT];
        } else if (Token == "DT") {
          TokenType = TokenTypeTable[DT];
        } else if (Token == "ST") {
          TokenType = TokenTypeTable[ST];
        } else if (Token == "I") {
          TokenType = TokenTypeTable[REGADDR];
        } else {
          if (Token.length() <= 4) {
            TokenType = TokenTypeTable[VAR];
          } else {
            LogStream << "Error:Invalid var exist." << std::endl;
            throw LexEE;
          }
        }
        if (!TokenType.empty() && !Token.empty()) {
          LogStream << TokenType << " found: " << Token << std::endl;
          TokenType = "";
          TokenList.push_back(Token);
          Token = "";
        }
      } else {
        Token += x;
      }
    }
    if (!LogStream.str().empty() && LexerLogFile.good())
      LexerLogWriter(LogStream.str(), LexerLogFile);
    return TokenList;
  } catch (std::exception& e) {
    std::cerr << "Error occured!Error info: " << e.what() << std::endl;
  }
}

int main() {
  std::ofstream a("Test.log");
  std::ifstream b("test.asm");
  for (std::string s; getline(b, s, '\n');)
    for (auto x : lexer(s, a)) std::cout << x << std::endl;
  return 0;
}