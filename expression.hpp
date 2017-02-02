#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstdlib>
#include <string>

class Expression {
private:
    // Field for the value
    union {
        bool b;
        double d;
        std::string s;
    };
    // Field for the type of the value
    enum Type {
        None,
        Bool,
        Double,
        String
    } type;
            
public:

    // Default construct an Expression of type None
    Expression();

    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);

    // Construct an Expression with a single Number atom with value
    Expression(double value);

    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);

    // Equality operator for two Expressions, two expressions are equal if the
    // have the same type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;
};

#endif // EXPRESSION_HPP
