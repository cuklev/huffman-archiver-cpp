#include "compress.hpp"
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
	if(auto result = isLeaf(node)) {
		bin_out(1);
		bin_out.write(result.value());
		table[result.value()] = bit_sequence;
		return;
	}

	bin_out(0);

	bit_sequence.push_back(0);
	dfs(goDown(node, 0), bit_sequence, table, bin_out);

	bit_sequence.back() = 1;
	dfs(goDown(node, 1), bit_sequence, table, bin_out);

	bit_sequence.pop_back();
}

void compress(const std::array<uint64_t, BYTES_COUNT>& freq_table,
		std::istream& input,
		BinaryWrite& bin_out) {

	{
		uint64_t byte_length = 0;
		int non_zero = -1;
		for(int i = 0; i < BYTES_COUNT; ++i) {
			byte_length += freq_table[i];
			if(freq_table[i] > 0) {
				if(non_zero >= 0) non_zero = -2;
				else if(non_zero == -1) non_zero = i;
			}
		}
		bin_out.write(byte_length);

		if(byte_length == 0) return;
		if(non_zero >= 0) {
			bin_out(1);
			bin_out.write((uint8_t)non_zero);
			return;
		}
	}

	auto root = buildHuffmanTree(freq_table);

	if(root == nullptr) return; // should not happen anyway

	std::array<std::vector<bool>, BYTES_COUNT> table;

	{
		std::vector<bool> bit_sequence;
		dfs(root, bit_sequence, table, bin_out);
	}

	auto put_bit = [&bin_out](uint8_t f){ bin_out(f); };
	auto put_bits = [&](uch c){ std::for_each(table[c].begin(), table[c].end(), put_bit); };

	std::for_each(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), put_bits);
}
