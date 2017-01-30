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

		template<typename T>
		void write(T c) { // TODO: optimize for whole bytes
			for(int i = 8 * sizeof(T) - 1; i >= 0; --i) {
				this->operator()((c >> i) & 1);
			}
		}

		~BinaryWrite();
};
