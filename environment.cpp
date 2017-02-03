#include <cmath>
#include <functional>
#include "environment.hpp"

// Make a function 
EnvFunc makeexpfunc(Expression exp) {
    return [exp](Args args, Environment &env) {
        return exp;
    };
}

bool Environment::define(std::string symbol, Expression exp) {
    if (!(this->map.count(symbol))) {
        // store a lambda that returns the expression
        this->map[symbol] = makeexpfunc(exp);
        return true;
    } else {
        return false;
    }
}

bool Environment::define(std::string symbol, EnvFunc fun) {
    if (!(this->map.count(symbol))) {
        // store a lambda that returns the expression
        this->map[symbol] = fun;
        return true;
    } else {
        return false;
    }
}

EnvFunc Environment::retrieve(std::string symbol) {
    if (this->map.count(symbol)) {
        return this->map[symbol];
    } else {
        // TODO: handle non-existing error more helpfully
        // Lambda to return None expression
        return makeexpfunc(Expression());
    }
}

Environment::Environment() {
    this->map = std::map<std::string, EnvFunc>();
    // Put in default environment
    this->define("begin", BeginFn());
    this->define("if", IfFn());
    this->define("not", NotFn());
    this->define("and", BinaryBoolFn(std::logical_and<bool>()));
    this->define("or", BinaryBoolFn(std::logical_or<bool>()));
    this->define("<", CmpFn(std::less<float>()));
    this->define("<=", CmpFn(std::less_equal<float>()));
    this->define(">", CmpFn(std::greater<float>()));
    this->define(">=", CmpFn(std::greater_equal<float>()));
    this->define("=", CmpFn(std::equal_to<float>()));
    this->define("+", PlusMulFn(std::plus<float>()));
    this->define("-", SubFn());
    this->define("*", PlusMulFn(std::multiplies<float>()));
    this->define("/", DivFn());
    this->define("pi", Expression(atan2(0, -1)));
}
