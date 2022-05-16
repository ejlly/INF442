#include <iostream>
#include <ctime>

#include "tarjan.hpp"

int main(int argc, char **argv){

	if(argc == 1){
		std::cout << "Usage : " << argv[0] << " filename1 filename2 ...\n";
		return 0;
	}

	//Set rand seed for ER-graphs
	std::srand(time(nullptr));
	
	//Read .edges files
	for(int i(1); i<argc; i++){
		Graph g(argv[i]);
		//g.print();

		std::vector<std::vector<int>> test = tarjan(g);

		aff_cnx(test);
	}

}
