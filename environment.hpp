#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <string>
#include <vector>
#include "expression.hpp"
#include "environmentprocedures.hpp"

class Environment {
private:
    std::map<std::string, EnvFunc> map;    
public:
    // default constructor
    Environment();
    // Define a symbol. Returns true on success, false on failure (literal exp)
    bool define(std::string symbol, Expression exp);
    // Define a symbol. Returns true on success, false on failure (function)
    bool define(std::string symbol, EnvFunc func);
    // Retrieve the given symbol. Returns None Expression if symbol is not
    // defined
    EnvFunc retrieve(std::string symbol);
};


#endif // ENVIRONMENT_H
