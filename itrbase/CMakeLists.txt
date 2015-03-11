project(itrbase) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

add_subdirectory(platform)#add subdirectory
add_subdirectory(encode)
add_subdirectory(math)
add_subdirectory(protocol)

#build all lib into a single one
add_library(itrbase $<TARGET_OBJECTS:platform> $<TARGET_OBJECTS:encode> $<TARGET_OBJECTS:math> $<TARGET_OBJECTS:protocol>)
