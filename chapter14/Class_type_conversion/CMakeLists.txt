cmake_minimum_required(VERSION 3.5)

project(class_type_convert CXX)


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

add_executable(smallint src/small_int.cpp)

add_executable(userdefine src/user_define.cpp)

add_executable(smallint_overlaod_operator src/smallint_overload_operator.cpp)

target_compile_features(smallint PUBLIC cxx_auto_type)
target_compile_features(userdefine PUBLIC cxx_auto_type)
#target_compile_features(hasPtr_ptr PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS smallint userdefine smallint_overlaod_operator 
	RUNTIME DESTINATION usr/bin)

