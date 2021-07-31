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

    this->graph = Graph(rules);
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
    graph.Run();

    cout << endl << "Rule Evaluation" << endl;
    for (unsigned int i = 0; i < graph.sccs.size(); ++i) {
        bool wasInsert;
        bool runOnce = RunOnce(graph.sccs.at(i), i);
        rulesPassThrough = 0;

        cout << "SCC: " << PrintSCC(graph.sccs.at(i)) << endl;

        do {
            set<int>::iterator it = graph.sccs.at(i).begin();
            wasInsert = false;

            while (it != graph.sccs.at(i).end()) {
                cout << *rules.at(*it) << endl;
                if (ProcessRule(graph.RuleAtVertex(*it)) == true) {
                    wasInsert = true;
                }
                ++it;
            }

            ++rulesPassThrough;
            if (runOnce || !wasInsert) {
                cout << rulesPassThrough << " passes: "
                     << PrintSCC(graph.sccs.at(i)) << endl;
                break;
            }

        } while (wasInsert == true);
    }

    cout << endl;
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

string Interpreter::PrintSCC(std::set<int>& scc) const {
    ostringstream out;
    set<int>::iterator it = scc.begin();
    while (it != scc.end()) {
        out << 'R' << *it;
        ++it;
        if (it != scc.end()) {
            out << ',';
        }
    }
    return out.str();
}

bool Interpreter::RunOnce(set<int> scc, int vertex) {
    set<int>::iterator it = scc.begin();
    if (scc.size() != 1) {
        return false;
    }
    else if (!graph.CheckDependence(*it)) {
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

    ProcessRules();
    ProcessQueries();
}