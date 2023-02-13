cmake_minimum_required(VERSION 3.5)
set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER 			"/usr/bin/clang-15")
set(CMAKE_C_FLAGS	 			"-Wall -std=c11")
set(CMAKE_C_FLAGS_DEBUG	 		"-g")
set(CMAKE_C_FLAGS_MINSIZEREL	"-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE		"-O4 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")


set(CMAKE_CXX_COMPILER 			"/usr/bin/clang++-15")
set(CMAKE_CXX_FLAGS	 			"-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG	 	"-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL	"-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE		"-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_AR		"/usr/bin/llvm-ar-15")
set(CMAKE_LINKER	"/usr/bin/llvm-link-15")
set(CMAKE_NM		"/usr/bin/llvm-nm-15")
set(CMAKE_OBJDUMP		"/usr/bin/llvm-objdump-15")
set(CMAKE_RANLIB		"/usr/bin/llvm-ranlib-15")
