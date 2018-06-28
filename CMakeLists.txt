cmake_minimum_required(VERSION 2.8)

project(GTASA C CXX)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")
file(
    GLOB_RECURSE _source_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path}/*.c*"
    "${_src_root_path}/*.h*"
)

add_library(gtasa_reversed SHARED ${_source_list})

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    message("${_source}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()
