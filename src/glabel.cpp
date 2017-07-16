#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "glabel.h"
#include <iostream>

using namespace std;

const float GAMMA = 0.55;

void Node::standardize() {
    normalize(this->probabilities);
}

void print(std::map<int, Node*>& graph) {
    for (auto const &node : graph) {
        for (auto const &pair : node.second->probabilities) {
            std::cout << node.first << " " << pair.first << " " << pair.second << std::endl;
        }
    }
}

void propagate(std::map<int, Node*>& graph) {
    std::vector<std::pair<int,Node*>> nodes(graph.begin(), graph.end());
    std::random_shuffle(nodes.begin(), nodes.end());
    for (auto const &pair : nodes)
        for (auto const &neighbor : pair.second->neighbors) {
            if (!neighbor->fixed) {
                merge_left(neighbor->probabilities, pair.second->probabilities);
                neighbor->standardize();
            }
        }
}

void normalize(std::map<std::string, float>& distribution) {
    float total = 0.0;
    for (auto const &pair : distribution)
        total += pair.second;
    for (auto const &pair : distribution)
        distribution[pair.first] = pair.second / total;
}

void merge_left(std::map<std::string, float>& dst, std::map<std::string, float>& src) {
    for (auto const &pair : dst) {
        if (src.find(pair.first) != src.end())
            dst[pair.first] *= GAMMA * src[pair.first] + (1.0 - GAMMA) * (1.0 - src[pair.first]);
    }
}

void multiply_left(std::map<std::string, float>& dst, std::map<std::string, float>& src) {
    for (auto const &pair : dst) {
        if (src.find(pair.first) != src.end())
            dst[pair.first] *= src[pair.first];
    }
}
