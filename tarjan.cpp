#include "tarjan.hpp"

void check_composante(int node, Context &c) {
    c.order[node] = c.index;
    c.dfs_seen[node] = c.index++;

    c.pile.push(node);
    c.on_stack[node] = true;

    for (auto end : c.g.neighbours[node]) {
        if (c.order[end.to] == -1) {
            check_composante(end.to, c);
            c.dfs_seen[node] = std::min<int>(c.dfs_seen[node], c.dfs_seen[end.to]);
        } else if (c.on_stack[end.to]) {
            c.dfs_seen[node] = std::min<int>(c.dfs_seen[node], c.order[end.to]);
        }
    }

    if (c.order[node] == c.dfs_seen[node]) {
        c.connected_components.push_back(std::vector<int>());
        int tmp;
        do {
            tmp = c.pile.top();
            c.pile.pop();
            c.on_stack[tmp] = false;
            c.connected_components.back().push_back(tmp);
        } while (tmp != node);
    }
}

std::vector<std::vector<int>> tarjan(Graph& g) {
    Context context;

    int index(0);
    std::stack<int> pile;

    int order[g.n], dfs_seen[g.n];
    bool on_stack[g.n];

    std::vector<std::vector<int>> connected_components;

    for (int i(0); i < g.n; i++) {
        order[i] = -1;
        dfs_seen[i] = -1;
    }

    context.index = index;
    context.pile = pile;
    context.order = order;
    context.dfs_seen = dfs_seen;
    context.on_stack = on_stack;
    context.connected_components = connected_components;
    context.g = g;

    for (int node(0); node < g.n; node++) {
        if (order[node] == -1)
            check_composante(node, context);
    }

    return context.connected_components;
}

void display_connected_components(std::vector<std::vector<int>>& compo) {
    for (int i(0); i < compo.size(); i++) {
        std::cout << i << " : ";
        for (int j : compo[i]) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}