project(rekwarfare-engine)
cmake_minimum_required(VERSION 2.8.8)

set(RWENGINE_ALLOW_TESTS true)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_gl_LIBRARY})
include_directories(${rekwarfare-engine_SOURCE_DIR})

# Add global definitions
add_definitions("-std=c++11 -g -Wall -pedantic-errors -Wextra")

# Client
add_library(rekwarfare-engine
    system/System.cpp
    system/Input.cpp
    util/UString.cpp
    util/FPSCounter.cpp
    graphics/Window.cpp
    graphics/Drawer.cpp
    ent/Entity.cpp
    gui/GUIEntity.cpp
    gui/GUIEnvironment.cpp
    gui/Button.cpp
    net/NetTypes.cpp
    net/Client.cpp
    net/Server.cpp
    net/Socket.cpp
    audio/SoundPlayer.cpp
)

target_link_libraries(rekwarfare-engine
    ${SDL2_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLTTF_LIBRARY}
)

# TEST(S)
if(RWENGINE_ALLOW_TESTS)
add_executable(t1 test/t1/main.cpp)
target_link_libraries(t1
    ${SDL2_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLTTF_LIBRARY}
    rekwarfare-engine
)
add_executable(t2 test/t2/main.cpp)
target_link_libraries(t2
    ${SDL2_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLTTF_LIBRARY}
    rekwarfare-engine
)
endif(RWENGINE_ALLOW_TESTS)
