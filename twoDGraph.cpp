#include "twoDGraph.hpp"

#include <math.h>

#include <iostream>

#include "utils.hpp"

Point::Point(double _x, double _y) : x(_x), y(_y) {}

double Point::dist(const Point& other) {
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

TwoDGraph::TwoDGraph(int n) : Graph(n) {
    for (int i = 0; i < n; i++) {
        points.push_back(Point(rand_double(), rand_double()));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double d = points[i].dist(points[j]);
            neighbours[i].push_back(Edge(i, j, d));
            neighbours[j].push_back(Edge(j, i, d));
        }
    }
}

void TwoDGraph::draw(int size) {
    std::vector<std::string> grid(size);
    for (int i = 0; i < size; i++) {
        grid[i] = std::string(size, '.');
    }

    for (int i = 0; i < n; i++) {
        int positionX = floor(points[i].x * size);
        int positionY = floor(points[i].y * size);
        int cluster = clusters[i];
        char c = cluster == -1 ? '#' : (cluster < 10 ? cluster + '0' : cluster - 10 + 'a');
        grid[positionY][positionX] = c;
    }

    for (auto& s : grid) {
        std::cout << s << "\n";
    }
}