#include "sgpch.h"
#include "GameResources.h"


sf::Texture GameResources::headTexture;
sf::Texture GameResources::segmentTexture;
sf::Texture GameResources::cornerTexture;
sf::Texture GameResources::tailTexture;
sf::Font GameResources::gameFont;
sf::Texture GameResources::appleTexture;
sf::RectangleShape GameResources::backgroundMapSquare;
float GameResources::tilePixelSize;
const float GameResources::bitmapPixelSize = 20.f;
sf::RectangleShape GameResources::deathParticle;
std::mt19937 GameResources::generator;

void GameResources::initResources()
{
	tilePixelSize = 40.f;
	headTexture.loadFromFile("Sprites/snakeHead.png");
	segmentTexture.loadFromFile("Sprites/snakeSegment.png");
	tailTexture.loadFromFile("Sprites/snakeTail.png");
	cornerTexture.loadFromFile("Sprites/snakeCorner.png");
	appleTexture.loadFromFile("Sprites/apple.png");
	gameFont.loadFromFile("ka1.ttf");
	std::random_device rd;
	generator.seed(rd());
	setSquareStyle();
	setDeathParticleStyle();
}
float GameResources::getScale()
{
	return tilePixelSize/bitmapPixelSize;
}
GameResources::GameResources()
{
}

GameResources::~GameResources()
{
}

void GameResources::setDeathParticleStyle()
{
	deathParticle.setSize(sf::Vector2f(tilePixelSize/4, tilePixelSize/4));
	deathParticle.setFillColor(sf::Color::Red);
}

void GameResources::setSquareStyle()
{
	backgroundMapSquare.setSize(sf::Vector2f(tilePixelSize, tilePixelSize));
	backgroundMapSquare.setOutlineThickness(1);
	backgroundMapSquare.setOutlineColor(sf::Color::Black);
}
