#include "sgpch.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(uint8_t numberOfParticles, sf::Vector2f positionCenter, float maxLifeTime)
{
	for (int i = 0; i < numberOfParticles; i++)
	{

		sf::Vector2f velocity = sf::Vector2f(GameResources::getRandomInt(-500, 500), GameResources::getRandomInt(-500,500));
		Particle* part = new Particle{ velocity,GameResources::deathParticle };
		part->sprite.setPosition(positionCenter);
		Particles.push_back(part);
	}
	this->maxLifeTime = maxLifeTime;
}

void ParticleSystem::update()
{

	float delt = GameTime::deltaTime;
	for (auto &particle : Particles)
	{
		sf::Vector2f moveVector = particle->velocity * delt;
		moveVector.y += (particleGravity * delt * delt) / 2;
		particle->sprite.move(moveVector);
	}
	this->maxLifeTime -= delt;
	if (this->maxLifeTime <= 0)
	{
		this->~ParticleSystem();
		this->toDestroy = true;
	}

}

void ParticleSystem::render(sf::RenderWindow *window)
{
	for (auto& particle : Particles)
	{
		window->draw(particle->sprite);
	}
}

ParticleSystem::~ParticleSystem()
{
	for (auto particle : Particles)
	{
		delete particle;
	}
	Particles.clear();
}
