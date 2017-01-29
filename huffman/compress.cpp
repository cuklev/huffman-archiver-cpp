#include "compress.hpp"
#include "../binary/bin_stream.hpp"
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

void dfs(HuffmanNode* const node, std::vector<bool>& bit_sequence, std::array<std::vector<bool>, BYTES_COUNT>& table, BinaryWrite& bin_out) {
	auto child = node;
	bit_sequence.push_back(0);
	bin_out(0);
	if(auto result = goDownHuffman(child, 0)) {
		bin_out(1);
		bin_out.write(result.value());
		table[result.value()] = bit_sequence;
	} else {
		dfs(child, bit_sequence, table, bin_out);
	}

	child = node;
	bit_sequence.back() = 1;
	if(auto result = goDownHuffman(child, 1)) {
		bin_out(1);
		bin_out.write(result.value());
		table[result.value()] = bit_sequence;
	} else {
		dfs(child, bit_sequence, table, bin_out);
	}

	bit_sequence.pop_back();
}

void compress(const std::array<uint64_t, BYTES_COUNT>& freq_table,
		std::istream& input,
		std::ostreambuf_iterator<char>& out_iterator) {

	auto root = buildHuffmanTree(freq_table);

	if(root == nullptr) return;

	std::array<std::vector<bool>, BYTES_COUNT> table;
	BinaryWrite bin_out(out_iterator);

	{
		std::vector<bool> bit_sequence;
		dfs(root, bit_sequence, table, bin_out);
	}
	{
		uint64_t byte_length = 0;
		for(int i = 0; i < BYTES_COUNT; ++i)
			byte_length += freq_table[i];
		bin_out.write(byte_length);
	}

	auto put_bit = [&bin_out](uint8_t f){bin_out(f);};
	auto put_bits = [&](uch c){ std::for_each(table[c].begin(), table[c].end(), put_bit); };

	std::for_each(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), put_bits);
}
