#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

namespace Cargo {
    struct Token {
        std::string type;
        std::string value;
    };

    std::vector<Token> tokenize(const std::string& source);
}

#endif // LEXER_H