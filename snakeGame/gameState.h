#pragma once
class gameState
{
	public:
	virtual void update() = 0;
	virtual void render(sf::RenderWindow *window) = 0;
};

