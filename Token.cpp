#include <sstream>
using namespace std;

#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

string Token::toString() const {
    ostringstream out;
    string typeString = typeToString();
    out << "(" << typeString << ",\"" << description << "\"," << line << ")\n";
    return out.str();
}

string Token::typeToString() const {
    if (type == TokenType::COMMA) {
        return "COMMA";
    }
    else if (type == TokenType::PERIOD) {
        return "PERIOD";
    }
    else if (type == TokenType::Q_MARK) {
        return "Q_MARK";
    }
    else if (type == TokenType::LEFT_PAREN) {
        return "LEFT_PAREN";
    }
    else if (type == TokenType::RIGHT_PAREN) {
        return "RIGHT_PAREN";
    }
    else if (type == TokenType::COLON) {
        return "COLON";
    }
    else if (type == TokenType::COLON_DASH) {
        return "COLON_DASH";
    }
    else if (type == TokenType::MULTIPLY) {
        return "MULTIPLY";
    }
    else if (type == TokenType::ADD) {
        return "ADD";
    }
    else if (type == TokenType::SCHEMES) {
        return "SCHEMES";
    }
    else if (type == TokenType::FACTS) {
        return "FACTS";
    }
    else if (type == TokenType::RULES) {
        return "RULES";
    }
    else if (type == TokenType::QUERIES) {
        return "QUERIES";
    }
    else if (type == TokenType::ID) {
        return "ID";
    }
    else if (type == TokenType::STRING) {
        return "STRING";
    }
    else if (type == TokenType::COMMENT) {
        return "COMMENT";
    }
    else if (type == TokenType::UNDEFINED) {
        return "UNDEFINED";
    }
    else if (type == TokenType::END_OF_FILE) {
        return "EOF";
    }
    return "ERROR";
}