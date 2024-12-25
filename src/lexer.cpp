#include "../include/lexer.h"
#include <regex>

namespace Cargo
{

    std::vector<Token> tokenize(const std::string &source)
    {
        std::vector<Token> tokens;
        std::regex token_regex(R"((const)|(import)|(print)|([a-zA-Z_][a-zA-Z0-9_]*)|(\".*?\")|(;)|(\s+))");
        auto words_begin = std::sregex_iterator(source.begin(), source.end(), token_regex);
        auto words_end = std::sregex_iterator();

        for (auto it = words_begin; it != words_end; ++it)
        {
            std::smatch match = *it;
            if (match[1].matched)
                tokens.push_back({"KEYWORD", "const"});
            else if (match[2].matched)
                tokens.push_back({"KEYWORD", "import"});
            else if (match[3].matched)
                tokens.push_back({"FUNCTION", "print"});
            else if (match[4].matched)
                tokens.push_back({"IDENTIFIER", match.str()});
            else if (match[5].matched)
                tokens.push_back({"STRING", match.str()});
            else if (match[6].matched)
                tokens.push_back({"SEMICOLON", ";"});
        }

        return tokens;
    }
}