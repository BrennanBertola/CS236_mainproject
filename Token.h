#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,
    COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,FACTS,
    RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED,
    END_OF_FILE
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;
    std::string typeToString() const;

public:
    Token(TokenType type, std::string description, int line);

    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const Token& token) {
        os << token.toString();
        return os;
    }
};

#endif // TOKEN_H

