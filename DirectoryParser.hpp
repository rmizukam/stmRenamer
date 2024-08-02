#include <vector>
#include <filesystem>
#include <string>

class DirectoryParser {
public:
    std::vector<std::filesystem::directory_entry> directoryContents;

    std::filesystem::path getRepoRoot();
    void parseDirectory(std::string);
    void parseDirectory(std::filesystem::path);
    std::vector<std::filesystem::directory_entry> readConfig(std::filesystem::path);
    std::vector<std::string> readConfig(std::string txtPath);
    void print();
    DirectoryParser(std::string);
    DirectoryParser(std::filesystem::path);

protected:
    bool endsWith(const std::string& fullString, const std::string& ending);
    bool endsWith(const std::string& fullString, const std::vector<std::string>& endings);
    void makeDirName(std::filesystem::path);
private:
    
};