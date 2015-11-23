project(itrdevice) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory

AUX_SOURCE_DIRECTORY(./camera camera)
AUX_SOURCE_DIRECTORY(./joystick joystick)
#build all lib into a single one
add_library(itrdevice ${camera} ${joystick})

include_directories( "${itrdevice_SOURCE_DIR}/../itrbase")

target_link_libraries(itrdevice "${itrdevice_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


