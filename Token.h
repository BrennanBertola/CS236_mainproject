#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,
    COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,FACTS,
    RULES, QUIERIES, ID, STRING, COMMENT, UNDEFINED,
    END_OF_FILE
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);

    // TODO: add other needed methods
};

#endif // TOKEN_H

