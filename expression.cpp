#include "expression.hpp"
#include <iostream>

Expression::Expression() {
    this->type = None;
    this->arguments = Args();
}

Expression::Expression(bool value) {
    this->type = Bool;
    this->b = value;
    this->arguments = Args();
}

Expression::Expression(double value) {
    this->type = Number;
    this->d = value;
    this->arguments = Args();
}

Expression::Expression(const std::string & value) {
    this->type = Symbol;
    this->s = value.c_str();
    this->arguments = Args();
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
    // TODO: Error if this isn't a symbol
    return std::string(this->s);
}

double Expression::getnumber() const {
    return this->d;
}

bool Expression::getbool() const {
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

std::ostream& operator<<(std::ostream &strm, const Expression &exp) {
    switch (exp.gettype()) {
    case None:
        return strm << "(None)";
        break;
    case Bool:
        return strm << (exp.getbool() ? "(True)" : "(False)");
        break;
    case Number:
        return strm << "(" << exp.getnumber() << ")";
        break;
    case Symbol:
        return strm << "(" << exp.getsymbol() << ")";
    }
}

