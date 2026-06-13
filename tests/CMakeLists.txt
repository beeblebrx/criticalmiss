add_executable(game_tests
    GridTest.cpp
    GameTest.cpp
    EventHandlerTest.cpp
    GameLoopTest.cpp
    PartyTest.cpp
    PartyMemberTest.cpp
    CreatureTest.cpp
    ItemTest.cpp
    TrapTest.cpp
    TileTest.cpp
    LevelTest.cpp
    LevelParserTest.cpp
    EnemyTest.cpp
    LevelLoaderTest.cpp
    AttributeRandomizerTest.cpp
)

target_link_libraries(game_tests
    PRIVATE
        game
        io
        events
        GTest::gtest_main
)

target_compile_features(game_tests PRIVATE cxx_std_17)
target_compile_definitions(game_tests
    PRIVATE LEVEL1_PATH="${CMAKE_SOURCE_DIR}/assets/levels/level1.lvl")

include(GoogleTest)
gtest_discover_tests(game_tests)
