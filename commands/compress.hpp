#pragma once

#include<istream>
#include<ostream>

void compress(const char*, const char*);
void compress(const char*, std::ostream&);
void compress(std::istream&, std::ostream&);
