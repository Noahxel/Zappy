/*
** EPITECH PROJECT, 2023
** MyCpp
** File description:
** MyCppLib
*/

#pragma once
    #include <vector>
    #include <string>
    #include <iostream>

namespace MyCppLib {
    std::vector<std::string> splitString(std::string input, char delimiter);
    std::string removeUselessSpaces(std::string);
    std::vector<std::string> removeUselessSpacesFromArray(std::vector<std::string> input);
    std::string removeCharFromStr(std::string input, char unwanted);
    bool isStringDigits(std::string str);
};
