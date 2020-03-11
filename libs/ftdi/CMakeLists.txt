cmake_minimum_required( VERSION 3.14 )

project( ftdi LANGUAGES C CXX )

set( FTDI_INC_PATH "d:/Libraries/FTDI/include" )
# set( FTDI_LIB_PATH "d:/Libraries/FTDI/lib/Static/amd64" )
set( FTDI_LIB_PATH "d:/Libraries/FTDI/lib/amd64" )

########
### Test
########
if( WIN32 )
    set( EXECUTABLE_NAME ${PROJECT_NAME}Test )
else()
    set( EXECUTABLE_NAME ${PROJECT_NAME}Test.out )
endif()

include_directories( ${FTDI_INC_PATH} )
link_directories( ${FTDI_LIB_PATH} )

message( "Configuring test : ${PROJECT_NAME}Test.out${NORM}" )
file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp )
add_executable(
    ${EXECUTABLE_NAME}
    ${CXX_FILES}
)

target_link_libraries(
    ${EXECUTABLE_NAME}
LINK_PUBLIC
    ftd2xx.lib
)