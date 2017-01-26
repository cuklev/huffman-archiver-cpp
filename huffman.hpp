#ifndef __HUFFMAN_HPP
#define __HUFFMAN_HPP

#include<cstdint>
#include<array>

const int BYTES_COUNT = 1 << 8;

struct HuffmanNode;

HuffmanNode* buildHuffmanTree(const std::array<uint64_t, BYTES_COUNT>&);

#endif
