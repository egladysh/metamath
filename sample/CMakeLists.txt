cmake_minimum_required (VERSION 2.6)

project(mms)

if( APPLE )
	message( STATUS "***** Making OS X")
endif()

set( CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++" )

include_directories("../include")

file(GLOB src *.cpp *.h ../../include/*.h)

add_executable(mms ${src} )

target_link_libraries(mms)

