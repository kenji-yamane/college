cmake_minimum_required(VERSION 3.8)
project(kalman_filtering)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/binaries")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(source)