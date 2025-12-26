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

target_compile_definitions(${TARGET_NAME} PUBLIC
	ASC_FILES_RESULTS_DIR="$ENV{HOME}/progit2Results"
)

if(GREEK_VER)
	target_compile_definitions(${TARGET_NAME} PUBLIC
		SUFFIX_TYPE="_gr"
	)
else()
	target_compile_definitions(${TARGET_NAME} PUBLIC
		SUFFIX_TYPE="_en"
	)
endif()
