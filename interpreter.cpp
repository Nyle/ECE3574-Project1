#include "interpreter.hpp"
#include "tokenize.hpp"
#include "interpreter_syntax_error.hpp"

// For debugging
#include <iostream>

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    TokenList tokens = tokenize(expression);
    TokenList tokenscopy = TokenList(tokens);
    try {
        this->ast = constructast(tokens);
        return true;
    } catch(InterpreterSyntaxError & e) {
        return false;
    }
}

void Interpreter::printast(std::ostream & out) {    
    out << this->ast << "\n";
}

Expression Interpreter::eval() {
    return this->ast.eval(this->env);
}
