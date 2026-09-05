cmake_minimum_required(VERSION 3.15)
project(Sim VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(ext include)

add_executable(sim src/main.cpp)
add_executable(dbg_sim src/main.cpp)

target_compile_features(sim PRIVATE cxx_std_20)
target_compile_features(dbg_sim PRIVATE cxx_std_20)

target_compile_definitions(sim PRIVATE ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(dbg_sim PRIVATE ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# --- TESTS ---

add_executable(sim_tests tests/test_thrust_curve.cpp)
target_compile_features(sim_tests PRIVATE cxx_std_20)
target_compile_definitions(sim_tests PRIVATE ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME ThrustTests COMMAND sim_tests)
# target_compile_definitions(sim_tests PRIVATE ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
