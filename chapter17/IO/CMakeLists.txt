cmake_minimum_required(VERSION 3.5)

project(IO CXX)


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

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(file_tell_seek src/file_io.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_auto_type)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr)
target_compile_features(file_tell_seek PUBLIC cxx_constexpr)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

file(COPY "copy.out" DESTINATION "${PROJECT_BINARY_DIR}")

install(TARGETS ${PROJECT_NAME} file_tell_seek
	RUNTIME DESTINATION usr/bin)

