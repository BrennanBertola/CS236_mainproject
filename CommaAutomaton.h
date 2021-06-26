#ifndef MAINPROJECT_COMMAAUTOMATON_H
#define MAINPROJECT_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //MAINPROJECT_COMMAAUTOMATON_H
