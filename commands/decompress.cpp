#include "decompress.hpp"
#include "../huffman/decompress.hpp"

#include<fstream>

void decompress(const char* in_file, const char* out_file) {
	std::ifstream in(in_file);
	std::ofstream out(out_file);
	decompress(in, out);
}

void decompress(const char* in_file, std::ostream& out_stream) {
	std::ifstream in(in_file);
	decompress(in, out_stream);
}

void decompress(std::istream& in_stream, std::ostream& out_stream) {
	std::istreambuf_iterator<char> in_iterator(in_stream);
	std::ostreambuf_iterator<char> out_iterator(out_stream);

	BinaryRead bin_in(in_iterator);
	decompress(bin_in, out_iterator);
}
