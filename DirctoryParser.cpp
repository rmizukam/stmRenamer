#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "DirectoryParser.hpp"

DirectoryParser::DirectoryParser() 
    :directoryContents{}, directoryLocation{}
{}

void DirectoryParser::setDirectoryLocation(std::string folderName){
    bool dirNotFound {true};
    while (dirNotFound){
        std::tuple<bool,std::filesystem::directory_entry> dirExistsInfo = directoryExists(folderName);
        if (std::get<bool>(dirExistsInfo)){
            dirNotFound = false;
            directoryLocation = std::get<std::filesystem::directory_entry>(dirExistsInfo);
        } else {
            std::cout << "Directory Not Found. Please Try again: ";
            std::cin >> folderName;
        }
    }
}

std::tuple<bool, std::filesystem::directory_entry> DirectoryParser::directoryExists(std::string folderName){
    std::filesystem::path configPath = getRepoRoot();
    configPath/="baseDirs.txt";
    std::vector<std::filesystem::directory_entry> baseDirs {readConfig(configPath)};
    std::filesystem::path pathToFolder {};
    std::filesystem::path userPath {};
    bool dirExists {false};
    for (auto path:baseDirs) {
        userPath = path.path() / std::filesystem::path(folderName);
        if(std::filesystem::directory_entry(userPath).exists()){
            int anticipatedDirSize {200};
            directoryContents.reserve(anticipatedDirSize); // pre-allocate memory
            dirExists = true;
            break;
        }
    }
    if (!dirExists){
        userPath = "";
    }
    return {dirExists, std::filesystem::directory_entry(userPath)};
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

std::filesystem::path DirectoryParser::getRepoRoot(){
    std::filesystem::path currentPath {std::filesystem::current_path()};
    return {currentPath};
}

void DirectoryParser::parseDirectory(std::filesystem::path pathToDir){
    for (const auto &entry : std::filesystem::directory_iterator(pathToDir)){
        directoryContents.push_back(entry);
    }
}

void DirectoryParser::parseDirectory(std::string pathToDirString) {
    std::filesystem::path pathToDir {std::filesystem::path(pathToDirString)};
    parseDirectory(pathToDir);
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
        std::filesystem::directory_entry tempDirEntry {line};
        contents.push_back(tempDirEntry);
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

bool DirectoryParser::startsWith(const std::string& fullString, const std::string& beginning) { 
    if (beginning.size() > fullString.size()) 
        return false; 
    return fullString.compare(0, fullString.size() - beginning.size(), beginning) == 0; 
} 