#include "huffman.hpp"

#include<queue>

struct HuffmanNode {
	HuffmanNode* child[2];
	HuffmanNode() {
		child[0] = nullptr;
		child[1] = nullptr;
	}
};

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>& freq_table) {
	std::priority_queue<std::pair<uint64_t, HuffmanNode*>> q;

	for(int i = 0; i < (int)freq_table.size(); ++i) {
		if(freq_table[i] == 0) continue;
		q.push({-freq_table[i], new HuffmanNode});
	}

	while(q.size() > 1) {
		auto node = new HuffmanNode;

		auto freq = q.top().first;
		node->child[0] = q.top().second; q.pop();

		freq += q.top().first;
		node->child[1] = q.top().second; q.pop();

		q.push({freq, node});
	}

	// TODO: fix for empty array
	return q.top().second;
}
