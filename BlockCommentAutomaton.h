#ifndef MAINPROJECT_BLOCKCOMMENTAUTOMATON_H
#define MAINPROJECT_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    unsigned int unsignedIndex = 0;

public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};



#endif //MAINPROJECT_BLOCKCOMMENTAUTOMATON_H
