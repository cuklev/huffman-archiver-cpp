#pragma once

#include "huffman.hpp"
#include "../binary/bin_stream.hpp"
#include<iterator>

std::array<uint64_t, BYTES_COUNT> readTable(std::istream&);
void compress(const std::array<uint64_t, BYTES_COUNT>&,
		std::istream&,
		BinaryWrite&);
