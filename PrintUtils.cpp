#include "PrintUtils.h"

PrintUtils::PrintUtils()
{};

void PrintUtils::print(std::string string2Print){
    std::cout << string2Print << std::endl;
}

void PrintUtils::print(std::vector<std::string> vector2Print){
    for (size_t i{0}; i < vector2Print.size(); i++){
        print(vector2Print.at(i));
    }
}

void PrintUtils::print(int int2Print){
    std::cout << int2Print << std::endl;
}

void PrintUtils::print(std::vector<int> vector2Print){
    for (size_t i{0}; i < vector2Print.size(); i++){
        print(vector2Print.at(i));
    }
}

void PrintUtils::print(double dbl2Print){
    std::cout << dbl2Print << std::endl;
}

void PrintUtils::print(std::vector<double> vector2Print){
    for (size_t i{0}; i < vector2Print.size(); i++){
        print(vector2Print.at(i));
    }
}

void PrintUtils::print(std::filesystem::path singlePath){
    std::cout << singlePath << std::endl;
}

void PrintUtils::print(std::vector<std::filesystem::path> vecPaths){
    for (size_t i{0}; i<vecPaths.size(); i++) {
        print(vecPaths.at(i));
    }
}

void PrintUtils::print(std::tuple<bool, std::string> tup2print){
    std::cout << std::get<bool>(tup2print) << std::endl;
    std::cout << std::get<std::string>(tup2print) << std::endl;
}