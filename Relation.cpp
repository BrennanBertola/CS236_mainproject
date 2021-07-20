#include "Relation.h"
using namespace std;

string Relation::toString() const {
    set<Tuple>::const_iterator it;
    ostringstream out;

    for (it = tuples.begin(); it != tuples.end(); ++it) {
        out << "  ";
        for (unsigned i = 0; i < header.GetSize(); ++i) {
            out << header.GetAttribute(i) << "=";
            out << it->GetValue(i);
            if (i + 1 != header.GetSize()) {
                out << ", ";
            }
        }
        out << endl;
    }
    return out.str();
}

void Relation::Select1(unsigned int position, std::string value) {
    set<Tuple>::iterator it;
    for (it = tuples.begin(); it != tuples.end();) {
        if (it->GetValue(position) != value) {
           tuples.erase(it++);
        }
        else {
            ++it;
        }
    }

}

void Relation::Select2(unsigned int position1, unsigned int position2) {
    set<Tuple>::iterator it;
    for (it = tuples.begin(); it != tuples.end();) {
        if (it->GetValue(position1) != it->GetValue(position2)) {
            tuples.erase(it++);
        }
        else {
            ++it;
        }
    }
}

void Relation::Project(vector<int> positions) {
    for (unsigned int i = 0; i < positions.size(); ++i) {
        string tmp = header.GetAttribute(i);
        header.SetAttribute(i, header.GetAttribute(positions.at(i)));
        header.SetAttribute(positions.at(i), tmp);
    }
    for (unsigned int i = 0; i < header.GetSize() - positions.size(); ++i) {
        header.PopBack();
    }

    //creates new tuples with correctly swapped rows;
    set<Tuple>::iterator it = tuples.begin();
    vector<Tuple> newTuples;
    while (it != tuples.end()) {
        Tuple tmpTuple = *it;

        for (unsigned int i = 0; i < positions.size(); ++i) {
            string tmp = tmpTuple.GetValue(i);
            tmpTuple.SetValue(i, tmpTuple.GetValue(positions.at(i)));
            tmpTuple.SetValue(positions.at(i), tmp);
        }
        for (unsigned int i = 0; i < tmpTuple.GetSize() - positions.size(); ++i) {
            tmpTuple.PopBack();
        }

        newTuples.push_back(tmpTuple);
        ++it;
    }

    //clears old set then repopulates with new tuples
    tuples.clear();
    for (unsigned int i = 0; i < newTuples.size(); ++i) {
        tuples.insert(newTuples.at(i));
    }
}

void Relation::Rename(std::vector<std::string> names) {
    for (unsigned int i = 0; i < header.GetSize(); ++i) {
        header.SetAttribute(i, names.at(i));
    }
}