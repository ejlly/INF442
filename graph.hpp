#include <vector>

class Graph {
   public:
    std::vector<std::vector<int>> neighbours;
    std::vector<int> clusters;  // -1 means no cluster
    int n;
    Graph(int n);            // Empty graph
    Graph(int n, double p);  // ER
    void print();
};