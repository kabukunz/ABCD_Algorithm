cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME mexed_solver)

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

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
message("HEADERS" ${HEADERS})
file(GLOB_RECURSE CC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${CC_SOURCES} ${CPP_SOURCES})

# TODO: need include dirs not headers!
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

# add linked libraries
# target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
