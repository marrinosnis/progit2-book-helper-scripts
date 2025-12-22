cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(findLinks VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

option(GREEK_VER "Set it to true to create a Greek version of results file" OFF)

if(GREEK_VER)
	set(TARGET_NAME findLinks_gr)
else()
	set(TARGET_NAME findLinks_en)
endif()

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/findHttpLinks.cpp
)

if(GREEK_VER)
	target_compile_definitions(${TARGET_NAME} PUBLIC
		#FILE_OF_ALL_ASC_FILES="/home/runner/results/check_gr/allAscFiles_gr.txt"
		FILE_OF_ALL_ASC_FILES="/home/marinos/Desktop/progit2-book-helper-scripts/findHttpsLinks/results/check_gr/allAscFiles_gr.txt"
		SUFFIX_TYPE="_gr"
	)
else()
	target_compile_definitions(${TARGET_NAME} PUBLIC
	    	#FILE_OF_ALL_ASC_FILES="/home/runner/results/check_en/allAscFiles_en.txt"
	    	FILE_OF_ALL_ASC_FILES="/home/marinos/Desktop/progit2-book-helper-scripts/findHttpsLinks/results/check_en/allAscFiles_en.txt"
		SUFFIX_TYPE="_en"
	)
endif()
