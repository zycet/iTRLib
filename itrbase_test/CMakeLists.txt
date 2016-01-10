project(itrbase_test) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)  #debug mode

AUX_SOURCE_DIRECTORY(./ test)
include_directories("${itrbase_test_SOURCE_DIR}/../itrbase")

add_executable(itrbase_test ${test})
target_link_libraries(itrbase_test "${itrbase_test_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a")
