#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Audio
{
public:
    Audio();
    void playCoinSound();
    void playDamageSound(bool fatal);
    void playEnemyDamageSound();
    void playLastEnemyDeathSound();
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void playVictorySound();

private:
    sf::SoundBuffer bufferCoin1, bufferCoin2;
    sf::SoundBuffer bufferHeroDamageLessHarsh, bufferHeroDamage, bufferHeroDeath;
    sf::SoundBuffer bufferEnemyDamage;
    sf::SoundBuffer bufferLastEnemyDeath;
    sf::SoundBuffer bufferVictory;
    sf::Sound soundCoin, soundHeroDamage, soundHeroDeath, soundEnemyDamage;
    sf::Sound soundLastEnemyDeath;
    sf::Sound soundVictory;
    sf::Music backgroundMusic;
    void loadBuffer(sf::SoundBuffer& buffer, const std::string& filename);
};