cmake_minimum_required(VERSION 3.22)
project(Cpp-Platformer)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME}
        game/main.cpp
        game/entities/Player.cpp
        game/window/GameWindow.cpp
        game/utils/fpscounter.h
        game/utils/fpscounter.cpp game/entities/Enemy.cpp game/entities/Enemy.h)  # Include FPSCounter source files

include_directories(
        ${PROJECT_SOURCE_DIR}/game
        ${PROJECT_SOURCE_DIR}/game/entities
        ${PROJECT_SOURCE_DIR}/game/window
        ${PROJECT_SOURCE_DIR}/game/utils)  # Add the "utils" folder to include directories

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
find_package(SDL2_ttf REQUIRED)
if(SDL2_TTF_FOUND)
    include_directories(${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
endif()
