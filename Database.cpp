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

void Database::ProcessQuery(Predicate *query) {
    Relation currRelation = *relations.at(query->GetInitial());
    map<string, int> trackedValues;
    vector<string> valueOrder;
    vector<int> indexOrder;
    bool wasVariable = false;

    //Process selection on currRelation
    for (unsigned int i = 0; i < query->ParameterSize(); ++i) {
        Parameter currParameter = query->GetParameterAt(i);
        if (currParameter.IsConstant()) {
            currRelation.Select1(i,currParameter.GetDescription());
        }
        else if (!currParameter.IsConstant()) {
            wasVariable = true;
            string currValue = currParameter.GetDescription();
            map<string, int>::iterator it = trackedValues.find(currValue);

            if (it == trackedValues.end()) { //checks if currValue is in the map
                trackedValues.insert({currValue, i});
                valueOrder.push_back(currValue);
                indexOrder.push_back(i);
            }
            else {
                currRelation.Select2(it->second, i);
            }
        }
    }

    //Process Project on currRelation
    currRelation.Project(indexOrder);

    //Process Rename on currRelation
    if (wasVariable) {
        currRelation.Rename(valueOrder);
    }
    //outputs currRelation & if successful.
    cout << *query << "? ";
    if (!currRelation.IsTuplesEmpty()) {
        cout << "Yes(" << currRelation.GetTuplesSize() << ")" << endl;
        if (wasVariable) {
            cout << currRelation;
        }
    }
    else {
        cout << "No" << endl;
    }

}