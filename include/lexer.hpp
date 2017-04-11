#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
static std::string C8InsTable[] = {"ADD", "SUB",  "SUBN", "AND", "OR", "XOR",
                                   "SE",  "SNE",  "SYS",  "JP",  "LD", "DRW",
                                   "SKP", "CALL", "CLS",  "RET"};
static const std::string C88BitReg[] = {"V1", "V2", "V3", "V4", "V5",
                                        "V6", "V7", "V8", "V9", "VA",
                                        "VB", "VC", "VD", "VE", "VF"};
std::string TokenTypeTable[] = {"Instruction",      "8 Bit Register",
                                "Address Register", "Var",
                                "Delay Timer",      "Sound Timer"};
enum TokenTypeIndex { INS, REG8BIT, REGADDR, VAR, DT, ST };

// The empty
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

// Write log to file
bool LexerLogWriter(std::string LogLine, std::ofstream& LexerLogFile) {
  if (!LexerLogFile.is_open())
    return false;
  else {
    LexerLogFile << LogLine;
    return true;
  }
}

std::vector<std::string> libc8LineLineLexer(std::string ProgLine,
                                            std::ofstream& LexerLogFile) {
  std::vector<std::string> TokenList;
  try {
    if (ProgLine.length() == 0) throw LexEE;
    if (ProgLine.back() != ';') ProgLine += ";";
    std::stringstream LogStream;
    std::string Token("");
    std::string Var("");
    std::string param("");
    for (auto x : ProgLine) {
      std::string TokenType;
      if (x == ' ' || x == ',' || x == ';') {  // skip ' ' and ','
        if (&x == &ProgLine.back() && x != ' ' && x != ',' && x != ';') {
          Token += x;
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
    if (!LogStream.str().empty() && LexerLogFile.is_open())
      LexerLogWriter(LogStream.str(), LexerLogFile);
  } catch (std::exception& e) {
    std::cerr << "Error occured!Error info: " << e.what() << std::endl;
  }
  return TokenList;
}

// None output style one line lexer
std::vector<std::string> libc8LineLineLexer(std::string ProgLine) {
  std::ofstream NullOf;
  return libc8LineLineLexer(ProgLine, NullOf);
}

std::vector<std::string> libc8Lexer(std::string Source,
                                    std::ofstream& OutStream) {
  std::stringstream SourceStream;
  SourceStream << Source;
  std::vector<std::string> TokenList;
  std::string ProgLine;
  while (std::getline(SourceStream, ProgLine)) {
    std::vector<std::string> LineList = libc8LineLineLexer(ProgLine, OutStream);
    TokenList.insert(TokenList.end(), LineList.begin(), LineList.end());
  }
  return TokenList;
}

std::vector<std::string> libc8Lexer(std::string Source) {
  std::ofstream NullOStream;
  return libc8Lexer(Source, NullOStream);
}