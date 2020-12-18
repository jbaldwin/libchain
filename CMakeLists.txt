cmake_minimum_required(VERSION 3.0.2)
project(chain CXX)

# Set the githooks directory to auto format and update the readme.
message("${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR} -> git config --local core.hooksPath .githooks")
execute_process(
    COMMAND git config --local core.hooksPath .githooks
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

option(CHAIN_BUILD_TESTS    "Build the tests. Default=ON" ON)
option(CHAIN_CODE_COVERAGE  "Enable code coverage, tests must also be enabled. Default=OFF" OFF)
option(CHAIN_BUILD_EXAMPLES "Build the examples. Default=ON" ON)

message("${PROJECT_NAME} CHAIN_BUILD_EXAMPLES = ${CHAIN_BUILD_EXAMPLES}")
message("${PROJECT_NAME} CHAIN_BUILD_TESTS    = ${CHAIN_BUILD_TESTS}")
message("${PROJECT_NAME} CHAIN_CODE_COVERAGE  = ${CHAIN_CODE_COVERAGE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN
    inc/chain/chain.hpp src/chain.cpp
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
    if(CHAIN_CODE_COVERAGE)
        target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
        target_link_libraries(${PROJECT_NAME} PRIVATE gcov)
    endif()

    enable_testing()
    add_subdirectory(test)
endif()

if(CHAIN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
