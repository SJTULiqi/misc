project(misc)
cmake_minimum_required(VERSION 3.4)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

if(CMAKE_COMPILER_IS_GNUCXX)
    # add_definitions(-std=c++11) # for all compilers 
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}") # only for cxx compilers
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(findJobs findJobs.cpp)
add_executable(testSTLMap TestSTLMap.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/2048)
add_subdirectory(${PROJECT_SOURCE_DIR}/hannuo)
add_executable(division3 division3.cpp)
add_executable(lamp lamp.cpp)
add_executable(helpLostMan helpLostMan.cpp)
add_executable(numberPair numberPair.cpp)