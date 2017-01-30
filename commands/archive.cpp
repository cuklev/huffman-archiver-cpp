#include "archive.hpp"
#include "../huffman/compress.hpp"
#include "../binary/bin_stream.hpp"

#include<fstream>
#include<vector>
#include<experimental/filesystem>

void archive_files(const std::vector<std::string>& filenames, std::ostream& out_stream) {
	std::ostreambuf_iterator<char> out_iterator(out_stream);

	for(auto& fn : filenames) { // TODO: must strip base path
		for(char c : fn) *out_iterator = c;
		*out_iterator = '\0';
	}
	*out_iterator = '\0';

	BinaryWrite bin_out(out_iterator);

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
	namespace fs = std::experimental::filesystem;

	std::vector<std::string> filenames;

	if(fs::is_regular_file(in_file)) {
		filenames.push_back(in_file);
	} else if(fs::is_directory(in_file)) {
		for(auto& p: fs::recursive_directory_iterator(in_file)) {
			if(!fs::is_regular_file(p)) continue;
			filenames.push_back(p.path());
		}
	} // else not supported, yet!

	archive_files(filenames, out_stream);
}

void archive(std::istream& in_stream, std::ostream& out_stream) {
	std::vector<std::string> filenames;
	std::string fn;

	while(std::getline(in_stream, fn))
		filenames.push_back(fn);

	archive_files(filenames, out_stream);
}
