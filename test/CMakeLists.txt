cmake_minimum_required(VERSION 3.0.2)
project(chain_test CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN_TEST
    JoinTest.hpp
    main.cpp
    SplitTest.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES_LIB_CHAIN_TEST})
add_test(NAME ChainTest COMMAND ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE chain)
