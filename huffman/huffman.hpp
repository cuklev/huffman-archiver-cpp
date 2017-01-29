#pragma once

#include<array>
#include<vector>
#include<experimental/optional>

const int BYTES_COUNT = 1 << 8;

struct HuffmanNode;

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>&);

std::experimental::optional<unsigned char> goDownHuffman(HuffmanNode*&, int);

HuffmanNode* makeNode();
HuffmanNode* makeLeftChild(HuffmanNode* const);
HuffmanNode* makeRightChild(HuffmanNode* const);
void putChar(HuffmanNode* const, char);
