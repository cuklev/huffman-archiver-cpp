#pragma once

#include<array>
#include<vector>
#include<experimental/optional>

const int BYTES_COUNT = 1 << 8;

struct HuffmanNode;

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>&);

std::array<std::vector<bool>, BYTES_COUNT> buildCompressTable(HuffmanNode*);

std::experimental::optional<char> goDownHuffman(HuffmanNode*&, int);
