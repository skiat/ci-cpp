cmake_minimum_required(VERSION 3.2)

project(ci-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} "main.cpp")



configure_file( CMakeLists.txt.in googletest-download/CMakeLists.txt )
execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process( COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory( ${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build )
                 
set(UNIT_TESTS, basic-test.cpp)

# these steps compile and link the unit-tests executable
enable_testing()  # gives us a make test target
add_test( all unit-tests ) # gives us a make test all target
add_executable( unit-tests test-main.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
TARGET_INCLUDE_DIRECTORIES( unit-tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries( unit-tests LINK_PUBLIC
    gtest
    gmock
)


IF (UNIX)
    SET(CHECK_COVERAGE ON)
ENDIF (UNIX)
if (CHECK_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage.cmake)
    setup_target_for_coverage(${PROJECT_NAME}_coverage unit-tests coverage)
ENDIF (CHECK_COVERAGE)


