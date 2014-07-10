cmake_minimum_required (VERSION 2.8)

set(libname "sconf")
project(${libname} CXX)

option(SCONF_BUILD_TESTS "Build tests" ON)

set(libtype STATIC)

if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

if(MSVC)
	foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
	endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(src
#	"src/sconf.cpp"
#	"src/property.cpp"
	"src/property_base.cpp"
	"src/group.cpp"
	"src/cfg_helper.cpp"
	)

set(hdr_public
	"include/sconf/sconf.h"
	"include/sconf/group.h"
	"include/sconf/cfg.h"
	"include/sconf/cfg_helper.h"
	"include/sconf/property.h"
	"include/sconf/property_base.h"
	)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/jsoncpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/slog)

list(APPEND libs "jsoncpp")
list(APPEND libs "slog")

list(APPEND include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${libname} ${libtype} ${src} ${hdr_public})

set_target_properties(${libname} PROPERTIES
	PUBLIC_HEADER "${hdr_public}"
	INCLUDE_DIRECTORIES "${include_dirs}"
	INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}"
	)

target_link_libraries(${libname} ${libs})

if(SCONF_BUILD_TESTS)
	set(testname "sconf_tests")
	add_executable(${testname} EXCLUDE_FROM_ALL "tests/tests.cpp")
	target_link_libraries(${testname} ${libname})
endif()

install(TARGETS ${libname}
	LIBRARY DESTINATION lib COMPONENT lib
	ARCHIVE DESTINATION lib COMPONENT lib
	RUNTIME DESTINATION bin COMPONENT bin
	PUBLIC_HEADER DESTINATION include/sconf COMPONENT dev)
