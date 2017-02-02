#include "expression.hpp"

Expression::Expression() {
    this->type = None;
    this->arguments = std::vector<Expression>();
}

Expression::Expression(bool value) {
    this->type = Bool;
    this->b = value;
    this->arguments = std::vector<Expression>();
}

Expression::Expression(double value) {
    this->type = Double;
    this->d = value;
    this->arguments = std::vector<Expression>();
}

Expression::Expression(const std::string & value) {
    this->type = String;
    this->s = value;
    this->arguments = std::vector<Expression>();
}

Expression::Expression(const Expression & exp) {
    this->type = exp.type;
    switch(this->type) {
    case None:
        break;
    case Bool:
        this->b = exp.b;
        break;
    case Double:
        this->d = exp.d;
        break;
    case String:
        this->s = exp.s;
        break;
    }
    this->arguments = std::vector<Expression>(exp.arguments);
}

Expression::~Expression() {
    using std::string;
    if (this->type == String) {
        (&this->s)->string::~string();
    }
}

bool Expression::operator==(const Expression & exp) const noexcept {
    return this->type == exp.type && ( // Same type
        // Same value
        // TODO: two of none type---have same value
        (this->type == Bool && this->b == exp.b) ||
        (this->type == Double && this->d == exp.d) ||
        (this->type == String && this->s == exp.s)) &&
        // Same number of arguments
        this->arguments.size() == exp.arguments.size();
}

void Expression::addargument(Expression & exp) {
    this->arguments.push_back(exp);
}
