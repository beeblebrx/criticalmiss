cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(game STATIC
    src/game/Game.cpp
    src/game/Grid.cpp
    src/game/GameObject.cpp
    src/game/Player.cpp
    src/game/Enemy.cpp
    src/game/GameLoop.cpp
)
target_include_directories(game PUBLIC include)
target_compile_features(game PUBLIC cxx_std_17)

add_library(render STATIC
    src/render/Renderer.cpp
)
target_link_libraries(render PUBLIC game SFML::Graphics)

add_library(events STATIC
    src/events/EventHandler.cpp
)
target_link_libraries(events PUBLIC game SFML::Graphics)

add_executable(criticalmiss src/main.cpp)
target_link_libraries(criticalmiss PRIVATE render events)
