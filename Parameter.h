#ifndef MAINPROJECT_PARAMETER_H
#define MAINPROJECT_PARAMETER_H

#include <sstream>
#include "Token.h"

class Parameter {
private:
    TokenType type;
    bool isConstant;
    std::string description;
public:
    Parameter(TokenType type, std::string description) {
        this->type = type;
        this->description = description;

        if(type == TokenType::STRING) {
            isConstant = true;
        }
        else {
            isConstant = false;
        }
    }

    std::string GetDescription() {return description;}
    bool IsConstant() {return isConstant;}

    std::string toString() const {
        std::ostringstream out;
        out << description;
        return out.str();
    }
    friend std::ostream& operator<< (std::ostream& os, const Parameter& parameter) {
        os << parameter.toString();
        return os;
    }

};


#endif //MAINPROJECT_PARAMETER_H
