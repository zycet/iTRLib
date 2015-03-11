project(itralgorithm) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory
add_subdirectory(classifier)
add_subdirectory(filter)

#build all lib into a single one
add_library(itralgorithm $<TARGET_OBJECTS:classifier> $<TARGET_OBJECTS:filter>)

include_directories( "${itralgorithm_SOURCE_DIR}/../itrbase")

target_link_libraries(itralgorithm "${itralgorithm_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


