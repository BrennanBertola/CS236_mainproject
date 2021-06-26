#ifndef MAINPROJECT_RIGHTPARENAUTOMATON_H
#define MAINPROJECT_RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //MAINPROJECT_RIGHTPARENAUTOMATON_H
