#ifndef MAINPROJECT_INTERPRETER_H
#define MAINPROJECT_INTERPRETER_H

#include <vector>
#include <sstream>

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

    void ProcessQueries();
public:
    Interpreter () {};
    ~Interpreter() {delete database;}
    Interpreter (DatalogProgram* datalog);

    void Run();

    std::string toString() const {
        std::ostringstream out;
        out << *database;
        return out.str();
    }

    friend std::ostream& operator<< (std::ostream& os, const Interpreter& interpreter) {
        os << interpreter.toString();
        return os;
    }
};


#endif //MAINPROJECT_INTERPRETER_H
