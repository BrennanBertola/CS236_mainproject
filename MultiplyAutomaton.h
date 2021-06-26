#ifndef MAINPROJECT_MULTIPLYAUTOMATON_H
#define MAINPROJECT_MULTIPLYAUTOMATON_H

#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //MAINPROJECT_MULTIPLYAUTOMATON_H
