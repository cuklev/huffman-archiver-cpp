#include "decompress.hpp"
#include "huffman.hpp"

void decompress(std::istreambuf_iterator<char>& in_iterator,
		std::ostreambuf_iterator<char>& out_iterator) {

	std::array<uint64_t, BYTES_COUNT> freq_table;

	{
		auto dest = (char*)freq_table.data();
		for(int left = sizeof(freq_table); left > 0; --left) {
			*dest = *in_iterator;
			++in_iterator;
			++dest;
		}
	}

	uint64_t bytes_left = 0;
	for(auto x : freq_table)
		bytes_left += x;

	auto root = buildHuffmanTree(freq_table);
	auto node = root;

	while(!in_iterator.equal(std::istreambuf_iterator<char>())) {
		unsigned char c = *in_iterator;
		++in_iterator;

		for(int i = 7; i >= 0; --i) {
			auto result = goDownHuffman(node, (c >> i) & 1);
			if(result) {
				*out_iterator = result.value();
				if(bytes_left == 0) break;
				node = root;
			}
		}
	}
}
