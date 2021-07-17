using namespace std;

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(Lexer* lexer) {
    index = 0;
    for (unsigned int i = 0; i < lexer->tokens.size(); ++i) {
        this->tokens.push_back(lexer->tokens.at(i));
    }
}

DatalogProgram::~DatalogProgram() {
    while(!schemes.empty()) {
        delete schemes.back();
        schemes.pop_back();
    }
    while(!facts.empty()) {
        delete facts.back();
        facts.pop_back();
    }
    while(!queries.empty()) {
        delete queries.back();
        queries.pop_back();
    }
    while(!rules.empty()) {
        delete rules.back();
        rules.pop_back();
    }
}

void DatalogProgram::Run() {
    ParseToken(TokenType::SCHEMES);
    ParseToken(TokenType::COLON);
    ParseScheme();
    ParseSchemeList();

    ParseToken(TokenType::FACTS);
    ParseToken(TokenType::COLON);
    ParseFactList();

    ParseToken(TokenType::RULES);
    ParseToken(TokenType::COLON);
    ParseRuleList();

    ParseToken(TokenType::QUERIES);
    ParseToken(TokenType::COLON);
    ParseQuery();
    ParseQueryList();
    ParseToken(TokenType::END_OF_FILE);

    PopulateDomain();
}

void DatalogProgram::ParseToken(TokenType tokenType) {
    if (tokenType == tokens.at(index)->GetTokenType()) {
        ++index;
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ++index;
        ParseToken(tokenType);
    }
    else {
        throw string ("Failure!\n  " + tokens.at(index)->toString());
    }
}

void DatalogProgram::ParseToken(TokenType tokenType, Predicate* predicate) {
    if (tokenType == tokens.at(index)->GetTokenType()) {
        predicate->AddToParameter(tokens.at(index)->GetTokenType(),
                                 tokens.at(index)->GetDescription());
        ++index;
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ++index;
        ParseToken(tokenType, predicate);
    }
    else {
        throw string ("Failure!\n  " + tokens.at(index)->toString());
    }
}

//==================================================================================

void DatalogProgram::ParseSchemeList() {
    if (tokens.at(index)->GetTokenType() == TokenType::ID) {
        ParseScheme();
        ParseSchemeList();
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParseSchemeList();
    }
}

void DatalogProgram::ParseScheme() {
    ParseToken(TokenType::ID);
    Predicate* curr = new Predicate(tokens.at(index - 1)->GetDescription());
    ParseToken(TokenType::LEFT_PAREN);
    ParseToken(TokenType::ID, curr);
    ParseIdList(curr);
    ParseToken(TokenType::RIGHT_PAREN);
    schemes.push_back(curr);
}

void DatalogProgram::ParseFactList() {
    if (tokens.at(index)->GetTokenType() == TokenType::ID) {
        ParseFact();
        ParseFactList();
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParseFactList();
    }
}

void DatalogProgram::ParseFact() {
    ParseToken(TokenType::ID);
    Predicate* curr = new Predicate(tokens.at(index - 1)->GetDescription());
    ParseToken(TokenType::LEFT_PAREN);
    ParseToken(TokenType::STRING, curr);
    ParseStringList(curr);
    ParseToken(TokenType::RIGHT_PAREN);
    ParseToken(TokenType::PERIOD);
    facts.push_back(curr);
}

void DatalogProgram::ParseRuleList() {
    if (tokens.at(index)->GetTokenType() == TokenType::ID) {
        ParseRule();
        ParseRuleList();
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParseRuleList();
    }
}

void DatalogProgram::ParseRule() {
    Rule* curr = new Rule();
    ParseHeadPredicate(curr);
    ParseToken(TokenType::COLON_DASH);

    Predicate* currPred = new Predicate(tokens.at(index)->GetDescription());
    ParsePredicate(currPred);
    curr->AddPredicate(*currPred);
    delete currPred;

    ParsePredicateList(curr);
    ParseToken(TokenType::PERIOD);

    rules.push_back(curr);
}

void DatalogProgram::ParseQueryList() {
    if (tokens.at(index)->GetTokenType() == TokenType::ID) {
        ParseQuery();
        ParseQueryList();
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParseQueryList();
    }
}

