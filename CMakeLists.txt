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

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
    GIT_SHALLOW    ON
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(game STATIC
    src/game/Game.cpp
    src/game/Grid.cpp
    src/game/GameObject.cpp
    src/game/Animate.cpp
    src/game/Creature.cpp
    src/game/Inanimate.cpp
    src/game/Item.cpp
    src/game/Trap.cpp
    src/game/HealthPotion.cpp
    src/game/SpikeTrap.cpp
    src/game/Party.cpp
    src/game/Enemy.cpp
    src/game/GameLoop.cpp
    src/game/AttributeRandomizer.cpp
)
target_include_directories(game PUBLIC include)
target_compile_features(game PUBLIC cxx_std_17)

add_library(render STATIC
    src/render/Renderer.cpp
)
target_link_libraries(render PUBLIC game SFML::Graphics)

add_library(events STATIC
    src/events/EventHandler.cpp
    src/events/SFMLEventSource.cpp
)
target_link_libraries(events PUBLIC game SFML::Graphics)

add_executable(criticalmiss src/main.cpp)
target_link_libraries(criticalmiss PRIVATE render events)

enable_testing()
add_subdirectory(tests)
