cmake_minimum_required(VERSION 3.0)

project(GTASA C CXX)

include_directories( source\\ source\\game_sa\\ source\\game_sa\\Animation\\ source\\game_sa\\Audio\\ source\\game_sa\\Collision\\ source\\game_sa\\Core\\ source\\game_sa\\Entity\\ source\\game_sa\\Entity\\Dummy\\ source\\game_sa\\Entity\\Object\\ source\\game_sa\\Entity\\Ped\\ source\\game_sa\\Entity\\Vehicle\\ source\\game_sa\\Enums\\ source\\game_sa\\Fx\\ source\\game_sa\\Models\\ source\\game_sa\\Plugins\\ source\\game_sa\\RenderWare\\ source\\game_sa\\RenderWare\\rw\\ source\\game_sa\\Scripts\\ source\\game_sa\\Tasks\\ source\\game_sa\\Tasks\\TaskTypes\\ ) 


set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")
file(
    GLOB_RECURSE _headerfiles_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path}/source/*.h*"
)

file(
    GLOB_RECURSE _sourcefiles_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path}/source/*.c*"
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gta_reversed)

add_library(gta_reversed SHARED ${_headerfiles_list} ${_sourcefiles_list})
set_target_properties(gta_reversed PROPERTIES SUFFIX ".asi")

target_link_libraries(gta_reversed debug "${_src_root_path}/source/detours.lib")
target_link_libraries(gta_reversed optimized "${_src_root_path}/source/detours.lib")

target_compile_definitions(gta_reversed PRIVATE NOMINMAX)

foreach(_header IN ITEMS ${_headerfiles_list})
	get_filename_component(_header_path "${_header}" PATH)
	string(REPLACE "/" "\\" _header_path_msvc "${_header_path}")
	string(REPLACE "source" "" _header_path_strip_source_filter "${_header_path_msvc}")
	source_group("\\Headers\\${_header_path_strip_source_filter}" FILES "${_header}")
endforeach()


foreach(_source IN ITEMS ${_sourcefiles_list})
	get_filename_component(_source_path "${_source}" PATH) 
	string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
	string(REPLACE "source" "Sources" _source_path_strip_source_filter "${_source_path_msvc}")
	source_group("${_source_path_strip_source_filter}" FILES "${_source}")
endforeach()


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /YuStdInc.h")

set_source_files_properties(source/StdInc.cpp
    PROPERTIES
    COMPILE_FLAGS "/YcStdInc.h"
    )

list(APPEND _sourcefiles_list StdInc.cpp)