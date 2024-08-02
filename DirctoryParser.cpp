#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "DirectoryParser.hpp"

DirectoryParser::DirectoryParser()
    :directoryContents{}
{}

DirectoryParser::DirectoryParser(std::string)
    :directoryContents{}
{
    int anticipatedDirSize {200};
    directoryContents.reserve(anticipatedDirSize); // pre-allocate memory
}

// Function to check if a string ends with another string 
bool DirectoryParser::endsWith(const std::string& fullString, const std::string& ending) { 
    if (ending.size() > fullString.size()) 
        return false; 
    return fullString.compare(fullString.size() - ending.size(), ending.size(), ending) == 0; 
} 

bool DirectoryParser::endsWith(const std::string& fullString, const std::vector<std::string>& endings) { 
    std::vector<bool> resultsVec;
    for (size_t i {0}; i < endings.size(); i++){
        resultsVec.push_back(endsWith(fullString, endings.at(i)));
    }
    if (std::any_of(resultsVec.begin(), resultsVec.end(), [](bool i){return i == true;})){
        return true;
    } else{
        return false;
    }
} 

void DirectoryParser::parseDirectory(std::filesystem::path pathToDir){
    std::regex aliasPattern {"alias"};
    std::vector<std::string> fileExtToExtract {".mp4", ".jpgeg"};
    for (const auto &entry : std::filesystem::directory_iterator(pathToDir)){
        if (endsWith(entry.path().string(), fileExtToExtract)){
            directoryContents.push_back(entry);
        }
    }
}

void DirectoryParser::print(){
    for (size_t i {0}; i < directoryContents.size(); i++){
        std::cout << directoryContents.at(i).path().string() << std::endl;
    }
}

std::vector<std::filesystem::directory_entry> DirectoryParser::readConfig(std::filesystem::path txtPath){
    std::ifstream fileIn (txtPath);
    std::vector<std::filesystem::directory_entry> contents;
    std::string line;
    while (std::getline (fileIn, line)){
        std::istringstream ss(line);
        std::string tempStr;
        while(ss >> tempStr){
            contents.push_back(std::filesystem::directory_entry(tempStr));
        }
    }
    fileIn.close();
    return contents;
}

std::vector<std::string> DirectoryParser::readConfig(std::string txtPath){
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