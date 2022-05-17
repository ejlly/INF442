#include "graph.hpp"

#include <algorithm>
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

bool Edge::operator<(Edge& o) {
    return length < o.length;
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
        if (!directed)
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

std::vector<int> Graph::epsilon_neighbourhood(int node, double max_dist) {
    std::vector<int> result;
    result.push_back(node);
    for (Edge e : neighbours[node]) {
        if (e.length < max_dist) {
            result.push_back(e.to);
        }
    }
    return result;
}

std::vector<std::vector<int>> Graph::get_components() {
    int max_cluster_id = -1;
    for (int i = 0; i < n; i++) {
        max_cluster_id = std::max(clusters[i], max_cluster_id);
    }

    std::vector<std::vector<int>> result(max_cluster_id + 1);

    for (int i = 0; i < n; i++) {
        if (clusters[i] != -1) {
            result[clusters[i]].push_back(i);
        }
    }

    return result;
}

int Graph::getGoodMinPoints() {
    int sum_of_number_of_neighbours = 0;
    for (int i = 0; i < n; i++) {
        sum_of_number_of_neighbours += neighbours[i].size();
    }
    int avg_number_of_neighbours = std::ceil(sum_of_number_of_neighbours * 1.0 / n);
    int sqrt_n = std::ceil(sqrt(n));

    return std::min(sqrt_n / 2, avg_number_of_neighbours);
}

double Graph::get_good_max_dist(int min_points) {
    double sum_distance_to_M_closest_point = 0;
    int nb_relevant_points = 0;
    for (int i = 0; i < n; i++) {
        if (neighbours[i].size() >= min_points) {
            std::sort(neighbours[i].begin(), neighbours[i].end());
            sum_distance_to_M_closest_point += neighbours[i][(min_points - 1)].length;
            nb_relevant_points++;
        }
    }
    if (nb_relevant_points == 0) return -1;  // All points will be noise with this min_points parameter
    return sum_distance_to_M_closest_point / nb_relevant_points;
}