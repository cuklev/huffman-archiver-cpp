#include "compress.hpp"
#include "../binary/bin_stream.hpp"
#include<algorithm>

using uch = unsigned char;

std::array<uint64_t, BYTES_COUNT> readTable(std::istream& input) {
	std::array<uint64_t, BYTES_COUNT> freq_table;
	freq_table.fill(0);
	std::for_each(std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>(),
			[&freq_table](uch c){ ++freq_table[c]; });

	return freq_table;
}

void compress(const std::array<uint64_t, BYTES_COUNT>& freq_table,
		std::istream& input,
		std::ostreambuf_iterator<char>& out_iterator) {

	auto root = buildHuffmanTree(freq_table);

	{
		const char* src = (char*)freq_table.data();
		for(int left = sizeof(freq_table); left > 0; --left) {
			*out_iterator = *src;
			++src;
		}
	}

	if(root == nullptr) return;
	auto table = buildCompressTable(root);

	BinaryWrite bin_out(out_iterator);
	auto put_bit = [&bin_out](uint8_t f){bin_out(f);};
	auto put_bits = [&](uch c){ std::for_each(table[c].begin(), table[c].end(), put_bit); };

	std::for_each(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), put_bits);
}
