#ifndef MAINPROJECT_TUPLE_H
#define MAINPROJECT_TUPLE_H

#include <vector>

class Tuple {
private:
    std::vector<std::string> values;
public:
    void AddValue(std::string value) {
        values.push_back(value);
    }

    bool operator< (const Tuple & other) const {
        return this->values < other.values;
    }
};

#endif //MAINPROJECT_TUPLE_H
