#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstdlib>
#include <string>
#include <vector>


class Expression {
private:
    // Fields for the attom value
    union {
        bool b;
        double d;
        const char * s;
    };
    // Fields for the type of attom value
    enum Type {None, Bool, Double, String} type;
    std::vector<Expression> arguments;
public:

    // Default construct an Expression of type None; for cases with errors
    Expression();

    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);

    // Construct an Expression with a single Number atom with value
    Expression(double value);

    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);

    // Copy constructor
    Expression(const Expression & exp);

    // Equality operator for two Expressions, two expressions are equal if the
    // have the same type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;

    // Add an expression as the last argument
    void addargument(Expression exp);
};

#endif // EXPRESSION_HPP
