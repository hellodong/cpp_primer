cmake_minimum_required(VERSION 3.5)

project(bind_first_use CXX)

add_executable(${PROJECT_NAME} 	src/main.cpp src/textDecode.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_auto_type)

message("List features of compiler:${CMAKE_CXX_COMPILE_FEATURES}")

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION usr/bin)

