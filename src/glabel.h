#include <map>
#include <set>
#include <string>

class Node {
public:
    bool fixed;
    int identifier;
    std::set<Node*> neighbors;
    std::map<std::string, float> probabilities;

    void standardize();
};

/**
 * Print a flat space separated values representation of the graph.
 */
void print(std::map<int, Node*>& nodes);

/**
 * Iterate over all nodes and implement a simple varient of message passing.
 */
void propagate(std::map<int, Node*>& nodes);

/**
 * Make the probability distribution add up to one.
 */
void normalize(std::map<std::string, float>& distribution);

/**
 * Merge the `src` distribution into the `dst` distribution.
 */
void merge_left(std::map<std::string, float>& dst, std::map<std::string, float>& src);

/**
 * Multiply the `src` distribution and the `dst` distribution.
 */
void multiply_left(std::map<std::string, float>& dst, std::map<std::string, float>& src);
