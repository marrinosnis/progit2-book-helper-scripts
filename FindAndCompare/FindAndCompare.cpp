#include "FindAndCompare.h"

namespace fs = std::filesystem;

FindAndCompare::FindAndCompare(std::regex regexForSearch, std::string dirForResults) {
	if(!dirForResults.empty()) {
		resultsDir = dirForResults;
		rgx = regexForSearch;
	} else {
		std::cout << "Neither directory for results nor regex can be empty\n";
	}
}

FindAndCompare::~FindAndCompare(){}

void FindAndCompare::findAndSearchFiles(std::list<std::string> filePaths) {

	for(const std::string& path : filePaths) {
		inStream.open(path, std::ios_base::in);

		filename = fileBasename(path);
		std::cout << "The name of the file is: " << filename << '\n';

		if(inStream.is_open()) {
			/*SUFFIX_TYPE defines the type of the ending of the file, if it will be _en for english or _gr for greek */
			currentPath = resultsDir + filename + ".txt";
			outStream.open(fs::path(currentPath), std::ios_base::out);
			while(std::getline(inStream, content)) {
				lineCounter++;
				if(std::regex_search(content, match, rgx)) {
					outStream << match.str() <<" \tat line " << lineCounter << "\n\n";
				}
			}
			if (fs::file_size(fs::path(currentPath)) == 0) {
				fs::remove(fs::path(currentPath));
			}
			lineCounter = 0;
			outStream.close();
			inStream.close();

		} else {
			std::cout << "The file doesn't exists\n";
		}
	}
}

std::list<std::string> FindAndCompare::findAllFiles(std::string parentFolder) {

	std::list<std::string> filesPath{};
	std::string ASCSuffix {".asc"};
	int counter {0};

	for(const auto& entry : fs::recursive_directory_iterator(parentFolder)) {
		// check that entry.path() (the file at that path) has the ".asc" suffix, with string().compare() function
		// string().compare(indexToStart. howManyCharsToCheck, stringToCompareWith);
		if (!entry.path().string().compare(entry.path().string().length() - ASCSuffix.size(), ASCSuffix.size(), ASCSuffix) ) {
			counter++;
			std::cout << "the current path is: " << entry << '\n';
			filesPath.push_back(entry.path());
		}
	}

	std::cout << "The total number of .asc files is: " << counter << '\n';
	return filesPath;
}

std::string FindAndCompare::fileBasename(std::string path) {
	std::string temp {path.substr(path.find_last_of("//") + 1)};
	return temp.substr(0, temp.find_last_of("."));
}