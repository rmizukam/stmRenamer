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

std::vector<std::string> FRenamer::readTxtFile(std::string txtPath){
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

std::vector<std::string> FRenamer::readTxtFile(std::filesystem::path txtPath){
    return {readTxtFile(txtPath.string())};
}

std::tuple<bool, std::string> FRenamer::isNameInFileName(std::vector<std::string> aliasTxt, std::string filePath, std::string userInput){
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
    return { false, userInput };
}

std::tuple<bool, std::string> FRenamer::isNameInFileName(std::vector<std::string> aliasTxt, std::filesystem::path filePath, std::string userInput){
    return { isNameInFileName(aliasTxt, filePath.string(), userInput) };
}

std::string FRenamer::reformatName(std::vector<std::string> aliasTxt, std::filesystem::path filePath, std::string name){
    std::string year {};
    std::string month {};
    std::string day {};
    std::string hour {};
    std::string min {};
    std::string sec {};
    std::string fileName { filePath.stem().string() };
    std::string fileExt { filePath.extension().string() };
    std::tuple nameInFileInfo = isNameInFileName(aliasTxt,filePath, name);
    std::string name2use {std::get<std::string>(nameInFileInfo)};
    int nNumsInName = extractAmtNumInName(name2use);

    std::regex desiredDateFormat {"\\d{4}-\\d{2}-\\d{2}[\\s|_|:]\\d{2}-\\d{2}(-\\d{2})*.*"};
    std::regex year_Month_DD_HH_mm_ss {"\\d{4}-\\w-\\d{2}_\\d{2}-\\d{2}-*\\d{2}*"};
    std::regex MMDDYYYY_combine {"\\d{8}-\\d{2}-\\d{2}-\\d{2}"};
    std::regex HHmmss_combine {"\\d{4}-\\d{2}-\\d{2}_*\\d{6}"};
    std::regex Month_DD_YYYY_HH_mm_ss {"\\w-\\d{2}-\\d{4}_\\d{2}-\\d{2}-*\\d{2}*"};
    std::regex YYYYMMDDHHmm_combine {"\\d{12}"};
    const int MAX_ELEMENTS_IN_DATE {6};
    std::vector<std::string> finalNums {};
    if (std::regex_search(fileName, desiredDateFormat)){
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
        for (size_t i {0}; i < MAX_ELEMENTS_IN_DATE; i++){
            finalNums.push_back(numsInFileName.at(i));
        }
    } else if (std::regex_search(fileName, year_Month_DD_HH_mm_ss)){
        fileName = convertMonthString2MonthIdx(fileName);
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
    } else if (std::regex_search(fileName, MMDDYYYY_combine)){
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
    } else if (std::regex_search(fileName, HHmmss_combine)){
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
    } else if (std::regex_search(fileName, Month_DD_YYYY_HH_mm_ss)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
    } else if (std::regex_search(fileName, YYYYMMDDHHmm_combine)){
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(numsInFileName, nNumsInName);
    }






    
    

}

std::filesystem::path FRenamer::getRepoRoot(){
    std::filesystem::path currentPath {std::filesystem::current_path()};
    return {currentPath};
}

std::vector<std::string> FRenamer::splitNumStr(std::string numStr){
    std::vector<std::string> outVec {};
    for (size_t i{0}; i < numStr.size(); i += 2){
        outVec.push_back(numStr.substr(i, 2));
    }
    return {outVec};
}

std::string FRenamer::getIndex(std::vector<std::string> v, std::string K){
    auto it = find(v.begin(), v.end(), K); 
    int index {};
    // If element was found 
    if (it != v.end())  
    { 
        // calculating the index of K 
        index = it - v.begin(); 
    } 
    else { 
        // If the element is not present in the vector 
        index = -1 ;
    } 
    return { convertNum2Str(index) };
}

std::string FRenamer::convertNum2Str(int num){
    char buffer [5];
    return { std::string(buffer) };
}

bool FRenamer::startsWith(const std::string& fullString, const std::string& beginning) { 
    if (beginning.size() > fullString.size()) 
        return false; 
    return fullString.compare(0, fullString.size() - beginning.size(), beginning) == 0; 
} 

std::string FRenamer::join(std::vector<std::string> stringVec, std::string delimeter){
    std::string outString {};
    for (size_t i{0}; i < stringVec.size(); i++){
        outString.append(stringVec.at(i));
        outString.append(delimeter);
    }
    return {outString};
}

std::string FRenamer::join(std::vector<std::string> stringVec){
    return {join(stringVec, "")};
}

std::string FRenamer::extractExtraInfo(std::string inStr){
    auto found {0};
    found = inStr.find_last_of('_');
    if (found == 0 || found == -1){
        return {""};
    } else{
        return { inStr.substr(found + 1, inStr.size()-found) };
    }
}

std::string FRenamer::convertMonthString2MonthIdx(std::string fName){
    std::filesystem::path repoRoot {getRepoRoot()};
    std::filesystem::path listOfMonthTxt {repoRoot.append("listOfMonths.txt")};
    std::vector<std::string> listOfMonths = readTxtFile(listOfMonthTxt);
    std::vector<std::string> listOfMonthAbreviate = readTxtFile(listOfMonthTxt.replace_filename("listOfMonthsAbreviate.txt"));
    bool matchFound {false};
    bool matchFoundAbr {false};
    for (size_t i{0}; i < listOfMonths.size(); i++){
        std::regex monthPattern (listOfMonths.at(i));
        matchFound = std::regex_search(fName, monthPattern);
        std::regex monthPatternAbr (listOfMonthAbreviate.at(i));
        matchFoundAbr = std::regex_search(fName, monthPatternAbr);
        if (matchFound){
            std::string monthNum {getIndex(listOfMonths, listOfMonths.at(i))};
            std::regex_replace(fName, monthPattern, monthNum);
            break;
        }else if (matchFoundAbr){
            std::string monthNum {getIndex(listOfMonths, listOfMonthAbreviate.at(i))};
            std::regex_replace(fName, monthPatternAbr, monthNum);
            break;
        }
    }
    return {fName};
}


std::vector<std::string> FRenamer::removeNumsInName(std::vector<std::string> numsFromName, int amtNumsInName){
    numsFromName.erase(numsFromName.begin(), numsFromName.begin() + amtNumsInName);
    return {numsFromName};
}


