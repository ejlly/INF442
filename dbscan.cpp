#include "dbscan.hpp"

#include <vector>

#include "graph.hpp"

DbscanParameters::DbscanParameters(double eps_, int M_) : eps(eps_), M(M_) {}

void naive_dbscan(Graph& g, DbscanParameters parameters) {
    int currentCluster = 0;
    bool visited[g.n];
    std::fill_n(visited, g.n, false);
    for (int node = 0; node < g.n; node++) {
        if (visited[node]) continue;

        visited[node] = true;
        std::vector<int> nodeNeighbours = g.epsilonNeighbours(node, parameters.eps);

        if (nodeNeighbours.size() < parameters.M) {
            g.clusters[node] = -1;
            continue;
        }

        g.clusters[node] = currentCluster;

        for (int i = 0; i < nodeNeighbours.size(); i++) {
            int neighbour = nodeNeighbours[i];
            if (visited[neighbour]) {
                // By default nodes are labeled as noise
                if (g.clusters[neighbour] == -1) {
                    g.clusters[neighbour] = currentCluster;
                }

                continue;
            }

            visited[neighbour] = true;
            std::vector<int> neighbourNeighbours = g.epsilonNeighbours(neighbour, parameters.eps);

            // Concatenate lists
            // Duplicates will be noticed when checking if a node has been visited
            for (int u : neighbourNeighbours) {
                nodeNeighbours.push_back(u);
            }
        }

        currentCluster++;
    }
}

void extendCluster(Graph& g, int node, std::vector<int>& neighbours, int currentCluster, DbscanParameters parameters) {
    g.clusters[node] = currentCluster;

    // pour chaque point P' de PtsVoisins
    //   si P' n'a pas été visité
    //      marquer P' comme visité
    //      PtsVoisins' = epsilonVoisinage(D, P', eps)
    //      si tailleDe(PtsVoisins') >= MinPts
    //         PtsVoisins = PtsVoisins U PtsVoisins'
    //   si P' n'est membre d'aucun cluster
    //      ajouter P' au cluster C
}