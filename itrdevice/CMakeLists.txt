project(itrdevice) #project name
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(LIBRARY_OUTPUT_PATH "bin/debug")#force change build directory
set(CMAKE_BUILD_TYPE DEBUG)	 #debug mode

#add subdirectory
add_subdirectory(camera)
add_subdirectory(joystick)

#build all lib into a single one
add_library(itrdevice $<TARGET_OBJECTS:camera> $<TARGET_OBJECTS:joystick>)

include_directories( "${itrdevice_SOURCE_DIR}/../itrbase")

target_link_libraries(itrdevice "${itrdevice_SOURCE_DIR}/../itrbase/bin/debug/libitrbase.a" )


