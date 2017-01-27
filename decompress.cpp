#include "decompress.hpp"
#include "huffman.hpp"

std::string decompress(const std::string& data) {
	std::string decompressed;

	std::array<uint64_t, BYTES_COUNT> freq_table;
	std::copy(data.c_str(), data.c_str() + sizeof(freq_table), (char*)freq_table.data());

	uint64_t decompressed_length = 0;
	for(auto x : freq_table)
		decompressed_length += x;

	decompressed.reserve(decompressed_length);

	auto root = buildHuffmanTree(freq_table);
	auto node = root;

	for(int i = sizeof(freq_table); i < (int)data.size(); ++i) {
		unsigned char c = data[i];
		for(int i = 7; i >= 0; --i) {
			auto result = goDownHuffman(node, (c >> i) & 1);
			if(result) {
				decompressed.push_back(result.value());
				if(decompressed.size() == decompressed_length) break;
				node = root;
			}
		}
	}

	return decompressed;
}
