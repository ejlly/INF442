#include "graph.hpp"

#include <iostream>

#include "utils.hpp"

Edge::Edge(int _from, int _to) {
    from = _from;
    to = _to;
    length = 1;
}

Edge::Edge(int _from, int _to, double _length) {
    from = _from;
    to = _to;
    length = _length;
}

Graph::Graph(int _n) {
    n = _n;
    clusters.resize(n, -1);
    neighbours.resize(n);
}

Graph::Graph(int _n, double p) {
    n = _n;
    clusters.resize(n, -1);
    neighbours.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && rand_double() < p) {
                neighbours[i].push_back(Edge(i, j));
            }
        }
    }
}

void Graph::print() {
    std::cout << "Graph with " << n << " nodes\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << "in cluster" << clusters[i] << " has neighbours: ";
        for (Edge e : neighbours[i]) std::cout << e.to << ", ";
        std::cout << std::endl;
    }
}