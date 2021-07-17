#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Lexer.h"
#include "DatalogProgram.h"
#include "Interpreter.h"


int main(int argc, char** argv) {
    // check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }

    string currLine;
    string fullLine;
    const char spacer = '\n';
    Lexer* lexer = new Lexer();


    while (!input.eof()) {
        getline(input, currLine);
        fullLine.append(currLine);
        fullLine.push_back(spacer);
    }

    lexer->Run(fullLine);

    DatalogProgram* datalog = new DatalogProgram(lexer);
    try {
        datalog->Run();
    } catch (string e) {
        cout << e;
    }

    Interpreter* interpreter = new Interpreter(datalog);

    interpreter->Run();

    delete lexer;
    delete datalog;
    delete interpreter;

    return 0;
}