#pragma once

class GameTime
{

	static sf::Clock timer;
	public:
	static float deltaTime;
	static void updateTime()
	{
		deltaTime = timer.restart().asSeconds();
	}

};
