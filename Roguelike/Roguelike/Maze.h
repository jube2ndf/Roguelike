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
			room,
			door,
		};
		Maze();
		Maze(int width, int height);
		std::vector<sf::Vector2f> CreateMaze(int roomcount, int rheight, int rwidth);
		sf::Vector2f FindFreeCellPlayer();
		sf::Vector2f FindFreeCellEnemy();
        sf::Vector2f FindFreeCellDoor();

		MazeCell& At(int x, int y);

		std::vector<std::pair<sf::Vector2f, int>> GetPositionEnemys();
        void SetPositionEnemys(std::vector<std::pair<sf::Vector2f, int>> enemy);
        sf::Vector2f GetPositionDoor();

	private:
		bool deadend(int x, int y);
		int _width;
		int _height;
		std::vector<MazeCell> _map;
        std::vector<std::pair<sf::Vector2f, int>> enemy;
        sf::Vector2f positionDoor;
	};
} // namespace Roguelike