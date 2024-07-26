#ifndef _F_RENAMER_H_
#define _F_RENAMER_H_

#include <filesystem>
#include <vector>
#include <string>
#include <tuple>

class FRenamer {
    public:       
        std::vector<std::filesystem::path> newNames;
        std::vector<std::filesystem::path> oldNames;
        std::string nameToUse;

        std::vector<std::string> readAlias(std::string txtPath);
        void setOldNames(std::vector<std::filesystem::path> old);
        void initiateNewNames();
        std::tuple<bool, std::string> isNameInFileName(std::vector<std::string> aliasTxt, std::string filePath);
        std::tuple<bool, std::string> isNameInFileName(std::vector<std::string> aliasTxt, std::filesystem::path filePath);
        std::string detectNameFormat(std::filesystem::path filePath);
        std::vector<std::string> extractNums(std::string);

        int extractAmtNumInName(std::string);
        std::vector<std::string> extractDateString(std::string name, std::string str);
        std::vector<std::string> splitNumStr(std::string numStr);
        
        FRenamer();
        FRenamer(std::vector<std::filesystem::path> old);
    private:
};
#endif