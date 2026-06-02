#include "pch.h"
#include "AudioManager.h"


std::unique_ptr<sf::Music>
GameEngine::AudioManager::_music;

void GameEngine::AudioManager::Initialize()
{
	_music = std::make_unique<sf::Music>();
}

void GameEngine::AudioManager::Shutdown()
{
	_music.reset();
}

bool GameEngine::AudioManager::PlayMusic(const std::string& path, bool loop, float volume)
{
    if (!_music)
        return false;

    if (!_music->openFromFile(path))
        return false;

    _music->setLooping(loop);
    _music->setVolume(volume);
    _music->play();

    return true;
}
