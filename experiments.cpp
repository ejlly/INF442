#include "experiments.hpp"

#include <chrono>
#include <set>

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

void do_experiments_ER(const int N, const int NB_TEST, const int NB_PROB, const double MAX_VALUE) {
    double p(0);

    std::ofstream ofs;
    ofs.open("results.csv", std::ofstream::out);

    ofs << "Size : " << N << "\n";

    for (double p(0); p <= MAX_VALUE; p += MAX_VALUE / NB_PROB) {
        int nb_compo = 0;
        int nb_compo_isolated = 0;
        std::set<int> sizes;

        for (int i(0); i < NB_TEST; i++) {
            Graph er(N, p);

            auto connections = tarjan(er);

            int nb_compo_loop = connections.size();

            for (int j(0); j < nb_compo_loop; j++) {
                int tmp_size(connections[j].size());
                if (sizes.find(tmp_size) == sizes.end())
                    sizes.insert(tmp_size);
                nb_compo_isolated += (tmp_size == 1);
            }
            nb_compo += nb_compo_loop;
        }

        nb_compo /= NB_TEST;
        nb_compo_isolated /= NB_TEST;

        std::cout << "Parameter :\n\t-size : " << N << "\n\t-probability : " << p << "\n"
                  << "\n\t-average number of compenents : " << nb_compo << "\n\t-nb_compo_isolated : " << nb_compo_isolated << "\n\n";

        ofs << p << "," << nb_compo << "," << nb_compo_isolated << "\n";
    }

    ofs.close();
}