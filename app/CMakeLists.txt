cmake_minimum_required(VERSION 3.12...3.16)

add_executable(app main.cpp)

target_compile_features(app PRIVATE cxx_std_17)

target_include_directories(app PRIVATE ${Acoustics-Demos_SOURCE_DIR}/libs/libigl/include)

target_link_libraries(app PRIVATE fmt::fmt)
target_link_libraries(app PRIVATE acoustics_lib)
target_link_libraries(app PRIVATE polyscope)
target_link_libraries(app PRIVATE geometry-central)
