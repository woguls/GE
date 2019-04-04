cmake_minimum_required(VERSION 2.8.12)

project(sdlv8)

set(V8LIB ${PROJECT_SOURCE_DIR}/../GE/external/v8/v8/out.gn/x64.release.sample/obj/libv8_monolith.a)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package (Threads REQUIRED )
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    # ${PROJECT_SOURCE_DIR}/../GE/external/v8/
    # ${PROJECT_SOURCE_DIR}/../GE/external/v8/v8/include
    ${PROJECT_SOURCE_DIR}/external/v8/
    ${PROJECT_SOURCE_DIR}/external/v8/v8/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/external/v8pp
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/external
    )

message(STATUS "sdl include dir: ${SDL2_INCLUDE_DIRS}")
message(STATUS "sdl_image include dir: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "sdl_ttf include dir: ${SDL2_TTF_INCLUDE_DIR}")

add_executable(shell
    src/shell-main.cc
    src/shell/impl/shell.cc
    src/shell/impl/v8_embeddable.cc
    src/shell/impl/v8_platform.cc
    external/tinyxml-2/tinyxml2.cpp
    external/base64/base64.cpp
    external/miniz/miniz.c
    src/sdl-modules/impl/window_flags.cc
    src/sdl-modules/impl/render_flags.cc
    src/sdl-modules/impl/init_flags.cc
    src/sdl-modules/impl/sdl_init.cc
    src/sdl-modules/impl/sdl_window.cc
    src/sdl-modules/impl/sdl_renderer.cc
    src/sdl-modules/impl/sdl_surface.cc
    src/sdl-modules/impl/sdl_pixelformat.cc
    src/sdl-modules/impl/sdl_texture_access.cc
    src/sdl-modules/impl/sdl_texture.cc
    src/sdl-modules/impl/sdl_rect.cc
    src/sdl-modules/impl/sdl_ttf.cc
    src/sdl-modules/impl/sdl_event.cc
    src/resource-modules/impl/resource.cc
    src/resource-modules/impl/directory.cc
    src/resource-modules/impl/tileset_surface.cc
    src/resource-modules/impl/tilelayer_surface.cc
    src/resource-modules/impl/tilemap.cc
    src/threading-modules/impl/isolate.cc
    src/resource/impl/directory.cc
    src/resource/impl/reference.cc
    src/resource/impl/tilemap.cc
    external/v8pp/v8pp/context.cpp
)

set_property(TARGET shell PROPERTY CXX_STANDARD 17)
set_property(TARGET shell PROPERTY CXX_STANDARD_REQUIRED ON)

add_custom_command(
    TARGET shell POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/external/res $<TARGET_FILE_DIR:shell>/res)

add_custom_command(
    TARGET shell POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/js $<TARGET_FILE_DIR:shell>/js)

target_link_libraries(shell PRIVATE
    stdc++fs
    ${V8LIB}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARY}
    Threads::Threads
    dl
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOG_DEBUG_MESSAGES")
set(CMAKE_BUILD_TYPE Debug)

target_compile_definitions(shell PUBLIC $<$<CONFIG:DEBUG>:DEBUG>)