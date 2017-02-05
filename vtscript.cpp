#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter.hpp"

#include <functional>

int main(int argc, char * argv[]) {
    Interpreter interp = Interpreter();
    std::ifstream in(argv[1]);
    if (!interp.parse(in)) {
        std::cout << "There was an error in parsing\n";
        return EXIT_FAILURE;
    }
    std::cout << interp.eval() << "\n";

    return EXIT_SUCCESS;
}
