#include <cctype>
using namespace std;

#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const string &input) {
    unsignedIndex = 0;
    if (input[index] == '#') {
        inputRead++;
        unsignedIndex++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const string &input) {
    if (input[index] != '\n' && !(unsignedIndex >= input.size())) {
       inputRead++;
       unsignedIndex++;
       index++;
       S1(input);
    }
}