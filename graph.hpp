#pragma once

#include <vector>

class Edge {
   public:
    int from;
    int to;
    double length;
    Edge(int from, int to, double length);
    Edge(int from, int to);
};

class Graph {
   public:
    std::vector<std::vector<Edge>> neighbours;
    std::vector<int> clusters;  // -1 means no cluster
    int n;
    Graph(int n);            // Empty graph
    Graph(int n, double p);  // ER
    void print();
    std::vector<int> epsilonNeighbours(int node, double eps);
};