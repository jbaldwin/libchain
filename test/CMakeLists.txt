cmake_minimum_required(VERSION 3.0.2)
project(libchain_test CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN_TEST
    test_equality.cpp
    test_find.cpp
    test_join.cpp
    test_replace.cpp
    test_split.cpp
    test_strerror.cpp
    test_to_number.cpp
    test_transform.cpp
    test_trim.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES_LIB_CHAIN_TEST})
target_link_libraries(${PROJECT_NAME} PRIVATE chain)

if(CHAIN_CODE_COVERAGE)
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME} PRIVATE gcov)
endif()

add_test(NAME ChainTest COMMAND ${PROJECT_NAME})
