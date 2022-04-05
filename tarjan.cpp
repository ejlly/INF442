#include "tarjan.hpp"

using namespace std;

vector<vector<int>> tarjan(Graph g){
	int index(0);
	stack<Point_With_Info> pile;

	int order[g.n], dfs_seen[g.n];

	for(int i(0); i<g.n; i++){
		order[i] = -1;
		dfs_seen[i] = -1;
	}
	

	for(int node(0); node<g.n; node++)
		if(order[node] == -1)
			check_composante(node, index, pile, order, dfs_seen);
	
}

void check_composante(int node, int index, stack &pile, int *order, int *dfs_seen){
	order[node] = index;
	dfs_seen[node] = index++;

	pile.push
}
