cmake_minimum_required( VERSION 3.14 )

project( lira LANGUAGES C CXX )

###########
### Library
###########
message( "${CYN}Configuring library : ${PROJECT_NAME}${NOMR}" )
file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_library(
    ${PROJECT_NAME}
STATIC
    ${CXX_FILES}
)
target_include_directories(
    ${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

########
### Test
########
message( "${MAG}Configuring test : ${PROJECT_NAME}Test.out${NORM}" )
file( GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp )
add_executable(
    ${PROJECT_NAME}Test
    ${CXX_FILES}
)
target_link_libraries(
    ${PROJECT_NAME}Test
LINK_PUBLIC
    ${PROJECT_NAME}
)