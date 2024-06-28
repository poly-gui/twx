cmake_minimum_required(VERSION 3.21)

include(ExternalProject)

project(twx
	VERSION 0.1.0
	LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory(vendor/json-c json-c)

add_library(${PROJECT_NAME} STATIC src/twx.c src/space.c src/colors.c src/border.c src/strutil.c)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json-c ${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashmap)

target_link_libraries(${PROJECT_NAME} PRIVATE json-c)
