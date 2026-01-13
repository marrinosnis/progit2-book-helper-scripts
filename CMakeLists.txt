cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(main VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

option(GREEK_VER "Set it to true to create a Greek version of results file" OFF)

if(GREEK_VER)
	set(TARGET_NAME mainExec_gr)
else()
	set(TARGET_NAME mainExec_en)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/FindAndCompare)

add_executable(${TARGET_NAME})

target_link_libraries(${TARGET_NAME} PRIVATE
	FindCompare
)

target_include_directories(${TARGET_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/FindAndCompare
)

target_sources(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_compile_definitions(${TARGET_NAME} PUBLIC
    PROGIT2_RESULTS_DIR="$ENV{HOME}/progit2Results"
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