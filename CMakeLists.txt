cmake_minimum_required( VERSION 3.12 )

if( WIN32 )
    add_definitions( /Dnot=! )
endif()

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )

#
# base
#
project( base )
add_executable( ${PROJECT_NAME}  src/main.cpp )
target_link_libraries( ${PROJECT_NAME} )
