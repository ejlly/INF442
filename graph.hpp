#ifndef MY_GRAPH_HPP
#define MY_GRAPH_HPP

#include <vector>

class Graph{
	public:
		std::vector<std::vector<int>> neighbours;
		int n;
		Graph();
		Graph(int n);  // Empty graph
};

#endif
