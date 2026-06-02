#include "pch.h"
#include <stdexcept>
#include "TextureManager.h"

namespace GameEngine
{
	sf::Texture& TextureManager::load(const std::string& path)
	{
		auto iter = TextureManager::_textures.find(path);
		if (iter != TextureManager::_textures.end())
			return *(iter->second.get());
		auto texture =
			std::make_unique<sf::Texture>();

		if (!texture->loadFromFile(path))
		{
			std::cout << "FAILED TO LOAD: " << path << std::endl;
			std::cout << "ABS PATH: " << std::filesystem::absolute(path) << std::endl;
			throw std::runtime_error("Texture load failed");
		}

		auto& ref = *texture;

		TextureManager::_textures[path] = std::move(texture);

		return ref;
	}
}