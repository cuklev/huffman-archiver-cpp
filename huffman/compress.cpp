#include "compress.hpp"
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

	uint64_t index = 0;
	char buffer_char = 0;
	std::for_each(std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>(),
			[&](uch c) {
				for(unsigned f : table[c]) {
					buffer_char |= f << (~index & 7);
					++index;
					if((index & 7) == 0) {
						*out_iterator = buffer_char;
						buffer_char = 0;
					}
				}
			});

	if((index & 7) > 0)
		*out_iterator = buffer_char;
}
