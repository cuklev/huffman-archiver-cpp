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

	int last_not_zero = -1;
	uint64_t bytes_left = 0;
	for(int i = 0; i < (int)freq_table.size(); ++i) {
		bytes_left += freq_table[i];
		if(freq_table[i] == 0) continue;

		if(last_not_zero == -1)
			last_not_zero = i;
		else if(last_not_zero >= 0)
			last_not_zero = -2;
	}
	
	if(last_not_zero >= 0) {
		for(int left = freq_table[last_not_zero]; left > 0; --left)
			*out_iterator = last_not_zero;
		return;
	}

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
