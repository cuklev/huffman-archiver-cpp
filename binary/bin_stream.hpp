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
		~BinaryWrite();
};
