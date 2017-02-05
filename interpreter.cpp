#include "interpreter.hpp"
#include "tokenize.hpp"

// For debugging
#include <iostream>

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    TokenList tokens = tokenize(expression);
    TokenList tokenscopy = TokenList(tokens);
    this->ast = constructast(tokens);
    return this->ast.gettype() != None;
}

void Interpreter::printast(std::ostream & out) {    
    out << this->ast << "\n";
}

Expression Interpreter::eval() {
    return this->ast.eval(this->env);
}
