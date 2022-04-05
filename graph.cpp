#include "graph.hpp"

#include <random>

Graph::Graph(int _n) {
    n = _n;
    neighbours.resize(n);
}

Graph::Graph(int _n, double p) {
    n = _n;
    neighbours.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && rand_double() < p) {
                neighbours[i].push_back(j);
            }
        }
    }
}

double rand_double() {
    return (double)std::rand() / RAND_MAX;
}