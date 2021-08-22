add_library(lib RungeKutta.cpp Lorentz.cpp)
target_link_libraries(lib Eigen3::Eigen)
