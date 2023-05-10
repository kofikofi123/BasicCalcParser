#include "calcParser.h"
#include "calcScanner.h"
#include <algorithm>
#include <iostream>

int main(int argc, char* argv[]){
	if (argc < 2){
		return -1;
	}

	CalcParser parser;

	std::cout << "result: " << parser.computeString(argv[1]) << std::endl;

	return 0;
}
