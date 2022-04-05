#include <iostream>

#include "dbscan.hpp"
#include "graph.hpp"

int main() {
    std::cout << "Hello world" << std::endl;
    Graph g(3);
    g.print();
    Graph g2(5, 0.5);
    g2.print();
    Graph g3(5, 0.1);
    g3.print();
}