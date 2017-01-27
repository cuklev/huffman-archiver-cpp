#include "compress.hpp"

#include<iostream>
#include<fstream>

void printUsage() {
	std::cout << "Give option\n";
}

const std::string COMPRESS_COMMAND = "c";
const std::string DECOMPRESS_COMMAND = "d";

int main(int argc, char** argv) {
	if(argc < 4) {
		printUsage();
		return 1;
	}

	std::ifstream in(argv[2]);
	std::ofstream out(argv[3]);

	if(argv[1] == COMPRESS_COMMAND) {
		std::string data;
		data.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
		out << compress(data);
	}
	else if(argv[1] == DECOMPRESS_COMMAND) {
		std::cerr << "Not implemented\n";
		return 1;
	}
	else {
		printUsage();
		return 1;
	}
}
