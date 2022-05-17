#include "dbscan.hpp"

#include <vector>

#include "graph.hpp"

DbscanParameters::DbscanParameters(double max_dist_, int min_points_) : max_dist(max_dist_), min_points(min_points_) {}

void dbscan(Graph& g, const DbscanParameters& parameters) {
    int current_cluster = 0;
    bool visited[g.n];
    std::fill_n(visited, g.n, false);
    for (int node = 0; node < g.n; node++) {
        if (visited[node]) continue;

        visited[node] = true;
        std::vector<int> node_neighbours = g.epsilon_neighbourhood(node, parameters.max_dist);

        if (node_neighbours.size() < parameters.min_points) {
            g.clusters[node] = -1;
            continue;
        }

        g.clusters[node] = current_cluster;

        for (int i = 0; i < node_neighbours.size(); i++) {
            int neighbour = node_neighbours[i];

            if (g.clusters[neighbour] == -1) {
                g.clusters[neighbour] = current_cluster;
            }

            if (visited[neighbour]) {
                continue;
            }

            visited[neighbour] = true;
            std::vector<int> neighbour_neighbours = g.epsilon_neighbourhood(neighbour, parameters.max_dist);

            // Only add neighbour's neighbours if the current neighbour is a core node
            if (neighbour_neighbours.size() >= parameters.min_points) {
                // Concatenate lists
                // Duplicates will be noticed when checking if a node has been visited
                for (int u : neighbour_neighbours) {
                    node_neighbours.push_back(u);
                }
            }
        }

        current_cluster++;
    }
}