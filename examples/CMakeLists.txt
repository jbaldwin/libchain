cmake_minimum_required(VERSION 2.8)
project(chain_examples)

### readme ###
project(chain_readme CXX)
add_executable(${PROJECT_NAME} readme.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE chain)
