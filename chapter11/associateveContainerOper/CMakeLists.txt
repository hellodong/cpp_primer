cmake_minimum_required(VERSION 3.5)

project(associative_container_operate CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")
else()
    message("build type: ${CMAKE_BUILD_TYPE}")
endif()

add_executable(map_it 	src/map_iterator.cpp)

target_compile_features(map_it PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS map_it
	RUNTIME DESTINATION usr/bin)

