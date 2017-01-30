#pragma once

#include<iterator>

class BinaryWrite {
	private:
		std::ostreambuf_iterator<char> it_;
		int index_;
		unsigned char buffer_;

	public:
		BinaryWrite(std::ostream&);
		BinaryWrite(const BinaryWrite&) = delete;

		void operator()(bool);
		void writeAlignedByte(char);

		void writeUnalignedByte(unsigned char);
		void writeUnalignedUInt64(uint64_t);

		~BinaryWrite();
};
