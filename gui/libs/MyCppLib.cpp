/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** MyCppLib
*/

#include "MyCppLib.hpp"

namespace MyCppLib {
    std::vector<std::string> splitString(std::string input, char delimiter)
    {
        std::vector<std::string> output;
        std::size_t start = 0;
        std::size_t end = 0;

        if (input.find(delimiter) == std::string::npos) {
            output.push_back(input);
            return (output);
        }

        while ((end = input.find(delimiter, start)) != std::string::npos) {
            output.push_back(input.substr(start, end - start));
            start = end + 1;
        }
        output.push_back(input.substr(start));
        return output;
    }

    std::string removeUselessSpaces(std::string input)
    {
        std::string output;
        std::size_t firstNonSpaceCharId = 0;
        std::size_t lastNonSpaceCharId = input.size();

        for (; input[firstNonSpaceCharId] && input[firstNonSpaceCharId] == ' '; firstNonSpaceCharId++)
        for (; input[lastNonSpaceCharId] && input[lastNonSpaceCharId] == ' '; lastNonSpaceCharId--);

        for (std::size_t i = firstNonSpaceCharId; i < lastNonSpaceCharId; i++)
            output.push_back(input[i]);

        return output;
    }

    std::string removeCharFromStr(std::string input, char unwanted)
    {
        std::string output;
        std::size_t inputSize = input.size();

        for (std::size_t i = 0; i < inputSize; i++) {
            if (input[i] == unwanted)
                continue;
            output.push_back(input[i]);
        }
        return output;
    }

    std::vector<std::string> removeUselessSpacesFromArray(std::vector<std::string> input)
    {
        std::vector<std::string> output;
        std::size_t inputSize = input.size(); 

        for (std::size_t i = 0; i < inputSize; i++) {
            output.push_back(removeUselessSpaces(input[i]));
        }

        return output;
    }

    bool isStringDigits(std::string str)
    {
        std::size_t strSize = str.size();

        for (std::size_t i = 0; i < strSize; i++) {
            if (!std::isdigit(str[i]))
                return false;
        }
        return true;
    }
}
