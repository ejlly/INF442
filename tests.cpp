#include <algorithm>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>

#include "dbscan.hpp"
#include "experiments.hpp"
#include "tarjan.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Usage : " << argv[0] << " filename1 filename2 ...\n";
        return 0;
    }

    if (argc < 3) {
        std::cout << "Usage : " << argv[0] << " [-d|-u] filename1 filename2 ...\n";
        return 0;
    }

    // Set rand seed for ER-graphs
    std::srand(time(nullptr));

    // https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
    bool directed;

    if (std::strcmp(argv[1], "-d")) {
        directed = true;
    } else if (std::strcmp(argv[1], "-u")) {
        directed = false;
    } else if (std::strcmp(argv[1], "-e")) {
        do_experiments_ER(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        return 0;  // experiment
    } else {
        std::cout << "Usage : " << argv[0] << " [-d|-u] filename1 filename2 ... \n";
        return 0;
    }

    // Read .edges files
    for (int i(2); i < argc; i++) {
        std::string path = argv[i];
        // do_experiment_speed(path, true);
        do_experiment_dbscan_components_size(path);
    }
}
