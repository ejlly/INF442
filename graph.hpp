#include <vector>

class Graph {
   public:
    std::vector<std::vector<int>> neighbours;
    int n;
    Graph(int n);            // Empty graph
    Graph(int n, double p);  // ER
};