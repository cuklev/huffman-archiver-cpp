#include "compress.hpp"
#include "decompress.hpp"

#include<iostream>
#include<fstream>

void printUsage() {
	std::cout << "Give option\n";
}

const std::string COMPRESS_COMMAND = "c";
const std::string DECOMPRESS_COMMAND = "d";
const std::string ARCHIVE_COMMAND = "a";
const std::string EXTRACT_COMMAND = "x";

int main(int argc, char** argv) {
	if(argc < 2) {
		printUsage();
		return 1;
	}

	std::istream* const in = argc > 2 ? new std::ifstream(argv[2]) : &std::cin;
	std::ostream* const out = argc > 3 ? new std::ofstream(argv[3]) : &std::cout;

	if(argv[1] == COMPRESS_COMMAND) {
		std::string data((std::istreambuf_iterator<char>(*in)),
				std::istreambuf_iterator<char>());
		*out << compress(data);
	}
	else if(argv[1] == DECOMPRESS_COMMAND) {
		std::istreambuf_iterator<char> in_iterator(*in);
		std::ostreambuf_iterator<char> out_iterator(*out);
		decompress(in_iterator, out_iterator);
	}
	else if(argv[1] == ARCHIVE_COMMAND) {
		std::cerr << "Archive is not implemented\n";
		return 1;
	}
	else if(argv[1] == EXTRACT_COMMAND) {
		std::cerr << "Extract is not implemented\n";
		return 1;
	}
	else {
		printUsage();
		return 1;
	}
}
