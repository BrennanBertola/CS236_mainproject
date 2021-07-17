#ifndef MAINPROJECT_DATABASE_H
#define MAINPROJECT_DATABASE_H

#include <map>
#include "Relation.h"
#include "Predicate.h"

class Database {
private:
    std::map<std::string, Relation*> relations;

public:
    ~Database();

    void AddRelation(const std::string name, Header header);
    void AddTuple(const std::string name, Tuple tuple);

};


#endif //MAINPROJECT_DATABASE_H
