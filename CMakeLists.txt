cmake_minimum_required(VERSION 3.16)
project(smooth_3d_model)

set(CMAKE_CXX_STANDARD 14)

add_executable(a main.cpp model_wrapper.cpp data.cpp modified_mesh.cpp)

target_link_libraries(a -lassimp)