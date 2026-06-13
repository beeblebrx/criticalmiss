#include <gtest/gtest.h>
#include "game/LevelParser.hpp"
#include <stdexcept>

namespace {

const char* const kValidLevel =
    "name: The Entrance\n"
    "monsters: 2\n"
    "traps: 1\n"
    "max_items: 3\n"
    "up: -\n"
    "down: level2\n"
    "---\n"
    "#####\n"
    "#...#\n"
    "#####\n";

TEST(LevelParserTest, ParsesDimensions) {
    game::LevelParser parser;
    game::Level level = parser.parse(kValidLevel);

    EXPECT_EQ(level.getWidth(), 5);
    EXPECT_EQ(level.getHeight(), 3);
}

TEST(LevelParserTest, ParsesWallsAndFloors) {
    game::LevelParser parser;
    game::Level level = parser.parse(kValidLevel);

    EXPECT_FALSE(level.isPassable(0, 0));  // wall border
    EXPECT_FALSE(level.isPassable(2, 0));  // top wall
    EXPECT_TRUE(level.isPassable(1, 1));   // interior floor
    EXPECT_TRUE(level.isPassable(3, 1));
}

TEST(LevelParserTest, ParsesMetadata) {
    game::LevelParser parser;
    game::Level level = parser.parse(kValidLevel);

    EXPECT_EQ(level.getName(), "The Entrance");
    EXPECT_EQ(level.getMonsterCount(), 2);
    EXPECT_EQ(level.getTrapCount(), 1);
    EXPECT_EQ(level.getMaxItems(), 3);
}

TEST(LevelParserTest, ParsesLinksWithDashAsEmpty) {
    game::LevelParser parser;
    game::Level level = parser.parse(kValidLevel);

    EXPECT_EQ(level.getUpLevel(), "");
    EXPECT_EQ(level.getDownLevel(), "level2");
}

TEST(LevelParserTest, MissingSeparatorThrows) {
    game::LevelParser parser;
    EXPECT_THROW(parser.parse("name: X\n#####\n"), std::invalid_argument);
}

TEST(LevelParserTest, RaggedRowsThrow) {
    game::LevelParser parser;
    EXPECT_THROW(parser.parse("---\n#####\n#..#\n"), std::invalid_argument);
}

TEST(LevelParserTest, UnknownCharacterThrows) {
    game::LevelParser parser;
    EXPECT_THROW(parser.parse("---\n#####\n#.X.#\n#####\n"), std::invalid_argument);
}

TEST(LevelParserTest, NonIntegerMetadataThrows) {
    game::LevelParser parser;
    EXPECT_THROW(parser.parse("monsters: lots\n---\n###\n"), std::invalid_argument);
}

TEST(LevelParserTest, EmptyMapThrows) {
    game::LevelParser parser;
    EXPECT_THROW(parser.parse("name: X\n---\n"), std::invalid_argument);
}

} // namespace
