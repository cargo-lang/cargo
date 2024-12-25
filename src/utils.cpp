#include <fstream>
#include "../include/utils.h"

namespace Cargo
{
    std::string ReadFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Error: Unable to open file: " + filename);
        }

        std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return code;
    }
}