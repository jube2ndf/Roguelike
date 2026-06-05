#include "pch.h"
#include <stdexcept>
#include "TextureManager.h"
#include "Logger.h"

namespace GameEngine
{
	sf::Texture& TextureManager::load(const std::string& path)
	{
		auto iter = TextureManager::_textures.find(path);
		if (iter != TextureManager::_textures.end())
		{
			LOG_INFO("TextureManager", "Loaded from memory: " + path);
			return *(iter->second.get());
		}
		auto texture =
			std::make_unique<sf::Texture>();

		if (!texture->loadFromFile(path))
		{
			LOG_ERROR("TextureManager", "Error opening file for Texture: " + path);
			throw std::runtime_error("Texture load failed");
		}

		auto& ref = *texture;

		TextureManager::_textures[path] = std::move(texture);
		LOG_INFO("TextureManager", "Loaded from file" + path);
		return ref;
	}
}