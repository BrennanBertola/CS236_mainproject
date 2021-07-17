#ifndef MAINPROJECT_RELATION_H
#define MAINPROJECT_RELATION_H

#include <set>
#include <iostream>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
std::string name;
Header header;
std::set<Tuple> tuples;

public:
    Relation(const std::string name, const Header header) {
        this->name = name;
        this->header = header;
    }

    void AddTuple(Tuple tuple) {
        tuples.insert(tuple);
    }
};


#endif //MAINPROJECT_RELATION_H
