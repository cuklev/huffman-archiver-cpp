#include "bin_stream.hpp"

BinaryRead::BinaryRead(std::istream& in)
	: it_(in),
	index_(7) {}

bool BinaryRead::operator()() {
	bool f = (*it_ >> index_) & 1;
	if(index_ > 0) {
		--index_;
	} else {
		index_ = 7;
		++it_;
	}
	return f;
}

char BinaryRead::readAlignedByte() {
	char c = *it_;
	++it_;
	return c;
}

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
