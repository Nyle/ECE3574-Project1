#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <cstdlib>
#include <fstream>
#include "expression.hpp"
#include "environment.hpp"

class Interpreter {
private:
    Expression ast;
    Environment env;
public:
    // Default construct an Interpreter with the default environment and an
    // empty AST
    Interpreter();

    // Given a vtscript program as a std::istream, attempt to parse into an
    // internal AST return true on success, false on failure
    bool parse(std::istream & expression) noexcept;

    // Evaluate the current AST and return the resulting Expression
    // throws InterpreterSemanticError if a semantic error is encountered
    // the exception message string should document the nature of the semantic
    // error 
    Expression eval();

    // Evaluate the given expression with the given envioronment
    Expression eval(Expression exp, Environment & env);
};
    
#endif // INTERPRETER_HPP
