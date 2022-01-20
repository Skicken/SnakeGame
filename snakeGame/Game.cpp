#include "sgpch.h"
#include "Game.h"
Game::Game()
{
	resources.initResources();
	initVariables();
	initWindow();

}

Game::~Game()
{
	delete this->window;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(810,840);
	this->window = new sf::RenderWindow(this->videoMode, "Snake game", sf::Style::Titlebar | sf::Style::Close );
	initGame();
	this->window->setFramerateLimit(30);
}

void Game::initVariables()
{
	this->window = nullptr;
	this->game = nullptr;

}
void Game::initGame()
{
	if (this->game != nullptr) delete this->game;
	uint8_t tileNumber = (this->videoMode.height - 40) / GameResources::tilePixelSize;
	this->game = new GameRun(tileNumber);

}
void Game::pollEvents()
{
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}

	}
}

void Game::update()
{
	this->pollEvents();
	timer.updateTime();
	//std::cout << GameTime::deltaTime << std::endl;
	this->game->update();
	if (this->game->gameHasEnded())
	{
		initGame();
	}
}

void Game::render()
{
	sf::RectangleShape scoreLine;
	scoreLine.setSize(sf::Vector2f(2,600));
	scoreLine.setPosition(sf::Vector2f(600, 0));
	this->window->clear();
	this->game->render(this->window);
	//this->window->draw(scoreLine);
	this->window->display();
}
const float Game::getSpriteScale()
{
	return 1.f;
}

