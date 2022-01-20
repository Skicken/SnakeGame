#pragma once
#include "gameUtilities/GameResources.h"
#include "gameUtilities/GameTime.h"
enum direction{ RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};
struct Segment
{
	sf::Sprite sprite;
	direction spriteDirection;
	sf::Vector2i position;
};
class Player
{

	//texture ...
	public:
		
		const bool hasCollidedWithSelf();
		Player(sf::Vector2i startingPos,uint8_t *tileSize,uint8_t segments=4);
		void setFacing(direction dir);
		direction getFacing();
		sf::Vector2i getHeadPosition();
		sf::Vector2i getTailPosition();
		std::vector<Segment>& getSegments();
		void Move();
		void setOrigin();
		float getCornerRotation(direction from, direction to);
		const float getSpriteOffsetWidth();
		const float getSpriteOffsetHeight();
		void popHeadSegment();
		sf::Vector2f getRenderedSegmentPosition(Segment &segment);
		void addSegment();
		const sf::Vector2i getOldTailPosition() { return oldTailPosition; }
		void passBorderPosition(sf::Vector2i &position);
	private:
		std::vector<Segment> snake;
		direction facing;
		sf::Vector2i oldTailPosition;
		uint8_t *tiles;

};