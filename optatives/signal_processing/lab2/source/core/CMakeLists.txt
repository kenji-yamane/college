add_library(core KalmanFilter.cpp Robot2DLocalizer.cpp BallTracker.cpp Clock.cpp Robot2DSimulator.cpp BallSimulator.cpp math/RandomUtils.cpp)
target_link_libraries(core Eigen3::Eigen)