#include "decompress.hpp"
#include "huffman.hpp"

void dfs(BinaryRead& bin_in, HuffmanNode* const node) {
	if(bin_in()) {
		putChar(node, bin_in.readUnalignedByte());
	} else {
		dfs(bin_in, makeLeftChild(node));
		dfs(bin_in, makeRightChild(node));
	}
}

void decompress(BinaryRead& bin_in,
		std::ostreambuf_iterator<char>& out_iterator) {

	auto bytes_left = bin_in.readUnalignedUInt64();
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
