#include "extract.hpp"
#include "../huffman/decompress.hpp"

#include<fstream>
#include<vector>

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

	for(auto& fn : filenames) {
		// TODO: ensure directory exists
		std::ofstream out(out_dir + ("/" + fn));
		std::ostreambuf_iterator<char> out_iterator(out);
		decompress(in_iterator, out_iterator);
	}
}
