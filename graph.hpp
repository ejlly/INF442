#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Edge {
   public:
    int from;
    int to;
    double length;
    Edge(int from, int to, double length);
    Edge(int from, int to);
    bool operator<(Edge& o);
};

class Graph {
   public:
    std::vector<std::vector<Edge>> neighbours;
    std::vector<int> clusters;  // -1 means no cluster
    int n;
    Graph();
    Graph(int n);                            // Empty graph
    Graph(int n, double p);                  // ER
    Graph(std::string path, bool directed);  // From a path. Duplicate edges if it is undirected
    void print();
    std::vector<int> epsilon_neighbourhood(int node, double max_dist);
    std::vector<std::vector<int>> get_components();

    // heuristics for the dbscan
    double get_good_max_dist(int min_points);
    int getGoodMinPoints();
};
