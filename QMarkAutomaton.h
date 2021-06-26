#ifndef MAINPROJECT_QMARKAUTOMATON_H
#define MAINPROJECT_QMARKAUTOMATON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton
{
public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //MAINPROJECT_QMARKAUTOMATON_H
