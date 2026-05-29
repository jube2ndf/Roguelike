#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace GameEngine
{
    class AudioManager
    {
    public:
        static sf::SoundBuffer& LoadSound(const std::string& path)
        {
            auto it = _buffers.find(path);
            if (it != _buffers.end())
                return *it->second;

            auto buffer = std::make_unique<sf::SoundBuffer>();
            buffer->loadFromFile(path);

            auto& ref = *buffer;
            _buffers[path] = std::move(buffer);

            return ref;
        }

        static sf::Sound& PlaySound(const std::string& path)
        {
            auto sound = std::make_unique<sf::Sound>();
            sound->setBuffer(LoadSound(path));
            sound->play();

            auto& ref = *sound;
            _sounds.push_back(std::move(sound));

            return ref;
        }

    private:
        inline static std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> _buffers;
        inline static std::vector<std::unique_ptr<sf::Sound>> _sounds;
    };
}