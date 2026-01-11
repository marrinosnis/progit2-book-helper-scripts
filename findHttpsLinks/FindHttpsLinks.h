#include <string>
#include <list>
#include <filesystem>
#include <fstream>


class FindHttpsLinks {

private:

    std::string content {};
    int lineCounter {};
    std::regex rgx {};
    std::list<std::string> filePaths{};
    std::string currentPath {};
    std::string filename {};
    int filesThatMatchTheRequirement {};
	std::string resultsDir {};

	std::fstream inStream;
	std::fstream outStream;

public:
    FindHttpsLinks(std::string dirForResults = "", std::regex regexForSearch = "");
	~FindHttpsLinks(){}


	std::list<std::string> findAllFiles(std::string parentFolder);
	std::string fileBasename(std::string path);
	void findAndSearchFiles(std::list<std::string>);

};
