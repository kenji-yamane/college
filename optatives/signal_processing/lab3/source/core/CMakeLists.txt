add_library(core Clock.cpp DDRModel.cpp DDRLocalizer.cpp DDRSimulator.cpp math/RandomUtils.cpp math/MathUtils.cpp)
target_link_libraries(core Eigen3::Eigen)
include_directories(".")