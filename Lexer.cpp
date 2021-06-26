#include <cctype>
using namespace std;

#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    while (input.size() > 0) {
        int maxRead = 0;
        int lineNumber = 1;
        Automaton *maxAutomata = automata.at(0);

        while (isspace(input.front())) {
            if (input.front() == '\n') {
                ++lineNumber;
            }
            input.erase(0, 1);
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
    /*add end of file token to all tokens
    */
}
