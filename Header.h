#ifndef MAINPROJECT_HEADER_H
#define MAINPROJECT_HEADER_H

#include <vector>

class Header {
private:
    std::vector<std::string> attributes;
public:
    void AddAttribute(std::string attribute) {
        attributes.push_back(attribute);
    }

};

#endif //MAINPROJECT_HEADER_H
