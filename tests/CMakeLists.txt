cmake_minimum_required(VERSION "2.8.1")

PROJECT(tests)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

include_directories(../src)
file(GLOB SRC
    *.cpp
    *.hpp
    ../src/*.cpp
    ../src/*.hpp
    )

set(tests
    test_1
    )

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

foreach(test ${tests})
    add_executable(${test} ${test}.cpp ${SRC})
    target_link_libraries(${test} ${CMAKE_THREAD_LIBS_INIT})
    add_test(NAME ${test} COMMAND ${test})
    #set_tests_properties(${test} PROPERTIES TIMEOUT 10)
endforeach()

#Check whether all tests in the current folder are present
file(READ "${CMAKE_CURRENT_LIST_FILE}" CURRENT_LIST_FILE_CONTENT)
file(GLOB ALL_TEST_SOURCES "test_*.cpp")
foreach(TEST_SOURCE ${ALL_TEST_SOURCES})
    get_filename_component(TESTNAME "${TEST_SOURCE}" NAME_WE)
    string(REGEX MATCH "${TESTNAME}" MATCH_TESTNAME "${CURRENT_LIST_FILE_CONTENT}")
    if (NOT MATCH_TESTNAME)
        message(AUTHOR_WARNING "Test '${TESTNAME}' is not known to CTest.")
    endif()
endforeach()
