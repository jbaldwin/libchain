cmake_minimum_required(VERSION 2.8)
project(chain_examples)

### readme ###
project(chain_readme CXX)
add_executable(${PROJECT_NAME} readme.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE chain)

### bench_replace ###
project(chain_bench_replace CXX)
add_executable(${PROJECT_NAME} bench_replace.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE chain pthread)
