#pragma once

#include <string>

void do_experiment_dbscan_components_size(std::string& path);
void do_experiment_tarjan_speed(std::string& path, bool directed);
void do_experiments_ER(const int N, const int NB_TEST, const int NB_PROB, const double MAX_VALUE,
                       std::string output_path);
void do_experiments_2D(const int M, const double EPS, const int NB_TEST, const int INCR_N, const int MAX_N,
                       std::string output_path);