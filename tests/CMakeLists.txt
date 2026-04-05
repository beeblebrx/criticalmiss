add_executable(game_tests
    GridTest.cpp
    GameTest.cpp
)

target_link_libraries(game_tests
    PRIVATE
        game
        GTest::gtest_main
)

target_compile_features(game_tests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(game_tests)
