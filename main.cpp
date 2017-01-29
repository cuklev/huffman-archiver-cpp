#include "huffman/compress.hpp"
#include "huffman/decompress.hpp"

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
		std::ostream* const out = argc > 3 ? new std::ofstream(argv[3]) : &std::cout;
		std::ostreambuf_iterator<char> out_iterator(*out);

		std::array<uint64_t, BYTES_COUNT> freq_table;

		if(argc > 2) {
			std::ifstream in_file(argv[2]);
			freq_table = readTable(in_file);
			in_file.close();
			in_file.open(argv[2]);
			compress(freq_table, in_file, out_iterator);
		} else {
			const std::string in_data((std::istreambuf_iterator<char>(std::cin)),
					std::istreambuf_iterator<char>());

			{
				std::istringstream in_stream(in_data);
				freq_table = readTable(in_stream);
			}
			{
				std::istringstream in_stream(in_data);
				compress(freq_table, in_stream, out_iterator);
			}
		}
	}
	else if(argv[1] == DECOMPRESS_COMMAND) {
		std::istream* const in = argc > 2 ? new std::ifstream(argv[2]) : &std::cin;
		std::ostream* const out = argc > 3 ? new std::ofstream(argv[3]) : &std::cout;

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
