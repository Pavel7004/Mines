cmake_minimum_required (VERSION 3.10)

project (MinesGame)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (include_dir "${PROJECT_SOURCE_DIR}/inc")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (MinesGame ${source_files})

target_include_directories (MinesGame PRIVATE ${include_dir})
