#include "huffman.hpp"

#include<iostream>
#include<algorithm>

int main() {
	std::string line;
	std::getline(std::cin, line);

	std::array<uint64_t, BYTES_COUNT> freq_table;
	for(auto& x : freq_table) x = 0;
	for(unsigned char c : line) ++freq_table[c];

	auto root = buildHuffmanTree(freq_table);
	auto table = buildCompressTable(root);

	/*
	for(int i = 0; i < (int)table.size() ; ++i) {
		if(table[i].empty()) continue;
		std::cout << (char)i << ": ";
		for(bool x : table[i]) std::cout << x;
		std::cout << '\n';
	}
	*/

	std::vector<bool> compressed;
	for(unsigned char c : line) {
		std::copy(table[c].begin(), table[c].end(), std::back_inserter(compressed));
	}

	compressed.resize((compressed.size() + 7) & 0xFF);
	for(int i = 0, x = 0; i < (int)compressed.size(); ++i) {
		x |= compressed[i] << (~i & 7);
		if((i & 7) == 7) {
			std::cout << (unsigned char)x;
			x = 0;
		}
	}
}
