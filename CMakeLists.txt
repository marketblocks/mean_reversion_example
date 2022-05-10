# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required (VERSION 3.8)

project ("mean_reversion_example")

add_subdirectory ("marketblocks")

enable_testing()

add_executable (mean_reversion_example "main.cpp" "strategy.h" "strategy.cpp")

target_link_libraries(mean_reversion_example marketblocks_lib)
target_include_directories(mean_reversion_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/marketblocks/src)
