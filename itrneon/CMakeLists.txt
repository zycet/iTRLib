project(itrneon) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory
add_subdirectory(math)

#build all lib into a single one
add_library(itrneon $<TARGET_OBJECTS:mathneon>)

include_directories( "${itrneon_SOURCE_DIR}/../itrbase")

target_link_libraries(itrneon "${itrneon_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


