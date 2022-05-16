#include <iostream>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>

#include "tarjan.hpp"

#define N 25
#define NB_TEST 1000
#define NB_PROB 2000
#define MAX_VALUE ((double) 1)

int main(int argc, char **argv){

	double p(0);

	std::ofstream ofs;
	ofs.open("results.csv", std::ofstream::out);

	ofs << "Size : " << N << "\n";
	

	for(double p(0); p <= MAX_VALUE; p+= MAX_VALUE/NB_PROB){


		int nb_compo = 0; 
		int nb_compo_isolated = 0;
		std::set<int> sizes;

		for(int i(0); i<NB_TEST; i++){
			Graph er(N, p);

			auto connections = tarjan(er);

			int nb_compo_loop = connections.size();
			
			for(int j(0); j<nb_compo_loop; j++){
				int tmp_size(connections[j].size());
				if(sizes.find(tmp_size) == sizes.end())
					sizes.insert(tmp_size);
				nb_compo_isolated += (tmp_size == 1);
			}
			nb_compo += nb_compo_loop;
		}

		nb_compo /= NB_TEST;
		nb_compo_isolated /= NB_TEST;

		std::cout << "Parameter :\n\t-size : " << N << "\n\t-probability : " << p << "\n" << "\n\t-average number of compenents : " << nb_compo << "\n\t-nb_compo_isolated : " << nb_compo_isolated << "\n\n";
		
		ofs << p << "," << nb_compo << "," << nb_compo_isolated << "\n";
	}

	ofs.close();

}
