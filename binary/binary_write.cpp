#include "binary_write.hpp"

BinaryWrite::BinaryWrite(std::ostream& out)
	: it_(out),
	index_(8),
	buffer_(0) {}

void BinaryWrite::operator()(bool bit) {
	--index_;
	buffer_ |= (uint8_t)bit << index_;
	if(index_ == 0) {
		*it_ = buffer_;
		index_ = 8;
		buffer_ = 0;
	}
}

void BinaryWrite::writeAlignedByte(char c) {
	*it_ = c;
}

void BinaryWrite::writeUnalignedByte(unsigned char c) {
	*it_ = buffer_ | (c >> (8 - index_));
	buffer_ = c << index_;
}

void BinaryWrite::writeUnalignedUInt64(uint64_t x) {
	*it_ = buffer_ | (uint8_t)(x >> (64 - index_));
	for(int i = 56 - index_; i >= 0; i -= 8)
		*it_ = (uint8_t)(x >> i);
	buffer_ = x << index_;
}

BinaryWrite::~BinaryWrite() {
	if(index_ < 7) *it_ = buffer_;
}
