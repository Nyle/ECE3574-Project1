#include "expression.hpp"

Expression::Expression() {
    this->type = None;
}

Expression::Expression(bool value) {
    this->type = Bool;
    this->b = value;
}

Expression::Expression(double value) {
    this->type = Double;
    this->d = value;
}

Expression::Expression(const std::string & value) {
    this->type = String;
    this->s = value;
}

bool Expression::operator==(const Expression & exp) const noexcept {
    if (exp.type != this->type) { return false; }
    switch (this->type) {
    case None:
        return true;
        break;
    case Bool:
        return this->b == exp.b;
        break;
    case Double:
        return this->d == exp.d;
        break;
    case String:
        return this->s == exp.s;
        break;
    }
}
