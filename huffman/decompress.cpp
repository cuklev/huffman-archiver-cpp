#include "decompress.hpp"
#include "huffman.hpp"
#include "../binary/bin_stream.hpp"

void dfs(BinaryRead& bin_in, HuffmanNode* const node) {
	if(bin_in()) {
		unsigned char c = 0;
		for(int i = 7; i >= 0; --i)
			c |= (uint8_t)bin_in() << i;
		putChar(node, c);
	} else {
		dfs(bin_in, makeLeftChild(node));
		dfs(bin_in, makeRightChild(node));
	}
}

void decompress(std::istreambuf_iterator<char>& in_iterator,
		std::ostreambuf_iterator<char>& out_iterator) {

	BinaryRead bin_in(in_iterator);

	auto root = makeNode();
	dfs(bin_in, root);

	uint64_t bytes_left = 0;
	for(int i = 63; i >= 0; --i)
		bytes_left |= (uint8_t)bin_in() << i;

/*
	int last_not_zero = -1;
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
*/

	auto node = root;
	while(true) {
		if(auto result = goDownHuffman(node, bin_in())) {
			*out_iterator = result.value();
			--bytes_left;
			if(bytes_left == 0) break;
			node = root;
		}
	}
}
