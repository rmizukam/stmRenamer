#include <iostream>
#include "DirectoryParser.hpp"
#include "FileRenamer.hpp"

bool isNumber(const std::string &);

int main(){
    std::cout << "Welcome to file renamer" << std::endl;
    std::cout << "select an option from the menu below" << std::endl;
    bool operating {true};
    std::string folderName {};
    std::cout << "______________________________________________" << std::endl;
    std::cout << "Enter name of folder to rename files: ";
    std::cin >> folderName;
    FileRenamer frenamer;
    frenamer.setDirectoryLocation(folderName);
    frenamer.parseDirectoryForRename();
    frenamer.reformatName(folderName);

    std::string userResponseStr {};
    int userResponse{};
    do {
        std::cout << "______________________________________________" << std::endl;
        std::cout << "0. Execute Rename" << std::endl;
        std::cout << "1. Display New Full File Path(s)" << std::endl;
        std::cout << "2. Display New File Name(s)" << std::endl;
        std::cout << "3. Print Current Contents of Folder" << std::endl;
        std::cout << "4. Enter New Folder" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter Response: ";
        std::cin >> userResponseStr;
        std::cout << "______________________________________________" << std::endl;

        if (isNumber(userResponseStr) && userResponseStr.size() == 1){
            userResponse = std::stoi(userResponseStr);
        } else {
            userResponse = -1;
        }

        if (userResponse == 1){
            frenamer.print(frenamer.directoryContents, frenamer.newFileNames);
        } else if (userResponse == 2) {
            frenamer.printFilename(frenamer.directoryContents, frenamer.newFileNames);
        } else if(userResponse == 3) {
            frenamer.print(frenamer.directoryContents);
        } else if (userResponse == 4) {
            std::cout << "Enter name of folder to rename files: ";
            std::cin >> folderName;
            frenamer.reset();
            frenamer.setDirectoryLocation(folderName);
            frenamer.parseDirectoryForRename();
            frenamer.reformatName(folderName);
        } else if (userResponse == 5) {
            operating = false;
        } else if (userResponse == 0){
            frenamer.executeRename(folderName);
        } else {
            std::cout << "Invalid Entry. Please try again: ";
            std::cin >> userResponse;
        }

    } while (operating);
}

bool isNumber(const std::string &stringUserInput) {
    for (auto c:stringUserInput) {
        if (!isdigit(c)){
            return {false};
        }
    }
    return {true};
}