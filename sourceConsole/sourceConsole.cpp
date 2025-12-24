#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <filesystem>

namespace fs = std::filesystem;

std::string fileBasename(std::string path);
std::list<std::string> findAllFiles(std::string path);


int main(int argc, char* argv[]) {
	std::fstream inStream;
	std::fstream outStream;

	std::string content {};
	std::string secondLineContent {};
	int lineCounter {};
	std::regex rgx ("(\\[source,console\\])");
	std::smatch match;
	std::list<std::string> filePaths{};
	std::string currentPath {};

	std::regex rgx2 {};
	std::smatch match2;

	std::string homeDir = getenv("HOME");
	std::string resultsDir = "/results/sourceConsoleRes";
	std::string resultsDirPath = homeDir + resultsDir + SUFFIX_TYPE + "/";

	if(argc < 2)
		std::cerr << "Error! No input from the user\n";
	std::string filePath = argv[1];

	if(!fs::exists(resultsDirPath)) {
		if(!fs::create_directories(resultsDirPath)) {
			std::cerr << "Failed to create the ~/Desktop/diff_check_ directory\n";
		}
	}

	filePaths = findAllFiles(filePath);

	for(const auto& path : filePaths) {

		std::cout << path << '\n';	
		inStream.open(path, std::ios_base::in);
	
		std::string filename = fileBasename(path);
		std::cout << "the name of the file is: " << filename << "\n\n";
	
		if(inStream.is_open()) {
			currentPath = resultsDirPath + filename + SUFFIX_TYPE + ".txt";
			outStream.open(currentPath, std::ios_base::app);
			while(std::getline(inStream, content)){
				// if (check) {
				// 	outStream << content << "\n\n\n\n";
				// 	check = false;	
				// }
				lineCounter++;
				if(std::regex_match(content, match, rgx)) {
					std::cout <<  match[0] << '\n';
					outStream << match[0] << std::endl;
	
					std::getline(inStream, secondLineContent); //store exactly the next line of content to the secondLineContent variable
					// std::cout << secondLineContent << '\n';  //prints the "----"
					outStream << secondLineContent << '\n';
	
					rgx2 = secondLineContent;
	
					while(std::getline(inStream, content)){
						std::cout << content << "\n";
						outStream << content << '\n';
						if (std::regex_match(content, match2, rgx2)) {
							std::cout << "\n==================Found the end of the hashes block" << match2[0] << "==================\n\n";	
							outStream << "\n==================Found the end of the hashes block" << match2[0] << "==================\n\n";	
							break;
						}
					}
					outStream << std::endl;

				} 
			}
			
			if (fs::file_size(fs::path(currentPath)) == 0) {
				outStream << "File: " << filename << ", doesn't contain any [source, console] line" << std::endl;
				// fs::remove(fs::path(currentPath)); //previous logic, was to not keep it.s
			}

			outStream.close();
			inStream.close();

		} else {
			std::cout << "The file doesn't exists\n\n";
		}

		inStream.close();
	}

	return 0;
}

std::string fileBasename(std::string path){
	std::string temp {path.substr(path.find_last_of("//") + 1)};
	
	return temp.substr(0, temp.find_last_of("."));
}

std::list<std::string> findAllFiles(std::string parentFolder) {
	// std::list<std::string> filesPath{};

	// for (const auto &entry : fs::directory_iterator(path)) {
	// 	// std::cout << entry.path() << std::endl;
	// 	filesPath.push_back(entry.path());
	// }

	// return filesPath;

	std::list<std::string> filesPath{};
	std::string ASCSuffix {".asc"};
	int counter {0};

	for(const auto& entry : fs::recursive_directory_iterator(parentFolder)) {
		// check that entry.path() has the ".asc" suffix, with the string().compare() function
		//string().compare(indexToStart, howManyCharsToCheck, stringToCompareWith);
		if (!entry.path().string().compare(entry.path().string().length() - ASCSuffix.size(), ASCSuffix.size(), ASCSuffix) ) {
			counter++;
			std::cout << "the current path is: " << entry << '\n';
			filesPath.push_back(entry.path());
		}
	}

	std::cout << "\n\nThe total number of .asc files is: " << counter << '\n';
	return filesPath;
}