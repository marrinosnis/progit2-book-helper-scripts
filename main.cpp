#include <FindAndCompare.h>  //also includes <iostream> and <fstream>
#include <exception>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

	// std::fstream inStream;
	// std::fstream outStream;

	// std::string content {};
	// int lineCounter {};
	std::regex rgx ("<<ch.*#.*>>");
	// std::smatch match;
	std::string filePath{};
	std::list<std::string> filePaths{};
	// std::string currentPath {};
	// std::string filename {};
	std::string allChapterReferences {"/allChapterReferences/chapterResFiles"};
	allChapterReferences = PROGIT2_RESULTS_DIR + allChapterReferences + "_en/";

	try{
		if(argc < 2) {
			throw std::logic_error("Error! No input from the user");
		}

		filePath = argv[1];

	} catch (std::logic_error& e) {
		std::cerr << "Error code: " << e.what() << ' ';
		exit(1);
	}

	// std::cout << "The type of the file is " << SUFFIX_TYPE << std::endl;


	std::string directory = fs::path(allChapterReferences).parent_path().string();
	std::cout << "The parent path is: " << directory << '\n';

	if(!fs::exists(directory)) {
		if(!fs::create_directories(directory)) {
			std::cerr << "Failed to create ~/progit2Results/allChapterReferences/chapterResFiles directory\n";
		}
	}

	// here is called the constructor of the class. In the constructor I have to pass
	// the 2 values of the results directory, and the regex to be used to search.
	FindAndCompare findObj(rgx, "allChapterReferences/chapterResFiles");
	findObj.findAllFiles(filePath);
	findObj.findAndSearchFiles(filePaths);


	// for(const std::string& path : filePaths) {

	// 	inStream.open(path, std::ios_base::in);

	// 	filename = findObj.fileBasename(path);
	// 	std::cout << "The name of the file is: " << filename << '\n';

	// 	if(inStream.is_open()) {
	// 		currentPath = allChapterReferences + filename + ".txt";
	// 		outStream.open(fs::path(currentPath), std::ios_base::out);
	// 		while(std::getline(inStream, content)){
	// 			lineCounter++;
	// 			if(std::regex_search(content, match, rgx)){
	// 				// std::cout << "The match is equal to " << match.str() << " at line " << lineCounter << "\n\n";
	// 				outStream << match.str() << " at line " << lineCounter << std::endl;
	// 			}
	// 		}
	// 		if (fs::file_size(fs::path(currentPath)) == 0) {
	// 			// outStream << "File " << filename << " doesn't contain any http link";
	// 			fs::remove(fs::path(currentPath)); //previous logic, was to not keep it and remove the file
	// 		}

	// 		lineCounter = 0 ;

	// 		outStream.close();
	// 		inStream.close();

	// 	} else {
	// 		std::cout << "The file doesn't exists\n\n";
	// 	}
	// }

	return 0;
}


std::list<std::string> findAllFilesAndInSubdirectories(std::string parentFolder) {

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
