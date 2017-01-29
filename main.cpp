#include "huffman/compress.hpp"
#include "huffman/decompress.hpp"
#include "commands/compress.hpp"
#include "commands/decompress.hpp"

#include<iostream>
#include<fstream>
#include<sstream>

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

	if(argv[1] == COMPRESS_COMMAND) {
		if(argc > 3) compress(argv[2], argv[3]);
		else if(argc > 2) compress(argv[2], std::cout);
		else compress(std::cin, std::cout);
	}
	else if(argv[1] == DECOMPRESS_COMMAND) {
		if(argc > 3) decompress(argv[2], argv[3]);
		else if(argc > 2) decompress(argv[2], std::cout);
		else decompress(std::cin, std::cout);
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
