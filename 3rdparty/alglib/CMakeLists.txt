project(alglib) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

AUX_SOURCE_DIRECTORY(. DIR)
ADD_LIBRARY(container OBJECT ${DIR})
