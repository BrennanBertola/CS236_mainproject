#include "Interpreter.h"
using namespace std;

Interpreter::Interpreter(DatalogProgram *datalog) {
    this->datalog = datalog;
    rulesPassThrough = 0;

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

void Interpreter::ProcessQueries() {
    cout << "Query Evaluation" << endl;
    for (unsigned int i = 0; i < queries.size(); ++i) {
        database->ProcessQuery(queries.at(i));
    }
}

void Interpreter::ProcessRules() {
    bool wasInsert = false;
    for (unsigned int i = 0; i < rules.size(); ++i) {
        cout << *rules.at(i) << endl;
        if (ProcessRule(rules.at(i)) == true) {
            wasInsert = true;
        }
    }

    ++rulesPassThrough;
    if (wasInsert) {
        ProcessRules();
    }
    else {
        cout << "\nSchemes populated after " << rulesPassThrough;
        cout << " passes through the Rules.\n" << endl;
    }
}

bool Interpreter::ProcessRule(Rule* currRule) {
    vector<Relation> newRelations;
    vector<int> projectOrder;
    for (unsigned int i = 0; i < currRule->PredicatesSize(); ++i) {
        Predicate* tmpPredicate = currRule->GetPredicate(i);
        newRelations.push_back(database->ProcessPredicate(tmpPredicate));
    }

    Relation joinRelation = newRelations.at(0);
    for (unsigned int i = 1; i < newRelations.size(); ++i) {
        joinRelation.Join(newRelations.at(i));
    }

    for (unsigned int i = 0; i < currRule->GetHeadSize(); ++i) {
        for (unsigned int j = 0; j < joinRelation.GetHeaderSize(); ++j) {
            if (joinRelation.GetHeaderAt(j) == currRule->GetHeadAt(i)) {
                projectOrder.push_back(j);
                break;
            }
        }
    }

    joinRelation.Project(projectOrder);
    if (database->Union(joinRelation, currRule->GetName())) {
        return true;
    }
    return false;
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

    cout << "Rule Evaluation" << endl;
    ProcessRules();
    ProcessQueries();
}