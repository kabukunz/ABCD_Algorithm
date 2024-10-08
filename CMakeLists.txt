
# cmake_minimum_required(VERSION 2.8)
# project(ABCD)
# add_subdirectory(dependencies/eigen)
# add_subdirectory(mexed_solver)

# include_directories(dependencies/eigen/Eigen)


cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ABCD)

set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} CXX C)

# add eigen, igl, boost

# include(FetchContent)
# FetchContent_Declare(
#     eigen
#     GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
#     GIT_TAG 3.3.7
# )
# FetchContent_MakeAvailable(eigen)

add_subdirectory(dependencies/eigen)

set(ABCD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/mexed_solver)

file(GLOB_RECURSE HEADERS ${ABCD_SRC}/*.h)
message("HEADERS" ${HEADERS})
file(GLOB_RECURSE CC_SOURCES ${ABCD_SRC}/*.cc)
file(GLOB_RECURSE CPP_SOURCES ${ABCD_SRC}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${CC_SOURCES} ${CPP_SOURCES})

# TODO: need include dirs not headers!
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/eigen")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/mexed_solver/VS_mex/simple_mex")


# add linked libraries
# target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
