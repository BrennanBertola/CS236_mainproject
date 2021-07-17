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
    void AddPredicate(Predicate input) {
        predicates.push_back(input);
    }

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
