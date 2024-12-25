#include "../include/parser.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> variables;

void handleImport(const Cargo::Token &token)
{
    std::ifstream file(token.value + ".cargo");
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Could not import file: " + token.value);
    }

    std::string source_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    auto tokens = Cargo::tokenize(source_code);
    Cargo::parse(tokens);
}

void handlePrint(const std::vector<Cargo::Token> &tokens, size_t &index)
{
    if (index + 1 < tokens.size() && tokens[index + 1].type == "STRING")
    {
        std::cout << tokens[index + 1].value.substr(1, tokens[index + 1].value.size() - 2) << std::endl;
        index++;
    }
    else if (index + 1 < tokens.size() && tokens[index + 1].type == "IDENTIFIER")
    {
        const auto &var = tokens[index + 1].value;
        if (variables.find(var) != variables.end())
        {
            std::cout << variables[var] << std::endl;
        }
        else
        {
            throw std::runtime_error("Error: Undefined variable: " + var);
        }
        index++;
    }
    else
    {
        throw std::runtime_error("Error: Invalid syntax in print statement.");
    }
}

namespace Cargo
{
    void parse(const std::vector<Token> &tokens)
    {
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            if (tokens[i].type == "KEYWORD" && tokens[i].value == "const")
            {
                if (i + 2 < tokens.size() && tokens[i + 1].type == "IDENTIFIER" && tokens[i + 2].type == "STRING")
                {
                    variables[tokens[i + 1].value] = tokens[i + 2].value.substr(1, tokens[i + 2].value.size() - 2);
                    i += 2;
                }
                else
                {
                    throw std::runtime_error("Error: Invalid const declaration.");
                }
            }
            else if (tokens[i].type == "KEYWORD" && tokens[i].value == "import")
            {
                if (i + 1 < tokens.size() && tokens[i + 1].type == "IDENTIFIER")
                {
                    handleImport(tokens[i + 1]);
                    i++;
                }
                else
                {
                    throw std::runtime_error("Error: Invalid import statement.");
                }
            }
            else if (tokens[i].type == "FUNCTION" && tokens[i].value == "print")
            {
                handlePrint(tokens, i);
            }
        }
    }
}