#include "huffman.hpp"

#include<queue>

struct HuffmanNode {
	unsigned char symbol;
	HuffmanNode* child[2];

	HuffmanNode() {
		child[0] = nullptr;
		child[1] = nullptr;
	}

	HuffmanNode(char s)
		: symbol(s) {
		child[0] = nullptr;
		child[1] = nullptr;
	}
};

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>& freq_table) {
	std::priority_queue<std::pair<uint64_t, HuffmanNode*>> q;

	for(int i = 0; i < (int)freq_table.size(); ++i) {
		if(freq_table[i] == 0) continue;
		q.push({-freq_table[i], new HuffmanNode(i)});
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

void dfs(const HuffmanNode* node, std::vector<bool>& bit_sequence, std::array<std::vector<bool>, BYTES_COUNT>& table) {
	if(!node->child[0]) {
		table[node->symbol] = bit_sequence;
		return;
	}

	bit_sequence.push_back(0);
	dfs(node->child[0], bit_sequence, table);
	bit_sequence.back() = 1;
	dfs(node->child[1], bit_sequence, table);
	bit_sequence.pop_back();
}

std::array<std::vector<bool>, BYTES_COUNT> buildCompressTable(HuffmanNode* root) {
	std::array<std::vector<bool>, BYTES_COUNT> table;

	std::vector<bool> bit_sequence;
	dfs(root, bit_sequence, table);

	return table;
}
