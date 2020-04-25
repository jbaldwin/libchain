cmake_minimum_required(VERSION 3.0.2)
project(chain CXX)

option(CHAIN_BUILD_TESTS    "Build the tests. Default=ON" ON)
option(CHAIN_CODE_COVERAGE  "Enable code coverage, tests must also be enabled. Default=OFF" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN
    inc/chain/Chain.hpp src/Chain.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES_LIB_CHAIN})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wno-unknown-pragmas
        -Wall
        -Wextra
        -Weffc++
        -Werror
        -Wpedantic
        -pedantic-errors
    )
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Weffc++
        -Werror
        -Wpedantic
        -pedantic-errors
    )
endif()

if(CHAIN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
