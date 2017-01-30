#include "archive.hpp"
#include "../huffman/compress.hpp"

#include<fstream>
#include<vector>
#include<experimental/filesystem>

void archive_files(const std::vector<std::string>& filenames, std::ostream& out_stream) {
	BinaryWrite bin_out(out_stream);

	for(auto& fn : filenames) {
		for(char c : fn) bin_out.writeAlignedByte(c);
		bin_out.writeAlignedByte('\0');
	}
	bin_out.writeAlignedByte('\0');

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

	auto parent_path = fs::path(in_file).parent_path();
	if(!parent_path.empty())
		fs::current_path(fs::path(in_file).parent_path());

	auto file = fs::path(in_file).filename();

	if(fs::is_regular_file(file)) {
		filenames.push_back(file);
	} else if(fs::is_directory(file)) {
		for(auto& p: fs::recursive_directory_iterator(file)) {
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
