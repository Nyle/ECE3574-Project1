#include "interpreter.hpp"
#include "tokenize.hpp"
#include "interpreter_syntax_error.hpp"

// For debugging
#include <iostream>

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    try {
        TokenList tokens = tokenize(expression);
        this->ast = constructast(tokens);
        if (tokens.size() != 0) {
            this->parsingerror = "Error: Extra Input";
            return false;
        }
        return true;
    } catch(InterpreterSyntaxError & e) {
        this->parsingerror = e.what();
        return false;
    }
}

std::string Interpreter::getparsingerror() const {
    return this->parsingerror;
}

void Interpreter::printast(std::ostream & out) {    
    out << this->ast << "\n";
}

Expression Interpreter::eval() {
    return this->ast.eval(this->env);
}
