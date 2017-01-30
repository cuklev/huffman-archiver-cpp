#include "extract.hpp"
#include "../huffman/decompress.hpp"

#include<fstream>
#include<vector>
#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;

void extract(const char* in_file, const char* out_dir) {
	std::ifstream in(in_file);
	extract(in, out_dir);
}

void extract(std::istream& in_stream, const char* out_dir) {
	std::istreambuf_iterator<char> in_iterator(in_stream);

	std::vector<std::string> filenames;

	std::string fn;
	while(true) {
		char next = *in_iterator;
		++in_iterator;
		if(next == '\0') {
			if(fn.empty()) break;
			filenames.push_back(fn);
			fn.clear();
		}
		else {
			fn.push_back(next);
		}
	}

	BinaryRead bin_in(in_iterator);
	for(auto& fn : filenames) {
		std::string full_name = fs::path(out_dir) / fn;
		const auto ind = full_name.find_last_of("/");
		fs::create_directories(full_name.substr(0, ind));

		std::ofstream out(full_name);
		std::ostreambuf_iterator<char> out_iterator(out);
		decompress(bin_in, out_iterator);
	}
}
