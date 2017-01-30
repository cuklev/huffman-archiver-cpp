#include "commands/compress.hpp"
#include "commands/decompress.hpp"
#include "commands/archive.hpp"
#include "commands/extract.hpp"

#include<iostream>
#include<fstream>
#include<sstream>

void printUsage(const char* prog_name) {
	std::cout << "Usage:\n  "
		<< prog_name << " c|d|a|x [in file] [out file]\n";
}

const std::string COMPRESS_COMMAND = "c";
const std::string DECOMPRESS_COMMAND = "d";
const std::string ARCHIVE_COMMAND = "a";
const std::string EXTRACT_COMMAND = "x";

int main(int argc, char** argv) {
	if(argc < 2) {
		printUsage(argv[0]);
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
		if(argc > 3) archive(argv[2], argv[3]);
		else if(argc > 2) archive(argv[2], std::cout);
		else archive(std::cin, std::cout);
	}
	else if(argv[1] == EXTRACT_COMMAND) {
		if(argc > 3) extract(argv[2], argv[3]);
		else if(argc > 2) extract(std::cin, argv[2]);
		else std::cerr << "Where to extract?\n";
	}
	else {
		printUsage(argv[0]);
		return 1;
	}
}
