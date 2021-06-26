#ifndef MAINPROJECT_ADDAUTOMATON_H
#define MAINPROJECT_ADDAUTOMATON_H

#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //MAINPROJECT_ADDAUTOMATON_H
