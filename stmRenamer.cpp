#include <string>
#include <iostream>
#include <vector>
#include "DirParser.h"
#include "PrintUtils.h"
#include <regex>

int main(){
    PrintUtils printer;
    DirParser dir;
    dir.getUserInput();
    std::vector<std::string> aliasTxt {dir.renamerObj.readTxtFile(dir.aliasPath.string())};

    for (auto pathName : dir.directoryContents){
        std::tuple<bool, std::string> nameInFile {dir.renamerObj.isNameInFileName(aliasTxt, pathName, dir.userInput)};
        std::string nameFormat { dir.renamerObj.reformatName(aliasTxt, pathName, dir.userInput) };
    }
    printer.print(dir.renamerObj.oldNames, dir.renamerObj.newNames);

    // std::string oldname = "D:\\WD Files\\WD Software\\Fraps\\_Movie\\2024-07-18 06-17-29.mkv";
    // std::string newname = "D:\\WD Files\\WD Software\\Fraps\\_Movie\\banana.mkv";

    // std::rename(oldname.c_str(), newname.c_str());

}