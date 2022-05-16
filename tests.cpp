#include <chrono>
#include <ctime>
#include <iostream>

#include "tarjan.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Usage : " << argv[0] << " filename1 filename2 ...\n";
        return 0;
    }

    // Set rand seed for ER-graphs
    std::srand(time(nullptr));

    // Read .edges files
    for (int i(1); i < argc; i++) {
        Graph g(argv[i]);
        // Graph g(i + 3, 0.4);
        // g.print();

        auto start = std::chrono::system_clock::now();

        std::vector<std::vector<int>> results = tarjan(g);

        auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now() - start)
                         .count();

        std::cout << "Connected components of " << argv[i] << "\n";
        display_connected_components(results);
        display_components_summary(results);
        std::cout << "Computed in " << delay << "ms\n";
    }
}
