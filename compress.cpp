#include "compress.hpp"
#include "huffman.hpp"

std::string compress(const std::string& data) {
	using uch = unsigned char;

	std::array<uint64_t, BYTES_COUNT> freq_table;
	freq_table.fill(0);
	for(uch c : data) ++freq_table[c];
	auto root = buildHuffmanTree(freq_table);
	auto table = buildCompressTable(root);

	std::string compressed((char*)freq_table.data(), sizeof(freq_table));

	uint64_t index = 0;
	for(uch c : data) {
		for(unsigned f : table[c]) {
			if((index & 7) == 0)
				compressed.push_back(0);
			compressed.back() |= f << (~index & 7);
			++index;
		}
	}

	return compressed;
}
