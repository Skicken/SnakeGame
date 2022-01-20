#pragma once
#include "GameResources.h"
#include "GameTime.h"
class ParticleSystem
{   
    float maxLifeTime;
    const float particleGravity = 100.f;
    struct Particle
    {
        sf::Vector2f velocity;
        sf::RectangleShape sprite;
    };
    std::vector<Particle*> Particles;
    public:
    ParticleSystem(uint8_t numberOfParticles,sf::Vector2f positionCenter,float maxLifeTime);
    void update();
    void render(sf::RenderWindow* window);
    virtual ~ParticleSystem();
    bool toDestroy = false;

};

