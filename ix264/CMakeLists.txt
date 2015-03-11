project(ix264) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

AUX_SOURCE_DIRECTORY(. DIR)
ADD_LIBRARY(ix264  ${DIR})

include_directories( "${ix264_SOURCE_DIR}/../itrbase")

target_link_libraries(ix264 "${ix264_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


