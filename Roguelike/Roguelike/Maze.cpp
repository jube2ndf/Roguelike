#include "Maze.h"
#include "Wall.h"

Roguelike::Maze::Maze() : Maze(25, 25) {}

Roguelike::Maze::Maze(int width, int height) {
  this->_height = height;
  this->_width = width;
  this->_map.assign(this->_height * this->_width, MazeCell::wall);
}

std::vector<sf::Vector2f> Roguelike::Maze::CreateMaze() {
  int x = 1;
  int y = 1;

  int rx = 0, ry = 0, rw = 0, rh = 0;

  for (int i = 0; i < this->_width * this->_height * 0.05; i++) {
    rw = 2 + rand() % static_cast<int>(this->_width*0.1);
    rh = 2 + rand() % static_cast<int>(this->_height * 0.1);

    rx = 1 + rand() % (this->_width - rw - 2);
    ry = 1 + rand() % (this->_height - rh - 2);

    for (int y = ry; y < ry + rh; y++) {
      for (int x = rx; x < rx + rw; x++) {
        this->_map[y * this->_width + x] = MazeCell::empty;
      }
    }
  }
  x = rx + rw / 2;
  y = ry + rh / 2;
  this->_map[y * this->_width + x] = MazeCell::empty;
  std::vector<std::pair<int, int>> dirs = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
  for (int i = 0; i < this->_width * this->_height * 0.3; i++) {
    int dirIndex = rand() % 4;

    int nx = x + dirs[dirIndex].first;
    int ny = y + dirs[dirIndex].second;

    if (nx > 0 && ny > 0 && nx < this->_width - 1 && ny < this->_height - 1) {
      this->_map[ny * this->_width + nx] = MazeCell::empty;
      this->_map[((y + ny) / 2) * this->_width + ((x + nx) / 2)] =
          MazeCell::empty;

      x = nx;
      y = ny;
    }
  }
  std::vector<sf::Vector2f> walls;
  for (int y = 0; y < this->_height; y++) {
    for (int x = 0; x < this->_width; x++) {
      if (this->_map[y * this->_width + x] == MazeCell::wall
          ) {
        walls.push_back({x * 32.f, y * 32.f});
      }
    }
  }
  return walls;
}

sf::Vector2f Roguelike::Maze::FindFreeCellPlayer() {
  for (int i = 0; i < this->_height * this->_width; i++) {
    int x = rand() % this->_width;
    int y = rand() % this->_height;

    if (this->_map[y * this->_width + x] == MazeCell::empty) {
      this->_map[y * this->_width + x] = MazeCell::player;
      return {x * 32.f, y * 32.f};
    }
  }
}

sf::Vector2f Roguelike::Maze::FindFreeCellEnemy() {
  for (int i = 0; i < this->_height * this->_width; i++) {
    int x = rand() % this->_width;
    int y = rand() % this->_height;

    if (this->_map[y * this->_width + x] == MazeCell::empty) {
      this->_map[y * this->_width + x] = MazeCell::enemy;
      return {x * 32.f, y * 32.f};
    }
  }
}

Roguelike::Maze::MazeCell &Roguelike::Maze::At(int x, int y) {
  return this->_map[y * this->_width + x];
}
