#pragma once

#include "graph.hpp"

class DbscanParameters {
   public:
    double max_dist;
    int min_points;
    DbscanParameters(double max_dist, int min_points);
};

void dbscan(Graph& g, const DbscanParameters& parameters);