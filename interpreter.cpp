#include "interpreter.hpp"
#include "tokenize.hpp"

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    this->ast = constructast(tokenize(expression));
    return this->ast.gettype() != None;
}

Expression Interpreter::eval(Expression exp, Environment & env) {
    if (exp.gettype() != Symbol) { return exp; }
    Args args = exp.getargs();
    for (size_t i = 0; i < args.size(); i++) {
        args[i] = eval(args[i], env);
    }
    std::string symbol = exp.getsymbol();
    return env.retrieve(symbol)(args, env);
}

Expression Interpreter::eval() {
    return eval(this->ast, this->env);
}
