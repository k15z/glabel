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

void print(std::map<int, Node*>& nodes);
void propagate(std::map<int, Node*>& nodes);
void normalize(std::map<std::string, float>& distribution);
void merge_left(std::map<std::string, float>& dst, std::map<std::string, float>& src);
void multiply_left(std::map<std::string, float>& dst, std::map<std::string, float>& src);
