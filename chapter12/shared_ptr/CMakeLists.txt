cmake_minimum_required(VERSION 3.5)

project(shared_ptr CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (MSVC)
    message("Compiler msvc")
else()
if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")
else()
    message("build type: ${CMAKE_BUILD_TYPE}")
endif()

endif()

add_executable(shared_ptr 	src/shared_ptr.cpp)
add_executable(str_blob 	src/strblob.cpp src/strblob_impl.cpp)
add_executable(new          src/new_delete.cpp)

target_compile_features(shared_ptr PUBLIC cxx_auto_type)
target_compile_features(str_blob PUBLIC cxx_auto_type)
target_compile_features(new PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS shared_ptr str_blob new
	RUNTIME DESTINATION usr/bin)

