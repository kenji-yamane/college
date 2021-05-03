cmake_minimum_required(VERSION 3.8)
project(list5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/binaries")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_subdirectory(lib)

add_executable(gaussian_sample gaussian_sample.cpp)
target_link_libraries(gaussian_sample lib)

add_executable(uniform_sample uniform_sample.cpp)
target_link_libraries(uniform_sample lib)

add_executable(ulam_sample ulam_sample.cpp)

add_executable(lorentz_attractor lorentz_attractor.cpp)
target_link_libraries(lorentz_attractor lib)

add_executable(lorentz_time_series lorentz_time_series.cpp)
target_link_libraries(lorentz_time_series lib)

