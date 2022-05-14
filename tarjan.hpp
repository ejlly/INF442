#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "graph.hpp"

std::vector<std::vector<int>> tarjan(Graph g);

void aff_cnx(std::vector<std::vector<int>> compo);

#endif

