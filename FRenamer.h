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
        void initiateNewNames();
        std::tuple<bool, std::string> isNameInFileName(std::vector<std::string> aliasTxt, std::string filePath, std::string userInput);
        std::tuple<bool, std::string> isNameInFileName(std::vector<std::string> aliasTxt, std::filesystem::path filePath, std::string userInput);
        std::vector<std::string> readTxtFile(std::string txtPath);
        std::vector<std::string> readTxtFile(std::filesystem::path txtPath);
        std::string reformatName(std::vector<std::string> aliasTxt, std::filesystem::path filePath, std::string name);
        void setOldNames(std::vector<std::filesystem::path> old);
        FRenamer();
        FRenamer(std::vector<std::filesystem::path> old);
    private:
        std::string convertMonthString2MonthIdx(std::string fName);
        std::string convertNum2Str(int num);
        int extractAmtNumInName(std::string);
        std::string extractExtraInfo(std::string inStr);
        std::vector<std::string> extractNums(std::string);
        std::filesystem::path getRepoRoot();
        std::string getIndex(std::vector<std::string> v, std::string K);
        std::string join(std::vector<std::string> stringVec, std::string delimeter);
        std::string join(std::vector<std::string> stringVec);
        std::vector<std::string> removeNumsInName(std::vector<std::string> numsFromName, int amtNumsInName);
        bool startsWith(const std::string& fullString, const std::string& beginning);
        std::vector<std::string> splitNumStr(std::string numStr);

};
#endif