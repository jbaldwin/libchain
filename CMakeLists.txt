cmake_minimum_required(VERSION 3.0.2)
project(chain CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES_LIB_CHAIN
    inc/chain/Chain.hpp src/Chain.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES_LIB_CHAIN})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

enable_testing()
add_subdirectory(test)
