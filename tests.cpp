#include <chrono>
#include <ctime>
#include <iostream>

#include "tarjan.hpp"

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

        auto start = std::chrono::system_clock::now();

        std::vector<std::vector<int>> test = tarjan(g);

        auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now() - start)
                         .count();

        std::cout << "Connected components of " << argv[i] << "\n";
        std::cout << "Computed in " << delay << "ms\n";
        display_connected_components(test);
    }
}
