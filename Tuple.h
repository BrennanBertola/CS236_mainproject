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

    unsigned int GetSize() const {return values.size();}
    std::string GetValue(unsigned int index) const {return values.at(index);}
    void SetValue(unsigned int index, std::string value) {values.at(index) = value;}
    void PopBack() {values.pop_back();}
};

#endif //MAINPROJECT_TUPLE_H
