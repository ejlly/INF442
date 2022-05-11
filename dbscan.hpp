#pragma once

#include "graph.hpp"

class DbscanParameters {
   public:
    double maxDist;
    int minPoints;
    DbscanParameters(double maxDist, int minPoints);
};

void naive_dbscan(Graph& g, DbscanParameters parameters);