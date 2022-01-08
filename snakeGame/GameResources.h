#pragma once
class GameResources
{
	public:
	static	sf::Texture headTexture;
	static	sf::Texture segmentTexture;
	static	sf::Texture cornerTexture;
	static	sf::Texture tailTexture;
	static  sf::Texture appleTexture;
	static  sf::RectangleShape backgroundMapSquare;
	static  sf::RectangleShape deathParticle;
	static	float tilePixelSize;
	static  sf::Font gameFont;
	static void initResources();
	static float getScale();
	static std::mt19937 generator;
	static int getRandomInt(int min, int max)
	{
		std::uniform_int_distribution< int > distr(min, max);
		return distr(generator);
	}
	GameResources();
	virtual ~GameResources();
	private:
	static void setDeathParticleStyle();
	static void setSquareStyle();
	static const float bitmapPixelSize;

	

};

