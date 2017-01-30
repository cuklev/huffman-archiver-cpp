#include "binary_read.hpp"

BinaryRead::BinaryRead(std::istream& in)
	: it_(in),
	index_(8) {}

bool BinaryRead::operator()() {
	--index_;
	bool f = (*it_ >> index_) & 1;
	if(index_ == 0) {
		index_ = 8;
		++it_;
	}
	return f;
}

char BinaryRead::readAlignedByte() {
	char c = *it_;
	++it_;
	return c;
}

char BinaryRead::readUnalignedByte() {
	unsigned char c = (unsigned char)*it_ << (8 - index_);
	++it_;
	return c | (unsigned char)*it_ >> index_;
}

uint64_t BinaryRead::readUnalignedUInt64() {
	uint64_t x = 0;
	for(int i = 64 - index_; i >= 0; i -= 8) {
		x |= (uint64_t)(uint8_t)*it_ << i;
		++it_;
	}
	return x | (uint64_t)(uint8_t)*it_ >> index_;
}
