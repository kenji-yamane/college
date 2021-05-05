cmake_minimum_required(VERSION 3.8)
project(tb1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/binaries")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_subdirectory(lib)

add_executable(lorentz_spectrum lorentz_spectrum.cpp)
target_link_libraries(lorentz_spectrum lib)

add_executable(lorentz_map_max lorentz_map_max.cpp)
target_link_libraries(lorentz_map_max lib)

add_executable(lorentz_ts_max lorentz_ts_max.cpp)
target_link_libraries(lorentz_ts_max lib)

