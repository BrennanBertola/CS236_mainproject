#ifndef MAINPROJECT_PERIODAUTOMATA_H
#define MAINPROJECT_PERIODAUTOMATA_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //MAINPROJECT_PERIODAUTOMATA_H
