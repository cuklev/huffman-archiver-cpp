#pragma once

#include "huffman.hpp"
#include<iterator>

std::array<uint64_t, BYTES_COUNT> readTable(std::istream&);
void compress(const std::array<uint64_t, BYTES_COUNT>&,
		std::istream&,
		std::ostreambuf_iterator<char>&);
