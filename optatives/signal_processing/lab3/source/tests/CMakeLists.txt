set(CORE_DIR ../core)

include_directories(${CORE_DIR})

add_executable(DDR_ComponentTest DDR_ComponentTest.cpp)
target_link_libraries(DDR_ComponentTest core)