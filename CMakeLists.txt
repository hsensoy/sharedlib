cmake_minimum_required(VERSION 2.8.4)

SET( PROJ_NAME      "shared" )
SET( PROJ_PATH      ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH  ${CMAKE_BINARY_DIR} )
FILE( GLOB_RECURSE PROJ_SOURCES src/*.c )
FILE( GLOB_RECURSE PROJ_HEADERS include/${PROJ_NAME}/*.h )
SET( PROJ_INCLUDES  "include" "include/shared" )
SET( CMAKE_C_FLAGS "-std=gnu99 -O3 -g")
SET (${PROJ_NAME}_VERSION_MAJOR 0)
SET (${PROJ_NAME}_VERSION_MINOR 1)

PROJECT(${PROJ_NAME})
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

ADD_LIBRARY( ${PROJ_NAME} STATIC ${PROJ_SOURCES} )

enable_testing()
FILE( GLOB_RECURSE PROJ_TESTS tests/*.c )

install(TARGETS ${PROJ_NAME} DESTINATION lib/${PROJ_NAME})
install(FILES include/${PROJ_NAME}/debug.h include/${PROJ_NAME}/util.h include/${PROJ_NAME}/stringalgo.h include/${PROJ_NAME}/darray.h DESTINATION include/${PROJ_NAME})
