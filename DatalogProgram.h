#ifndef MAINPROJECT_DATALOGPROGRAM_H
#define MAINPROJECT_DATALOGPROGRAM_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

#include "Token.h"
#include "Lexer.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
    void ParseToken(TokenType tokenType);
    void ParseToken(TokenType tokenType, Predicate* predicate);

    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();

    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();

    void ParseHeadPredicate(Rule* rule);
    void ParsePredicate(Predicate* predicate);

    void ParsePredicateList(Rule* rule);
    void ParseParameterList(Predicate* predicate);
    void ParseStringList(Predicate* predicate);
    void ParseIdList(Predicate* predicate);
    void ParseParameter(Predicate* predicate);

    void PopulateDomain();

    std::vector<Token*> tokens;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domains;

    unsigned int index;
public:
    DatalogProgram() {index = 0;};
    DatalogProgram(Lexer* lexer);
    ~DatalogProgram();

    void Run();

    unsigned int GetSchemesSize() {return schemes.size();}
    Predicate* GetSchemeAt(unsigned int index) {return schemes.at(index);}

    unsigned int GetFactsSize() {return facts.size();}
    Predicate* GetFactAt(unsigned int index) {return facts.at(index);}

    unsigned int GetQueriesSize() {return queries.size();}
    Predicate* GetQueryAt(unsigned int index) {return queries.at(index);}

    unsigned int GetRulesSize() {return rules.size();}
    Rule* GetRuleAt(unsigned int index) {return rules.at(index);}

    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, const DatalogProgram& log) {
        os << log.toString();
        return os;
    }
};


#endif //MAINPROJECT_DATALOGPROGRAM_H
