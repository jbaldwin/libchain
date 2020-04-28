cmake_minimum_required(VERSION 3.0.2)
project(libchain_test CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN_TEST
    EqualityTest.hpp
    FindTest.hpp
    JoinTest.hpp
    ReplaceTest.hpp
    SplitTest.hpp
    StrerrorTest.hpp
    ToNumberTest.hpp
    TransformTest.hpp
    TrimTest.hpp

    # Included for full coverage, can't seem to get gvoc to pickup src/Chain.cpp yet
    ../inc/chain/Chain.hpp ../src/Chain.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES_LIB_CHAIN_TEST})
target_link_libraries(${PROJECT_NAME} PRIVATE chain)

if(CHAIN_CODE_COVERAGE)
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME} PRIVATE gcov)
endif()

add_test(NAME ChainTest COMMAND ${PROJECT_NAME})
