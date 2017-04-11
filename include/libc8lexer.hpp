#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

const char AlphaTable[] = "0123456789ABCDEFHIJKLNPRSTW";
// The empty
class LexEmptyExc : public std::runtime_error {
 public:
  LexEmptyExc() : runtime_error("Empty Line."){};
  virtual const char* what() const throw() { return runtime_error::what(); }
} LexEE;
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

std::vector<std::string> libc8LineLineLexer(std::string ProgLine) {
  std::vector<std::string> TokenList;
  try {
    if (ProgLine.length() == 0) throw LexEE;
    if (ProgLine.back() != ';') ProgLine += ";";
    std::string Token("");
    for (auto x : ProgLine) {
      if (std::find(std::begin(AlphaTable), std::end(AlphaTable), x) ==
          std::end(AlphaTable))
        throw LexET;
      std::string TokenType;
      if (x == ' ' || x == ',' || x == ';') {  // skip ' ' and ','
        if (&x == &ProgLine.back() && x != ' ' && x != ',' && x != ';') {
          Token += x;
        }
      } else {
        Token += x;
      }
    }
  } catch (std::exception& e) {
    std::cerr << "Error occured!Error info: " << e.what() << std::endl;
  }
  return TokenList;
}

std::vector<std::string> libc8Lexer(std::string Source) {
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
