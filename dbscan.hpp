#pragma once

#include "graph.hpp"

class DbscanParameters {
   public:
    double maxDist;
    int minPoints;
    DbscanParameters(double maxDist, int minPoints);
};

void dbscan(Graph& g, const DbscanParameters& parameters);