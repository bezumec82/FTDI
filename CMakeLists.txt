cmake_minimum_required( VERSION 3.17 )

project( SoundDevice LANGUAGES C CXX )

set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES  ON )

if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}" )
  message( SEND_ERROR "In-source builds are not allowed." )
endif ()

if( MINGW )
    message( "Compile using MINGW compiler : " ${MSVC_TOOLSET_VERSION} )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -std=c++17 -O0" )
elseif( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17" )
endif()

set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_INSTALL_PREFIX           ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out )

add_subdirectory(libs)