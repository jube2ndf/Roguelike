#include "Maze.h"
#include "Wall.h"

Roguelike::Maze::Maze() : Maze(20, 20) {}

Roguelike::Maze::Maze(int width, int height) {
  this->_height = height;
  this->_width = width;
  this->_map.assign(this->_height * this->_width, MazeCell::wall);
}

struct Room {
  int x;
  int y;
  int w;
  int h;

  int CenterX() const { return x + w / 2; }
  int CenterY() const { return y + h / 2; }
};
bool Intersects(const Room &a, const Room &b) {
  return a.x - 2 < b.x + b.w && a.x + a.w + 2 > b.x && a.y - 2 < b.y + b.h &&
         a.y + a.h + 2 > b.y;
}
std::vector<sf::Vector2f> Roguelike::Maze::CreateMaze(int roomcount,
                                                      int rheight, int rwidth) {
  std::vector<Room> rooms;
  int createdRooms = 0;
  int attempts = 0;
  int maxAttempts = roomcount * 20;

  while (createdRooms < roomcount && attempts < maxAttempts) {
    attempts++;

    Room room;

    room.w = rwidth;
    room.h = rheight;

    room.x = 1 + rand() % (_width - room.w - 2);
    room.y = 1 + rand() % (_height - room.h - 2);

    bool overlaps = false;

    for (auto &other : rooms) {
      if (Intersects(room, other)) {
        overlaps = true;
        break;
      }
    }

    if (overlaps)
      continue;

    rooms.push_back(room);
    createdRooms++;

    for (int y = room.y; y < room.y + room.h; y++) {
      for (int x = room.x; x < room.x + room.w; x++) {
        At(x, y) = MazeCell::room;
      }
    }
  }

  for (size_t i = 1; i < rooms.size(); i++) {
    Room &a = rooms[i - 1];
    Room &b = rooms[i];

    int x1 = a.CenterX();
    int y1 = a.CenterY();

    int x2 = b.CenterX();
    int y2 = b.CenterY();
    int minX = std::min(x1, x2);
    int maxX = std::max(x1, x2);

    for (int x = minX; x <= maxX; x++)
      At(x, y1) = MazeCell::empty;
    int minY = std::min(y1, y2);
    int maxY = std::max(y1, y2);

    for (int y = minY; y <= maxY; y++)
      At(x2, y) = MazeCell::empty;
  }

  for (int x = 0; x < _width; x++) {
    At(x, 0) = MazeCell::wall;
    At(x, _height - 1) = MazeCell::wall;
  }

  for (int y = 0; y < _height; y++) {
    At(0, y) = MazeCell::wall;
    At(_width - 1, y) = MazeCell::wall;
  }

  std::vector<sf::Vector2f> walls;
  for (int y = 0; y < this->_height; y++) {
    for (int x = 0; x < this->_width; x++) {
      if (this->_map[y * this->_width + x] == MazeCell::wall) {
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

    if (this->_map[y * this->_width + x] == MazeCell::room) {
      this->_map[y * this->_width + x] = MazeCell::player;
      return {x * 32.f, y * 32.f};
    }
  }
}

sf::Vector2f Roguelike::Maze::FindFreeCellEnemy() {
  for (int i = 0; i < this->_height * this->_width; i++) {
    int x = rand() % this->_width;
    int y = rand() % this->_height;

    if (this->_map[y * this->_width + x] == MazeCell::room) {
      this->_map[y * this->_width + x] = MazeCell::enemy;
      return {x * 32.f, y * 32.f};
    }
  }
}

Roguelike::Maze::MazeCell &Roguelike::Maze::At(int x, int y) {
  return this->_map[y * this->_width + x];
}

bool Roguelike::Maze::deadend(int x, int y) {
  int a = 0;

  if (x != 1) {
    if (this->_map[y * this->_width + x - 2] == MazeCell::empty)
      a += 1;
  } else
    a += 1;

  if (x != 1) {
    if (this->_map[y * this->_width + x - 2] == MazeCell::empty)
      a += 1;
  } else
    a += 1;

  if (y != 1) {
    if (this->_map[(y - 2) * this->_width + x] == MazeCell::empty)
      a += 1;
  } else
    a += 1;

  if (x != this->_width - 2) {
    if (this->_map[y * this->_width + (x + 2)] == MazeCell::empty)
      a += 1;
  } else
    a += 1;

  if (y != this->_height - 2) {
    if (this->_map[(y + 2) * this->_width + x] == MazeCell::empty)
      a += 1;
  } else
    a += 1;

  if (a == 4)
    return 1;
  else
    return 0;
}
