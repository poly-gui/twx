cmake_minimum_required(VERSION 3.21)

project(twx
	VERSION 0.1.0
	LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(twx src/twx.c src/space.c src/colors.c src/strutil.c)

target_include_directories(twx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

