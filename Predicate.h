#ifndef MAINPROJECT_PREDICATE_H
#define MAINPROJECT_PREDICATE_H

#include <vector>
#include <sstream>
#include "Parameter.h"

class Predicate {
private:
    std::vector<Parameter> parameter;
    std::string initialID;
public:


    Predicate() {};
    Predicate(std::string id) {
        initialID = id;
    }

    void AddToParameter(TokenType type, std::string description) {
        Parameter tmp(type, description);
        parameter.push_back(tmp);
    }

    void SetInitial(std::string input) {initialID = input;}
    std::string GetInitial() {return initialID;}

    unsigned int ParameterSize() {return parameter.size();}
    Parameter GetParameterAt(unsigned int index) {return parameter.at(index);}

    std::string toString() const {
        std::ostringstream out;
        out << initialID << '(';
        for (unsigned int i = 0; i < parameter.size(); ++i) {
            out << parameter.at(i);
            if (i + 1 != parameter.size()) {
                out << ',';
            }
        }
        out << ')';
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Predicate& predicate) {
        os << predicate.toString();
        return os;
    }
};

#endif //MAINPROJECT_PREDICATE_H
