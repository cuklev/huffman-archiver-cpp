#include "huffman.hpp"

#include<queue>

struct HuffmanNode {
	unsigned char symbol;
	HuffmanNode* child[2];

	HuffmanNode() {
		child[0] = nullptr;
		child[1] = nullptr;
	}

	HuffmanNode(unsigned char s)
		: symbol(s) {
		child[0] = nullptr;
		child[1] = nullptr;
	}
};

struct NodePriority {
	uint64_t priority;
	HuffmanNode* node;

	inline bool operator<(const NodePriority& other) const {
		return priority > other.priority;
	}
};

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>& freq_table) {
	std::priority_queue<NodePriority> q;

	for(int i = 0; i < (int)freq_table.size(); ++i) {
		if(freq_table[i] == 0) continue;
		q.push({freq_table[i], new HuffmanNode(i)});
	}

	if(q.empty()) return nullptr;

	while(q.size() > 1) {
		auto node = new HuffmanNode;

		auto freq = q.top().priority;
		node->child[0] = q.top().node; q.pop();

		freq += q.top().priority;
		node->child[1] = q.top().node; q.pop();

		q.push({freq, node});
	}

	return q.top().node;
}

std::experimental::optional<unsigned char> goDownHuffman(HuffmanNode*& node, int direction) {
	node = node->child[direction];
	if(node->child[0]) return {};
	return {node->symbol};
}

HuffmanNode* makeNode() {
	return new HuffmanNode();
}
HuffmanNode* makeLeftChild(HuffmanNode* const node) {
	return node->child[0] = makeNode();
}
HuffmanNode* makeRightChild(HuffmanNode* const node) {
	return node->child[1] = makeNode();
}

void putChar(HuffmanNode* const node, char c) {
	node->symbol = c;
}
