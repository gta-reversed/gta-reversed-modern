cmake_minimum_required(VERSION 3.16)

project(GTASA C CXX)

#############################################################################################
############# create the gta_reversed project
#############################################################################################

if(MSVC_TOOLSET_VERSION)
    message("MSVC_TOOLSET_VERSION: ${MSVC_TOOLSET_VERSION}")
endif()

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS 1)
set(INSTALL_DOCS 0)
set(INSTALL_PKG_CONFIG_MODULE 0)
set(INSTALL_CMAKE_PACKAGE_MODULE 0)

# Put DLLs in root
set(CMAKE_INSTALL_BINDIR .)
# And other components in its own folder
set(CMAKE_INSTALL_LIBDIR gta-reversed/lib)
set(CMAKE_INSTALL_INCLUDEDIR gta-reversed/include)

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
if (MSVC)
    target_compile_options(gta_reversed PRIVATE "/MP" "/Zc:preprocessor" "/wd26812" "/wd26495")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
# DISABLE DEP. WARNINGS (GCC)
    target_compile_options(ogg PRIVATE "-w")
    #target_compile_options(imgui PRIVATE "-w")
    target_compile_options(vorbisfile PRIVATE "-w")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
# DISABLE DEP. WARNINGS (CLANG)
    target_compile_options(ogg PRIVATE "-Wno-everything")
    #target_compile_options(imgui PRIVATE "-Wno-everything")
    target_compile_options(vorbisfile PRIVATE "-Wno-everything")
endif()
set_target_properties(gta_reversed
    PROPERTIES
    SUFFIX ".asi"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

target_include_directories(gta_reversed PRIVATE
    source/
    source/toolsmenu/
    source/game_sa/
    source/game_sa/Debug/
    source/game_sa/Animation/
    source/game_sa/Attractors/

    source/game_sa/Audio/
    source/game_sa/Audio/Config
    source/game_sa/Audio/Entities
    source/game_sa/Audio/Hardware
    source/game_sa/Audio/Loaders
    source/game_sa/Audio/Managers
    source/game_sa/Audio/Utility

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
target_compile_definitions(gta_reversed PRIVATE
    _CRT_SECURE_NO_WARNINGS
    NOMINMAX
    USE_GTASA_ALLOCATOR
    EXTRA_DEBUG_FEATURES
    FIX_BUGS
)
target_compile_features(gta_reversed PRIVATE cxx_std_23)

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

target_precompile_headers(gta_reversed PRIVATE source/StdInc.cpp)
install(TARGETS gta_reversed DESTINATION .)

list(APPEND _sourcefiles_list StdInc.cpp)

#############################################################################################
############# create the imgui project
#############################################################################################

set(IMGUI_DIR "libs/imgui")
add_library(imgui STATIC)

target_sources(imgui
    PRIVATE
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp

    PRIVATE
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx9.cpp

    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(imgui
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    PUBLIC ${IMGUI_DIR}/misc/
    PUBLIC ${IMGUI_DIR}/misc/cpp
    PUBLIC ${IMGUI_DIR}/misc/debuggers
)
target_link_libraries(imgui PRIVATE d3d9 ${CMAKE_DL_LIBS})
target_compile_definitions(imgui PRIVATE _CRT_SECURE_NO_WARNINGS)
