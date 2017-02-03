#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <string>
#include "expression.hpp"

// This module should define the C++ types and code required to implement the
// vtscript environment mapping.

class Environment {
private:
    std::map<std::string, Expression> map;    
public:
    // Define a symbol. Returns true on success, false on failure
    bool define(std::string symbol, Expression exp);
    // Retrieve the given symbol. Returns None Expression if symbol is not
    // defined
    Expression retrieve(std::string symbol);
};

#endif // ENVIRONMENT_H
