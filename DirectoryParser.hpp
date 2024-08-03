#pragma once

#include <vector>
#include <filesystem>
#include <string>
#include <tuple>

class DirectoryParser {
public:
    std::filesystem::directory_entry directoryLocation;
    std::vector<std::filesystem::directory_entry> directoryContents;
    
    std::tuple<bool, std::filesystem::directory_entry> directoryExists(std::string);
    std::filesystem::path getRepoRoot();
    void parseDirectory(std::string);
    void parseDirectory(std::filesystem::path);
    std::vector<std::filesystem::directory_entry> readConfig(std::filesystem::path);
    std::vector<std::string> readConfig(std::string txtPath);
    void setDirectoryLocation(std::string folderName);
    void print();
    DirectoryParser();

protected:
    bool endsWith(const std::string& fullString, const std::string& ending);
    bool endsWith(const std::string& fullString, const std::vector<std::string>& endings);
    bool startsWith(const std::string& fullString, const std::string& beginning);

    
};