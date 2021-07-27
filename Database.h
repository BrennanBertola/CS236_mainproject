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
    void ProcessQuery(Predicate* query);
    Relation ProcessPredicate(Predicate* predicate);

    bool Union(Relation unionRelation, string name);

    std::string toString() const {
        std::map<std::string, Relation*>::const_iterator it;
        std::ostringstream out;
        for (it = relations.begin(); it != relations.end(); ++it) {
            out << *it->second;
        }
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Database& base) {
        os << base.toString();
        return os;
    }
};


#endif //MAINPROJECT_DATABASE_H
