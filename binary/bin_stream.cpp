#include "bin_stream.hpp"

BinaryRead::BinaryRead(std::istreambuf_iterator<char>& it)
	: it_(it),
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

BinaryWrite::BinaryWrite(std::ostreambuf_iterator<char>& it)
	: it_(it),
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

BinaryWrite::~BinaryWrite() {
	if(index_ < 7) *it_ = buffer_;
}
