project(AVL_tree C CXX)
cmake_minimum_required(VERSION 3.9)


# define a macro that helps defining an option
macro(sfml_set_option var default type docstring)
    if (NOT DEFINED ${var})
        set(${var} ${default})
    endif ()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()


# determine whether to create a debug or release build
sfml_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")


# Set flags
set(CMAKE_CXX_STANDARD 11)


# Define sources and executable
set(EXECUTABLE_NAME "AVL_tree")
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GENERATED_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE GENERATED_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)


add_executable(${EXECUTABLE_NAME} main.cpp ${GENERATED_HEADERS} ${GENERATED_SOURCES})