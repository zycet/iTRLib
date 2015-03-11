project(itrsystem) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

AUX_SOURCE_DIRECTORY(. DIR)
ADD_LIBRARY(itrsystem  ${DIR})

include_directories( "${itrsystem_SOURCE_DIR}/../itrbase")
#include_directories( "../itrbase")
target_link_libraries(itrsystem "${itrsystem_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


