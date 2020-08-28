cmake_minimum_required(VERSION 3.10)

project(NCraft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


ADD_LIBRARY(NCraft 
  ${CMAKE_SOURCE_DIR}/src/NCraftMain.cpp
)

set(srcs 
   src/inc/math/Vec3f.h
)

file(GLOB srcs
    "src/*.h"
    "src/*.cpp"
    "src/inc/math/*.h"
    "src/math/*.cpp"
    # "src/inc/*.h"
)

# target_include_directories(NCraft PRIVATE ${CMAKE_SOURCE_DIR}/src/inc/)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
target_link_libraries(NCraft glfw)
target_link_libraries(NCraft ${GLFW3_LIBRARY})

# include_directories(${CMAKE_SOURCE_DIR}/glad/include/khr)

find_package(OpenGL REQUIRED)
target_link_libraries(NCraft OpenGL::GL)




include_directories(glad/include/)

include_directories(${CMAKE_SOURCE_DIR}/src/inc/math/)
include_directories(${CMAKE_SOURCE_DIR}/src/inc/)


include_directories(${CMAKE_SOURCE_DIR})

target_include_directories(NCraft PRIVATE "src/inc/")
# glad
add_library("glad" "glad/src/glad.c")
target_include_directories("glad" PRIVATE "glad/include/")
target_include_directories(NCraft PRIVATE "glad/include/")
target_link_libraries(NCraft "glad" "${CMAKE_DL_LIBS}")


add_executable(NCraftExe ${CMAKE_SOURCE_DIR}/src/NCraftMain.cpp ${srcs} )
target_link_libraries(NCraftExe NCraft)

