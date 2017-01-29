#pragma once

#include<istream>
#include<ostream>

void archive(const char*, const char*);
void archive(const char*, std::ostream&);
void archive(std::istream&, std::ostream&);
