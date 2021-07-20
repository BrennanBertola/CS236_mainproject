#ifndef MAINPROJECT_RELATION_H
#define MAINPROJECT_RELATION_H

#include <set>
#include <iostream>
#include <sstream>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
std::string name;
Header header;
std::set<Tuple> tuples;

public:
    Relation() {};
    Relation(const std::string name, const Header header) {
        this->name = name;
        this->header = header;
    }

    void AddTuple(Tuple tuple) {
        tuples.insert(tuple);
    }
    bool IsTuplesEmpty() {return tuples.empty();}
    unsigned int GetTuplesSize() {return tuples.size();}

    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const Relation& relation) {
        os << relation.toString();
        return os;
    }

    void Select1(unsigned int position, std::string value);
    void Select2(unsigned int position1, unsigned int position2);
    void Project(std::vector<int> positions);
    void Rename(std::vector<std::string> names);
};

#endif //MAINPROJECT_RELATION_H
