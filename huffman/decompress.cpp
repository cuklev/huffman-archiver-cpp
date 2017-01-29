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

	uint64_t bytes_left = 0;
	for(int i = 63; i >= 0; --i)
		bytes_left |= (uint8_t)bin_in() << i;

	if(bytes_left == 0) return;

	auto root = makeNode();
	dfs(bin_in, root);

	if(auto result = isLeaf(root)) {
		while(bytes_left > 0) {
			*out_iterator = result.value();
			--bytes_left;
		}
		return;
	}

	auto node = root;
	while(true) {
		node = goDown(node, bin_in());
		if(auto result = isLeaf(node)) {
			*out_iterator = result.value();
			--bytes_left;
			if(bytes_left == 0) break;
			node = root;
		}
	}
}
