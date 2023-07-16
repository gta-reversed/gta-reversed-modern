add_subdirectory(ogg EXCLUDE_FROM_ALL)
add_library(Ogg::ogg ALIAS ogg)
set(BUILD_SHARED_LIBS 1)
set(INSTALL_DOCS 0)
set(INSTALL_PKG_CONFIG_MODULE 0)
set(INSTALL_CMAKE_PACKAGE_MODULE 0)
set(OGG_LIBRARY ogg)
set(OGG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/ogg/include")
set(OGG_FOUND 1)

add_subdirectory(vorbis EXCLUDE_FROM_ALL)

option(SPDLOG_ENABLE_PCH "" ON)
option(SPDLOG_USE_STD_FORMAT "" ON)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

#############################################################################################
############# create the imgui project
#############################################################################################

set(IMGUI_DIR "imgui")
add_library(imgui STATIC)

target_sources(imgui PRIVATE
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp

    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx9.cpp

    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMGUI_DIR}/misc/
    ${IMGUI_DIR}/misc/cpp
    ${IMGUI_DIR}/misc/debuggers
)
target_link_libraries(imgui PRIVATE d3d9 ${CMAKE_DL_LIBS})
target_compile_definitions(imgui PRIVATE _CRT_SECURE_NO_WARNINGS)

# set options before add_subdirectory
# available options: TRACY_ENABLE , TRACY_ON_DEMAND , TRACY_NO_BROADCAST , TRACY_NO_CODE_TRANSFER , ...
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
option(TRACY_CALLSTACK "" ON)
add_subdirectory(tracy) # target: TracyClient or alias Tracy :: TracyClient
