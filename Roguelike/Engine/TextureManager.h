#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <string>
namespace GameEngine {
	class TextureManager final{
	public:
		static sf::Texture& load(const std::string& path);
	private:
		inline static 
		std::unordered_map<
			std::string, 
			std::unique_ptr<sf::Texture>
		> 
		_textures;
	};
}