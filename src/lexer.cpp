#include <cctype>
#include <iostream>
#include "../include/lexer.h"

namespace Cargo
{
    std::vector<Token> tokenize(const std::string &source)
    {
        std::vector<Token> tokens;
        size_t i = 0;

        while (i < source.size())
        {
            if (std::isspace(source[i]))
            {
                i++;
                continue;
            }
            if (std::isalpha(source[i]))
            {
                size_t start = i;
                while (i < source.size() && (std::isalnum(source[i]) || source[i] == '_'))
                    i++;
                std::string word = source.substr(start, i - start);
                if (word == "let")
                    tokens.push_back({"KEYWORD", word});
                else if (word == "print")
                    tokens.push_back({"KEYWORD", word});
                else
                    tokens.push_back({"IDENTIFIER", word});
            }
            else if (source[i] == '@')
            {
                i++;
                if (source.substr(i, 6) == "import")
                {
                    i += 6;
                    tokens.push_back({"IMPORT", "@import"});
                }
            }
            else if (source[i] == '"')
            {
                size_t start = ++i;
                while (i < source.size() && source[i] != '"')
                    i++;
                if (i >= source.size())
                {
                    std::cerr << "Unterminated string literal" << std::endl;
                    exit(1);
                }
                tokens.push_back({"STRING", source.substr(start, i - start)});
                i++;
            }
            else if (std::isdigit(source[i]))
            {
                size_t start = i;
                while (i < source.size() && std::isdigit(source[i]))
                    i++;
                tokens.push_back({"NUMBER", source.substr(start, i - start)});
            }
            else if (source[i] == '=')
            {
                tokens.push_back({"EQUAL", "="});
                i++;
            }
            else if (source[i] == '+')
            {
                tokens.push_back({"PLUS", "+"});
                i++;
            }
            else if (source[i] == ';')
            {
                tokens.push_back({"SEMICOLON", ";"});
                i++;
            }
            else
            {
                std::cerr << "Unknown character: " << source[i] << std::endl;
                exit(1);
            }
        }

        return tokens;
    }
}