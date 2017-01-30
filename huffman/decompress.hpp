#pragma once

#include "../binary/binary_read.hpp"

void decompress(BinaryRead&, std::ostreambuf_iterator<char>&);
