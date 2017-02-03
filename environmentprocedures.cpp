#include "environmentprocedures.hpp"
#include "environment.hpp"


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
        // TODO: Throw an error
    }
}

void type(Type t, Args args, bool onlyfirst) {
    if (onlyfirst) {
        if (args[0].gettype() != t) {
            // TODO: Throw an error
        }
        return;
    }
    for(auto const &arg: args) {
        if (arg.gettype() != t) {
            // TODO: Throw an error
        }
    }
}

Expression NotFn::operator()(Args args, Environment &env) const {
    arity(Unary, args);
    type(Bool, args);
    
    return Expression(!args[0].getbool());
}

BinaryBoolFn::BinaryBoolFn(std::function<bool(bool,bool)> func) {
    this->func = func;
}

Expression BinaryBoolFn::operator()(Args args, Environment &env) const {
    arity(M_ary, args);
    type(Bool, args);
    bool res = args[0].getbool();
    for(size_t i = 1; i < args.size(); i++) {
        res = this->func(res, args[i].getbool());
    }
    return Expression(res);
}

CmpFn::CmpFn(std::function<bool(float,float)>) {
    this->func = func;
}

Expression CmpFn::operator()(Args args, Environment &env) const {
    arity(Binary, args);
    type(Number, args);
    return Expression(this->func(args[0].getnumber(), args[1].getnumber()));
}


PlusMulFn::PlusMulFn(std::function<float(float,float)>) {
    this->func = func;
}

Expression PlusMulFn::operator()(Args args, Environment &env) const {
    arity(M_ary, args);
    type(Number, args);
    double res = args[0].getnumber();
    for(size_t i = 1; i < args.size(); i++) {
        res = this->func(res, args[i].getnumber());
    }
    return Expression(res);
}

Expression SubFn::operator()(Args args, Environment &env) const {
    if (args.size() == 1) {// Instead this should be the negative operator
        type(Number, args);
        return Expression(-1 * args[0].getnumber());
    }
    arity(Binary, args);
    type(Number, args);
    return Expression(args[0].getnumber() - args[1].getnumber());
}

Expression DivFn::operator()(Args args, Environment &env) const {
    if (args.size() == 1) {// Instead this should be the negative operator
        type(Number, args);
        return Expression(-1 * args[0].getnumber());
    }
    arity(Binary, args);
    type(Number, args);
    return Expression(args[0].getnumber() / args[1].getnumber());
}

Expression DefineFn::operator()(Args args, Environment &env) const {
    arity(Binary, args);
    type(Symbol, args, true);
    if (env.define(args[0].getsymbol(), args[1])) {
        return args[1]; // TODO: figure out what to actually return here
    } else {
        return Expression();
        // TODO: throw an error
    }
}

Expression BeginFn::operator()(Args args, Environment &env) const {
    return args[args.size() - 1];
}

Expression IfFn::operator()(Args args, Environment &env) const {
    arity(Ternary, args);
    type(Bool, args, true);
    return args[0].getbool() ? args[1] : args[2];
}
