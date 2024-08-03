#pragma once
#include <string>
#include "DirectoryParser.hpp"

class FileRenamer : public DirectoryParser {
public:
    std::vector<std::string> aliasTxt;
    std::vector<std::filesystem::directory_entry> newFileNames;
    FileRenamer(): DirectoryParser() {};

    void executeRename(std::string);
    std::tuple<bool, std::string> isNameInFileName(std::string filePath, std::string userInput);
    std::tuple<bool, std::string> isNameInFileName(std::filesystem::path filePath, std::string userInput);
    void parseDirectoryForRename();
    void parseDirectoryForRename(std::filesystem::path pathToDir);
    void parseDirectoryForRename(std::string pathToDirString);
    void print(std::vector<std::filesystem::directory_entry>);
    void print(std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>);
    void printFilename(std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>);
    void reformatName(std::string userInput);
    std::string reformatName(std::filesystem::path filePath, std::string userInput);
    void setAliasTxt();
    void reset();
private:
    std::string convertMonthString2MonthIdx(std::string fName);
    std::string convertNum2Str(int num);
    std::vector<std::string> extractNums(std::string);
    int extractAmtNumInName(std::string);
    std::string getIndex(std::vector<std::string> v, std::string K);
    std::vector<std::string> removeNumsInName(std::vector<std::string> numsFromName, int amtNumsInName);
    std::vector<std::string> removeNumsInName(std::tuple<bool, std::string> numsFromNameInfo, std::vector<std::string> numsFromName, int amtInName);
    std::vector<std::string> splitNumStr(std::string numStr);
};