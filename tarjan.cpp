#include "tarjan.hpp"

using namespace std;

struct Context{
	int index;
	stack<int> pile;
	int *order;
	int *dfs_seen;
	bool *on_stack;
	vector<vector<int>> connected_components;
	Graph g;
};

void check_composante(int node, Context &c){
	c.order[node] = c.index;
	c.dfs_seen[node] = c.index++;

	c.pile.push(node);
	c.on_stack[node] = true;

	for(auto end: c.g.neighbours[node]){
		if(c.order[end] == -1){
			check_composante(end, c);
			c.dfs_seen[node] = min<int>(c.dfs_seen[node], c.dfs_seen[end]);
		}
		else if(c.on_stack[end]){
			c.dfs_seen[node] = min<int>(c.dfs_seen[node], c.order[end]);
		}
	}

	if(c.order[node] == c.dfs_seen[node]){
		c.connected_components.push_back(vector<int>());
		int tmp;
		do{
			tmp = c.pile.top();
			c.pile.pop();
			c.on_stack[tmp] = false;
			c.connected_components.back().push_back(tmp);
		}while(tmp != node);
	}

}
vector<vector<int>> tarjan(Graph g){
	Context contexte;

	int index(0);
	stack<int> pile;

	int order[g.n], dfs_seen[g.n];
	bool on_stack[g.n];

	vector<vector<int>> connected_components;

	for(int i(0); i<g.n; i++){
		order[i] = -1;
		dfs_seen[i] = -1;
	}
	
	contexte.index = index;
	contexte.pile = pile;
	contexte.order = order;
	contexte.dfs_seen = dfs_seen;
	contexte.on_stack = on_stack;
	contexte.connected_components = connected_components;
	contexte.g = g;


	for(int node(0); node<g.n; node++)
		if(order[node] == -1)
			check_composante(node, contexte);
	
	return connected_components;
}


void aff_cnx(std::vector<std::vector<int>> compo){
	for(int i(0); i<compo.size(); i++){
		std::cout << i << " : ";
		for(int j : compo[i]){
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
}

