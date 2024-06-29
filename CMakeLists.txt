cmake_minimum_required(VERSION 3.21)

project(twx
	VERSION 0.1.0
	LANGUAGES C)

include(ExternalProject)

option(BUILD_TESTING "" OFF)
include(CTest)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory(vendor/json-c json-c)

add_library(${PROJECT_NAME} STATIC
	src/twx.c 
	src/modifiers.c
	src/modifier_table.c
	src/styledef.c
	src/to_json.c
	src/space.c 
	src/colors.c 
	src/border.c 
	src/strutil.c)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json-c ${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashmap)

target_link_libraries(${PROJECT_NAME} PRIVATE json-c)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

add_custom_target(combined ALL
	COMMAND ${CMAKE_AR} -x $<TARGET_FILE:${PROJECT_NAME}>
	COMMAND ${CMAKE_AR} -x $<TARGET_LINKER_FILE:json-c-static>
	COMMAND ${CMAKE_AR} -qcs libtwx.a *.o
	COMMAND rm -r ${CMAKE_BINARY_DIR}/*.o
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DEPENDS twx json-c-static)

if (BUILD_TESTING)
	add_subdirectory(vendor/unity unity)

	add_executable(${PROJECT_NAME}_test test/test.c)

	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

	target_link_libraries(${PROJECT_NAME}_test PRIVATE twx unity)
	add_test(
		NAME ${PROJECT_NAME}_test
		COMMAND ${PROJECT_NAME}_test)
endif()
