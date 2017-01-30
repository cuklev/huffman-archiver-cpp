#include "binary_read.hpp"

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
