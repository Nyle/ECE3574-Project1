#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include <iostream>

Expression::Expression() {
    this->type = None;
    this->arguments = Args();
}

Expression::Expression(bool value) : Expression() {
    this->type = Bool;
    this->b = value;
}

Expression::Expression(double value) : Expression() {
    this->type = Number;
    this->d = value;
}

Expression::Expression(const std::string & value) : Expression() {
    this->type = Symbol;
    this->s = value;
}

Expression::Expression(const Expression & exp) {
    this->type = exp.type;
    switch(this->type) {
    case None:
        break;
    case Bool:
        this->b = exp.b;
        break;
    case Number:
        this->d = exp.d;
        break;
    case Symbol:
        this->s = exp.s;
        break;
    }
    this->arguments = Args(exp.arguments);
}

Type Expression::gettype() const {
    return this->type;
}

std::string Expression::getsymbol() const {
    if (this->type != Symbol) {
        throw InterpreterSemanticError(
            "Error: expected expression to be of type Symbol");
    }
    return this->s;
}

double Expression::getnumber() const {
    if (this->type != Number) {
        throw InterpreterSemanticError(
            "Error: expected expression to be of type Number");
    }
    return this->d;
}

bool Expression::getbool() const {
    if (this->type != Bool) {
        throw InterpreterSemanticError(
            "Error: expected expression to be of type Bool");
    }
    return this->b;
}

bool Expression::operator==(const Expression & exp) const noexcept {
    return this->type == exp.type && ( // Same type
        // Same value
        this->type == None ||
        (this->type == Bool && this->b == exp.b) ||
        (this->type == Number && this->d == exp.d) ||
        (this->type == Symbol && this->s == exp.s)) &&
        // Same number of arguments
        this->arguments.size() == exp.arguments.size();
}

void Expression::addargument(Expression exp) {
    // TODO: This shouldn't be happening if the type is not symbol
    this->arguments.push_back(exp);
}

Args Expression::getargs() const {
    return this->arguments;
}

Expression Expression::eval(Environment & env) const {
    if (this->type != Symbol) {
        return *this;
    }
    return env.retrieve(this->s)(this->arguments, env);
}

std::ostream& operator<<(std::ostream &strm, const Expression &exp) {
    // Output opening parenthesis
    strm << "(";
    // Output closing parenthesis
    switch (exp.gettype()) {
    case None:
        strm << "(None)";
        break;
    case Bool:
        strm << (exp.getbool() ? "True" : "False");
        break;
    case Number:
        strm << exp.getnumber();
        break;
    case Symbol:
        strm << exp.getsymbol();
    }
    // Output each argument
    for (const auto &arg: exp.getargs()) {
        strm << arg;
    }
    
    strm << ")";
    // Output attom
    return strm;
}
