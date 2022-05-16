#include "experiments.hpp"

#include "dbscan.hpp"
#include "graph.hpp"
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