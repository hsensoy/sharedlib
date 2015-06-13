cmake_minimum_required(VERSION 2.8.4)

SET( PROJ_NAME      "shared" )
SET( PROJ_PATH      ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH  ${CMAKE_BINARY_DIR} )
FILE( GLOB_RECURSE PROJ_SOURCES src/*.c )
FILE( GLOB_RECURSE PROJ_HEADERS include/${PROJ_NAME}/*.h )
SET( PROJ_INCLUDES  "include" "include/shared" )
SET( CMAKE_C_FLAGS "-std=gnu99 -O3 -g -DNDEBUG")
SET (${PROJ_NAME}_VERSION_MAJOR 0)
SET (${PROJ_NAME}_VERSION_MINOR 1)

PROJECT(${PROJ_NAME})
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

ADD_LIBRARY( ${PROJ_NAME} STATIC ${PROJ_SOURCES} )

enable_testing()
SET ( PROJ_TESTS
   "tchashmap")

foreach( t ${PROJ_TESTS} )
       add_executable( test_${PROJ_NAME}_${t} tests/${t}.c)

          target_link_libraries( test_${PROJ_NAME}_${t} ${PROJ_NAME})
          add_test( test_${PROJ_NAME}_${t}  ./test_${PROJ_NAME}_${t} )
endforeach(t)

install(TARGETS ${PROJ_NAME} DESTINATION lib/${PROJ_NAME})
install(FILES include/${PROJ_NAME}/debug.h include/${PROJ_NAME}/util.h include/${PROJ_NAME}/stringalgo.h include/${PROJ_NAME}/darray.h include/${PROJ_NAME}/chashmap.h include/${PROJ_NAME}/murmurhash.h DESTINATION include/${PROJ_NAME})
