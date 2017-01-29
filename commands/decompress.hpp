#pragma once

#include<istream>
#include<ostream>

void decompress(const char*, const char*);
void decompress(const char*, std::ostream&);
void decompress(std::istream&, std::ostream&);
