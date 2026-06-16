#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
namespace Roguelike {
class Maze {
public:
  enum class MazeCell {
    wall = 0,
    empty = 1,
    player = 2,
    enemy = 3,
  };
  Maze();
  Maze(int width, int height);

  std::vector<sf::Vector2f> CreateMaze();
  sf::Vector2f FindFreeCellPlayer();
  sf::Vector2f FindFreeCellEnemy();

  MazeCell &At(int x, int y);

private:
  int _width;
  int _height;
  std::vector<MazeCell> _map;
};
} // namespace Roguelike