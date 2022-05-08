cmake_minimum_required(VERSION 3.12...3.16)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Acoustics-Demos_SOURCE_DIR}/include/acoustics/*.h")

add_library(acoustics_lib ${HEADER_LIST} eigen_frequency.cpp
        )
target_compile_features(acoustics_lib PRIVATE cxx_std_17)

target_include_directories(acoustics_lib PUBLIC ../include)

target_include_directories(acoustics_lib PRIVATE Eigen3::Eigen)

target_link_libraries(acoustics_lib PRIVATE fmt::fmt)

if(OpenMP_CXX_FOUND)
    target_link_libraries(acoustics_lib PRIVATE OpenMP::OpenMP_CXX)
endif()

target_link_libraries(acoustics_lib PRIVATE Eigen3::Eigen)
#target_link_libraries(acoustics_lib PRIVATE CGAL)
target_link_libraries(acoustics_lib PRIVATE geometry-central)