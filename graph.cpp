#include "graph.hpp"

#include <map>

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

Graph::Graph(){};

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

Graph::Graph(std::string path, bool directed) {
    std::ifstream file(path);

    std::map<std::string, int> table;

    int last_int_seen = 0;

    std::string from, to;

    while (!file.eof()) {
        file >> from >> to;

        if (table.count(from) == 0) {
            table[from] = last_int_seen++;
            neighbours.push_back(std::vector<Edge>());
        }

        if (table.count(to) == 0) {
            table[to] = last_int_seen++;
            neighbours.push_back(std::vector<Edge>());
        }

        neighbours[table[from]].push_back(Edge(table[from], table[to]));
		if(!directed)
			neighbours[table[to]].push_back(Edge(table[to], table[from]));
    }

    n = last_int_seen;
    clusters.resize(n, -1);
}

void Graph::print() {
    std::cout << "Graph with " << n << " nodes\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << "in cluster" << clusters[i] << " has neighbours: ";
        for (Edge e : neighbours[i]) std::cout << e.to << ", ";
        std::cout << std::endl;
    }
}

std::vector<int> Graph::epsilonNeighbourhood(int node, double maxDist) {
    std::vector<int> result;
    result.push_back(node);
    for (Edge e : neighbours[node]) {
        if (e.length < maxDist) {
            result.push_back(e.to);
        }
    }
    return result;
}
