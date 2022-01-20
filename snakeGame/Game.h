#pragma once

#include "gameRun/GameRun.h"
#include "gameUtilities/GameTime.h"
#include "gameUtilities/GameResources.h"
class Game
{
	private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	GameRun* game;
	GameTime timer;
	GameResources resources;
	void initWindow();
	void initVariables();
	void initGame();
	void pollEvents();
	public:
	Game();
	virtual~Game();
	const bool isRunning() const;
	void update();
	void render();
	const static float getSpriteScale();
	

};