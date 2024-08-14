cmake_minimum_required (VERSION 3.8)
project (ASA4J)

# TODO wall
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 64bit compile
SET(CMAKE_CXX_FLAGS "-m64")
SET(CMAKE_C_FLAGS "-m64")
SET(CMAKE_EXE_LINKER_FLAGS "-m64")
SET(CMAKE_MODULE_LINKER_FLAGS "-m64")
SET(CMAKE_SHARED_LINKER_FLAGS "-m64")

set(CMAKE_POSITION_INDEPENDENT_CODE ON) # fPIC

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")

add_library(tar SHARED CoreCLRHost.cpp CoreCLRHost.hpp utils.hpp Sample1.h
	dynamicLinker/dynamicLinker.cpp)
target_link_libraries(tar dl stdc++fs)
target_include_directories(tar PUBLIC ${JNI_INCLUDE_DIRS} dynamicLinker)

add_jar(sample1 Sample1.java GENERATE_NATIVE_HEADERS sample-native)

execute_process(COMMAND dotnet build)
