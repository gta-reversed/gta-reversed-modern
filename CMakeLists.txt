cmake_minimum_required(VERSION 3.0)

project(GTASA C CXX)

#############################################################################################
############# create the gta_reversed project
#############################################################################################

add_subdirectory(libs/ogg)
add_library(Ogg::ogg ALIAS ogg)

set(OGG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/ogg/include")
set(OGG_LIBRARY ogg)
set(OGG_FOUND 1)

add_subdirectory(libs/vorbis)

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

add_library(gta_reversed MODULE ${_headerfiles_list} ${_sourcefiles_list} .editorconfig)
set_target_properties(gta_reversed PROPERTIES SUFFIX ".asi")

target_include_directories(gta_reversed PRIVATE
    source/
    source/toolsmenu/
    source/game_sa/
    source/game_sa/Debug/
    source/game_sa/Animation/
    source/game_sa/Audio/
    source/game_sa/Collision/
    source/game_sa/Core/
    source/game_sa/Entity/
    source/game_sa/Entity/Dummy/
    source/game_sa/Entity/Object/
    source/game_sa/Entity/Ped/
    source/game_sa/Entity/Vehicle/
    source/game_sa/Enums/
    source/game_sa/Events/
    source/game_sa/Fx/
    source/game_sa/Models/
    source/game_sa/Plugins/
    source/game_sa/RenderWare/
    source/game_sa/RenderWare/rw/
    source/game_sa/Scripts/
    source/game_sa/Tasks/
    source/game_sa/Tasks/TaskTypes/
    libs/imgui/
    libs/imgui/misc/cpp/
)
target_link_libraries(gta_reversed ogg ${OGG_LIBRARY} imgui vorbisfile)
target_compile_definitions(gta_reversed PRIVATE NOMINMAX _CRT_SECURE_NO_WARNINGS USE_GTASA_ALLOCATOR)

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

if (MSVC)
   set_target_properties(gta_reversed PROPERTIES COMPILE_FLAGS "/YuStdInc.h")
   set_source_files_properties(source/StdInc.cpp PROPERTIES COMPILE_FLAGS "/YcStdInc.h")
endif(MSVC)

list(APPEND _sourcefiles_list StdInc.cpp)

#############################################################################################
############# create the imgui project
#############################################################################################

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(IMGUI_FILES_1 imconfig.h imgui.cpp imgui.h imgui_demo.cpp imgui_draw.cpp imgui_internal.h imgui_widgets.cpp imstb_rectpack.h imstb_textedit.h imstb_truetype.h)
set(IMGUI_FILES_2 imgui_stdlib.h imgui_stdlib.cpp)

foreach(_file_name IN ITEMS ${IMGUI_FILES_1})
    list(APPEND IMGUI_ALL_FILES "libs/imgui/${_file_name}")
endforeach()

foreach(_file_name IN ITEMS ${IMGUI_FILES_2})
    list(APPEND IMGUI_ALL_FILES "libs/imgui/misc/cpp/${_file_name}")
endforeach()

add_library(imgui STATIC ${IMGUI_ALL_FILES} )
target_include_directories(imgui PRIVATE
    libs/imgui/
    libs/imgui/misc/cpp/
)
target_compile_definitions(imgui PRIVATE _CRT_SECURE_NO_WARNINGS)
