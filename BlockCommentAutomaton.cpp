#include <cctype>
using namespace std;

#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const string &input) {
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

void BlockCommentAutomaton::S1(const string &input) {
    if (unsignedIndex >= input.size()) {
        wasEOFReached = true;
    }
    else if (input[index] == '|') {
        inputRead++;
        unsignedIndex++;
        index++;
        S2(input);
    }
    else {
        S4(input);
    }

}

void BlockCommentAutomaton::S2(const string &input) {
    if (unsignedIndex >= input.size()) {
        wasEOFReached = true;
    }
    else if (input[index] == '|') {
        inputRead++;
        unsignedIndex++;
        index++;
        S3(input);
    }
    else if (isprint(input[index]) || input[index] == '\n') {
        if (input[index] == '\n') {
            newLines++;
        }
        inputRead++;
        unsignedIndex++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S3(const string &input) {
    if (unsignedIndex >= input.size()) {
        wasEOFReached = true;
    }
    else if (input[index] == '#') {
        inputRead++;
    }
    else {
        S2(input);
    }
}

void BlockCommentAutomaton::S4(const string &input) {
    if (input[index] != '\n' && !(unsignedIndex >= input.size())) {
        inputRead++;
        unsignedIndex++;
        index++;
        S4(input);
    }
}