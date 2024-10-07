
cmake_minimum_required(VERSION 2.8)
project(ABCD)
add_subdirectory(dependencies/eigen)
add_subdirectory(mexed_solver)

include_directories(dependencies/eigen/Eigen)