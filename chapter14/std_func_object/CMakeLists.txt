cmake_minimum_required(VERSION 3.5)

project(std_func_obj CXX)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (MSVC)
    message("Compiler msvc")
else()

if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -fsanitize=address ")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")
else()
    message("build type: ${CMAKE_BUILD_TYPE}")
endif()

endif()

add_executable(std_func_obj src/std_func_obj.cpp)
add_executable(tmp_func_obj src/tmp_func_obj.cpp)
add_executable(binops src/map_std_function.cpp)

target_compile_features(std_func_obj PUBLIC cxx_auto_type)
target_compile_features(tmp_func_obj PUBLIC cxx_auto_type)
target_compile_features(binops PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS std_func_obj tmp_func_obj binops
	RUNTIME DESTINATION usr/bin)

