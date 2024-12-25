#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"

namespace Cargo
{
    void parse(const std::vector<Token> &tokens);
}

#endif
