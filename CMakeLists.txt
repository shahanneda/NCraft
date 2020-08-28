cmake_minimum_required(VERSION 3.10)

project(NCraft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_LIBRARY(NCraft 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)


# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
target_link_libraries(NCraft glfw)
target_link_libraries(NCraft ${GLFW3_LIBRARY})

find_package(OpenGL REQUIRED)
target_link_libraries(NCraft OpenGL::GL)




add_executable(NCraftExe ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(NCraftExe NCraft)

