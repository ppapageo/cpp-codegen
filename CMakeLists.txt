cmake_minimum_required(VERSION 2.8.8)
project(Codegen)
### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory.")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++14 -O3 -ldl")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_BOTH_LIBRARIES})

#============= Build info =================================

message(STATUS "System is " ${CMAKE_SYSTEM_NAME})
message(STATUS "Architecture is " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "Compiler is " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Source dir is " ${CMAKE_SOURCE_DIR})
message(STATUS "Source dir is " ${CMAKE_SOURCE_DIR})
message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "Linker Flags: " ${CMAKE_EXE_LINKER_FLAGS})

##Access CMAKE_CXX_FLAGS for codegen compilation
##For per target flags, export respective flags seperately

file(WRITE cmpflags.txt ${CMAKE_CXX_FLAGS})
##tests have to access flags too
file(WRITE build/cmpflags.txt ${CMAKE_CXX_FLAGS})

##Access templates from build
message(STATUS "Copying templates to " ${PROJECT_SOURCE_DIR}/build)
file(COPY ${PROJECT_SOURCE_DIR}/templates DESTINATION ${PROJECT_SOURCE_DIR}/build)
#==========================================================

include_directories(include)
set(SOURCE_DIR "src/")
add_subdirectory(${SOURCE_DIR})
#============= Install ======================

install(FILES cmpflags.txt
	DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY include
	DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY templates
	DESTINATION ${CMAKE_INSTALL_PREFIX})
