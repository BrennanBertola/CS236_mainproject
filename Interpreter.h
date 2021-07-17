#ifndef MAINPROJECT_INTERPRETER_H
#define MAINPROJECT_INTERPRETER_H

#include <vector>

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram* datalog;
    Database* database = new Database();

    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;

    Header CreatHeader(Predicate* scheme);
    Tuple CreatTuple(Predicate* fact);
public:
    Interpreter () {};
    ~Interpreter() {delete database;}
    Interpreter (DatalogProgram* datalog);

    void Run();

};


#endif //MAINPROJECT_INTERPRETER_H
