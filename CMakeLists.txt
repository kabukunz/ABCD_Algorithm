
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

# compile_with_pardiso =0;          %<-- Select Eigen/Pardiso linear solver
option(compile_with_pardiso           "compile_with_pardiso"              OFF)

# if(compile_with_pardiso)
#     set(_USE_PARDISO ON)
# endif()

# openmp flags
# compiler_option='/openmp';        % Compiler flags

# sources
set(ABCD_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(ABCD_SRC "${ABCD_DIR}/mexed_solver/mex")

file(GLOB_RECURSE HEADERS "${ABCD_SRC}/*.h")
file(GLOB_RECURSE CC_SOURCES "${ABCD_SRC}/*.cc")
file(GLOB_RECURSE CPP_SOURCES "${ABCD_SRC}/*.cpp")

# %% data load 
# clear mex
# mex(['-I',eigen_path], ['-I',inc_path], ['-I',igl_path], 'load_obj_mesh_mex.cc', 'cpp/common/util/mesh_obj_io.cc');

unset(DATA_LOAD_SOURCES)
list(APPEND DATA_LOAD_SOURCES "${ABCD_SRC}/load_obj_mesh_mex.cc")
list(APPEND DATA_LOAD_SOURCES "${ABCD_SRC}/cpp/common/util/mesh_obj_io.cc")

# Mesh Data initialization and distortion computation code
# mex( '-DMEX_COMPILE_FLAG',['COMPFLAGS="$COMPFLAGS ' compiler_option '"'],['-I',eigen_path],['-I',boost_path],...
#     ['-I',inc_path],['-I',VS_path],'GetMeshData_mex.cc', ...

unset(DATA_INIT_DIST_SOURCES)
list(APPEND DATA_INIT_DIST_SOURCES "${ABCD_SRC}/GetMeshData_mex.cc")

if(NOT compile_with_pardiso)

# %%  compile 2D ABCD solver for all iterations  with Eigen
# % Do not set _USE_PARDISO macro in linear_solver.h while compiling it
# if ~compile_with_pardiso
#     mex( '-DMEX_COMPILE_FLAG',['COMPFLAGS="$COMPFLAGS ' compiler_option '"'],['-I',eigen_path],['-I',boost_path],...
#         ['-I',inc_path],['-I',VS_path],'ABCD_FixerOptimizer_2d_mex.cc', ...
#         ['-I',VS_path],'ABCD_optimization_core_2d.cpp', ...

unset(2D_ABCD_EIGEN_SOLVER_SOURCES)
list(APPEND 2D_ABCD_EIGEN_SOLVER_SOURCES "${ABCD_SRC}/ABCD_FixerOptimizer_2d_mex.cc")
list(APPEND 2D_ABCD_EIGEN_SOLVER_SOURCES "${ABCD_SRC}/ABCD_optimization_core_2d.cpp")

# %%  compile ABCD 3D code with Eigen
# % Do not set _USE_PARDISO macro in linear_solver.h while compiling it
# mex( '-DMEX_COMPILE_FLAG',['COMPFLAGS="$COMPFLAGS ' compiler_option '"'],['-I',eigen_path],['-I',boost_path],...
#     ['-I',inc_path],['-I',VS_path],'ABCD_FixerOptimizer_3d_mex.cc', ...
#     ['-I',VS_path],'ABCD_optimization_core_3d.cpp', ...

unset(3D_ABCD_EIGEN_SOLVER_SOURCES)
list(APPEND 3D_ABCD_EIGEN_SOLVER_SOURCES "${ABCD_SRC}/ABCD_FixerOptimizer_3d_mex.cc")
list(APPEND 3D_ABCD_EIGEN_SOLVER_SOURCES "${ABCD_SRC}/ABCD_optimization_core_3d.cpp")

else()

# %% compile 2D ABCD  with Pardiso (Optional)
# pardiso_path = './';
# mex( '-DMEX_COMPILE_FLAG',['COMPFLAGS="$COMPFLAGS ' compiler_option '"'],['-I',eigen_path],['-I',boost_path],...
#     ['-I',inc_path],['-I',VS_path],'ABCD_FixerOptimizer_2d_mex.cc', ...
#     ['-I',VS_path], ['-L' pardiso_path], ...
# 'ABCD_optimization_core_2d.cpp', ...

# 'cpp/common/solver/pardiso/pardiso_solver.cc', ...

# %%  ABCD 3D code  with Pardiso (Optional)
# % Set "#define _USE_PARDISO 1" in  linear_solver.h
# % Put pardiso binaries in /mexed_solver/mex/, and link it with  mex
# pardiso_path = './';
# mex( '-DMEX_COMPILE_FLAG',['COMPFLAGS="$COMPFLAGS ' compiler_option '"'],['-I',eigen_path],['-I',boost_path],...
#     ['-I',inc_path],['-I',VS_path], ['-L' pardiso_path], ...
#     'ABCD_FixerOptimizer_3d_mex.cc', ...
#     ['-I',VS_path],'ABCD_optimization_core_3d.cpp', ...

# 'cpp/common/solver/pardiso/pardiso_solver.cc', ...

endif()

# exclude pardiso
if(NOT compile_with_pardiso)
    list(FILTER HEADERS EXCLUDE REGEX "pardiso_solver.h")
    list(FILTER CC_SOURCES EXCLUDE REGEX "pardiso_solver.cc")
endif()

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
# list(APPEND MATLAB_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/matlab/bin/maci64/mex")

target_link_libraries(${PROJECT_NAME} ${MATLAB_LIBRARIES})

# create main
set(ABCD_MAIN "${ABCD_DIR}/wrapper")
add_executable(${PROJECT_NAME}_main "${ABCD_MAIN}/main.cpp")
target_link_libraries(${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME})

# properties
set_target_properties(${PROJECT_NAME}_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})


