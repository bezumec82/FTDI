cmake_minimum_required( VERSION 3.17 )

project( FTDI LANGUAGES C CXX )

set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES  ON )

if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}" )
  message( SEND_ERROR "In-source builds are not allowed." )
endif ()

set( FTDI_INC_PATH "d:/Libraries/FTDI/include" )
# set( FTDI_LIB_PATH "d:/Libraries/FTDI/lib/Static/amd64" )
set( FTDI_LIB_PATH "d:/Libraries/FTDI/lib/amd64" )

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

include_directories( ${FTDI_INC_PATH} )
link_directories( ${FTDI_LIB_PATH} )

file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_executable( 
    ${PROJECT_NAME}
    ${CXX_FILES}
)

message( "FTDI library : ${FTDI_LIB}" )
target_link_libraries (
    ${PROJECT_NAME}
LINK_PUBLIC
    ftd2xx.lib
)