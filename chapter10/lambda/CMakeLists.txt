cmake_minimum_required(VERSION 3.5)

project(lambda CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION usr/bin)

