#include <cctype>
#include <sstream>
using namespace std;

#include "Lexer.h"
#include "CommaAutomaton.h"
#include "QMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    while(!automata.empty()) {
        delete automata.back();
        automata.pop_back();
    }
    while(!tokens.empty()) {
        delete tokens.back();
        tokens.pop_back();
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton);
    automata.push_back(new QMarkAutomaton);
    automata.push_back(new LeftParenAutomaton);
    automata.push_back(new RightParenAutomaton);
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
}

string Lexer::toString() const {
    std::ostringstream out;
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        out << *tokens.at(i);
    }
    out << "Total Tokens = " << tokens.size();
    return out.str();
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton *maxAutomata = automata.at(0);

        while (isspace(input.front())) {
            if (input.front() == '\n') {
                ++lineNumber;
            }
            input.erase(0, 1);
        }
        if (!(input.size() > 0)) {
            continue;
        }

        for (unsigned int i = 0; i < automata.size(); ++i) {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomata = automata.at(i);
            }
        }

        if (maxRead > 0) {
            string tmpString = input.substr(0, maxRead);
            Token *currToken = maxAutomata->CreateToken(tmpString, lineNumber);
            tokens.push_back(currToken);
            lineNumber += maxAutomata->NewLinesRead();
        } else {
            maxRead = 1;
            Token *currToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
            tokens.push_back(currToken);
        }

        input.erase(0, maxRead);
    }
    Token *currToken = new Token(TokenType::END_OF_FILE, "", lineNumber);
    tokens.push_back(currToken);
}
