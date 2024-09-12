cmake_minimum_required(VERSION 3.5)

project(quate CXX)


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

add_executable(quate src/quate_virtual.cpp)
add_executable(bulkquate src/bulkquate_quate.cpp)
add_executable(quate_dft_para src/bulkquate_quate_dft_para.cpp)
add_executable(disc_quate src/Disc_quate.cpp)
add_executable(bulkquate_derived_disc src/bulkquate_derived_disc.cpp)

target_compile_features(quate PUBLIC cxx_auto_type)
target_compile_features(bulkquate PUBLIC cxx_auto_type)
target_compile_features(quate_dft_para PUBLIC cxx_auto_type)
target_compile_features(disc_quate PUBLIC cxx_auto_type)
target_compile_features(bulkquate_derived_disc PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS quate
	RUNTIME DESTINATION usr/bin)

