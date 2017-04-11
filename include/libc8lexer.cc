#include "./libc8lexer.hpp"

#include <algorithm>
#include <iostream>
C8Token::C8Token(C8TokenType TypeID, std::string Token, unsigned int Pos_Start,
                 unsigned int Pos_End) {
  this->TypeID = TypeID;
  this->Token = Token;
  this->Pos_Start = Pos_Start;
  this->Pos_End = Pos_End;
}

// return Type name
inline std::string C8Token::Type() { return C8TokenTypeTable[this->TypeID]; }

// return Token string
inline std::string C8Token::TokenStr() { return this->Token; }

inline std::string C8Token::Pos() {
  // if only one character
  if (this->Pos_End == 0) {
    return std::to_string(Pos_Start);
  }
  // multiply characters
  else {
    std::stringstream Pos_Range;
    Pos_Range << Pos_Start;
    Pos_Range << " - ";
    Pos_Range << Pos_End;
    return Pos_Range.str();
  }
}
C8Lexer::C8Lexer(std::string SourceProg) { this->SourceProg = SourceProg; }

// scan source and constructs token lists
bool C8Lexer::Scan() {
  // if non valid source read
  if (this->SourceProg.empty())
    return false;
  else {
    // Read Source Program Char-By-Char
    std::string Temp_Token = "";
    for (auto CharInSource = SourceProg.begin();
         CharInSource != SourceProg.end(); CharInSource++) {
      unsigned int NowPos = CharInSource - SourceProg.begin();
      // if find unvalid characters
      if (std::find(std::begin(AlphaTable), std::end(AlphaTable),
                    *CharInSource) == std::end(AlphaTable))
        return false;
      // Found Comment
      if (*CharInSource == '/' && *(CharInSource + 1) == '/') {
        while (*CharInSource != '\n') CharInSource++;  // skip to next line
        continue;
      }
      // skip spaces,tabs and newline
      if (*CharInSource != ' ' && *CharInSource != '\t' &&
          *CharInSource != '\n') {
        Temp_Token += *CharInSource;
      }

      // If comma found
      if (Temp_Token == ",") {
        C8Token Token(COMMA, Temp_Token, NowPos);
        this->TokenList.push_back(Token);
        Temp_Token = "";
      }
      // If Instruction found
      else if (std::find(std::begin(C8InsTable), std::end(C8InsTable),
                         Temp_Token) != std::end(C8InsTable)) {
        C8Token Token(INS, Temp_Token, NowPos, NowPos + Temp_Token.length());
        this->TokenList.push_back(Token);
        Temp_Token = "";
      }
      // If 8 Register found
      else if (Temp_Token[0] == 'V' &&
               ((Temp_Token[1] >= '0' && Temp_Token[1] <= '9') ||
                (Temp_Token[1] >= 'A' && Temp_Token[1] <= 'F'))) {
        C8Token Token(BIT8REG, Temp_Token, NowPos, NowPos + 1);
        this->TokenList.push_back(Token);
        Temp_Token = "";
      }
      // Address Register found
      else if (Temp_Token == "I") {
        C8Token Token(ADDREG, Temp_Token, NowPos);
        this->TokenList.push_back(Token);
        Temp_Token = "";
      }
      // Timer found
      else if (Temp_Token == "DT" || Temp_Token == "ST") {
        C8Token Token(TIMER, Temp_Token, NowPos, NowPos + 1);
        this->TokenList.push_back(Token);
        Temp_Token = "";
      }
      // Var found
      else if (*(CharInSource + 1) == ' ' || *(CharInSource + 1) == ',' ||
               *(CharInSource + 1) == '\t' || *(CharInSource + 1) == '\n' ||
               CharInSource + 1 == SourceProg.end()) {
        if (!Temp_Token.empty()) {
          C8Token Token(VAR, Temp_Token, NowPos, NowPos + Temp_Token.length());

          this->TokenList.push_back(Token);
          Temp_Token = "";
        }
      }
    }
  }
  return true;
}

// Return TokenList (Waring : Empty list would also returned)
std::vector<C8Token>& C8Lexer::GetList() { return this->TokenList; }

// Generates lexer output string
std::string C8Lexer::Output(std::vector<C8Token> TokenList) {
  std::stringstream LexerOutputStream;
  for (auto Token : TokenList) {
    LexerOutputStream << "[" << Token.Type() << "]    (" << Token.Pos()
                      << ") : " << Token.TokenStr() << std::endl;
  }
  return LexerOutputStream.str();
}

std::string C8Lexer::Output() { return this->Output(this->TokenList); }