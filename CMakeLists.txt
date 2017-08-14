cmake_minimum_required(VERSION 3.8)

project(LogBackup)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#	CXX_STANDARD 17
#	CXX_STANDARD_REQUIRED ON
#)

set(CMAKE_CXX_FLAGS "-std=c++17 -lstdc++fs" )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(stdc++fs UNKNOWN IMPORTED)
#set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")

add_executable(${PROJECT_NAME}
	"entrypoint.cpp"
	"progArgs.cpp"
	"progArgs.h"
	)

target_link_libraries(${PROJECT_NAME} stdc++fs)
