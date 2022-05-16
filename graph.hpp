#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
	Graph();
    Graph(int n);            // Empty graph
    Graph(int n, double p);  // ER
	Graph(std::string path);
    void print();
    std::vector<int> epsilonNeighbourhood(int node, double maxDist);
};
