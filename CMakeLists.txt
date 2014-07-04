cmake_minimum_required (VERSION 2.8)

set(libname "sconf")
project(${libname} CXX)

option(SCONF_BUILD_TESTS "Build tests" ON)

set(libtype STATIC)

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

set(SLOG_BUILD_TESTS OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/jsoncpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/slog)

list(APPEND libs "jsoncpp")
list(APPEND libs "slog")

list(APPEND include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/include")
list(APPEND include_dirs "${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include")
list(APPEND include_dirs "${CMAKE_SOURCE_DIR}/vendor/slog/include")

add_library(${libname} ${libtype} ${src} ${hdr_public})

set_target_properties(${libname} PROPERTIES
	PUBLIC_HEADER "${hdr_public}"
	INCLUDE_DIRECTORIES "${include_dirs}")

target_link_libraries(${libname} ${libs})

if(SCONF_BUILD_TESTS)
	add_executable(tests "tests/tests.cpp")
	set_target_properties(tests PROPERTIES
		INCLUDE_DIRECTORIES "${include_dirs}")
	target_link_libraries(tests ${libname})
endif()

install(TARGETS ${libname}
	LIBRARY DESTINATION lib COMPONENT lib
	ARCHIVE DESTINATION lib COMPONENT lib
	RUNTIME DESTINATION bin COMPONENT bin
	PUBLIC_HEADER DESTINATION include COMPONENT dev)