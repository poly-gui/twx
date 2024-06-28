cmake_minimum_required(VERSION 3.21)

include(ExternalProject)

project(twx
	VERSION 0.1.0
	LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory(vendor/json-c json-c)

# on mac, cmake finds compilers that do not include standard headers
# which causes problems for code that imports them.
# this piece of code is borrowed from https://github.com/nasa/trick/issues/979
if (CMAKE_SYSTEM_NAME MATCHES Darwin)
	if ((NOT DEFINED ${CMAKE_C_COMPILER}) AND (EXISTS /usr/bin/cc))
		set(CMAKE_C_COMPILER /usr/bin/cc)
	endif()
endif()

set(HASHMAP_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashmap)

ExternalProject_Add(hashmap
	PREFIX ${HASHMAP_LIB_PATH}
	SOURCE_DIR ${HASHMAP_LIB_PATH}
	BUILD_IN_SOURCE true
	CONFIGURE_COMMAND ""
	INSTALL_COMMAND ""
	BUILD_COMMAND ${CMAKE_C_COMPILER} -c ${HASHMAP_LIB_PATH}/hashmap.c && ${CMAKE_AR} cr ${CMAKE_BINARY_DIR}/libhashmap.a ${HASHMAP_LIB_PATH}/hashmap.o)

add_library(${PROJECT_NAME} STATIC src/twx.c src/space.c src/colors.c src/border.c src/strutil.c)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json-c ${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashmap)

target_link_libraries(${PROJECT_NAME} PRIVATE json-c ${CMAKE_BINARY_DIR}/libhashmap.a)
