cmake_minimum_required(VERSION 3.20)
project(criticalmiss LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED IMPORTED_TARGET
    sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(criticalmiss
    src/main.cpp
    src/game/Game.cpp
    src/game/Grid.cpp
    src/game/GameObject.cpp
    src/game/Player.cpp
    src/game/Enemy.cpp
)

target_include_directories(criticalmiss PRIVATE include)
target_link_libraries(criticalmiss PRIVATE PkgConfig::SFML)
