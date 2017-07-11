cmake_minimum_required(VERSION 2.8)

project(LogBackup)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#	CXX_STANDARD 11
#	CXX_STANDARD_REQUIRED ON
#	CXX_EXTENSIONS OFF
#)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(${PROJECT_NAME}
	"entrypoint.cpp"
	"ProgArgs.cpp"
	"ProgArgs.h"
	)
