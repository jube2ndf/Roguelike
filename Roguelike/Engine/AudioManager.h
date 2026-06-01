#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

namespace GameEngine
{
    class AudioManager final
    {
    public:

        // =========================
        // Sound Effects
        // =========================

        static sf::SoundBuffer& LoadSound(const std::string& path)
        {
            auto it = _buffers.find(path);

            if (it != _buffers.end())
                return *it->second;

            auto buffer =
                std::make_unique<sf::SoundBuffer>();

            if (!buffer->loadFromFile(path))
                throw std::runtime_error(
                    "Failed to load sound: " + path);

            auto& ref = *buffer;

            _buffers[path] = std::move(buffer);

            return ref;
        }

        static sf::Sound& PlaySound(
            const std::string& path,
            bool loop = false,
            float volume = 100.f)
        {
            auto sound =
                std::make_unique<sf::Sound>();

            sound->setBuffer(
                LoadSound(path));

            sound->setLooping(loop);
            sound->setVolume(volume);

            sound->play();

            auto& ref = *sound;

            _sounds.push_back(
                std::move(sound));

            return ref;
        }

        static void StopAllSounds()
        {
            for (auto& sound : _sounds)
            {
                sound->stop();
            }
        }

        static void PauseAllSounds()
        {
            for (auto& sound : _sounds)
            {
                sound->pause();
            }
        }

        static void ResumeAllSounds()
        {
            for (auto& sound : _sounds)
            {
                if (sound->getStatus() ==
                    sf::SoundSource::Status::Paused)
                {
                    sound->play();
                }
            }
        }

        static void SetSoundsVolume(float volume)
        {
            for (auto& sound : _sounds)
            {
                sound->setVolume(volume);
            }
        }

        // =========================
        // Music
        // =========================

        static bool PlayMusic(
            const std::string& path,
            bool loop = true,
            float volume = 100.f)
        {
            if (!_music.openFromFile(path))
                return false;

            _music.setLooping(loop);
            _music.setVolume(volume);

            _music.play();

            return true;
        }

        static void StopMusic()
        {
            _music.stop();
        }

        static void PauseMusic()
        {
            _music.pause();
        }

        static void ResumeMusic()
        {
            if (_music.getStatus() ==
                sf::SoundSource::Status::Paused)
            {
                _music.play();
            }
        }

        static void SetMusicVolume(float volume)
        {
            _music.setVolume(volume);
        }

        static bool IsMusicPlaying()
        {
            return
                _music.getStatus() ==
                sf::SoundSource::Status::Playing;
        }

        // =========================
        // Update
        // =========================

        static void Update()
        {
            _sounds.erase(
                std::remove_if(
                    _sounds.begin(),
                    _sounds.end(),
                    [](const auto& sound)
                    {
                        return
                            sound->getStatus() ==
                            sf::SoundSource::Status::Stopped;
                    }),
                _sounds.end());
        }

        static void Shutdown()
        {
            StopMusic();
            StopAllSounds();

            _sounds.clear();
            _buffers.clear();
        }

    private:

        inline static std::unordered_map<
            std::string,
            std::unique_ptr<sf::SoundBuffer>>
            _buffers;

        inline static std::vector<
            std::unique_ptr<sf::Sound>>
            _sounds;

        inline static sf::Music _music;
    };
}