#ifndef MAINPROJECT_STRINGAUTOMATON_H
#define MAINPROJECT_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    unsigned int unsignedIndex = 0;

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //MAINPROJECT_STRINGAUTOMATON_H
