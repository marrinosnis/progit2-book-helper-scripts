#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <filesystem>

namespace fs = std::filesystem;

std::list<std::string> findAllFilesAndInSubdirectories(std::string parentFolder);
std::string fileBasename(std::string path);
std::fstream& operator<<(std::fstream& COUT, const std::list<std::string>& filesPath);

int main(int argc, char* argv[]) {
	
	std::fstream inStream;
	std::fstream outStream;

	std::string content {};
	int lineCounter {};
	std::regex rgx (R"(https:\/\/\S+)");
	std::smatch match;
	std::list<std::string> filePaths{};
	std::string currentPath{};
	std::string filename {};
	int filesThatMatchTheRequirement {0};
	std::string allHttpsASCResFiles {"/allHttpsASCFiles/httpsResFiles"};
	allHttpsASCResFiles = PROGIT2_RESULTS_DIR + allHttpsASCResFiles + SUFFIX_TYPE  + "/";

	std::string listAllASCFiles = {"/allASCFiles/listOfAllASCFiles"};
	listAllASCFiles = PROGIT2_RESULTS_DIR + listAllASCFiles + SUFFIX_TYPE;

	if(argc < 2)
		std::cerr << "\nError! No input from the user\n";
	std::string filePath = argv[1];

	std::string directory = fs::path(listAllASCFiles).parent_path().string();
	std::cout << "The parent path is: " << directory << '\n';
	
	if(!fs::exists(directory)) {
		if(!fs::create_directories(directory)) {
			std::cerr << "Failed to create the ~/Desktop/check directory\n";
		}
	}

	std::string directoryForFiles = fs::path(allHttpsASCResFiles).string();
	std::cout << "The directoryForFiles is: " << directoryForFiles << '\n';

	if (!fs::exists(directoryForFiles)){
		if(!fs::create_directories(directoryForFiles)) {
			std::cerr << "Failed to create the ~/progit2Results/allHttpsASCResFiles directory\n";
		}
	}

	filePaths = findAllFilesAndInSubdirectories(filePath);
	
	outStream.open(listAllASCFiles, std::ios_base::out);
	outStream << filePaths;
	outStream.close();


	for(const std::string& path : filePaths) {

		inStream.open(path, std::ios_base::in);

		filename = fileBasename(path);
		std::cout << "THE NAME OF THE FILE IS: " << filename << '\n';

		if(inStream.is_open()) {
			/*SUFFIX_TYPE defines the type of ending of the file, if it will be _en for english or _gr for greek*/
			currentPath = allHttpsASCResFiles + filename + ".txt";  //filename changes all the time, in the loop
			outStream.open(fs::path(currentPath), std::ios_base::out);
			while(std::getline(inStream, content)) {
				lineCounter++;
				if(std::regex_search(content, match, rgx)) {
					// std::cout << "The match prefix is: " << match.prefix() << '\n';
					// std::cout << "The match str is : " << match.str() << '\n';
					outStream << match.str() << " \tat line " << lineCounter << '\n' << std::endl;
				}
			}
			if (fs::file_size(fs::path(currentPath)) == 0) {
				// outStream << "File " << filename << " doesn't contain any http link";
				fs::remove(fs::path(currentPath)); //previous logic, was to not keep it and remove the file
			}

			lineCounter = 0;

			outStream.close();
			inStream.close();

		} else {
			std::cout << "The file doesn't exists\n";
		}

	}
	
	return 0;
}

std::list<std::string> findAllFilesAndInSubdirectories(std::string parentFolder){

	std::list<std::string> filesPath{};
	std::string ASCSuffix {".asc"};
	int counter {0};

	for(const auto& entry : fs::recursive_directory_iterator(parentFolder)) {
		// check that entry.path() has the ".asc" suffix, with the string().compare() function
		// string().compare(indexToStart, howManyCharsToCheck, stringToCompareWith);
		if (!entry.path().string().compare(entry.path().string().length() - ASCSuffix.size(), ASCSuffix.size(), ASCSuffix) ) {
			counter++;
			// std::cout << "the current path is: " << entry << '\n';
			filesPath.push_back(entry.path());
		}
	}

	std::cout << "\n\nThe total number of .asc files is: " << counter << '\n';
	return filesPath;
}

std::string fileBasename(std::string path){
	std::string temp {path.substr(path.find_last_of("//") + 1)};
	return temp.substr(0, temp.find_last_of("."));
}

std::fstream& operator<<(std::fstream& COUT, const std::list<std::string>& filesPath){
	for(const auto& i : filesPath)
		COUT << i << '\n';
	return COUT;
}

