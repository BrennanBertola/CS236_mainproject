#ifndef MAINPROJECT_GRAPH_H
#define MAINPROJECT_GRAPH_H

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include "Rule.h"

class Graph {
private:
    std::vector<Rule*> rules;
    std::vector<int> postOrder;
    std::set<int> scc;
    std::set<int> selfDependent;
    std::map<int, std::set<int>> graph;
    std::map<int, std::set<int>> reverseGraph;
    std::map<int, bool> wasVisited;
    std::map<int, Rule*>ruleVertex;

    void BuildGraphs();

    void DFSOnReverse();
    void DFSOnReverse(int vertex);

    void DFSOnOriginal();
    void DFSOnOriginal(int vertex);

    void ReversePostOrder();
public:
    std::vector<std::set<int>> sccs;


    Graph() {};
    Graph(std::vector<Rule*> rules);

    void Run();
    Rule* RuleAtVertex(int vertex) {return ruleVertex.find(vertex)->second;}
    bool CheckDependence(int vertex);

};


#endif //MAINPROJECT_GRAPH_H
