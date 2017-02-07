#include "environmentprocedures.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include "expression.hpp"


enum Arity {Nullary, Unary, Binary, Ternary, M_ary, Any};

// Throws an error if the number of elements in args doesn't line up with the
// arity
void arity(Arity a, Args args) {
    size_t nargs = args.size();
    if ((a == Nullary && nargs == 0) ||
        (a == Unary && nargs == 1) ||
        (a == Binary && nargs == 2) ||
        (a == Ternary && nargs == 3) ||
        (a == M_ary && nargs >= 2) ||
        (a == Any)) {
        return;
    } else {
        throw InterpreterSemanticError(
            (a == Nullary ? "Error: Expected 0 arguments but got" :
             a == Unary ? "Error: Expected 1 argument but got " :
             a == Binary ? "Error: Expected 2 arguments but got" :
             a == Ternary ? "Error: Expected 3 arguments but got" :
             a == M_ary ? "Error: Expected >= 2 arguments but got" :
             "Error: Expected undefined number of arguments but got ") +
            nargs);
    }
}

Expression NotFn::operator()(Args args, Environment &env) const {
    arity(Unary, args);
    
    return Expression(!args[0].eval(env).getbool());
}

BinaryBoolFn::BinaryBoolFn(std::function<bool(bool,bool)> func) {
    this->func = func;
}

Expression BinaryBoolFn::operator()(Args args, Environment &env) const {
    arity(M_ary, args);
    bool res = args[0].eval(env).getbool();
    for(size_t i = 1; i < args.size(); i++) {
        res = this->func(res, args[i].eval(env).getbool());
    }
    return Expression(res);
}

CmpFn::CmpFn(std::function<bool(float,float)> func) {
    this->func = func;
}

Expression CmpFn::operator()(Args args, Environment &env) const {
    arity(Binary, args);
    return Expression(this->func(args[0].eval(env).getnumber(),
                                 args[1].eval(env).getnumber()));
}


PlusMulFn::PlusMulFn(std::function<float(float,float)> func) {
    this->func = func;
}

Expression PlusMulFn::operator()(Args args, Environment &env) const {
    arity(M_ary, args);
    double res = args[0].eval(env).getnumber();
    for(size_t i = 1; i < args.size(); i++) {
        res = this->func(res, args[i].eval(env).getnumber());
    }
    return Expression(res);
}

Expression SubFn::operator()(Args args, Environment &env) const {
    if (args.size() == 1) {// Instead this should be the negative operator
        return Expression(-1 * args[0].eval(env).getnumber());
    }
    arity(Binary, args);
    return Expression(args[0].eval(env).getnumber() -
                      args[1].eval(env).getnumber());
}

Expression DivFn::operator()(Args args, Environment &env) const {
    if (args.size() == 1) {// Instead this should be the negative operator
        return Expression(-1 * args[0].eval(env).getnumber());
    }
    arity(Binary, args);
    return Expression(args[0].eval(env).getnumber() /
                      args[1].eval(env).getnumber());
}

Expression DefineFn::operator()(Args args, Environment &env) const {
    arity(Binary, args);
    Expression res = args[1].eval(env);
    env.define(args[0].getsymbol(), res); // Don't evaluate
    return res;
}

Expression BeginFn::operator()(Args args, Environment &env) const {
    Expression result;
    for(auto const &arg: args) {
        result = arg.eval(env);
    }
    return result;
}

Expression IfFn::operator()(Args args, Environment &env) const {
    arity(Ternary, args);
    return args[0].eval(env).getbool() ?
        args[1].eval(env) : args[2].eval(env);
}
