project(itrvision) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory
add_subdirectory(camera)
add_subdirectory(feature)
add_subdirectory(helper)
add_subdirectory(operation)
add_subdirectory(process)

#build all lib into a single one
add_library(itrvision $<TARGET_OBJECTS:cameraparameter> $<TARGET_OBJECTS:feature> $<TARGET_OBJECTS:helper> $<TARGET_OBJECTS:operation> $<TARGET_OBJECTS:process>)

include_directories( "${itrvision_SOURCE_DIR}/../itrbase")
include_directories( "${itrvision_SOURCE_DIR}/../itralgorithm")
include_directories( "${itrvision_SOURCE_DIR}/../3rdparty/alglib")

target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )
target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../itralgorithm/bin/debug/libitralgorithm.a" )
target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../3rdparty/alglib/bin/debug/libalglib.a" )
