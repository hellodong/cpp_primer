cmake_minimum_required(VERSION 3.5)

project(implicity_cap_lambda CXX)

add_executable(impilicity_reference 	src/reference.cpp)
add_executable(impilicity_value 	src/value.cpp)
#add_executable(impilicity_mux1 		src/implici_refe.cpp)
#add_executable(impilicity_mux2 		src/implici_value.cpp)

install(TARGETS impilicity_reference impilicity_value
	RUNTIME DESTINATION usr/bin)

