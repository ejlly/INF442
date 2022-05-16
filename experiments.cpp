#include "experiments.hpp"

#include <chrono>
#include <set>

#include "dbscan.hpp"
#include "graph.hpp"
#include "tarjan.hpp"
#include "twoDGraph.hpp"
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

void do_experiments_ER(const int N, const int NB_TEST, const int NB_PROB, const double MAX_VALUE,
                       std::string output_path) {
    std::ofstream ofs;
    ofs.open(output_path, std::ofstream::out);

    ofs << "p,avg_nb_composantes,avg_nb_composantes_isolees\n";

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

void do_experiments_2D(const int M, const double EPS, const int NB_TEST, const int INCR_N, const int MAX_N,
                       std::string output_path) {
    std::ofstream ofs;
    ofs.open(output_path, std::ofstream::out);

    ofs << "n,avg_nb_composantes,avg_nb_noise\n";

    for (int n = INCR_N; n <= MAX_N; n += INCR_N) {
        int nb_compo = 0;
        int nb_noise = 0;
        std::set<int> sizes;

        for (int i(0); i < NB_TEST; i++) {
            TwoDGraph g(n);
            dbscan(g, DbscanParameters(EPS, M));
            auto connections = g.get_components();

            int nb_compo_loop = connections.size();
            int nb_in_clusters = 0;
            for (auto& c : connections) {
                nb_in_clusters += c.size();
            }
            nb_compo += nb_compo_loop;
            nb_noise += n - nb_in_clusters;
        }

        nb_compo /= NB_TEST;
        nb_noise /= NB_TEST;

        ofs << n << "," << nb_compo << "," << nb_noise << "\n";
    }

    ofs.close();
}