void DatalogProgram::ParseQuery() {
    if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParseQuery();
    }
    Predicate* curr = new Predicate(tokens.at(index)->GetDescription());
    ParsePredicate(curr);
    ParseToken(TokenType::Q_MARK);
    queries.push_back(curr);
}

//==================================================================================

void DatalogProgram::ParseHeadPredicate(Rule* rule) {
    ParseToken(TokenType::ID);
    Predicate* currPred = new Predicate(tokens.at(index - 1)->GetDescription());
    ParseToken(TokenType::LEFT_PAREN);
    ParseToken(TokenType::ID, currPred);
    ParseIdList(currPred);
    ParseToken(TokenType::RIGHT_PAREN);
    rule->SetHead(*currPred);
    delete currPred;
}

void DatalogProgram::ParsePredicate(Predicate* predicate) {
    ParseToken(TokenType::ID);
    ParseToken(TokenType::LEFT_PAREN);
    ParseParameter(predicate);
    ParseParameterList(predicate);
    ParseToken(TokenType::RIGHT_PAREN);
}

void DatalogProgram::ParsePredicateList(Rule* rule) {
    if (tokens.at(index)->GetTokenType() == TokenType::COMMA) {
        ParseToken(TokenType::COMMA);

        Predicate* curr = new Predicate(tokens.at(index)->GetDescription());
        ParsePredicate(curr);
        rule->AddPredicate(*curr);
        delete curr;

        ParsePredicateList(rule);
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::COMMENT) {
        ParseToken(TokenType::COMMENT);
        ParsePredicateList(rule);
    }
}

//==================================================================================

void DatalogProgram::ParseParameter(Predicate* predicate) {
    if (tokens.at(index)->GetTokenType() == TokenType::STRING) {
        ParseToken(TokenType::STRING, predicate);
    }
    else if (tokens.at(index)->GetTokenType() == TokenType::ID) {
        ParseToken(TokenType::ID, predicate);
    }
    else {
        throw string ("Failure!\n  " + tokens.at(index)->toString());
    }
}

void DatalogProgram::ParseParameterList(Predicate* predicate) {
    if (tokens.at(index)->GetTokenType() == TokenType::COMMA) {
        ParseToken(TokenType::COMMA);
        ParseParameter(predicate);
        ParseParameterList(predicate);
    }
}

void DatalogProgram::ParseIdList(Predicate* predicate) {
    if (tokens.at(index)->GetTokenType() == TokenType::COMMA) {
        ParseToken(TokenType::COMMA);
        ParseToken(TokenType::ID, predicate);
        ParseIdList(predicate);
    }
}

void DatalogProgram::ParseStringList(Predicate* predicate) {
    if (tokens.at(index)->GetTokenType() == TokenType::COMMA) {
        ParseToken(TokenType::COMMA);
        ParseToken(TokenType::STRING, predicate);
        ParseStringList(predicate);
    }
}

//==================================================================================

void DatalogProgram::PopulateDomain() {
    for (unsigned int i = 0; i < facts.size(); ++i) {
        Predicate curr = *facts.at(i);
        for (unsigned int j = 0; j < curr.ParameterSize(); ++j) {
            string input = curr.GetParameterAt(j).GetDescription();
            domains.insert(input);
        }
    }
}

string DatalogProgram::toString() const {
    ostringstream out;

    out << "Success!\nSchemes(" << schemes.size() << "):" << endl;
    for (unsigned int i = 0; i < schemes.size(); ++i) {
        out << "  " << *schemes.at(i) << endl;
    }

    out << "Facts(" << facts.size() << "):" << endl;
    for (unsigned int i = 0; i < facts.size(); ++i) {
        out << "  " << *facts.at(i) << '.' << endl;
    }

    out << "Rules(" << rules.size() << "):" << endl;
    for (unsigned int i = 0; i < rules.size(); ++i) {
        out << "  " << *rules.at(i) << endl;
    }

    out << "Queries(" << queries.size() << "):" << endl;
    for (unsigned int i = 0; i < queries.size(); ++i) {
        out << "  " << *queries.at(i) << '?' << endl;
    }

    out << "Domain(" << domains.size() << "):" << endl;
    for (set<string>::iterator it = domains.begin(); it != domains.end(); ++it) {
        out << "  " << *it << endl;
    }

    return out.str();
}