#include <vector>
#include <filesystem>
#include <string>

class DirectoryParser {
public:
    std::vector<std::filesystem::directory_entry> directoryContents;

    void parseDirectory(std::filesystem::path);
    std::vector<std::filesystem::directory_entry> readConfig(std::filesystem::path);
    std::vector<std::string> readConfig(std::string txtPath);
    void print();
    DirectoryParser();
    DirectoryParser(std::string);
protected:
    bool endsWith(const std::string& fullString, const std::string& ending);
    bool endsWith(const std::string& fullString, const std::vector<std::string>& endings);
private:
    
};