#include "pch.h"
#include "AudioManager.h"
#include "Logger.h"


std::unique_ptr<sf::Music>
GameEngine::AudioManager::_music;

void GameEngine::AudioManager::Initialize()
{
	_music = std::make_unique<sf::Music>();
    LOG_INFO("AudioManager", "Initialized");
}

void GameEngine::AudioManager::Shutdown()
{
	_music.reset();
    LOG_INFO("AudioManager", "Shutdown");
}

bool GameEngine::AudioManager::PlayMusic(const std::string& path, bool loop, float volume)
{
    if (!_music) {
        LOG_WARN("AudioManager", "Attempting to play an audio file without initializing std::unique_ptr<sf::Music>");
        return false;
    }

    if (!_music->openFromFile(path))
    {
        LOG_WARN("AudioManager", "Error opening file for audio playback: " + path);
        return false;
    }
    _music->setLooping(loop);
    _music->setVolume(volume);
    _music->play();

    return true;
}
