#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter.hpp"

int main(int argc, char * argv[]) {
    Interpreter interp = Interpreter();
    std::ifstream in(argv[1]);
    interp.parse(in);
    std::cout << interp.eval() << '\n';

    return EXIT_SUCCESS;
}
