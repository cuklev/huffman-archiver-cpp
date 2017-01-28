#include "decompress.hpp"
#include "huffman.hpp"
#include<iterator>

std::string decompress(std::istreambuf_iterator<char>& data_iterator) {
	std::string decompressed;

	std::array<uint64_t, BYTES_COUNT> freq_table;

	{
		auto dest = (char*)freq_table.data();
		for(int left = sizeof(freq_table); left > 0; --left) {
			*dest = *data_iterator;
			++data_iterator;
			++dest;
		}
	}

	uint64_t decompressed_length = 0;
	for(auto x : freq_table)
		decompressed_length += x;

	decompressed.reserve(decompressed_length);

	auto root = buildHuffmanTree(freq_table);
	auto node = root;

	while(!data_iterator.equal(std::istreambuf_iterator<char>())) {
		unsigned char c = *data_iterator;
		++data_iterator;

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
