cmake_minimum_required(VERSION 3.5)

project(sepcific_container_alg CXX)

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

add_executable(gen_data		src/gen_odd_even.cpp)
add_executable(lst_merge 	src/lst_merge.cpp)
add_executable(lst_splice 	src/lst_splice.cpp)

target_compile_features(gen_data PUBLIC cxx_auto_type)
target_compile_features(lst_merge PUBLIC cxx_auto_type)
target_compile_features(lst_splice PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS gen_data lst_merge lst_splice
	RUNTIME DESTINATION usr/bin)

