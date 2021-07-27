#ifndef MAINPROJECT_RELATION_H
#define MAINPROJECT_RELATION_H

#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
std::string name;
Header header;

bool CanJoin (Tuple t1, Tuple t2, map<unsigned int, unsigned int> index);
Tuple CombineTuple (Tuple t1, Tuple t2, map<unsigned int, unsigned int> index);
public:
    std::set<Tuple> tuples;

    Relation() {};
    Relation(const std::string name, const Header header) {
        this->name = name;
        this->header = header;
    }

    bool AddTuple(Tuple tuple) {
        std::pair<std::set<Tuple>::iterator, bool> ret;
        ret = tuples.insert(tuple);
        return ret.second;
    }
    bool IsTuplesEmpty() {return tuples.empty();}
    unsigned int GetTuplesSize() {return tuples.size();}

    unsigned int GetHeaderSize() {return header.GetSize();}
    std::string GetHeaderAt(unsigned int index) {return header.GetAttribute(index);}

    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const Relation& relation) {
        os << relation.toString();
        return os;
    }

    void Select1(unsigned int position, std::string value);
    void Select2(unsigned int position1, unsigned int position2);
    void Project(std::vector<int> positions);
    void Rename(std::vector<std::string> names);
    void Join(Relation joinWith);
};

#endif //MAINPROJECT_RELATION_H
