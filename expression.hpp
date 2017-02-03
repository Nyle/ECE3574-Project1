#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstdlib>
#include <string>
#include <vector>

class Expression;

typedef std::vector<Expression> Args;

enum Type {None, Bool, Number, Symbol};

class Expression {
private:
    // Fields for the attom value
    union {
        bool b;
        double d;
        const char * s;
    };
    // Fields for the type of attom value
    Type type;
    Args arguments;
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

    // Get the type
    Type gettype() const;

    // Returns the symbol
    std::string getsymbol() const;

    // Returns the number
    double getnumber() const;

    // Returns the Boolean
    bool getbool() const;

    // Equality operator for two Expressions, two expressions are equal if the
    // have the same type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;

    // Add an expression as the last argument
    void addargument(Expression exp);

    // Get the arguments
    Args getargs() const;
};

#endif // EXPRESSION_HPP

// Overload of << to allow easy printing
std::ostream& operator<<(std::ostream &strm, const Expression &exp);
