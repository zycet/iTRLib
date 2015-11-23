project(itrvision) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory
AUX_SOURCE_DIRECTORY(./camera  camera)
AUX_SOURCE_DIRECTORY(./feature feature)
AUX_SOURCE_DIRECTORY(./helper  helper)
AUX_SOURCE_DIRECTORY(./operation operation)
AUX_SOURCE_DIRECTORY(./process process)
#build all lib into a single one
add_library(itrvision ${cameraparameter} ${feature} ${helper} ${operation} ${process})

include_directories( "${itrvision_SOURCE_DIR}/../itrbase")
include_directories( "${itrvision_SOURCE_DIR}/../itralgorithm")
include_directories( "${itrvision_SOURCE_DIR}/../3rdparty/alglib")

target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )
target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../itralgorithm/bin/debug/libitralgorithm.a" )
target_link_libraries(itrvision "${itrvision_SOURCE_DIR}/../3rdparty/alglib/bin/debug/libalglib.a" )
