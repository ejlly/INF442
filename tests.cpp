#include <iostream>
#include <ctime>
#include <cstring>
#include <algorithm>

#include "tarjan.hpp"

int main(int argc, char **argv){

	if(argc < 3){
		std::cout << "Usage : " << argv[0] << " [-d|-u] filename1 filename2 ...\n";
		return 0;
	}

	//Set rand seed for ER-graphs
	std::srand(time(nullptr));
	
	//https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
	bool directed;

	if(std::strcmp(argv[1], "-d") == 0){
		directed = true;
	}
	else if(std::strcmp(argv[1], "-u") == 0){
		directed = false;
	}
	else{
		std::cout << "Usage : " << argv[0] << " [-d|-u] filename1 filename2 ...\n";
		return 0;
	}


	//Read .edges files
	for(int i(2); i<argc; i++){
		Graph g(argv[i], directed);
		//g.print();

		std::vector<std::vector<int>> test = tarjan(g);

		aff_cnx(test);
	}

}
