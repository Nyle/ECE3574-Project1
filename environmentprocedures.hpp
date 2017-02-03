#ifndef ENVIRONMENTPROCDURES_HPP
#define ENVIRONMENTPROCDURES_HPP

#include <functional>
#include "expression.hpp"

enum Arity {Nullary, Unary, Binary, Ternary, M_ary, Any};

void arity(Arity a, Args args);
void type(Type t, Args args, bool onlyfirst=false);

class Environment;

// Functions to be stored in the environment
typedef std::function<Expression(std::vector<Expression>,
                                 Environment &env)> EnvFunc;

struct NotFn {
    Expression operator()(Args args, Environment &env) const;
};

struct BinaryBoolFn {
private:
    std::function<bool(bool,bool)> func;
public:
    BinaryBoolFn(std::function<bool(bool,bool)> func);
    Expression operator()(Args args, Environment &env) const;
};

struct CmpFn {
private:
    std::function<bool(float,float)> func;
public:
    CmpFn(std::function<bool(float,float)>);
    Expression operator()(Args args, Environment &env) const;
};

struct PlusMulFn {
private:
    std::function<float(float,float)> func;
public:
    PlusMulFn(std::function<float(float,float)>);
    Expression operator()(Args args, Environment &env) const;
};

struct SubFn {
    Expression operator()(Args args, Environment &env) const;
};

struct DivFn {
    Expression operator()(Args args, Environment &env) const;
};

struct DefineFn {
    Expression operator()(Args args, Environment &env) const;
};

struct BeginFn {
    Expression operator()(Args args, Environment &env) const;
};

struct IfFn {
    Expression operator()(Args args, Environment &env) const;
};

#endif // ENVIRONMENTPROCDURES_HPP
