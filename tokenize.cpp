#include "tokenize.hpp"
#include "expression.hpp"

#include <ctype.h>

// For debugging
#include <iostream>

// Constants for special characters
const char OPEN = '(';
const char CLOSE = ')';
const char COMMENT = ';';
// Token constants
const Token OPEN_TOKEN = Token(1, OPEN);
const Token CLOSE_TOKEN = Token(1, CLOSE);
const Token TRUE = "True";
const Token FALSE = "False";

// Whether or not c is a character that will end any preceding symbol
bool breakssymbols(char c) {
    return c == OPEN || c == CLOSE || c == COMMENT || isspace(c) || !isprint(c);
}

TokenList tokenize(std::istream & in) {
    TokenList tokens; // List of tokens found
    Token symbol = "";               // Hold multi-character symbols
    for (char tmp = in.get(); !in.eof(); tmp = in.get()) {
        if (breakssymbols(tmp)) {
            if (symbol.length() > 0) {
                tokens.push(symbol);
                symbol = "";
            }

            if (tmp == COMMENT) {
                // Read to the end of the comment
                while ((tmp = in.get()) != '\n' && !in.eof()) {}
            } else if (tmp == OPEN || tmp == CLOSE) {
                tokens.push(Token(1, tmp));
            }
        } else {
            symbol.push_back(tmp);
        }
    }

    if (symbol.length() > 0) {
        tokens.push(symbol);
    }
    
    return tokens;
}

// Converts a token to an expression
Expression tokentoexpression(Token token) {
    if (token == CLOSE_TOKEN) { return Expression(); }
    if (token == TRUE) { return Expression(true); }
    if (token == FALSE) { return Expression(false); }
    try {
        double value = stod(token);
        return Expression(value);
    } catch (std::invalid_argument & e){
        return Expression(token);
    }
}

Expression constructast(TokenList & tokens) {
    if (tokens.front() == OPEN_TOKEN) { // It's a parenthesized expression
        tokens.pop(); // remove the OPEN_TOKEN
        Expression result = constructast(tokens); // Get attom
        while(tokens.front() != CLOSE_TOKEN) {// TODO: handle malformed input
            result.addargument(constructast(tokens)); //get arguments
        }
        tokens.pop(); // Remove the CLOSE_TOKEN
        return result;
    }
    Expression result = tokentoexpression(tokens.front());
    tokens.pop(); // Remove the just processed token
    return result;
}
