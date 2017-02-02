#include "tokenize.hpp"
#include <ctype.h>

// Constants for special characters
const char OPEN = '(';
const char CLOSE = ')';
const char COMMENT = ';';
// Token constants
const std::string OPEN_TOKEN = std::string(1, OPEN);
const std::string CLOSE_TOKEN = std::string(1, CLOSE);
const std::string TRUE = "True";
const std::string FALSE = "False";

// Whether or not c is a character that will end any preceding symbol
bool breakssymbols(char c) {
    return c == OPEN || c == CLOSE || c == COMMENT || isspace(c);
}

std::vector<std::string> tokenize(std::istream & in) {
    std::vector<std::string> tokens; // List of tokens found
    bool incomment = false;          // If we are in a comment
    std::string symbol = "";         // Hold multi-character symbols
    for (char tmp = in.get(); !in.eof(); tmp = in.get()) {
        if (incomment) {
            if (tmp == '\n') {
                incomment = false;
            }
            continue;
        }

        if (!isprint(tmp)) { continue; }

        if (breakssymbols(tmp) && symbol.length() > 0) {
            tokens.push_back(symbol);
            symbol = "";
        }

        if (tmp == COMMENT){
            incomment = true;
        } else if (tmp == OPEN || tmp == CLOSE) {
            tokens.push_back(std::string(1, tmp));
        } else if (!breakssymbols(tmp)) {
            symbol.push_back(tmp);
        }
    }
    
    return tokens;
}

// Converts a token to an expression
Expression tokentoexpression(std::string token) {
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

// Pull out the next expression 
Expression extractexpression(std::vector<std::string> tokens, size_t & idx) {
    if (tokens[idx] == OPEN_TOKEN) { // It's a parenthesized expression
        // Make an expression with the first value after the open paren
        // as its attom
        Expression result = extractexpression(tokens, ++idx);
        while(tokens[idx++] != CLOSE_TOKEN) {// TODO: handle malformed input
            result.addargument(extractexpression(tokens, idx));
        }
        idx++; // move past the close token
        return result;
    }
    return tokentoexpression(tokens[idx++]);
}

Expression constructast(std::vector<std::string> tokens) {
    size_t idx = 0;
    return extractexpression(tokens, idx);
}
