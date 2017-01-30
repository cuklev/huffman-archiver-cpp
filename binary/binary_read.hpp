#pragma once

#include<iterator>

class BinaryRead {
	private:
		std::istreambuf_iterator<char> it_;
		int index_;

	public:
		BinaryRead(std::istream&);
		BinaryRead(const BinaryRead&) = delete;

		bool operator()();
		char readAlignedByte();

		char readUnalignedByte();
		uint64_t readUnalignedUInt64();
};
