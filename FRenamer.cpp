#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include "FRenamer.h"

FRenamer::FRenamer()
    :oldNames{}, newNames{}, nameToUse{}
{}

FRenamer::FRenamer(std::vector<std::filesystem::path> old) 
    :oldNames{old}, newNames{}, nameToUse{}
{}

void FRenamer::setOldNames(std::vector<std::filesystem::path> old) {
    oldNames = old;
}

void FRenamer::initiateNewNames(){
    std::vector<std::filesystem::path> tempNew;
    tempNew.reserve(oldNames.size());
}

std::vector<std::string> FRenamer::extractNums(std::string str){
    std::vector<std::string> extractedNums;
    std::regex numPattern ("\\d+");
    std::regex_token_iterator<std::string::iterator> strEnd;
    std::regex_token_iterator<std::string::iterator> regexParser {str.begin(), str.end(), numPattern};
    while (regexParser != strEnd){
        extractedNums.push_back(*regexParser++);
    }
    return extractedNums;
}

int FRenamer::extractAmtNumInName(std::string str){
    std::vector<std::string> nums = extractNums(str);
    return {static_cast<int>(nums.size())};
}

std::vector<std::string> FRenamer::readAlias(std::string txtPath){
    std::ifstream fileIn (txtPath);
    std::vector<std::string> contents;
    std::string line;
    while (std::getline (fileIn, line)){
        std::istringstream ss(line);
        std::string tempStr;
        while(ss >> tempStr){
            contents.push_back(tempStr);
        }
    }
    fileIn.close();
    return contents;
}

std::tuple<bool, std::string> FRenamer::isNameInFileName(std::vector<std::string> aliasTxt, std::string filePath){
    bool matchFound {false};
    std::string name2Use {};
    for (size_t i{0}; i < aliasTxt.size(); i++){
        name2Use = aliasTxt.at(i);
        std::regex namePattern (name2Use);
        matchFound = std::regex_search(filePath, namePattern);
        if (matchFound){
            return {matchFound, name2Use};
        }
    }
    return { false, "" };
}

std::tuple<bool, std::string> FRenamer::isNameInFileName(std::vector<std::string> aliasTxt, std::filesystem::path filePath){
    return { isNameInFileName(aliasTxt, filePath.string()) };
}

std::string FRenamer::detectNameFormat(std::filesystem::path filePath){
    std::string fileName { filePath.stem().string() };
    std::string fileExt { filePath.extension().string() };

    std::vector<std::string> listOfMonths = {"January", "February", "March", "April", "May", "June", 
    "July", "August", "September", "October", "November", "December"};

    return {" "};
}


// std::vector<std::string> FRenamer::extractDateString(std::string name, std::string str){
//     int nNumsInName = extractAmtNumInName(name);
//     std::vector<std::string> nums = extractNums(str);
//     if (nNumsInName > 0){
//         nums.erase(nums.begin(), nums.begin()+nNumsInName);
//     }
//     for (size_t i{0}; i < nums.size(); i++){
//         int finalNumElem {0};
//         if (nums.at(i).size() > 4){
//             std::string tempNumStr {nums.at(i)};
//             double numElems = static_cast<double>(nums.at(i).size());
//             double postDivide = numElems/2;
//             finalNumElem = std::ceil(postDivide);
//             for (size_t ii {0}; i < finalNumElem; i++){
                
//             }

//         }
        
//     }
//     return {nums};
// }







std::vector<std::string> FRenamer::splitNumStr(std::string numStr){
    double numElemsStr = static_cast<double>(numStr.size());
    double postDivide = numElemsStr/2;
    int numElemsVec = std::ceil(postDivide);

    return {"tets"};
}
