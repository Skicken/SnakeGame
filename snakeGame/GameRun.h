#pragma once
#include "gameState.h"
#include "Player.h"
#include "GameTime.h"
#include "ParticleSystem.h"
#include "tickClock.h"
class GameRun : public gameState
{   

    private:
    const sf::Vector2i unocuppiedConstant = sf::Vector2i(-1, -1);
    enum GameState{PLAYING,DIED,WAITINGFOR_END,END};
    enum TileState {EMPTY,APPLE,SNAKE};
    const sf::Vector2f mapRenderPosition = sf::Vector2f(5.f, 40.f);
    bool inputBlocked = false;
    float currentTick;
    std::vector<std::vector<sf::RectangleShape*>> backgroundMap;
    std::vector<std::vector<TileState>> tileState;
    GameState gameState;


    tickClock* mainTickClock;
    tickClock* deathTickClock;
    float maxTick;
    const float startMaxTick = 0.1f;
    const float deathAnimationTime = 3.f;
    std::vector<ParticleSystem*> segmentsDeathParticles;
    float DelayAfterForNewGame = 0.f;
    
    Player *player;
    uint8_t tiles;
    uint16_t score;

    int ticksForSpeed;
    int ticksForApple;

    sf::Vector2i applePosition;
    sf::Sprite appleSprite;

    void DeathGameLoop();
    void PlayGameLoop();
    void UpdateTileState();
    void setBackground();
    void spawnApple();
    sf::Vector2i getUnocuppiedPosition();
    void eatAppleIfCan();
    void playerInput();
    const bool hasDied();
    void setNextAppleTicks();
    void setNextTimeSpeedUpTicks();
    const int getSpeedPercentage();
    public:
    GameRun(uint8_t tiles);
    virtual ~GameRun();
    void update();
    void  render(sf::RenderWindow* window);
    bool gameHasEnded();

    

};

