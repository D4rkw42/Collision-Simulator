cmake_minimum_required(VERSION 3.29.7)

project(
    Geometric-Collisions-Simulator
    VERSION 1.0
    DESCRIPTION "Simulação de colisões feita em C++ e SDL2, com base nos princípios da geometria analítica"
    HOMEPAGE_URL "https://github.com/D4rkw42/Collision-Simulator"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# dependencies

find_package(SDL2 CONFIG REQUIRED) # SDL.h library
find_package(SDL2_ttf CONFIG REQUIRED) # SDL_ttf.h library
find_package(effolkronium_random CONFIG REQUIRED) # effolkronium::random library

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SDL2_INCLUDE_DIRS})

# opções de compilação

add_compile_options(-O2) # optmization
add_compile_options(-pipe) # fast compiling
add_compile_options(-pedantic) # error handling

# building project

add_executable(
    geometric-collisions-simulator
    
    src/main.cpp

    src/system/global.cpp
    src/system/event-handler.cpp

    src/config/SDL2/config.cpp
    src/config/SDL2/graphics/Window.cpp
    src/config/SDL2/graphics/text.cpp
    
    src/app/application.cpp
    
    src/core/geometric/Line.cpp
    src/core/geometric/Shape.cpp
    src/core/geometric/colliders.cpp
    
    src/core/physics/physics.cpp
    
    src/utils/system/keyboard.cpp
    src/utils/system/mouse.cpp

    src/utils/world/camera.cpp)

# linking external libraries

target_link_libraries(
    geometric-collisions-simulator PRIVATE

    ${SDL2_LIBRARIES}
    SDL2_ttf::SDL2_ttf
    effolkronium_random)
