#include <iostream>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/utils.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    try {
        std::string source_code = Cargo::ReadFile(argv[1]);
        auto tokens = Cargo::tokenize(source_code);
        Cargo::parse(tokens);
        //std::cout << "Parsing completed successfully!" << std::endl;
    }     catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}