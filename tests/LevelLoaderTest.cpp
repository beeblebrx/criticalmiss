#include <gtest/gtest.h>
#include "io/LevelLoader.hpp"
#include <stdexcept>

namespace {

TEST(LevelLoaderTest, LoadsAndParsesLevelFile) {
    io::LevelLoader loader;
    game::Level level = loader.load(LEVEL1_PATH);

    EXPECT_EQ(level.getWidth(), 16);
    EXPECT_EQ(level.getHeight(), 12);
    EXPECT_EQ(level.getName(), "The Entrance");
    EXPECT_FALSE(level.isPassable(0, 0));   // wall border
    EXPECT_TRUE(level.isPassable(1, 1));     // interior floor
}

TEST(LevelLoaderTest, MissingFileThrows) {
    io::LevelLoader loader;
    EXPECT_THROW(loader.load("/no/such/path/level.lvl"), std::runtime_error);
}

} // namespace
