#pragma once

#include "graph.hpp"

class DbscanParameters {
   public:
    double eps;
    int M;
    DbscanParameters(double eps, int M);
};

void naive_dbscan(Graph& g, DbscanParameters parameters);