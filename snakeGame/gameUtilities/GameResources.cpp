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
uint32_t GameResources::highScore;
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
	loadHighScore();
	setSquareStyle();
	setDeathParticleStyle();
}
float GameResources::getScale()
{
	return tilePixelSize/bitmapPixelSize;
}
const void GameResources::saveHighScore(uint32_t score)
{
	std::fstream highScoreFile;
	highScoreFile.open("data.bin", std::ios::binary | std::ios::out);
	highScoreFile.write(reinterpret_cast<const char*>(&score),sizeof(score));
	highScoreFile.close();
	highScore = score;
	return void();
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

void GameResources::loadHighScore()
{	
	std::fstream highScoreFile;
	highScoreFile.open("data.bin", std::ios::in | std::ios::binary);
	if (highScoreFile.good())
	{
		highScoreFile.read(reinterpret_cast<char*>(&highScore),sizeof(highScore));
	}
	else highScore = 0;
	highScoreFile.close();
}
