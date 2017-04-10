#include <fstream>
#include <sstream>
#include <string>
#include <vector>
bool LexerLogWriter(std::string LogLine, std::ofstream& LexerLogFile);
std::vector<std::string> lexer(std::string ProgLine,
                               std::ofstream& LexerLogFile);