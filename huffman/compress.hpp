#pragma once

#include "huffman.hpp"
#include "../binary/binary_write.hpp"

std::array<uint64_t, BYTES_COUNT> readTable(std::istream&);
void compress(const std::array<uint64_t, BYTES_COUNT>&,
		std::istream&,
		BinaryWrite&);
