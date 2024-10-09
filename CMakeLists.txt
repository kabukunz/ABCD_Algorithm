
cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME ABCD)

set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} CXX C)

# add eigen, igl, boost, openmp, matlab

# openmp
find_package(OpenMP)

if(NOT OpenMP_CXX_FOUND)
    message(FATAL_ERROR "Open MP not found for C++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# eigen
add_subdirectory(dependencies/eigen)

# sources
set(ABCD_SRC "${CMAKE_CURRENT_SOURCE_DIR}/mexed_solver/mex")

file(GLOB_RECURSE HEADERS ${ABCD_SRC}/*.h)
file(GLOB_RECURSE CC_SOURCES ${ABCD_SRC}/*.cc)
file(GLOB_RECURSE CPP_SOURCES ${ABCD_SRC}/*.cpp)

list(FILTER HEADERS EXCLUDE REGEX "pardiso_solver.h")
list(FILTER CC_SOURCES EXCLUDE REGEX "pardiso_solver.cc")

message("HEADERS" ${HEADERS})

# create library
add_library(${PROJECT_NAME} SHARED ${CC_SOURCES} ${CPP_SOURCES})

# includes
target_include_directories(${PROJECT_NAME} PUBLIC "${ABCD_SRC}/cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/eigen")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/libigl/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/matlab/extern/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/mexed_solver/VS_mex/simple_mex")
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS} ${OpenMP_CXX_INCLUDE_DIRS})

# linked libraries
target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})

unset(MATLAB_LIBRARIES)
list(APPEND MATLAB_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/matlab/bin/maci64/libeng.dylib")
list(APPEND MATLAB_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/matlab/bin/maci64/libmat.dylib")
list(APPEND MATLAB_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/matlab/bin/maci64/libmex.dylib")
list(APPEND MATLAB_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/matlab/bin/maci64/libmx.dylib")

target_link_libraries(${PROJECT_NAME} ${MATLAB_LIBRARIES})


# properties
# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})





# # target: OpenMP::OpenMP_CXX

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
# set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# add_executable(${PROJECT_NAME} ${SOURCES})

# target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS} ${OpenMP_CXX_INCLUDE_DIRS})

# target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})