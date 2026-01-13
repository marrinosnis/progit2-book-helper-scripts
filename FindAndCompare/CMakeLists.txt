set(LIB_NAME FindCompare)

add_library(${LIB_NAME})

target_sources(${LIB_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/FindAndCompare.cpp
)
