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

