cmake_minimum_required(VERSION 3.7)
project(CV)

set(CMAKE_CXX_STANDARD 11)

#set(CXX_FLAGS
#        -std=c++11
#        )
#
#string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
#
#set(CMAKE_CXX_FLAGS_DEBUG "-O0")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "    OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/CV)

add_executable(CV main.cpp)
target_link_libraries(CV myCV ${OpenCV_LIBS})

add_subdirectory(myCV)