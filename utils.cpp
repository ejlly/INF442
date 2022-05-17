#include "utils.hpp"

#include <algorithm>
#include <iostream>

double rand_double() {
    return (double)std::rand() / RAND_MAX;
}

void display_components_summary(std::vector<std::vector<int>>& components) {
    int max_componenet_size = 0;
    for (auto& c : components)
        max_componenet_size = std::max((int)c.size(), max_componenet_size);

    for (int i = 1; i <= max_componenet_size; i *= 2) {
        int count = 0;
        for (auto& c : components) {
            if (c.size() >= i && c.size() < i * 2) {
                count++;
            }
        }
        std::cout << count << " components of size between "
                  << i << " and " << 2 * i - 1 << "\n";
    }
}