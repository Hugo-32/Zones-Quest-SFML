#include "Audio.h"
#include <cstdlib>
#include <stdexcept>

Audio::Audio()
{
    loadBuffer(bufferCoin1, "Audio/geo_small_collect_1.wav");
    loadBuffer(bufferCoin2, "Audio/geo_small_collect_2.wav");
    loadBuffer(bufferHeroDamageLessHarsh, "Audio/hero_damage_less_harsh.wav");
    loadBuffer(bufferHeroDamage, "Audio/hero_damage.wav");
    loadBuffer(bufferHeroDeath, "Audio/hero_death_v2.wav");
    loadBuffer(bufferEnemyDamage, "Audio/enemy_damage.wav");
    loadBuffer(bufferLastEnemyDeath, "Audio/enemy_death_sword.wav");
    loadBuffer(bufferVictory, "Audio/victory.wav");

    soundHeroDamage.setBuffer(bufferHeroDamage);
    soundHeroDeath.setBuffer(bufferHeroDeath);
    soundEnemyDamage.setBuffer(bufferEnemyDamage);
    soundLastEnemyDeath.setBuffer(bufferLastEnemyDeath);
    soundVictory.setBuffer(bufferVictory);

    if (!backgroundMusic.openFromFile("Audio/bg_music.mp3")) {
        throw std::runtime_error("Failed to load background music");
    }
}

void Audio::playBackgroundMusic()
{
    backgroundMusic.setVolume(10);
    backgroundMusic.play();
}

void Audio::stopBackgroundMusic()
{
    backgroundMusic.stop();
}

void Audio::loadBuffer(sf::SoundBuffer& buffer, const std::string& filename)
{
    if (!buffer.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load " + filename);
    }
}

void Audio::playCoinSound()
{
    int randomSound = std::rand() % 2;
    soundCoin.setBuffer(randomSound == 0 ? bufferCoin1 : bufferCoin2);
    soundCoin.play();
}

void Audio::playDamageSound(bool fatal)
{
    if (fatal) {
        soundHeroDamage.setBuffer(bufferHeroDamage);
        soundHeroDeath.play();
        soundHeroDamage.play();
    }
    else {
        soundHeroDamage.setBuffer(bufferHeroDamageLessHarsh);
        soundHeroDamage.play();
    }
}

void Audio::playEnemyDamageSound()
{
    soundEnemyDamage.play();
}

void Audio::playLastEnemyDeathSound()
{
    soundLastEnemyDeath.play();
}

void Audio::playVictorySound()
{
    soundVictory.play();
}