project(rekwarfare)
cmake_minimum_required(VERSION 2.8.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_gl_LIBRARY})
include_directories(${rekwarfare_SOURCE_DIR})

# Add global definitions
add_definitions("-std=c++11 -g -Wall -pedantic-errors -Wextra")


# Dependenc(y/ies)
add_library(json11 lib/json11/json11.cpp)

add_library(sharedObjs OBJECT
    util/Ustring.cpp
    net/NetTypes.cpp
    net/Protocol.cpp
    net/Client.cpp
    net/Server.cpp
)

# Client
add_library(rekwarfare
    util/UFile.cpp
    util/Ujson.cpp
    graphics/Window.cpp
    graphics/Drawer.cpp
    gui/GUIEntity.cpp
    gui/GUIEnvironment.cpp
    $<TARGET_OBJECTS:sharedObjs>
    map/Map.cpp
    Language.cpp
    Configuration.cpp
    util/FPSCounter.cpp
    net/Socket.cpp
    audio/SoundPlayer.cpp
)

target_link_libraries(rekwarfare
    ${SDL2_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLTTF_LIBRARY}
    json11
)
