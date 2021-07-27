#ifndef MAINPROJECT_RULE_H
#define MAINPROJECT_RULE_H

#include <vector>
#include <sstream>
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> predicates;
public:
    Rule() {};

    void SetHead(Predicate predicate) {
        headPredicate = predicate;
    }
    std::string GetName() {return headPredicate.GetInitial();}
    unsigned int GetHeadSize() {return headPredicate.ParameterSize();}
    std::string GetHeadAt(unsigned int index) {
        return headPredicate.GetParameterAt(index).GetDescription();
    }

    void AddPredicate(Predicate input) {
        predicates.push_back(input);
    }

    unsigned int PredicatesSize() {return predicates.size();}
    Predicate* GetPredicate(unsigned int index) {return &predicates.at(index);}

    std::string toString() const {
        std::ostringstream out;
        out << headPredicate << " :- ";
        for (unsigned int i = 0; i < predicates.size(); ++i) {
            out << predicates.at(i);
            if (i + 1 != predicates.size()) {
                out << ',';
            }
            else {
                out << '.';
            }
        }
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Rule& rule) {
        os << rule.toString();
        return os;
    }
};

#endif //MAINPROJECT_RULE_H
