#ifndef _DIR_PARSER_H_
#define _DIR_PARSER_H_

#include <vector>
#include <string>
#include <filesystem>
#include "FRenamer.h"

class DirParser {
    friend class Printer;

    public:
        std::string userInput;
        std::string name;
        std::filesystem::path aliasPath;
        std::filesystem::path dirPath;
        std::vector<std::filesystem::path> directoryContents;
        FRenamer renamerObj;

        void getUserInput();
        void parseDir(const std::filesystem::path pathToDir);

        DirParser();
    private:
        std::string baseDir {"D:\\WD Files\\WD Software\\Fraps\\_Movie\\"};

        void makeDirName();
        bool endsWith(const std::string& fullString, const std::string& ending);
        bool endsWith(const std::string& fullString, const std::vector<std::string>& endings);
        

};

#endif