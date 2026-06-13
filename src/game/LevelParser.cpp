#include "game/LevelParser.hpp"

#include <map>
#include <sstream>
#include <stdexcept>

namespace game {

namespace {

std::string trim(const std::string& s) {
    std::size_t begin = s.find_first_not_of(" \t\r");
    if (begin == std::string::npos)
        return "";
    std::size_t end = s.find_last_not_of(" \t\r");
    return s.substr(begin, end - begin + 1);
}

int parseInt(const std::map<std::string, std::string>& header,
             const std::string& key, int defaultValue) {
    auto it = header.find(key);
    if (it == header.end())
        return defaultValue;

    const std::string& value = it->second;
    try {
        std::size_t consumed = 0;
        int result = std::stoi(value, &consumed);
        if (consumed != value.size())
            throw std::invalid_argument("trailing characters");
        return result;
    } catch (const std::exception&) {
        throw std::invalid_argument("Level metadata '" + key + "' is not an integer: " + value);
    }
}

std::string parseLink(const std::map<std::string, std::string>& header,
                      const std::string& key) {
    auto it = header.find(key);
    if (it == header.end() || it->second == "-")
        return "";
    return it->second;
}

} // namespace

Level LevelParser::parse(const std::string& text) const {
    std::istringstream stream(text);
    std::string line;

    std::map<std::string, std::string> header;
    bool separatorFound = false;

    while (std::getline(stream, line)) {
        std::string trimmed = trim(line);
        if (trimmed == "---") {
            separatorFound = true;
            break;
        }
        if (trimmed.empty())
            continue;

        std::size_t colon = trimmed.find(':');
        if (colon == std::string::npos)
            throw std::invalid_argument("Malformed header line: " + line);

        std::string key = trim(trimmed.substr(0, colon));
        std::string value = trim(trimmed.substr(colon + 1));
        header[key] = value;
    }

    if (!separatorFound)
        throw std::invalid_argument("Level is missing the '---' map separator");

    std::vector<std::string> rows;
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        rows.push_back(line);
    }
    while (!rows.empty() && rows.back().empty())
        rows.pop_back();

    if (rows.empty())
        throw std::invalid_argument("Level has no map rows");

    int width = static_cast<int>(rows.front().size());
    int height = static_cast<int>(rows.size());

    for (const std::string& row : rows) {
        if (static_cast<int>(row.size()) != width)
            throw std::invalid_argument("Level map rows have inconsistent widths");
    }

    Level level(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = rows[y][x];
            switch (c) {
                case '#': level.setTile(x, y, makeTile(TileType::RockWall));  break;
                case '.': level.setTile(x, y, makeTile(TileType::RockFloor)); break;
                default:
                    throw std::invalid_argument(
                        std::string("Unknown map character: '") + c + "'");
            }
        }
    }

    auto nameIt = header.find("name");
    level.setName(nameIt != header.end() ? nameIt->second : "");
    level.setMonsterCount(parseInt(header, "monsters", 0));
    level.setTrapCount(parseInt(header, "traps", 0));
    level.setMaxItems(parseInt(header, "max_items", 0));
    level.setUpLevel(parseLink(header, "up"));
    level.setDownLevel(parseLink(header, "down"));

    return level;
}

} // namespace game
