#include "io/LevelLoader.hpp"

#include "game/LevelParser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace io {

game::Level LevelLoader::load(const std::string& path) const {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Could not open level file: " + path);

    std::ostringstream contents;
    contents << file.rdbuf();

    game::LevelParser parser;
    return parser.parse(contents.str());
}

} // namespace io
