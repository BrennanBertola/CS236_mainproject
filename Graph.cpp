#include "Graph.h"
using namespace std;

Graph::Graph(std::vector<Rule *> rules) {
    set<int> tmp;
    for (unsigned int i = 0; i < rules.size(); ++i) {
        this->rules.push_back(rules.at(i));
        ruleVertex.insert({i, rules.at(i)});
        reverseGraph.insert({i, tmp});
    }
    for (unsigned int i = 0; i < rules.size(); ++i) {

    }
}

void Graph::Run() {
    BuildGraphs();
    DFSOnReverse();
    ReversePostOrder();
    DFSOnOriginal();
}

void Graph::ReversePostOrder() {
    for (unsigned int i = 0; i < postOrder.size() / 2; ++i) {
        swap(postOrder.at(i), postOrder.at(postOrder.size() - i - 1));
    }
}

bool Graph::CheckDependence(int vertex) {
    set<int>::iterator it = selfDependent.find(vertex);
    if (it != selfDependent.end()) {
        return true;
    }
    return false;
}

void Graph::BuildGraphs() {
    cout << "Dependency Graph" << endl;

    //build both the normal graph and its reverse
    for (unsigned int i = 0; i < rules.size(); ++i) {
        set<int>tmp;
        ostringstream out;
        out << "R" << i << ":";
        for (unsigned int j = 0; j < rules.at(i)->PredicatesSize(); ++j) {
            string name = rules.at(i)->GetPredicate(j)->GetInitial();
            for (unsigned int k = 0; k < rules.size(); ++k) {
                if (name == rules.at(k)->GetName() && i == k) {
                    tmp.insert(k);
                    reverseGraph.find(k)->second.insert(i);
                    selfDependent.insert(i);
                }
                else if (name == rules.at(k)->GetName()) {
                    tmp.insert(k);
                    reverseGraph.find(k)->second.insert(i);
                }
            }
        }

        set<int>::iterator it = tmp.begin();
        while (it != tmp.end()) {
            out << "R" << *it;
            ++it;
            if (it != tmp.end()) {
                out << ",";
            }
        }
        cout << out.str() << endl;
        graph.insert({i, tmp});
    }
}

void Graph::DFSOnReverse() {
    DFSOnReverse(0);

    //checks for next vertex that hasn't been visited
    int nextVertex;
    do {
        nextVertex = -1;
        for (unsigned int i = 0; i < rules.size(); ++i) {
            if (!wasVisited.find(i)->second) {
                nextVertex = i;
                break;
            }
        }
        if (nextVertex != -1) {
            DFSOnReverse(nextVertex);
        }
    } while (nextVertex != -1);

    wasVisited.clear();
}

void Graph::DFSOnReverse(int vertex) {
    bool canVisit = false;
    int nextVertex = 9999;
    wasVisited.insert({vertex, true});

    set<int>::iterator it = reverseGraph.find(vertex)->second.begin();
    while (it != reverseGraph.find(vertex)->second.end()) {
        if (!wasVisited.find(*it)->second && *it < nextVertex) {
            nextVertex = *it;
            canVisit = true;
        }
        ++it;
    }

    if (canVisit) {
        DFSOnReverse(nextVertex);
        DFSOnReverse(vertex);
    }
    postOrder.push_back(vertex);

    return;
}

void Graph::DFSOnOriginal() {
    DFSOnOriginal(postOrder.at(0));

    int nextVertex;
    do {
        nextVertex = -1;
        if (!scc.empty()) {
            sccs.push_back(scc);
        }

        for (unsigned int i = 0; i < postOrder.size(); ++i) {
            if (!wasVisited.find(postOrder.at(i))->second) {
                nextVertex = postOrder.at(i);
                break;
            }
        }

        if (nextVertex != -1) {
            scc.clear();
            DFSOnOriginal(nextVertex);
        }

    } while (nextVertex != -1);

    wasVisited.clear();
}

void Graph::DFSOnOriginal(int vertex) {
    bool canVisit = false;
    int nextVertex = 9999;
    scc.insert(vertex);
    wasVisited.insert({vertex, true});

    set<int>::iterator it = graph.find(vertex)->second.begin();
    while (it != graph.find(vertex)->second.end()) {
        if (!wasVisited.find(*it)->second && *it < nextVertex) {
            nextVertex = *it;
            canVisit = true;
        }
        ++it;
    }

    if (canVisit) {
        DFSOnOriginal(nextVertex);
        DFSOnOriginal(vertex);
    }
    scc.insert(vertex);

    return;
}