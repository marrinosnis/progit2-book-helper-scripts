#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <filesystem>

namespace fs = std::filesystem;

std::list<std::string> findAllFilesAndInSubdirectories(std::string parentFolder);

std::fstream& operator<<(std::fstream& COUT, const std::list<std::string>& filesPath);

std::string fileBasename(std::string path);


int main(int argc, char* argv[]) {

	std::fstream inStream;
	std::fstream outStream;

	
	std::string content {};
	int lineCounter {1};;
	std::regex rgx (R"(https:\/\/\S+)");
	std::smatch match;
	std::list<std::string> filePaths{};
	std::string currentPath{};
	int filesThatMatchTheRequirement {0};
	std::string homeDir = getenv("HOME");
	std::string allFilesFromTheRoot {"/results/allFilesFromTheRoot"};
	allFilesFromTheRoot = homeDir + allFilesFromTheRoot + SUFFIX_TYPE  + "/";
	
	std::cout << "Input the .asc file root path to read from\n\n";
	// std::cin >> filePath;
	if(argc < 2)
		std::cerr << "Error! No input from the user\n";
	std::string filePath = argv[1];
	
	filePaths = findAllFilesAndInSubdirectories(filePath);

	/* FILE_OF_ALL_ASC_FILES is written with a list of all .asc files that where calculated.*/
	std::string directory = fs::path(FILE_OF_ALL_ASC_FILES).parent_path().string();
	std::cout << "The parent path is: " << directory << '\n';
	std::string directoryForFiles = fs::path(allFilesFromTheRoot).string();
	std::cout << "The directoryForFiles is: " << directoryForFiles << '\n';
	if(!fs::exists(directory)) {
		if(!fs::create_directories(directory)) {
			std::cerr << "Failed to create the ~/Desktop/check directory\n";
		}
	}
	if (!fs::exists(directoryForFiles)){
		if(!fs::create_directories(directoryForFiles)) {
			std::cerr << "Failed to create the ~/Desktop/allFilesFromTheRoot_en directory\n";
		}
	}
	outStream.open(FILE_OF_ALL_ASC_FILES, std::ios_base::app);
	outStream << filePaths;
	outStream.close();


	for(const std::string& path : filePaths) {

		inStream.open(path, std::ios_base::in);

		std::string filename = fileBasename(path);

		std::cout << "THE NAME OF THE FILE IS: " << filename << "\n\n";

		if(inStream.is_open()){
			/*SUFFIX_OF_FILE defines the type of the extension, if it will be _en for english or _gr for greek*/
			currentPath = allFilesFromTheRoot + filename + SUFFIX_TYPE + ".txt";  //filename changes all the time, in the loop
			outStream.open(fs::path(currentPath), std::ios_base::app);
			lineCounter = 1;
			while(std::getline(inStream, content)) {
				if(std::regex_search(content, match, rgx)) {
					outStream << content << " \tat line " << lineCounter << '\n' << std::endl;
				}
				lineCounter++;
			}
			if (fs::file_size(fs::path(currentPath)) == 0) {
				outStream << "File " << filename << " doesn't contain any http link";
				// fs::remove(fs::path(currentPath)); //previous logic, was to not keep it.s
			}
			outStream.close();
			inStream.close();
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
			std::cout << "the current path is: " << entry << '\n';
			filesPath.push_back(entry.path());
		}
	}

	std::cout << "\n\nThe total number of .asc files is: " << counter << '\n';
	return filesPath;
}

std::fstream& operator<<(std::fstream& COUT, const std::list<std::string>& filesPath){
	for(const auto& i : filesPath)
		COUT << i << '\n';
	return COUT;
}

std::string fileBasename(std::string path){
	std::string temp {path.substr(path.find_last_of("//") + 1)};
	
	return temp.substr(0, temp.find_last_of("."));
}
