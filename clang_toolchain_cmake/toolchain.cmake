cmake_minimum_required(VERSION 3.5)

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER 			"/usr/bin/clang")
set(CMAKE_C_FLAGS	 			"-Wall -std=c11")
#set(CMAKE_C_FLAGS_DEBUG	 		"-g")
set(CMAKE_C_FLAGS_MINSIZEREL	"-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE		"-O4 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")


set(CMAKE_CXX_COMPILER 			"/usr/bin/clang++")
set(CMAKE_CXX_FLAGS	 			"-Wall -std=c++11")
#set(CMAKE_CXX_FLAGS_DEBUG	 	"-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL	"-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE		"-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_AR		"/usr/bin/llvm-ar")
set(CMAKE_LINKER	"/usr/bin/llvm-link")
set(CMAKE_NM		"/usr/bin/llvm-nm")
set(CMAKE_OBJDUMP	"/usr/bin/llvm-objdump")
set(CMAKE_RANLIB	"/usr/bin/llvm-ranlib")
