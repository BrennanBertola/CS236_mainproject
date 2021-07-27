#include <map>
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
    vector<string>newHeader;

    for (unsigned int i = 0; i < positions.size(); ++i) {
        string tmp = header.GetAttribute(positions.at(i));
        newHeader.push_back(tmp);
    }
    header.SetHeader(newHeader);

    //creates new tuples with correctly swapped rows;
    set<Tuple>::iterator it = tuples.begin();
    vector<Tuple> newTuples;
    while (it != tuples.end()) {
        Tuple tmpTuple = *it;
        vector<string>newTuple;

        for (unsigned int i = 0; i < positions.size(); ++i) {
            string tmp = tmpTuple.GetValue(positions.at(i));
            newTuple.push_back(tmp);
        }
        tmpTuple.SetTuple(newTuple);
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

void Relation::Join(Relation joinWith) {
    map<unsigned int, unsigned int> matchingIndex;
    for (unsigned int i = 0; i < header.GetSize(); ++i) {
        for (unsigned int j = 0; j < joinWith.GetHeaderSize(); ++j) {
            if (header.GetAttribute(i) == joinWith.GetHeaderAt(j)) {
                matchingIndex.insert({j, i});
            }
        }
    }

    map<unsigned int, unsigned int>::iterator it;
    for (unsigned int j = 0; j < joinWith.GetHeaderSize(); ++j) {
        it = matchingIndex.find(j);
        if (it == matchingIndex.end()) {
            header.AddAttribute(joinWith.GetHeaderAt(j));
        }
    }

    set<Tuple>::iterator tuple1 = tuples.begin();
    vector<Tuple> newTuples;
    while (tuple1 != tuples.end()) {
        set<Tuple>::iterator tuple2 = joinWith.tuples.begin();
        while (tuple2 != joinWith.tuples.end()) {
            if (CanJoin(*tuple1, *tuple2, matchingIndex)) {
                newTuples.push_back(CombineTuple(*tuple1, *tuple2, matchingIndex));
            }
            ++tuple2;
        }
        ++tuple1;
    }

    tuples.clear();
    for (unsigned int i = 0; i < newTuples.size(); ++i) {
        tuples.insert(newTuples.at(i));
    }
}

bool Relation::CanJoin(Tuple t1, Tuple t2, map<unsigned int, unsigned int> index) {
    map<unsigned int, unsigned int>::iterator it = index.begin();
    while (it != index.end()) {
        if (t1.GetValue(it->second) != t2.GetValue(it->first)) {
            return false;
        }
        ++it;
    }
    return true;
}

Tuple Relation::CombineTuple(Tuple t1, Tuple t2, map<unsigned int, unsigned int> index) {
    Tuple tmpTuple = t1;
    map<unsigned int, unsigned int>::iterator it;
    for (unsigned int j = 0; j < t2.GetSize(); ++j) {
        it = index.find(j);
        if (it == index.end()) {
            tmpTuple.PushBack(t2.GetValue(j));
        }
    }

    return tmpTuple;
}