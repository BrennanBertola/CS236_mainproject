#include <cctype>
using namespace std;

#include "StringAutomaton.h"

void StringAutomaton::S0(const string &input) {
    unsignedIndex = 0;
    if (input[index] == '\'') {
        inputRead++;
        unsignedIndex++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const string &input) {
    if (unsignedIndex >= input.size()) {
        wasEOFReached = true;
    }
    else if (input[index] == '\'') {
        inputRead++;
        unsignedIndex++;
        index++;
        S2(input);
    }
    else if (isprint(input[index]) || input[index] == '\n') {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        unsignedIndex++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S2(const string &input) {
    if (input[index] == '\'') {
        inputRead++;
        unsignedIndex++;
        index++;
        S1(input);
    }
}