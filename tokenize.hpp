#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <vector>
#include <istream>

#include "expression.hpp"

// Split the given stream into a set of tokens, stored as a vector of strings
std::vector<std::string> tokenize(std::istream & in);

// Construct an AST from the list of tokens
Expression constructast(std::vector<std::string> tokens);

#endif
