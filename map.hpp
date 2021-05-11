#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include "player.hpp"

class Map
{
public:
  Map();
  void renderingPlayer(const Player& player);
  const std::string& string() const;

  bool checkWall(const point_t& point) const;

  int getWidth() const;
  int getHeight() const;

private:
  std::string map_;
  int width_;
  int height_;

  point_t playerOnMap;
};

#endif