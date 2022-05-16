#include "experiments.hpp"

#include <chrono>

#include "dbscan.hpp"
#include "graph.hpp"
#include "tarjan.hpp"
#include "utils.hpp"

void do_experiment_dbscan_components_size(std::string& path) {
    Graph g(path, false);

    std::cout << "Connected components of " << path << "\n";

    for (int j = 1; j < 5000; j *= 2) {
        auto results = g.get_components();

        std::cout << "Connected components of " << path << " with M = " << j << "\n";
        for (auto& c : results) std::cout << c.size() << " ";
        std::cout << "\n";
    }
}

void do_experiment_speed(std::string& path, bool directed) {
    Graph g(path, directed);

    auto start = std::chrono::system_clock::now();

    std::vector<std::vector<int>> results = tarjan(g);

    auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now() - start)
                     .count();
    std::cout << "Computed in " << delay << "ms\n";
}