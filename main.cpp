#include "compress.hpp"
#include "decompress.hpp"

#include<iostream>
#include<fstream>

void printUsage() {
	std::cout << "Give option\n";
}

const std::string COMPRESS_COMMAND = "c";
const std::string DECOMPRESS_COMMAND = "d";

int main(int argc, char** argv) {
	if(argc < 2) {
		printUsage();
		return 1;
	}

	std::istream* in = argc > 2 ? new std::ifstream(argv[2]) : &std::cin;
	std::ostream* out = argc > 3 ? new std::ofstream(argv[3]) : &std::cout;

	if(argv[1] == COMPRESS_COMMAND) {
		std::string data;
		data.assign(std::istreambuf_iterator<char>(*in), std::istreambuf_iterator<char>());
		*out << compress(data);
	}
	else if(argv[1] == DECOMPRESS_COMMAND) {
		std::string data;
		data.assign(std::istreambuf_iterator<char>(*in), std::istreambuf_iterator<char>());
		*out << decompress(data);
	}
	else {
		printUsage();
		return 1;
	}
}
