cmake_minimum_required(VERSION 3.15)
project(Sim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(ext include)

add_executable(sim src/main.cpp)
add_executable(dbg_sim src/main.cpp)

target_compile_features(sim PRIVATE cxx_std_20)
target_compile_features(dbg_sim PRIVATE cxx_std_20)

target_compile_definitions(sim PRIVATE ROOT_DIR=${CMAKE_CURRENT_SOURCE_DIR})

