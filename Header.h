#ifndef MAINPROJECT_HEADER_H
#define MAINPROJECT_HEADER_H

#include <vector>
#include <iostream>
using namespace std;

class Header {
private:

public:
    void AddAttribute(std::string attribute) {
        attributes.push_back(attribute);
    }

    vector<string> attributes;

    unsigned int GetSize() const {return attributes.size();}
    std::string GetAttribute(unsigned int index) const {return attributes.at(index);}
    void SetAttribute(unsigned int index, std::string input) {attributes.at(index) = input;}
    void PopBack() {attributes.pop_back();}
    void SetHeader(vector<string>attributes) {swap(this->attributes, attributes);}

};

#endif //MAINPROJECT_HEADER_H
