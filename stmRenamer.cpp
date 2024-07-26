#include <string>
#include <iostream>
#include <vector>
#include "DirParser.h"
#include "PrintUtils.h"

int main(){
    PrintUtils printer;
    DirParser dir;
    dir.getUserInput();
    std::vector<std::string> aliasTxt {dir.renamerObj.readAlias(dir.aliasPath.string())};
    
    for (auto pathName : dir.directoryContents){
        std::tuple<bool, std::string> nameInFile {dir.renamerObj.isNameInFileName(aliasTxt, pathName)};
        std::string nameFormat { dir.renamerObj.detectNameFormat(pathName) };
        // std::vector<std::string> dateStr {dir.renamerObj.extractDateString(std::get<std::string>(nameInFile), pathName.filename().string())};
        
    }
    
    // std::string oldname = "D:\\WD Files\\WD Software\\Fraps\\_Movie\\2024-07-18 06-17-29.mkv";
    // std::string newname = "D:\\WD Files\\WD Software\\Fraps\\_Movie\\banana.mkv";

    // std::rename(oldname.c_str(), newname.c_str());
}