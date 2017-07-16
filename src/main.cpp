#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "glabel.h"

const float LAMBDA = 0.01;

/**
 * Add the nodes to the graph.
 */
void create_nodes(char* graph_csv, std::map<int, Node*>& graph) {
    int src, dst;
    std::ifstream fin(graph_csv);
    while (fin >> src >> dst) {
        if (graph.find(src) == graph.end()) {
            graph[src] = new Node();
            graph[src]->fixed = false;
            graph[src]->identifier = src;
        }

        if (graph.find(dst) == graph.end()) {
            graph[dst] = new Node();
            graph[dst]->fixed = false;
            graph[dst]->identifier = dst;
        }

        graph[src]->neighbors.insert(graph[dst]);
        graph[dst]->neighbors.insert(graph[src]);
    }
}

/**
 * Initialize the probabilities using the labels for deterministic nodes and using the
 * prior for unlabelled nodes.
 */
void init_probabilities(char* label_csv, std::map<int, Node*>& graph) {
    int node;
    std::string label;
    std::ifstream fin(label_csv);
    std::map<std::string, float> priors;
    while (fin >> node >> label) {
        priors[label] += 1.0;
        graph[node]->fixed = true;
        graph[node]->probabilities[label] = 1.0;
    }
    normalize(priors);

    for (auto const &pair : graph) {
        for (auto const &item : priors)
            if (pair.second->probabilities.find(item.first) == pair.second->probabilities.end())
                pair.second->probabilities[item.first] = LAMBDA / priors.size();
        multiply_left(pair.second->probabilities, priors);
        pair.second->standardize();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: ./graph-labeller graph.csv label.csv" << std::endl;
    }

    std::map<int, Node*> graph;

    create_nodes(argv[1], graph);
    init_probabilities(argv[2], graph);

    for (int i = 0; i < 100; i++)
        propagate(graph);
    
    print(graph);
    return 0;
}
