#pragma once

#include "../binary/bin_stream.hpp"
#include<iterator>

void decompress(BinaryRead&, std::ostreambuf_iterator<char>&);
