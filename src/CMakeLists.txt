cmake_minimum_required(VERSION 2.6)

file(
	GLOB SOURCE_FILES
	AbstractAlgorithm.cpp
)

include_directories(
)

link_directories(
)

link_libraries(
)

add_library(abstractalgorithm_shared SHARED ${SOURCE_FILES})
set_target_properties(abstractalgorithm_shared PROPERTIES OUTPUT_NAME "abstractalgorithm")

add_library(abstractalgorithm_static STATIC ${SOURCE_FILES})
set_target_properties(abstractalgorithm_static PROPERTIES OUTPUT_NAME "abstractalgorithm")

install(
	TARGETS abstractalgorithm_shared abstractalgorithm_static
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
)

set(HEADERS AbstractAlgorithm.h)
install(
	FILES ${HEADERS}
	DESTINATION "include"
)