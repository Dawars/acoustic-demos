cmake_minimum_required(VERSION 3.12...3.16)
project(Acoustics-Demos VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(OpenMP)
find_package(Eigen3 REQUIRED)

add_subdirectory(libs/fmt)
#add_subdirectory(libs/cgal)

add_subdirectory(libs/geometry-central)
add_subdirectory(libs/polyscope)
# Add libIGL
option(LIBIGL_COPYLEFT_TETGEN "Use Tetgen (Copyleft)" ON)
include(libigl)

add_subdirectory(src)
add_subdirectory(app)