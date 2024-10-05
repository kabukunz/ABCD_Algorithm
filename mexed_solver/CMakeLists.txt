cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME mexed_solver)

set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} CXX C)

# add eigen, igl, boost

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
# file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add linked libraries
# target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
