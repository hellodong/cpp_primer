cmake_minimum_required(VERSION 3.5)

project(sales_data_copy CXX)


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

add_executable(${PROJECT_NAME} src/main.cpp src/Sales_data.cpp)
add_executable(NoCopy src/Nocopy.cpp )


target_compile_features(${PROJECT_NAME} PUBLIC cxx_auto_type)
target_compile_features(NoCopy PUBLIC cxx_auto_type)

message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS ${PROJECT_NAME} NoCopy
	RUNTIME DESTINATION usr/bin)

