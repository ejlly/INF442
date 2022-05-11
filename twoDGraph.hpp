#pragma once

#include <vector>

#include "graph.hpp"

class Point {
   public:
    double x, y;
    Point(double x, double y);
    double dist(const Point& other);
};

class TwoDGraph : public Graph {
   public:
    std::vector<Point> points;
    TwoDGraph(int n);
    void draw(int size);
};