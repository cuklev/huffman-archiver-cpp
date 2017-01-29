#pragma once

#include<iterator>

class BinaryRead {
	private:
		std::istreambuf_iterator<char>& it_;
		int index_;

	public:
		BinaryRead(std::istreambuf_iterator<char>&);
		BinaryRead(const BinaryRead&) = delete;
		bool operator()();
};

class BinaryWrite {
	private:
		std::ostreambuf_iterator<char>& it_;
		int index_;
		unsigned char buffer_;

	public:
		BinaryWrite(std::ostreambuf_iterator<char>&);
		BinaryWrite(const BinaryWrite&) = delete;
		void operator()(bool);

		template<typename T>
		void write(T c) { // TODO: optimize for whole bytes
			for(int i = 8 * sizeof(T) - 1; i >= 0; --i) {
				this->operator()((c >> i) & 1);
			}
		}

		~BinaryWrite();
};
