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
add_executable(set_it 	src/set_iterator.cpp)
add_executable(traversal_map 	src/traversal_map.cpp)
add_executable(set_insert 	src/set_insert.cpp)
add_executable(map_insert 	src/map_insert.cpp)
add_executable(map_insert_rtn 	src/map_insert_rtn.cpp)
add_executable(access_element 	src/set_access_element.cpp)
add_executable(find_instead_index src/map_find_instead_index.cpp)

target_compile_features(map_it PUBLIC cxx_auto_type)
target_compile_features(set_it PUBLIC cxx_auto_type)
target_compile_features(traversal_map PUBLIC cxx_auto_type)
target_compile_features(set_insert PUBLIC cxx_auto_type)
target_compile_features(map_insert PUBLIC cxx_auto_type)
target_compile_features(map_insert_rtn PUBLIC cxx_auto_type)
target_compile_features(access_element PUBLIC cxx_auto_type)
target_compile_features(find_instead_index PUBLIC cxx_auto_type)

#message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS map_it set_it traversal_map set_insert map_insert map_insert_rtn access_element find_instead_index
	RUNTIME DESTINATION usr/bin)

