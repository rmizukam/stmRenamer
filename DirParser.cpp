#include <iostream>
#include <regex>
#include <stdexcept>
#include "DirParser.h"


DirParser::DirParser()
    :userInput{}, aliasPath{}, name{}, dirPath{}, directoryContents{}, 
    renamerObj()
{
    int anticipatedNumElem {150};
    directoryContents.reserve(anticipatedNumElem); // allocating space for anticipatedNumElem elements in vector
}

// Function to check if a string ends with another string 
bool DirParser::endsWith(const std::string& fullString, const std::string& ending) { 
    if (ending.size() > fullString.size()) 
        return false; 
    return fullString.compare(fullString.size() - ending.size(), ending.size(), ending) == 0; 
} 

bool DirParser::endsWith(const std::string& fullString, const std::vector<std::string>& endings){
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

// have user input the name of the folder to be parsed
void DirParser::getUserInput(){
    bool searchingForDir {true};
    do {
        std::cout << "Input Name: ";
        std::cin >> userInput;
        std::cout << std::endl;
        makeDirName();
        if (dirPath.empty()){
            std::cout << "\"" << userInput << "\" Not Found.\nCheck spelling and try again." << std::endl;
        } else{
            searchingForDir = false;
        }
    } while (searchingForDir);

    parseDir(dirPath);
}

// construct the Directory name 
void DirParser::makeDirName(){
    std::filesystem::path tempPath {baseDir};
    if (std::filesystem::directory_entry(tempPath.append(userInput)).exists()){
        dirPath = tempPath;
    } else if (std::filesystem::directory_entry(tempPath.replace_filename("_Cam").append(userInput)).exists()){
        dirPath = tempPath;
    } else if(std::filesystem::directory_entry(tempPath.replace_filename("z)Archive").append(userInput)).exists()){
        dirPath = tempPath;
    }
}

void DirParser::parseDir(const std::filesystem::path pathToDir){
    std::regex aliasPattern {"alias"};
    std::vector<std::string> fileExtToExtract {".mp4", ".jpeg"};
    for (const auto &entry : std::filesystem::directory_iterator(pathToDir)){
        if (std::regex_search(entry.path().string(), aliasPattern)){
            aliasPath = entry.path();
        } else if (endsWith(entry.path().string(), fileExtToExtract)) {
            directoryContents.push_back(entry.path());
        }
    }
    renamerObj.setOldNames(directoryContents);
    renamerObj.initiateNewNames();
}

