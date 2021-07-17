#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();
    std::vector<Token*> tokens;

    void Run(std::string& input);
    unsigned int GetTokensSize() {return tokens.size();}
    Token GetTokenAt(int index) {return *tokens.at(index);}
    
    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const Lexer& lexer) {
        os << lexer.toString();
        return os;
    }

};

#endif // LEXER_H

