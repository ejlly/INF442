#include <iostream>

#include "dbscan.hpp"
#include "graph.hpp"

int main() {
    std::cout << "Hello world" << std::endl;
    Graph g(2, 0.5);
    g.print();
    Graph g2(5, 0.5);
    g2.print();
    Graph g3(5, 0.1);
    g3.print();

    naive_dbscan(g, DbscanParameters(1.5, 1));
    for (int c : g.clusters) std::cout << c << " ";
    std::cout << std::endl;
    // naive_dbscan(g2, DbscanParameters(1.5, 0));
    // for (int c : g.clusters) std::cout << c << " ";
    // std::cout << std::endl;
    // naive_dbscan(g3, DbscanParameters(1.5, 0));
    // for (int c : g.clusters) std::cout << c << " ";
    // std::cout << std::endl;
}