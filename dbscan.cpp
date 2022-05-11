#include "dbscan.hpp"

#include <vector>

#include "graph.hpp"

DbscanParameters::DbscanParameters(double maxDist_, int minPoints_) : maxDist(maxDist_), minPoints(minPoints_) {}

void naive_dbscan(Graph& g, const DbscanParameters& parameters) {
    int currentCluster = 0;
    bool visited[g.n];
    std::fill_n(visited, g.n, false);
    for (int node = 0; node < g.n; node++) {
        if (visited[node]) continue;

        visited[node] = true;
        std::vector<int> nodeNeighbours = g.epsilonNeighbourhood(node, parameters.maxDist);

        if (nodeNeighbours.size() < parameters.minPoints) {
            g.clusters[node] = -1;
            continue;
        }

        g.clusters[node] = currentCluster;

        for (int i = 0; i < nodeNeighbours.size(); i++) {
            int neighbour = nodeNeighbours[i];

            if (g.clusters[neighbour] == -1) {
                g.clusters[neighbour] = currentCluster;
            }
            
            if (visited[neighbour]) {
                continue;
            }

            visited[neighbour] = true;
            std::vector<int> neighbourNeighbours = g.epsilonNeighbourhood(neighbour, parameters.maxDist);

            // Only add neighbour's neighbours if the current neighbour is a core node
            if (neighbourNeighbours.size() >= parameters.minPoints) {
                // Concatenate lists
                // Duplicates will be noticed when checking if a node has been visited
                for (int u : neighbourNeighbours) {
                    nodeNeighbours.push_back(u);
                }
            }
        }

        currentCluster++;
    }
}