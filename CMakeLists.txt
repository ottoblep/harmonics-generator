cmake_minimum_required(VERSION 3.20)

project(harmonics_generator)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

install(TARGETS harmonics_generator DESTINATION bin)
