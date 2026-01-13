#include <string>
#include <list>
#include <filesystem>
#include <fstream>
#include <regex>
#include <iostream>

class FindAndCompare {

private:

    std::string content {};
    int lineCounter {};
    std::regex rgx {};
    std::smatch match;
    std::list<std::string> filePaths{};
    std::string currentPath {};
    std::string filename {};
    int filesThatMatchTheRequirement {};
	std::string resultsDir {};

	std::fstream inStream;
	std::fstream outStream;

public:
    FindAndCompare(std::regex regexForSearch, std::string dirForResults = "");
	~FindAndCompare();

	std::list<std::string> findAllFiles(std::string parentFolder);
	std::string fileBasename(std::string path);
	void findAndSearchFiles(std::list<std::string>);

};
