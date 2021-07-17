#include "Database.h"
using namespace std;

Database::~Database() {
    map<string, Relation*>::iterator it;
    for (it = relations.begin(); it != relations.end(); ++it) {
        delete it->second;
    }
}

void Database::AddRelation(const string name, Header header) {
    Relation* tmp = new Relation(name, header);
    relations.insert({name, tmp});
}

void Database::AddTuple(const string name, Tuple tuple) {
    Relation* tmp = relations.at(name);
    tmp->AddTuple(tuple);
}