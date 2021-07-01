#ifndef MAINPROJECT_LINECOMMENTAUTOMATON_H
#define MAINPROJECT_LINECOMMENTAUTOMATON_H


#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    unsigned int unsignedIndex = 0;

public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};



#endif //MAINPROJECT_LINECOMMENTAUTOMATON_H
