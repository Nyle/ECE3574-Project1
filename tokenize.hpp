#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <vector>
#include <istream>

#include "expression.hpp"

// This module should define the C++ types and code required to parse a
// vtscript program into an AST.

// Split the given stream into a set of tokens, stored as a vector of strings
std::vector<std::string> tokenize(std::istream & in);

#endif
