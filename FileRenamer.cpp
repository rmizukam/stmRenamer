#include <regex>
#include <iostream>
#include "FileRenamer.hpp"

std::string FileRenamer::convertMonthString2MonthIdx(std::string fName){
    std::filesystem::path repoRoot {getRepoRoot()};
    std::filesystem::path listOfMonthTxt {repoRoot.append("listOfMonths.txt")};
    std::vector<std::string> listOfMonths = readConfig(listOfMonthTxt.string());
    std::vector<std::string> listOfMonthAbreviate = readConfig(listOfMonthTxt.replace_filename("listOfMonthsAbreviate.txt").string());
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

std::string FileRenamer::convertNum2Str(int num){
    char buffer [5];
    return { std::string(buffer) };
}

void FileRenamer::executeRename(std::string userInput){
    std::string newNameForFile{};
    for(auto &oldPath:directoryContents){
        newNameForFile = reformatName(oldPath.path(), userInput);
        std::filesystem::rename(oldPath.path(), std::filesystem::path(newNameForFile));
    }
}

std::tuple<bool, std::string> FileRenamer::isNameInFileName(std::string filePath, std::string userInput){
    bool matchFound {false};
    std::string name2Use {};
    for (size_t i{0}; i < aliasTxt.size(); i++){
        name2Use = aliasTxt.at(i);
        std::regex namePattern (name2Use, std::regex::icase);
        matchFound = std::regex_search(filePath, namePattern);
        if (matchFound){
            return {matchFound, name2Use};
        }
    }
    return { false, userInput };
}
std::tuple<bool, std::string> FileRenamer::isNameInFileName(std::filesystem::path filePath, std::string userInput){
    return { isNameInFileName(filePath.stem().string(), userInput) };
}

int FileRenamer::extractAmtNumInName(std::string str){
    std::vector<std::string> nums = extractNums(str);
    return {static_cast<int>(nums.size())};
}

std::vector<std::string> FileRenamer::extractNums(std::string str){
    std::vector<std::string> extractedNums;
    std::regex numPattern ("\\d+");
    std::regex_token_iterator<std::string::iterator> strEnd;
    std::regex_token_iterator<std::string::iterator> regexParser {str.begin(), str.end(), numPattern};
    while (regexParser != strEnd){
        extractedNums.push_back(*regexParser++);
    }
    return extractedNums;
}

std::string FileRenamer::getIndex(std::vector<std::string> v, std::string K){
    auto it = find(v.begin(), v.end(), K); 
    int index {};
    // If element was found 
    if (it != v.end()) { 
        // calculating the index of K 
        index = it - v.begin(); 
    } 
    else { 
        // If the element is not present in the vector 
        index = -1 ;
    } 
    return { convertNum2Str(index) };
}

void FileRenamer::parseDirectoryForRename(std::filesystem::path pathToDir){
    std::regex aliasPattern {"alias", std::regex::icase};
    std::vector<std::string> fileExtToExtract {".mp4", ".jpeg", ".ts", ".mkv"};
    for (const auto &entry : std::filesystem::directory_iterator(pathToDir)){
        if (endsWith(entry.path().string(), fileExtToExtract)){
            directoryContents.push_back(entry);
        } else if (std::regex_search(entry.path().string(), aliasPattern)){
            aliasTxt = readConfig(entry.path().string());
        }
    }
}

void FileRenamer::parseDirectoryForRename(std::string pathToDirString) {
    std::filesystem::path pathToDir {std::filesystem::path(pathToDirString)};
    parseDirectoryForRename(pathToDir);
}

void FileRenamer::parseDirectoryForRename(){
    parseDirectoryForRename(directoryLocation.path().string());
}

void FileRenamer::print(std::vector<std::filesystem::directory_entry> paths2print){
    for (auto path:paths2print){
        std::cout << path << std::endl;
    }
}

void FileRenamer::print(std::vector<std::filesystem::directory_entry> oldNamePaths, std::vector<std::filesystem::directory_entry> newNamePaths){
    if (oldNamePaths.empty() || newNamePaths.empty()){
        std::cout << "Folder not set. Use option 1 and try this option again." << std::endl;
    } else {
        if (oldNamePaths.size() == newNamePaths.size()){
            for (size_t i{0}; i < oldNamePaths.size(); i++){
                std::cout << i << ": " << oldNamePaths.at(i).path().string() << "  -->  " << newNamePaths.at(i).path().string() << std::endl;
            }
        } else {
            std::cout << "Vectors not of same length" << std::endl;
        }
    }
}

void FileRenamer::printFilename(std::vector<std::filesystem::directory_entry> oldNamePaths, std::vector<std::filesystem::directory_entry> newNamePaths){
    if (oldNamePaths.empty() || newNamePaths.empty()){
        std::cout << "Folder not set. Use option 1 and try this option again." << std::endl;
    } else {
        if (oldNamePaths.size() == newNamePaths.size()){
            for (size_t i{0}; i < oldNamePaths.size(); i++){
                std::cout << i << ": " << oldNamePaths.at(i).path().filename().string() << "  -->  " << newNamePaths.at(i).path().filename().string() << std::endl;
            }
        } else {
            std::cout << "Vectors not of same length" << std::endl;
        }
    }
}

std::string FileRenamer::reformatName(std::filesystem::path filePath, std::string userInput) {
    std::string year {};
    std::string month {};
    std::string day {};
    std::string hour {};
    std::string min {};
    std::string sec {};
    std::string parentDir {filePath.parent_path().string()};
    std::string fileName { filePath.stem().string() };
    std::string fileExt { filePath.extension().string() };
    std::tuple nameInFileInfo = isNameInFileName(filePath, userInput);
    std::string name2use {std::get<std::string>(nameInFileInfo)};
    int nNumsInName = extractAmtNumInName(name2use);

    std::regex desiredDateFormat {"\\d{4}-\\d{2}-\\d{2}[\\s|_|:]\\d{2}-\\d{2}(-\\d{2})*.*", std::regex::icase};
    std::regex year_Month_DD_HH_mm_ss {"\\d{4}-\\w-\\d{2}_\\d{2}-\\d{2}-*\\d{2}*", std::regex::icase};
    std::regex MMDDYYYY_combine {"\\d{8}-\\d{2}-\\d{2}-\\d{2}", std::regex::icase};
    std::regex HHmmss_combine {"\\d{4}-\\d{2}-\\d{2}[_| |:]*\\d{6}", std::regex::icase};
    std::regex DDMMYYYY_HHmm {"\\d{8}[_|-]{1}\\d{4}", std::regex::icase};
    std::regex Month_DD_YYYY_HH_mm_ss {"[A-Za-z]{3,}-\\d{2}-\\d{4}[_| |:|-]*\\d{2}-\\d{2}-*\\d{2}*", std::regex::icase};
    std::regex YYYYMMDDHHmm_combine {"\\d{12}", std::regex::icase};

    const int MAX_ELEMENTS_IN_DATE {6};
    std::vector<std::string> finalNums {};
    if (std::regex_search(fileName, desiredDateFormat)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        year = numsInFileName.at(0);
        month = numsInFileName.at(1);
        day = numsInFileName.at(2);
        hour = numsInFileName.at(3);
        min = numsInFileName.at(4);
        if (numsInFileName.size() >= 6){
            sec = numsInFileName.at(5);
        }else{
            sec = "";
        }
    } else if (std::regex_search(fileName, year_Month_DD_HH_mm_ss)) {
        fileName = convertMonthString2MonthIdx(fileName);
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        year = numsInFileName.at(0);
        month = numsInFileName.at(1);
        day = numsInFileName.at(2);
        hour = numsInFileName.at(3);
        min = numsInFileName.at(4);
        if (numsInFileName.size() >= 6){
            sec = numsInFileName.at(5);
        }else{
            sec = "";
        }
    } else if (std::regex_search(fileName, MMDDYYYY_combine)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        std::string monthDayYear {numsInFileName.at(0)};
        month = monthDayYear.substr(0,2);
        day = monthDayYear.substr(2,2);
        year = monthDayYear.substr(4,4);
        hour = numsInFileName.at(1);
        min = numsInFileName.at(2);
        sec = numsInFileName.at(3);
    } else if (std::regex_search(fileName, HHmmss_combine)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        year = numsInFileName.at(0);
        month = numsInFileName.at(1);
        day = numsInFileName.at(2);
        std::string hourMinSec {numsInFileName.at(3)};
        hour = hourMinSec.substr(0, 2);
        min = hourMinSec.substr(2, 2);
        sec = hourMinSec.substr(4,2);
    } else if (std::regex_search(fileName, Month_DD_YYYY_HH_mm_ss)) {
        fileName = convertMonthString2MonthIdx(fileName);
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        month = numsInFileName.at(0);
        day = numsInFileName.at(1);
        year = numsInFileName.at(2);
        hour = numsInFileName.at(3);
        min = numsInFileName.at(4);
        if (numsInFileName.size() >= 6){
            sec = numsInFileName.at(5);
        }else{
            sec = "";
        }
    } else if (std::regex_search(fileName, YYYYMMDDHHmm_combine)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        std::string YYYYMMDDHHmm {numsInFileName.at(0)};
        year = YYYYMMDDHHmm.substr(0, 4);
        month = YYYYMMDDHHmm.substr(4, 2);
        day = YYYYMMDDHHmm.substr(6, 2);
        hour = YYYYMMDDHHmm.substr(8, 2);
        min = YYYYMMDDHHmm.substr(10,2);
        sec = "";
    }else if(std::regex_search(fileName, DDMMYYYY_HHmm)) {
        std::vector<std::string> numsInFileName = extractNums(fileName);
        numsInFileName = removeNumsInName(nameInFileInfo, numsInFileName, nNumsInName);
        year = numsInFileName.at(0).substr(4, 4);
        month = numsInFileName.at(0).substr(2, 2);
        day = numsInFileName.at(0).substr(0, 2);
        hour = numsInFileName.at(1).substr(0, 2);
        min = numsInFileName.at(1).substr(2, 2);
        sec = "";
    } else {
        return { filePath.string() };
    }
    std::string dateStr = year + "-" + month + "-" + day + "_" + hour + "-" + min;
    if (sec.compare("") != 0){
        dateStr += "-";
        dateStr += sec;
    }
    dateStr += fileExt;
    std::string outputName {name2use + "_" + dateStr};
    std::filesystem::path newPath {std::filesystem::path(parentDir) /= outputName};
    return {newPath.string()};
}

void FileRenamer::reformatName(std::string userInput){
    for (auto path:directoryContents){
        std::filesystem::path newPath = reformatName(path.path(), userInput);
        newFileNames.push_back(std::filesystem::directory_entry(newPath));
    }
}

std::vector<std::string> FileRenamer::removeNumsInName(std::vector<std::string> numsFromName, int amtNumsInName){
    numsFromName.erase(numsFromName.begin(), numsFromName.begin() + amtNumsInName);
    return {numsFromName};
}

std::vector<std::string> FileRenamer::removeNumsInName(std::tuple<bool, std::string> numsFromNameInfo, std::vector<std::string> numsFromName, int amtInName){
    bool namesInFileDetected {std::get<bool>(numsFromNameInfo)};
    std::string name2use {std::get<std::string>(numsFromNameInfo)};
    if (namesInFileDetected){
        numsFromName = removeNumsInName(numsFromName, amtInName);
    }
    return {numsFromName};
}

void FileRenamer::setAliasTxt(){
    std::regex aliasPattern {"alias.txt", std::regex::icase};
    for (const auto &entry:directoryContents){
        if (std::regex_search(entry.path().string(), aliasPattern));{
            aliasTxt = readConfig(entry.path().string());
        }
    }
}

std::vector<std::string> FileRenamer::splitNumStr(std::string numStr){
    std::vector<std::string> outVec {};
    for (size_t i{0}; i < numStr.size(); i += 2){
        outVec.push_back(numStr.substr(i, 2));
    }
    return {outVec};
}

void FileRenamer::reset(){
    aliasTxt = {};
    directoryContents = {};
    newFileNames = {};
}