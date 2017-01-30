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
	BinaryRead bin_in(in_stream);

	std::vector<std::string> filenames;

	std::string fn;
	while(true) {
		char next = bin_in.readAlignedByte();
		if(next == '\0') {
			if(fn.empty()) break;
			filenames.push_back(fn);
			fn.clear();
		}
		else {
			fn.push_back(next);
		}
	}

	for(auto& fn : filenames) {
		auto full_name = fs::path(out_dir) / fn;
		fs::create_directories(full_name.parent_path());

		std::ofstream out(full_name);
		std::ostreambuf_iterator<char> out_iterator(out);
		decompress(bin_in, out_iterator);
	}
}
