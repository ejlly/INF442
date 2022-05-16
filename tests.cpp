#include <algorithm>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>

#include "dbscan.hpp"
#include "experiments.hpp"
#include "tarjan.hpp"
#include "utils.hpp"

void print_usage(std::string path) {
    std::cout << "Usage : \n"
              << "For dbscan experiments: " << path << " [-d|-u] filename1 filename2 ... \n"
              << "For ER experiments: " << path << " -e  N NB_TEST NB_PROB MAX_VALUE path\n"
              << "For dbscan experiments: " << path << " -p M EPS NB_TEST INCR_N MAX_N path\n";
}

int main(int argc, char** argv) {
    if (argc == 1 || argc < 3) {
        print_usage(argv[0]);
        return 0;
    }

    // Set rand seed for ER-graphs
    std::srand(time(nullptr));

    // https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
    bool directed;

    if (std::strcmp(argv[1], "-d") == 0) {
        directed = true;
    } else if (std::strcmp(argv[1], "-u") == 0) {
        directed = false;
    } else if (std::strcmp(argv[1], "-e") == 0) {
        if (argc != 7) {
            print_usage(argv[0]);
            return 0;
        }
        do_experiments_ER(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atof(argv[5]), argv[6]);
        return 0;
    } else if (std::strcmp(argv[1], "-p") == 0) {
        if (argc != 8) {
            print_usage(argv[0]);
            return 0;
        }
        do_experiments_2D(atoi(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), argv[7]);
        return 0;
    } else {
        print_usage(argv[0]);
        return 0;
    }

    // Read .edges files
    for (int i(2); i < argc; i++) {
        std::string path = argv[i];
        // do_experiment_speed(path, true);
        do_experiment_dbscan_components_size(path);
    }
}