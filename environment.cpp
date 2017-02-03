#include "environment.hpp"

bool Environment::define(std::string symbol, Expression exp) {
    if (!(this->map.count(symbol))) {
        this->map[symbol] = exp;
        return true;
    } else {
        return false;
    }
}

Expression Environment::retrieve(std::string symbol) {
    if (this->map.count(symbol)) {
        return this->map[symbol];
    } else {
        return Expression();
    }
}
