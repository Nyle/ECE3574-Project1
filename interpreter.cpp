#include "interpreter.hpp"
#include "tokenize.hpp"
#include "interpreter_syntax_error.hpp"

// For debugging
#include <iostream>

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    this->parsingerror = "";
    try {
        TokenList tokens = tokenize(expression);
        if (tokens.size() == 0) {
            this->parsingerror = "Error: program can not be blank";
        }else if (tokens.front() != "(") {
            this->parsingerror = "Error: program must start with '('";
        } else {
            this->ast = constructast(tokens);
            if (tokens.size() != 0) {
                this->parsingerror = "Error: Extra Input";
            }
        }
    } catch(InterpreterSyntaxError & e) {
        this->parsingerror = e.what();
    }
    return this->parsingerror.size();
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
