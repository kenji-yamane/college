add_library(lib RandomUtils.cpp RungeKutta.cpp Lorentz.cpp)
target_link_libraries(lib Eigen3::Eigen)
