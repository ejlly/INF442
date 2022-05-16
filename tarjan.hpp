#pragma once

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#include "graph.hpp"

struct Context {
    int index;
    std::stack<int> pile;
    int *order;
    int *dfs_seen;
    bool *on_stack;
    std::vector<std::vector<int>> connected_components;
    Graph g;
};

void check_composante(int node, Context &c);

std::vector<std::vector<int>> tarjan(Graph g);

void display_connected_components(std::vector<std::vector<int>> compo);
