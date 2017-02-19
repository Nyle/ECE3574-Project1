#include "catch.hpp"

#include <string>
#include <sstream>

#include "expression.hpp"
#include "tokenize.hpp"
#include "interpreter_syntax_error.hpp"

Expression s_to_ast(std::string prog) {
    std::stringstream iss(prog);
    TokenList tokenlist = tokenize(iss);
    return constructast(tokenlist);
}

TEST_CASE("Test parsing program with comment", "[tokenize]") {
    REQUIRE_NOTHROW(s_to_ast("(define ; this is a comment\nr 10)"));
}

TEST_CASE("Test parsing program with different truncations", "[tokenize]") {
    REQUIRE_THROWS_AS(s_to_ast("("), InterpreterSyntaxError);
    REQUIRE_THROWS_AS(s_to_ast("(+"), InterpreterSyntaxError);
    REQUIRE_THROWS_AS(s_to_ast("(+ 5"), InterpreterSyntaxError);
    REQUIRE_THROWS_AS(s_to_ast("(+ (- 5 2) (/ 4 2)"), InterpreterSyntaxError);
}
