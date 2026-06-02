#pragma once
#include "EngineAPI.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

namespace GameEngine
{
    class ENGINE_API AudioManager
    {
    public:
        static void Initialize();
        static void Shutdown();

        static bool PlayMusic(
            const std::string& path,
            bool loop = true,
            float volume = 100.f);

    private:
        static std::unique_ptr<sf::Music> _music;
    };
}