cmake_minimum_required(VERSION 3.5)

project(has_ptr CXX)


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

add_executable(hasPtr_val src/hasPtr_val.cpp )
#add_executable(hasPtr_ptr src/hasPtr_ptr.cpp )


target_compile_features(hasPtr_val PUBLIC cxx_auto_type)
#target_compile_features(hasPtr_ptr PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS hasPtr_val
	RUNTIME DESTINATION usr/bin)

