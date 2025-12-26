cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(FindSourceConsoleBlocks VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

option(GREEK_VER "Set this option to create a Greek version for the executable" OFF)

if(GREEK_VER)
	set(TARGET_NAME sourceConsole_gr)
else()
	set(TARGET_NAME sourceConsole_en)
endif()

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/sourceConsole.cpp"
)

target_compile_definitions(${TARGET_NAME} PUBLIC
	PROGIT2_RESULTS_DIR="$ENV{HOME}/progit2Results"
)


if(GREEK_VER)
	target_compile_definitions(${TARGET_NAME} PUBLIC
		# FILE_OF_ALL_ASC_FILES="/home/runner/results/check_gr/allAscFiles_gr.txt"
		# FILE_OF_ALL_ASC_FILES="/home/marinos/Desktop/progit2-book-helper-scripts/findHttpsLinks/results/check_gr/allAscFiles_gr.txt"
		SUFFIX_TYPE="_gr"
	)
else()
	target_compile_definitions(${TARGET_NAME} PUBLIC
	    	# FILE_OF_ALL_ASC_FILES="/home/runner/results/check_en/allAscFiles_en.txt"
	    	# FILE_OF_ALL_ASC_FILES="/home/marinos/Desktop/progit2-book-helper-scripts/findHttpsLinks/results/check_en/allAscFiles_en.txt"
		SUFFIX_TYPE="_en"
	)
endif()
