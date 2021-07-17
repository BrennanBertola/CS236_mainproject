#include "Interpreter.h"
using namespace std;

Interpreter::Interpreter(DatalogProgram *datalog) {
    this->datalog = datalog;

    for (unsigned int i = 0; i < datalog->GetSchemesSize(); ++i) {
        schemes.push_back(datalog->GetSchemeAt(i));
    }

    for (unsigned int i = 0; i < datalog->GetFactsSize(); ++i) {
        facts.push_back(datalog->GetFactAt(i));
    }

    for (unsigned int i = 0; i < datalog->GetQueriesSize(); ++i) {
        queries.push_back(datalog->GetQueryAt(i));
    }

    for (unsigned int i = 0; i < datalog->GetRulesSize(); ++i) {
        rules.push_back(datalog->GetRuleAt(i));
    }
}

Header Interpreter::CreatHeader(Predicate *scheme) {
    Header currHeader;
    for (unsigned int i = 0; i < scheme->ParameterSize(); ++i) {
        currHeader.AddAttribute(scheme->GetParameterAt(i).GetDescription());
    }
    return currHeader;
}

Tuple Interpreter::CreatTuple(Predicate *fact) {
    Tuple currTuple;
    for (unsigned int i = 0; i < fact->ParameterSize(); ++i) {
        currTuple.AddValue(fact->GetParameterAt(i).GetDescription());
    }
    return currTuple;
}

void Interpreter::Run() {
    for (unsigned int i = 0; i < schemes.size(); ++i) {
        Header tmp = CreatHeader(schemes.at(i));
        database->AddRelation(schemes.at(i)->GetInitial(), tmp);
    }

    for (unsigned int i = 0; i < facts.size(); ++i) {
        Tuple tmp = CreatTuple(facts.at(i));
        database->AddTuple(facts.at(i)->GetInitial(), tmp);
    }
}