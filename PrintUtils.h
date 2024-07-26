#ifndef _PRINT_UTILS_H_
#define _PRINT_UTILS_H_

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>

class PrintUtils{
    public:
        void print(std::string string2Print);
        void print(std::vector<std::string> vector2Print);
        void print(int int2Print);
        void print(std::vector<int> vector2Print);
        void print(double dbl2Print);
        void print(std::vector<double> vector2Print);
        void print(std::filesystem::path singlePath);
        void print(std::vector<std::filesystem::path> vecPaths);
        void print(std::tuple<bool, std::string> tup2print);
        PrintUtils();
};

#endif