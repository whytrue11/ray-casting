#include "map.hpp"

#include "player.hpp"

Map::Map() :
  width_(15),
  height_(15),
  playerOnMap{0, 0}
{
  map_ += "###############";
  map_ += "#.............#";
  map_ += "#........#....#";
  map_ += "#.............#";
  map_ += "#.............#";
  map_ += "#.............#";
  map_ += "#......###....#";
  map_ += "#.............#";
  map_ += "#.............#";
  map_ += "#...#.........#";
  map_ += "#.............#";
  map_ += "#.............#";
  map_ += "#.......##....#";
  map_ += "#.............#";
  map_ += "###############";
}

void Map::renderingPlayer(const Player& player)
{
  if (playerOnMap.y != 0)
  {
    map_[playerOnMap.x + playerOnMap.y * width_] = '.';
  }

  int playerPosition = static_cast<int>(player.position().x + player.position().y * width_);
  if (map_[playerPosition] != '#')
  {
    map_[playerPosition] = player.getSymbol();
  }
}

const std::string& Map::string() const
{
  return map_;
}

bool Map::checkWall(const point_t& point) const
{
  return map_[static_cast<int>(point.x) + static_cast<int>(point.y) * width_] == '#';
}

int Map::getWidth() const
{
  return width_;
}

int Map::getHeight() const
{
  return height_;
}
