#include "tokenize.hpp"
#include <ctype.h>

std::vector<std::string> tokenize(std::istream & in) {
    std::vector<std::string> tokens; // List of tokens found
    
    std::string symbol = "";    // Hold multi-character symbols
    for (char tmp = in.get(); !in.eof(); tmp = in.get()) {
        if ((tmp == '(' || tmp == ')' || isspace(tmp)) && symbol.length() > 0) {
            // tmp is a divider of symbols. If we have constructed a symbol
            // push it as the next token
            tokens.push_back(symbol);
            symbol = "";
            if (tmp == '(' || tmp == ')') {
                // If we are on a paren, push it too as the next token
                std::string conv(1, tmp);
                tokens.push_back(conv);
            }
        } else {
            // Otherwise continue building the symbol
            symbol.push_back(tmp);
        }
    }
    
    return tokens;
}
