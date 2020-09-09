cmake_minimum_required(VERSION 3.10)

project(NCraft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

ADD_LIBRARY(NCraft 
  ${CMAKE_SOURCE_DIR}/src/NCraftMain.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)


set(other_srcs 
  "src/inc/utils/std_image.h"
)

# target_include_directories(NCraft PRIVATE ${CMAKE_SOURCE_DIR}/src/inc/)
# target_include_directories(NCraft PRIVATE ${CMAKE_SOURCE_DIR}/src/inc/utils)

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

include_directories(${CMAKE_SOURCE_DIR}/src/inc/utils)


#FILE(COPY yourImg.png DESTINATION "${CMAKE_BINARY_DIR}") later on coping shaders and resourses
target_include_directories(NCraft PRIVATE "src/inc/")
# glad
add_library("glad" "glad/src/glad.c")
target_include_directories("glad" PRIVATE "glad/include/")
target_include_directories(NCraft PRIVATE "glad/include/")
target_include_directories(NCraft PRIVATE "src/inc/")

target_link_libraries(NCraft "glad" "${CMAKE_DL_LIBS}")


add_executable(NCraftExe ${CMAKE_SOURCE_DIR}/src/NCraftMain.cpp ${srcs} ${SOURCES} ${other_srcs})
target_include_directories(NCraftExe PRIVATE "{CMAKE_SOURCE_DIR}src/inc/")


target_link_libraries(NCraftExe NCraft)

