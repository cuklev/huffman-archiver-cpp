#include "archive.hpp"
#include "../huffman/compress.hpp"
#include "../binary/bin_stream.hpp"

#include<fstream>
#include<vector>

void archive_files(const std::vector<std::string>& filenames, std::ostream& out_stream) {
	std::ostreambuf_iterator<char> out_iterator(out_stream);
	BinaryWrite bin_out(out_iterator);

	for(auto& fn : filenames) {
		for(char c : fn) *out_iterator = c;
		*out_iterator = '\0';
	}
	*out_iterator = '\0';

	for(auto& fn : filenames) {
		std::ifstream in(fn);
		auto freq_table = readTable(in);
		in.close();
		in.open(fn);
		compress(freq_table, in, bin_out);
	}
}

void archive(const char* in_file, const char* out_file) {
	std::ofstream out(out_file);
	archive(in_file, out);
}

void archive(const char* in_file, std::ostream& out_stream) {
	throw "Not implemented";
}

void archive(std::istream& in_stream, std::ostream& out_stream) {
	std::vector<std::string> filenames;
	std::string fn;

	while(std::getline(in_stream, fn))
		filenames.push_back(fn);

	archive_files(filenames, out_stream);
}
