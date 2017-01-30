#include "binary_write.hpp"

BinaryWrite::BinaryWrite(std::ostream& out)
	: it_(out),
	index_(7),
	buffer_(0) {}

void BinaryWrite::operator()(bool bit) {
	buffer_ |= (uint8_t)bit << index_;
	if(index_ > 0) {
		--index_;
	} else {
		*it_ = buffer_;
		index_ = 7;
		buffer_ = 0;
	}
}

void BinaryWrite::writeAlignedByte(char c) {
	*it_ = c;
}

BinaryWrite::~BinaryWrite() {
	if(index_ < 7) *it_ = buffer_;
}
